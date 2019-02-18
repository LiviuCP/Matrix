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
    void testCapacityWithConstructors();
    void testCopyConstructor();
    void testCapacityWithCopyConstructor();
    void testMoveConstructor();
    void testCapacityWithMoveConstructor();
    void testFunctionAt();
    void testSquareBracketsOperator();
    void testCopyAssignmentOperator();
    void testCapacityWithCopyAssignmentOperator();
    void testMoveAssignmentOperator();
    void testCapacityWithMoveAssignmentOperator();
    void testGetBaseArrayPtr();
    void testTranspose();
    void testCapacityWithTranspose();
    void testClear();
    void testResizeWithoutFillingInNewValues();
    void testCapacityWithResizeWithoutFillingInNewValues();
    void testResizeAndFillInNewValues();
    void testCapacityWithResizeAndFillInNewValues();
    void testShrinkToFit();
    void testInsertRowNoSetValue();
    void testInsertRowSetValue();
    void testCapacityWithInsertRow();
    void testInsertColumnNoSetValue();
    void testInsertColumnSetValue();
    void testCapacityWithInsertColumn();
    void testEraseRow();
    void testCapacityWithEraseRow();
    void testEraseColumn();
    void testCapacityWithEraseColumn();
    void testCatByRow();
    void testCapacityWithCatByRow();
    void testCatByColumn();
    void testCapacityWithCatByColumn();
    void testSplitByRow();
    void testCapacityWithSplitByRow();
    void testSplitByColumn();
    void testCapacityWithSplitByColumn();
    void testSwapMatrixes();
    void testSwapItems();
    void testSwapRows();
    void testSwapColumns();
    void testSwapRowColumn();
    void testSetAllItemsToValue();
    void testCopy();
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

    QVERIFY2(matrix.getRowCapacity() == 0 && matrix.getColumnCapacity() == 0, "Default constructor initialized matrix with wrong capacity");
}

void CommonTests::testInitListConstructor()
{
    IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6} };

    if (matrix.getRowCapacity() != 2 || matrix.getColumnCapacity() != 3)
    {
        QFAIL("Init list constructor initialized matrix with wrong capacity");
    }

    if (matrix.getNrOfRows() != 2 || matrix.getNrOfColumns() != 3)
    {
        QFAIL("Init list constructor initialized matrix with wrong number of rows and columns");
    }

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

    if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 2)
    {
        QFAIL("Identical matrix constructor initialized matrix with wrong capacity");
    }

    if (matrix.getNrOfRows() != 3 || matrix.getNrOfColumns() != 2)
    {
        QFAIL("Identical matrix constructor initialized matrix with wrong number of rows and columns");
    }

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

    if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 3)
    {
        QFAIL("Diagonal matrix constructor initialized matrix with wrong capacity");
    }

    if (matrix.getNrOfRows() != 3 || matrix.getNrOfColumns() != 3)
    {
        QFAIL("Diagonal matrix constructor initialized matrix with wrong number of rows and columns");
    }

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

void CommonTests::testCapacityWithConstructors()
{
    {
        IntMatrix matrix{3, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

        QVERIFY2(matrix.getRowCapacity() == 3 && matrix.getColumnCapacity() == 5, "Init list constructor initialized matrix with wrong capacity");
    }

    {
        IntMatrix matrix{4, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

        QVERIFY2(matrix.getRowCapacity() == 5 && matrix.getColumnCapacity() == 3, "Init list constructor initialized matrix with wrong capacity");
    }

    {
        IntMatrix matrix{
                            8, 10, {
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                                  }
                        };

        QVERIFY2(matrix.getRowCapacity() == 10 && matrix.getColumnCapacity() == 12, "Init list constructor initialized matrix with wrong capacity");
    }

    {
        IntMatrix matrix{
                            10, 8, {
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0
                                    }
                        };

        QVERIFY2(matrix.getRowCapacity() == 12 && matrix.getColumnCapacity() == 10, "Init list constructor initialized matrix with wrong capacity");
    }

    {
        IntMatrix matrix{3, 4, -5};

        QVERIFY2(matrix.getRowCapacity() == 3 && matrix.getColumnCapacity() == 5, "Identical matrix constructor initialized matrix with wrong capacity");
    }

    {
        IntMatrix matrix{4, 3, -5};

        QVERIFY2(matrix.getRowCapacity() == 5 && matrix.getColumnCapacity() == 3, "Identical matrix constructor initialized matrix with wrong capacity");
    }

    {
        IntMatrix matrix{25, 20, -2};

        QVERIFY2(matrix.getRowCapacity() == 31 && matrix.getColumnCapacity() == 25, "Identical matrix constructor initialized matrix with wrong capacity");
    }

    {
        IntMatrix matrix{20, 25, -2};

        QVERIFY2(matrix.getRowCapacity() == 25 && matrix.getColumnCapacity() == 31, "Identical matrix constructor initialized matrix with wrong capacity");
    }

    {
        IntMatrix matrix{3, std::pair<int, int>{-2,-3}};

        QVERIFY2(matrix.getRowCapacity() == 3 && matrix.getColumnCapacity() == 3, "Diag matrix constructor initialized matrix with wrong capacity");
    }

    {
        IntMatrix matrix{4, std::pair<int, int>{-2,-3}};

        QVERIFY2(matrix.getRowCapacity() == 5 && matrix.getColumnCapacity() == 5, "Diag matrix constructor initialized matrix with wrong capacity");
    }

    {
        IntMatrix matrix{8, std::pair<int, int>{-2,-3}};

        QVERIFY2(matrix.getRowCapacity() == 10 && matrix.getColumnCapacity() == 10, "Diag matrix constructor initialized matrix with wrong capacity");
    }

    {
        IntMatrix matrix{10, std::pair<int, int>{-2,-3}};

        QVERIFY2(matrix.getRowCapacity() == 12 && matrix.getColumnCapacity() == 12, "Diag matrix constructor initialized matrix with wrong capacity");
    }
}

void CommonTests::testCopyConstructor()
{
    {
        IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix matrixCopy{matrix};

        if (matrix.getRowCapacity() != 2 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Copy constructor initialized matrix with wrong capacity");
        }

        if (matrixCopy.getNrOfRows() != 2 || matrixCopy.getNrOfColumns() != 3)
        {
            QFAIL("Copy constructor initialized matrix with wrong number of rows and columns");
        }

        QVERIFY2(matrixCopy.at(0, 0) == 1 &&
                 matrixCopy.at(0, 1) == 2 &&
                 matrixCopy.at(0, 2) == 3 &&
                 matrixCopy.at(1, 0) == 4 &&
                 matrixCopy.at(1, 1) == 5 &&
                 matrixCopy.at(1, 2) == 6,

                 "Matrix elements have not been correctly initialized by the copy constructor");
    }

    {
        IntMatrix matrix{};
        IntMatrix matrixCopy{matrix};

        QVERIFY2(matrix.getRowCapacity() == 0 && matrix.getColumnCapacity() == 0, "Copy constructor initialized matrix with wrong capacity");
        QVERIFY2(matrix.getNrOfRows() == 0 && matrix.getNrOfColumns() == 0, "Copy constructor initialized matrix with wrong number of rows and columns");
    }
}

void CommonTests::testCapacityWithCopyConstructor()
{
    {
        IntMatrix matrix{3, 4, -1};
        IntMatrix matrixCopy{matrix};

        QVERIFY2(matrixCopy.getRowCapacity() == 3 && matrixCopy.getColumnCapacity() == 5, "Copy constructor failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix matrix{4, 3, -1};
        IntMatrix matrixCopy{matrix};

        QVERIFY2(matrixCopy.getRowCapacity() == 5 && matrixCopy.getColumnCapacity() == 3, "Copy constructor failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix matrix{7, 8, -1};
        IntMatrix matrixCopy{matrix};

        QVERIFY2(matrixCopy.getRowCapacity() == 8 && matrixCopy.getColumnCapacity() == 10, "Copy constructor failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix matrix{8, 7, -1};
        IntMatrix matrixCopy{matrix};

        QVERIFY2(matrixCopy.getRowCapacity() == 10 && matrixCopy.getColumnCapacity() == 8, "Copy constructor failed, capacity of the destination matrix is not correct!");
    }
}

void CommonTests::testMoveConstructor()
{
    IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6} };
    IntMatrix matrixMove{std::move(matrix)};

    if (matrixMove.getRowCapacity() != 2 || matrixMove.getColumnCapacity() != 3)
    {
        QFAIL("Move constructor initialized matrix with wrong capacity");
    }

    if (matrixMove.getNrOfRows() != 2 || matrixMove.getNrOfColumns() != 3)
    {
        QFAIL("Move constructor initialized matrix with wrong number of rows and columns");
    }

    QVERIFY2(matrixMove.at(0, 0) == 1 &&
             matrixMove.at(0, 1) == 2 &&
             matrixMove.at(0, 2) == 3 &&
             matrixMove.at(1, 0) == 4 &&
             matrixMove.at(1, 1) == 5 &&
             matrixMove.at(1, 2) == 6,

             "Matrix elements have not been correctly initialized by the move constructor");

    QVERIFY2(matrix.getRowCapacity() == 0 && matrix.getColumnCapacity() == 0, "Move constructor set the wrong number of rows and columns to the source matrix");

    QVERIFY2(matrix.getNrOfRows() == 0 && matrix.getNrOfColumns() == 0, "Move constructor set the wrong number of rows and columns to the source matrix");
}

void CommonTests::testCapacityWithMoveConstructor()
{
    {
        IntMatrix matrix{3, 4, -1};
        IntMatrix matrixMove{std::move(matrix)};

        QVERIFY2(matrixMove.getRowCapacity() == 3 && matrixMove.getColumnCapacity() == 5, "Move constructor failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix matrix{4, 3, -1};
        IntMatrix matrixMove{std::move(matrix)};

        QVERIFY2(matrixMove.getRowCapacity() == 5 && matrixMove.getColumnCapacity() == 3, "Move constructor failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix matrix{7, 8, -1};
        IntMatrix matrixMove{std::move(matrix)};

        QVERIFY2(matrixMove.getRowCapacity() == 8 && matrixMove.getColumnCapacity() == 10, "Move constructor failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix matrix{8, 7, -1};
        IntMatrix matrixMove{std::move(matrix)};

        QVERIFY2(matrixMove.getRowCapacity() == 10 && matrixMove.getColumnCapacity() == 8, "Move constructor failed, capacity of the destination matrix is not correct!");
    }
}

void CommonTests::testFunctionAt()
{
    {
        IntMatrix matrix{2, 3, 5};

        matrix.at(0, 0) = 10;
        matrix.at(0, 1) = 20;
        matrix.at(0, 2) = 30;
        matrix.at(1, 0) = 40;
        matrix.at(1, 1) = 50;
        matrix.at(1, 2) = 60;

        QVERIFY2(matrix[0] == 10 &&
                 matrix[1] == 20 &&
                 matrix[2] == 30 &&
                 matrix[3] == 40 &&
                 matrix[4] == 50 &&
                 matrix[5] == 60,

                 "The at() method does not work correctly, setup values are wrong!");
    }

    {
        IntMatrix matrix{2, 3, 5};

        matrix[0] = 70;
        matrix[1] = 80;
        matrix[2] = 90;
        matrix[3] = 100;
        matrix[4] = 110;
        matrix[5] = 120;

        QVERIFY2(matrix.at(0, 0) == 70 &&
                 matrix.at(0, 1) == 80 &&
                 matrix.at(0, 2) == 90 &&
                 matrix.at(1, 0) == 100 &&
                 matrix.at(1, 1) == 110 &&
                 matrix.at(1, 2) == 120,

                 "The at() method does not work correctly, read values are wrong!");
    }
}

void CommonTests::testSquareBracketsOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        QVERIFY2(matrix[0] == 1 &&
                 matrix[1] == 2 &&
                 matrix[2] == 3 &&
                 matrix[3] == 4 &&
                 matrix[4] == 5 &&
                 matrix[5] == 6 &&
                 matrix[6] == 7 &&
                 matrix[7] == 8 &&
                 matrix[8] == 9 &&
                 matrix[9] == 10 &&
                 matrix[10] == 11 &&
                 matrix[11] == 12,

                "The square brackets operator did not return the correct values!");
    }

    {
        IntMatrix matrix{4, 3, 2};

        matrix[0] = 10;
        matrix[1] = 20;
        matrix[2] = 30;
        matrix[3] = 40;
        matrix[4] = 50;
        matrix[5] = 60;
        matrix[6] = 70;
        matrix[7] = 80;
        matrix[8] = 90;
        matrix[9] = 100;
        matrix[10] = 110;
        matrix[11] = 120;

        int nrOfRows, nrOfColumns, rowCapacity, columnCapacity;
        int** matrixPtr{matrix.getBaseArrayPtr(nrOfRows, nrOfColumns, rowCapacity, columnCapacity)};

        QVERIFY2(matrixPtr[0][0] == 10 &&
                 matrixPtr[0][1] == 20 &&
                 matrixPtr[0][2] == 30 &&
                 matrixPtr[1][0] == 40 &&
                 matrixPtr[1][1] == 50 &&
                 matrixPtr[1][2] == 60 &&
                 matrixPtr[2][0] == 70 &&
                 matrixPtr[2][1] == 80 &&
                 matrixPtr[2][2] == 90 &&
                 matrixPtr[3][0] == 100 &&
                 matrixPtr[3][1] == 110 &&
                 matrixPtr[3][2] == 120,

                "The square brackets operator did not write the correct values!");
    }
}

void CommonTests::testCopyAssignmentOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix matrixCopy{3, 2, {7, 8, 9, 10, 11, 12}};

        matrixCopy = matrix;

        if (matrixCopy.getNrOfRows() != 2 || matrixCopy.getNrOfColumns() != 3)
        {
            QFAIL("Copy assignment failed, number of rows or columns of the destination matrix is not correct!");
        }

        if (matrixCopy.getRowCapacity() != 2 || matrixCopy.getColumnCapacity() != 3)
        {
            QFAIL("Copy assignment failed, capacity of the destination matrix is not correct!");
        }

        QVERIFY2(matrixCopy.at(0, 0) == 1 &&
                 matrixCopy.at(0, 1) == 2 &&
                 matrixCopy.at(0, 2) == 3 &&
                 matrixCopy.at(1, 0) == 4 &&
                 matrixCopy.at(1, 1) == 5 &&
                 matrixCopy.at(1, 2) == 6,

                 "Copy assignment failed, the destination matrix doesn't have the right values!");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix matrixCopy{};

        matrixCopy = matrix;

        if (matrixCopy.getNrOfRows() != 2 || matrixCopy.getNrOfColumns() != 3)
        {
            QFAIL("Copy assignment failed, number of rows or columns of the destination matrix is not correct!");
        }

        if (matrixCopy.getRowCapacity() != 2 || matrixCopy.getColumnCapacity() != 3)
        {
            QFAIL("Copy assignment failed, capacity of the destination matrix is not correct!");
        }

        QVERIFY2(matrixCopy.at(0, 0) == 1 &&
                 matrixCopy.at(0, 1) == 2 &&
                 matrixCopy.at(0, 2) == 3 &&
                 matrixCopy.at(1, 0) == 4 &&
                 matrixCopy.at(1, 1) == 5 &&
                 matrixCopy.at(1, 2) == 6,

                 "Copy assignment failed, the destination matrix doesn't have the right values!");
    }

    {
        IntMatrix matrix{};
        IntMatrix matrixCopy{3, 2, {7, 8, 9, 10, 11, 12}};

        matrixCopy = matrix;

        if (matrixCopy.getNrOfRows() != 0 || matrixCopy.getNrOfColumns() != 0)
        {
            QFAIL("Copy assignment failed, number of rows or columns of the destination matrix is not correct!");
        }

        if (matrixCopy.getRowCapacity() != 0 || matrixCopy.getColumnCapacity() != 0)
        {
            QFAIL("Copy assignment failed, capacity of the destination matrix is not correct!");
        }
    }

    {
        IntMatrix matrix{};
        IntMatrix matrixCopy{};

        matrixCopy = matrix;

        if (matrixCopy.getNrOfRows() != 0 || matrixCopy.getNrOfColumns() != 0)
        {
            QFAIL("Copy assignment failed, number of rows or columns of the destination matrix is not correct!");
        }

        if (matrixCopy.getRowCapacity() != 0 || matrixCopy.getColumnCapacity() != 0)
        {
            QFAIL("Copy assignment failed, capacity of the destination matrix is not correct!");
        }
    }

    {
        IntMatrix matrix{3, 4, 7};
        IntMatrix matrixCopy{2, 3, 8};

        matrixCopy = matrix;

        if (matrixCopy.getNrOfRows() != 3 || matrixCopy.getNrOfColumns() != 4)
        {
            QFAIL("Copy assignment failed, number of rows or columns of the destination matrix is not correct!");
        }

        if (matrixCopy.getRowCapacity() != 3 || matrixCopy.getColumnCapacity() != 5)
        {
            QFAIL("Copy assignment failed, capacity of the destination matrix is not correct!");
        }

        for (int row{0}; row < matrixCopy.getNrOfRows(); ++row)
        {
            for (int col{0}; col < matrixCopy.getNrOfColumns(); ++col)
            {
                if (matrixCopy.at(row, col) != 7)
                {
                    QFAIL("Copy assignment failed, the destination matrix doesn't have the right values!");
                    break;
                }
            }
        }
    }

    {
        IntMatrix matrix{4, 3, 9};
        IntMatrix matrixCopy{2, 3, 8};

        matrixCopy = matrix;

        if (matrixCopy.getNrOfRows() != 4 || matrixCopy.getNrOfColumns() != 3)
        {
            QFAIL("Copy assignment failed, number of rows or columns of the destination matrix is not correct!");
        }

        if (matrixCopy.getRowCapacity() != 5 || matrixCopy.getColumnCapacity() != 3)
        {
            QFAIL("Copy assignment failed, capacity of the destination matrix is not correct!");
        }

        for (int row{0}; row < matrixCopy.getNrOfRows(); ++row)
        {
            for (int col{0}; col < matrixCopy.getNrOfColumns(); ++col)
            {
                if (matrixCopy.at(row, col) != 9)
                {
                    QFAIL("Copy assignment failed, the destination matrix doesn't have the right values!");
                    break;
                }
            }
        }
    }

    {
        IntMatrix matrix{20, 20, 11};
        IntMatrix matrixCopy{2, 3, 8};

        matrixCopy = matrix;

        if (matrixCopy.getNrOfRows() != 20 || matrixCopy.getNrOfColumns() != 20)
        {
            QFAIL("Copy assignment failed, number of rows or columns of the destination matrix is not correct!");
        }

        if (matrixCopy.getRowCapacity() != 25 || matrixCopy.getColumnCapacity() != 25)
        {
            QFAIL("Copy assignment failed, capacity of the destination matrix is not correct!");
        }

        for (int row{0}; row < matrixCopy.getNrOfRows(); ++row)
        {
            for (int col{0}; col < matrixCopy.getNrOfColumns(); ++col)
            {
                if (matrixCopy.at(row, col) != 11)
                {
                    QFAIL("Copy assignment failed, the destination matrix doesn't have the right values!");
                    break;
                }
            }
        }
    }

    {
        IntMatrix matrix{22, 22, 12};
        IntMatrix matrixCopy{2, 3, 8};

        matrixCopy = matrix;

        if (matrixCopy.getNrOfRows() != 22 || matrixCopy.getNrOfColumns() != 22)
        {
            QFAIL("Copy assignment failed, number of rows or columns of the destination matrix is not correct!");
        }

        if (matrixCopy.getRowCapacity() != 27 || matrixCopy.getColumnCapacity() != 27)
        {
            QFAIL("Copy assignment failed, capacity of the destination matrix is not correct!");
        }

        for (int row{0}; row < matrixCopy.getNrOfRows(); ++row)
        {
            for (int col{0}; col < matrixCopy.getNrOfColumns(); ++col)
            {
                if (matrixCopy.at(row, col) != 12)
                {
                    QFAIL("Copy assignment failed, the destination matrix doesn't have the right values!");
                    break;
                }
            }
        }
    }

    {
        IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};

        matrix = matrix;

        if (matrix.getNrOfRows() != 2 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Same matrix copy assignment failed, number of rows or columns is not correct!");
        }

        if (matrix.getRowCapacity() != 2 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Same matrix copy assignment failed, capacity is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6,

                 "Same matrix copy assignment failed, the matrix doesn't have the right values!");
    }

    {
        IntMatrix matrix{};

        matrix = matrix;

        if (matrix.getNrOfRows() != 0 || matrix.getNrOfColumns() != 0)
        {
            QFAIL("Same matrix copy assignment failed, number of rows or columns is not correct!");
        }

        if (matrix.getRowCapacity() != 0 || matrix.getColumnCapacity() != 0)
        {
            QFAIL("Same matrix copy assignment failed, capacity is not correct!");
        }
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
        IntMatrix thirdMatrix{2, 2, {13, 14, 15, 16}};

        firstMatrix = secondMatrix = thirdMatrix;

        if (firstMatrix.getNrOfRows() != 2 || firstMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Copy assignment failed, number of rows or columns of the first matrix is not correct!");
        }

        if (firstMatrix.getRowCapacity() != 2 || firstMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Copy assignment failed, capacity of the first matrix is not correct!");
        }

        QVERIFY2(firstMatrix.at(0, 0) == 13 &&
                 firstMatrix.at(0, 1) == 14 &&
                 firstMatrix.at(1, 0) == 15 &&
                 firstMatrix.at(1, 1) == 16,

                 "Copy assignment failed, the first matrix doesn't have the right values!");
    }
}

void CommonTests::testCapacityWithCopyAssignmentOperator()
{
    using namespace std;
    auto copyAndTestCapacity = [](string testNumber, const IntMatrix& matrix, IntMatrix& matrixCopy, int desiredRowCapacity, int desiredColumnCapacity)
    {
        matrixCopy = matrix;

        QVERIFY2(matrixCopy.getRowCapacity() == desiredRowCapacity && matrixCopy.getColumnCapacity() == desiredColumnCapacity,
                 string{"Copy assignment failed, capacity of the destination matrix is not correct! Test number: " + testNumber}.c_str());
    };

    int testNumber{1};

    {
        IntMatrix matrixCopy{};
        copyAndTestCapacity(QString::number(testNumber++).toStdString(), IntMatrix{3, 4, -1}, matrixCopy, 3, 5);
    }

    {
        IntMatrix matrixCopy{};
        copyAndTestCapacity(QString::number(testNumber++).toStdString(), IntMatrix{4, 3, -1}, matrixCopy, 5, 3);
    }

    {
        IntMatrix matrixCopy{};
        copyAndTestCapacity(QString::number(testNumber++).toStdString(), IntMatrix{7, 8, -1}, matrixCopy, 8, 10);
    }

    {
        IntMatrix matrixCopy{};
        copyAndTestCapacity(QString::number(testNumber++).toStdString(), IntMatrix{8, 7, -1}, matrixCopy, 10, 8);
    }

    {
        IntMatrix matrixCopy{2, 3, -5};
        copyAndTestCapacity(QString::number(testNumber++).toStdString(), IntMatrix{3, 4, -1}, matrixCopy, 3, 5);
    }

    {
        IntMatrix matrixCopy{2, 3, -5};
        copyAndTestCapacity(QString::number(testNumber++).toStdString(), IntMatrix{4, 3, -1}, matrixCopy, 5, 3);
    }

    {
        IntMatrix matrixCopy{3, 4, -5};
        copyAndTestCapacity(QString::number(testNumber++).toStdString(), IntMatrix{7, 8, -1}, matrixCopy, 8, 10);
    }

    {
        IntMatrix matrixCopy{3, 4, -5};
        copyAndTestCapacity(QString::number(testNumber++).toStdString(), IntMatrix{8, 7, -1}, matrixCopy, 10, 8);
    }
}

void CommonTests::testMoveAssignmentOperator()
{
    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, 9, 10, 11, 12}};

        secondMatrix = std::move(firstMatrix);

        if (secondMatrix.getRowCapacity() != 2 || secondMatrix.getColumnCapacity() != 3)
        {
            QFAIL("Move assignment failed, capacity of the destination matrix is not correct!");
        }

        if (secondMatrix.getNrOfRows() != 2 || secondMatrix.getNrOfColumns() != 3)
        {
            QFAIL("Move assignment failed, number of rows or columns of the destination matrix is not correct!");
        }

        QVERIFY2(secondMatrix.at(0, 0) == 1 &&
                 secondMatrix.at(0, 1) == 2 &&
                 secondMatrix.at(0, 2) == 3 &&
                 secondMatrix.at(1, 0) == 4 &&
                 secondMatrix.at(1, 1) == 5 &&
                 secondMatrix.at(1, 2) == 6,

                 "Move assignment failed, the destination matrix doesn't have the right values!");

        QVERIFY2(firstMatrix.getRowCapacity() == 0 && firstMatrix.getColumnCapacity() == 0,
                 "Move assignment failed, capacity of the source matrix is not correct!");

        QVERIFY2(firstMatrix.getNrOfRows() == 0 && firstMatrix.getNrOfColumns() == 0,
                 "Move assignment failed, number of rows or columns of the source matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{};

        secondMatrix = std::move(firstMatrix);

        if (secondMatrix.getRowCapacity() != 2 || secondMatrix.getColumnCapacity() != 3)
        {
            QFAIL("Move assignment failed, capacity of the destination matrix is not correct!");
        }

        if (secondMatrix.getNrOfRows() != 2 || secondMatrix.getNrOfColumns() != 3)
        {
            QFAIL("Move assignment failed, number of rows or columns of the destination matrix is not correct!");
        }

        QVERIFY2(secondMatrix.at(0, 0) == 1 &&
                 secondMatrix.at(0, 1) == 2 &&
                 secondMatrix.at(0, 2) == 3 &&
                 secondMatrix.at(1, 0) == 4 &&
                 secondMatrix.at(1, 1) == 5 &&
                 secondMatrix.at(1, 2) == 6,

                 "Move assignment failed, the destination matrix doesn't have the right values!");

        QVERIFY2(firstMatrix.getRowCapacity() == 0 && firstMatrix.getColumnCapacity() == 0,
                 "Move assignment failed, capacity of the source matrix is not correct!");

        QVERIFY2(firstMatrix.getNrOfRows() == 0 && firstMatrix.getNrOfColumns() == 0,
                 "Move assignment failed, number of rows or columns of the source matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{3, 2, {7, 8, 9, 10, 11, 12}};

        secondMatrix = std::move(firstMatrix);

        QVERIFY2(secondMatrix.getRowCapacity() == 0 && secondMatrix.getColumnCapacity() == 0,
                 "Move assignment failed, capacity of the destination matrix is not correct!");

        QVERIFY2(secondMatrix.getNrOfRows() == 0 && secondMatrix.getNrOfColumns() == 0,
                 "Move assignment failed, number of rows or columns of the destination matrix is not correct!");

        QVERIFY2(firstMatrix.getRowCapacity() == 0 && firstMatrix.getColumnCapacity() == 0,
                 "Move assignment failed, capacity of the source matrix is not correct!");

        QVERIFY2(firstMatrix.getNrOfRows() == 0 && firstMatrix.getNrOfColumns() == 0,
                 "Move assignment failed, number of rows or columns of the source matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{};

        secondMatrix = std::move(firstMatrix);

        QVERIFY2(secondMatrix.getRowCapacity() == 0 && secondMatrix.getColumnCapacity() == 0,
                 "Move assignment failed, capacity of the destination matrix is not correct!");

        QVERIFY2(secondMatrix.getNrOfRows() == 0 && secondMatrix.getNrOfColumns() == 0,
                 "Move assignment failed, number of rows or columns of the destination matrix is not correct!");

        QVERIFY2(firstMatrix.getRowCapacity() == 0 && firstMatrix.getColumnCapacity() == 0,
                 "Move assignment failed, capacity of the source matrix is not correct!");

        QVERIFY2(firstMatrix.getNrOfRows() == 0 && firstMatrix.getNrOfColumns() == 0,
                 "Move assignment failed, number of rows or columns of the source matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
        IntMatrix thirdMatrix{2, 2, {13, 14, 15, 16}};

        firstMatrix = secondMatrix = std::move(thirdMatrix);

        if (firstMatrix.getRowCapacity() != 2 || firstMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Copy and/or move assignment failed, capacity of the first matrix is not correct!");
        }

        if (firstMatrix.getNrOfRows() != 2 || firstMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Copy and/or move assignment failed, number of rows or columns of the first matrix is not correct!");
        }

        QVERIFY2(firstMatrix.at(0, 0) == 13 &&
                 firstMatrix.at(0, 1) == 14 &&
                 firstMatrix.at(1, 0) == 15 &&
                 firstMatrix.at(1, 1) == 16,

                 "Copy and/or move assignment failed, the first matrix doesn't have the right values!");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
        IntMatrix thirdMatrix{2, 2, {13, 14, 15, 16}};

        firstMatrix = std::move(secondMatrix = thirdMatrix);

        if (firstMatrix.getRowCapacity() != 2 || firstMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Copy and/or move assignment failed, capacity of the first matrix is not correct!");
        }

        if (firstMatrix.getNrOfRows() != 2 || firstMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Copy and/or move assignment failed, number of rows or columns of the first matrix is not correct!");
        }

        QVERIFY2(firstMatrix.at(0, 0) == 13 &&
                 firstMatrix.at(0, 1) == 14 &&
                 firstMatrix.at(1, 0) == 15 &&
                 firstMatrix.at(1, 1) == 16,

                 "Copy and/or move assignment failed, the first matrix doesn't have the right values!");
    }
}

void CommonTests::testCapacityWithMoveAssignmentOperator()
{
    using namespace std;
    auto moveAndTestCapacity = [](string testNumber, IntMatrix& matrix, IntMatrix& matrixMove, int desiredRowCapacity, int desiredColumnCapacity)
    {
        matrixMove = move(matrix);

        QVERIFY2(matrixMove.getRowCapacity() == desiredRowCapacity && matrixMove.getColumnCapacity() == desiredColumnCapacity,
                 string{"Move assignment failed, capacity of the destination matrix is not correct! Test number: " + testNumber}.c_str());
    };

    int testNumber{1};

    {
        IntMatrix matrix{3, 4, -1};
        IntMatrix matrixMove{};

        moveAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixMove, 3, 5);
    }

    {
        IntMatrix matrix{4, 3, -1};
        IntMatrix matrixMove{};

        moveAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixMove, 5, 3);
    }

    {
        IntMatrix matrix{7, 8, -1};
        IntMatrix matrixMove{};

        moveAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixMove, 8, 10);
    }

    {
        IntMatrix matrix{8, 7, -1};
        IntMatrix matrixMove{};

        moveAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixMove, 10, 8);
    }

    {
        IntMatrix matrix{3, 4, -1};
        IntMatrix matrixMove{2, 3, -5};

        moveAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixMove, 3, 5);
    }

    {
        IntMatrix matrix{4, 3, -1};
        IntMatrix matrixMove{2, 3, -5};

        moveAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixMove, 5, 3);
    }

    {
        IntMatrix matrix{7, 8, -1};
        IntMatrix matrixMove{3, 4, -5};

        moveAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixMove, 8, 10);
    }

    {
        IntMatrix matrix{8, 7, -1};
        IntMatrix matrixMove{3, 4, -5};

        moveAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixMove, 10, 8);
    }
}

void CommonTests::testGetBaseArrayPtr()
{
    {
        IntMatrix matrix{};

        int nrOfRows, nrOfColumns, rowCapacity, columnCapacity;
        int** matrixPtr{matrix.getBaseArrayPtr(nrOfRows, nrOfColumns, rowCapacity, columnCapacity)};

        if (matrixPtr || nrOfRows != 0 || nrOfColumns != 0 || rowCapacity != 0 || columnCapacity != 0)
        {
            QFAIL("Passing resources outside the matrix failed, either the pointer is not null or the number of rows and columns of the empty matrix is different from 0!");
        }
    }

    {
        IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};

        int nrOfRows, nrOfColumns, rowCapacity, columnCapacity;
        int** matrixPtr{matrix.getBaseArrayPtr(nrOfRows, nrOfColumns, rowCapacity, columnCapacity)};

        if (!matrixPtr || nrOfRows != 2 || nrOfColumns != 3 || rowCapacity != 2 || columnCapacity != 3)
        {
            QFAIL("Passing resources outside the matrix failed, either the pointer is null or the number of rows and columns is not correct!");
        }

        QVERIFY2(matrixPtr[0][0] == 1 &&
                 matrixPtr[0][1] == 2 &&
                 matrixPtr[0][2] == 3 &&
                 matrixPtr[1][0] == 4 &&
                 matrixPtr[1][1] == 5 &&
                 matrixPtr[1][2] == 6,

                "Passing resources outside the matrix failed, the element values are not correct!");
    }
}

void CommonTests::testTranspose()
{
    {
        IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};

        matrix.transpose(matrix);

        if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Calculating transposed matrix failed, capacity is not correct!");
        }

        if (matrix.getNrOfRows() != 3 || matrix.getNrOfColumns() != 2)
        {
            QFAIL("Calculating transposed matrix failed, number of rows or columns is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 4 &&
                 matrix.at(1, 0) == 2 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(2, 0) == 3 &&
                 matrix.at(2, 1) == 6,

                 "Calculating transponsed matrix failed, the resulting values are incorrect!");
    }

    {
        IntMatrix matrix{};

        matrix.transpose(matrix);

        QVERIFY2(matrix.getRowCapacity() == 0 && matrix.getColumnCapacity() == 0,

                 "Calculating transposed matrix failed, capacity is not correct!");

        QVERIFY2(matrix.getNrOfRows() == 0 && matrix.getNrOfColumns() == 0,

                 "Calculating transposed matrix failed, number of rows or columns is not correct!");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix transposedMatrix{2, 2, {7, 8, 9, 10}};

        matrix.transpose(transposedMatrix);

        if (matrix.getRowCapacity() != 2 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Calculating transposed matrix failed, capacity of the source matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 2 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Calculating transposed matrix failed, number of rows or columns of the source matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6,

                 "Calculating transponsed matrix failed, the values of the source matrix are not correct!");

        if (transposedMatrix.getRowCapacity() != 3 || transposedMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Calculating transposed matrix failed, capacity of the destination (transposed) matrix is not correct!");
        }

        if (transposedMatrix.getNrOfRows() != 3 || transposedMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Calculating transposed matrix failed, number of rows or columns of the destination (transposed) matrix is not correct!");
        }

        QVERIFY2(transposedMatrix.at(0, 0) == 1 &&
                 transposedMatrix.at(0, 1) == 4 &&
                 transposedMatrix.at(1, 0) == 2 &&
                 transposedMatrix.at(1, 1) == 5 &&
                 transposedMatrix.at(2, 0) == 3 &&
                 transposedMatrix.at(2, 1) == 6,

                 "Calculating transponsed matrix failed, the values of the destination (transposed) matrix are not correct!");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix transposedMatrix{};

        matrix.transpose(transposedMatrix);

        if (matrix.getRowCapacity() != 2 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Calculating transposed matrix failed, capacity of the source matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 2 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Calculating transposed matrix failed, number of rows or columns of the source matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6,

                 "Calculating transponsed matrix failed, the values of the source matrix are not correct!");

        if (transposedMatrix.getRowCapacity() != 3 || transposedMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Calculating transposed matrix failed, capacity of the destination (transposed) matrix is not correct!");
        }

        if (transposedMatrix.getNrOfRows() != 3 || transposedMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Calculating transposed matrix failed, number of rows or columns of the destination (transposed) matrix is not correct!");
        }

        QVERIFY2(transposedMatrix.at(0, 0) == 1 &&
                 transposedMatrix.at(0, 1) == 4 &&
                 transposedMatrix.at(1, 0) == 2 &&
                 transposedMatrix.at(1, 1) == 5 &&
                 transposedMatrix.at(2, 0) == 3 &&
                 transposedMatrix.at(2, 1) == 6,

                 "Calculating transponsed matrix failed, the values of the destination (transposed) matrix are not correct!");
    }

    {
        IntMatrix matrix{};
        IntMatrix transposedMatrix{2, 2, {1, 2, 3, 4}};

        matrix.transpose(transposedMatrix);

        QVERIFY2(matrix.getRowCapacity() == 0 && matrix.getColumnCapacity() == 0,

                 "Calculating transposed matrix failed, capacity of the source matrix is not correct!");

        QVERIFY2(matrix.getNrOfRows() == 0 && matrix.getNrOfColumns() == 0,

                 "Calculating transposed matrix failed, number of rows or columns of the source matrix is not correct!");

        QVERIFY2(transposedMatrix.getRowCapacity() == 0 && transposedMatrix.getColumnCapacity() == 0,

                 "Calculating transposed matrix failed, capacity of the destination (transposed) matrix is not correct!");

        QVERIFY2(transposedMatrix.getNrOfRows() == 0 && transposedMatrix.getNrOfColumns() == 0,

                 "Calculating transposed matrix failed, number of rows or columns of the destination (transposed) matrix is not correct!");
    }

    {
        IntMatrix matrix{};
        IntMatrix transposedMatrix{};

        matrix.transpose(transposedMatrix);

        QVERIFY2(matrix.getRowCapacity() == 0 && matrix.getColumnCapacity() == 0,

                 "Calculating transposed matrix failed, capacity of the source matrix is not correct!");

        QVERIFY2(matrix.getNrOfRows() == 0 && matrix.getNrOfColumns() == 0,

                 "Calculating transposed matrix failed, number of rows or columns of the source matrix is not correct!");

        QVERIFY2(transposedMatrix.getRowCapacity() == 0 && transposedMatrix.getColumnCapacity() == 0,

                 "Calculating transposed matrix failed, capacity of the destination (transposed) matrix is not correct!");

        QVERIFY2(transposedMatrix.getNrOfRows() == 0 && transposedMatrix.getNrOfColumns() == 0,

                 "Calculating transposed matrix failed, number of rows or columns of the destination (transposed) matrix is not correct!");
    }
}

void CommonTests::testCapacityWithTranspose()
{
    using namespace std;
    auto transposeAndTestCapacity = [](string testNumber, IntMatrix& matrix, IntMatrix& transposedMatrix, int desiredRowCapacity, int desiredColumnCapacity)
    {
        matrix.transpose(transposedMatrix);

        QVERIFY2(transposedMatrix.getRowCapacity() == desiredRowCapacity && transposedMatrix.getColumnCapacity() == desiredColumnCapacity,
                 string{"Calculating transposed matrix failed, capacity of the destination (transposed) matrix is not correct! Test number: " + testNumber}.c_str());
    };

    int testNumber{1};

    {
        IntMatrix matrix{3, 4, 2};
        IntMatrix transposedMatrix{};

        transposeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, transposedMatrix, 5, 3);
    }

    {
        IntMatrix matrix{4, 3, 2};
        IntMatrix transposedMatrix{};

        transposeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, transposedMatrix, 3, 5);
    }

    {
        IntMatrix matrix{7, 8, 2};
        IntMatrix transposedMatrix{};

        transposeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, transposedMatrix, 10, 8);
    }

    {
        IntMatrix matrix{8, 7, 2};
        IntMatrix transposedMatrix{};

        transposeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, transposedMatrix, 8, 10);
    }

    {
        IntMatrix matrix{8, 7, 2};
        IntMatrix transposedMatrix{5, 6, 2};

        transposeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, transposedMatrix, 8, 10);
    }

    {
        IntMatrix matrix{8, 7, 2};
        IntMatrix transposedMatrix{6, 6, 2};

        transposeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, transposedMatrix, 7, 10);
    }

    {
        IntMatrix matrix{8, 7, 2};
        IntMatrix transposedMatrix{5, 7, 2};

        transposeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, transposedMatrix, 8, 8);
    }

    {
        IntMatrix matrix{8, 7, 2};
        IntMatrix transposedMatrix{6, 7, 2};

        transposeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, transposedMatrix, 7, 8);
    }

    {
        IntMatrix matrix{8, 7, 2};
        IntMatrix transposedMatrix{7, 8, 2};

        transposeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, transposedMatrix, 8, 10);
    }

    {
        IntMatrix matrix{3, 3, 2};

        transposeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrix, 3, 3);
    }

    {
        IntMatrix matrix{3, 4, 2};

        transposeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrix, 5, 5);
    }

    {
        IntMatrix matrix{4, 3, 2};

        transposeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrix, 5, 5);
    }

    {
        IntMatrix matrix{4, 4, 2};

        transposeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrix, 5, 5);
    }

    {
        IntMatrix matrix{7, 8, 2};

        transposeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrix, 8, 10);
    }

    {
        IntMatrix matrix{8, 7, 2};

        transposeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrix, 10, 8);
    }
}

void CommonTests::testClear()
{
    {
        IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};
        matrix.clear();

        QVERIFY2(matrix.getRowCapacity() == 0 && matrix.getColumnCapacity() == 0, "Clear failed, capacity is not correct!");
        QVERIFY2(matrix.getNrOfRows() == 0 && matrix.getNrOfColumns() == 0, "Clear failed, number of rows and columns is not correct!");
    }

    {
        IntMatrix matrix{};
        matrix.clear();

        QVERIFY2(matrix.getRowCapacity() == 0 && matrix.getColumnCapacity() == 0, "Clear failed, capacity is not correct!");
        QVERIFY2(matrix.getNrOfRows() == 0 && matrix.getNrOfColumns() == 0, "Clear failed, number of rows and columns is not correct!");
    }
}

void CommonTests::testResizeWithoutFillingInNewValues()
{
    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.resize(4, 2);

        if (matrix.getRowCapacity() != 4 || matrix.getColumnCapacity() != 2)
        {
            QFAIL("Resizing failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 4 || matrix.getNrOfColumns() != 2)
        {
            QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 8 &&
                 matrix.at(3, 0) == 10 &&
                 matrix.at(3, 1) == 11,

                "Resizing failed, the matrix does not have the correct values!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.resize(2, 3);

        if (matrix.getRowCapacity() != 2 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Resizing failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 2 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6,

                "Resizing failed, the matrix does not have the correct values!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.resize(3, 2);

        if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 2)
        {
            QFAIL("Resizing failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 3 || matrix.getNrOfColumns() != 2)
        {
            QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 8,

                "Resizing failed, the matrix does not have the correct values!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.resize(4, 5);

        if (matrix.getRowCapacity() != 4 || matrix.getColumnCapacity() != 5)
        {
            QFAIL("Resizing failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 4 || matrix.getNrOfColumns() != 5)
        {
            QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 8 &&
                 matrix.at(2, 2) == 9 &&
                 matrix.at(3, 0) == 10 &&
                 matrix.at(3, 1) == 11 &&
                 matrix.at(3, 2) == 12,

                "Resizing failed, the matrix does not have the correct values!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.resize(5, 3);

        if (matrix.getRowCapacity() != 5 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Resizing failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 5 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 8 &&
                 matrix.at(2, 2) == 9 &&
                 matrix.at(3, 0) == 10 &&
                 matrix.at(3, 1) == 11 &&
                 matrix.at(3, 2) == 12,

                "Resizing failed, the matrix does not have the correct values!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.resize(5, 4);

        if (matrix.getRowCapacity() != 5 || matrix.getColumnCapacity() != 4)
        {
            QFAIL("Resizing failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 5 || matrix.getNrOfColumns() != 4)
        {
            QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 8 &&
                 matrix.at(2, 2) == 9 &&
                 matrix.at(3, 0) == 10 &&
                 matrix.at(3, 1) == 11 &&
                 matrix.at(3, 2) == 12,

                "Resizing failed, the matrix does not have the correct values!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.resize(4, 3);

        if (matrix.getRowCapacity() != 4 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Resizing failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 4 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 8 &&
                 matrix.at(2, 2) == 9 &&
                 matrix.at(3, 0) == 10 &&
                 matrix.at(3, 1) == 11 &&
                 matrix.at(3, 2) == 12,

                "Resizing failed, the matrix does not retain its values if dimensions are unchanged!");
    }
}

void CommonTests::testCapacityWithResizeWithoutFillingInNewValues()
{
    using namespace std;

    auto resizeAndTestCapacity = [](string testNumber,
                           IntMatrix& matrix,
                           const IntMatrix& matrixCopy,
                           int desiredRowCapacity,
                           int desiredColumnCapacity,
                           int nrOfRows,
                           int nrOfColumns,
                           int inputRowCapacity=0,
                           int inputColumnCapacity=0
                          )
    {
        IntMatrix secondMatrixCopy{matrixCopy};

        int retainedNrOfRows{min(nrOfRows, secondMatrixCopy.getNrOfRows())};
        int retainedNrOfColumns{min(nrOfColumns, secondMatrixCopy.getNrOfColumns())};

        secondMatrixCopy.resize(nrOfRows, nrOfColumns, inputRowCapacity, inputColumnCapacity);

        if (secondMatrixCopy.getRowCapacity() != desiredRowCapacity || secondMatrixCopy.getColumnCapacity() != desiredColumnCapacity)
        {
            QFAIL(string{"Resizing failed, capacity of the matrix is not correct! Test number: " + testNumber}.c_str());
        }

        if (secondMatrixCopy.getNrOfRows() != nrOfRows || secondMatrixCopy.getNrOfColumns() != nrOfColumns)
        {
            QFAIL(string{"Resizing failed, number of rows or columns of the matrix is not correct! Test number: " + testNumber}.c_str());
        }

        bool retainedValuesAreCorrect{true};
        for (int row{0}; row < retainedNrOfRows; ++row)
        {
            for (int col{0}; col < retainedNrOfColumns; ++col)
            {
                if (secondMatrixCopy.at(row, col) != matrix.at(row, col))
                {
                    retainedValuesAreCorrect = false;
                    break;
                }
            }
        }

        QVERIFY2(retainedValuesAreCorrect, string{"Resizing failed, the matrix does not have the correct values for the retained items! Test number: " + testNumber}.c_str());
    };

    int testNumber{1};

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resize(10, 7);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, 10, 7, 9, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, 10, 7, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, 10, 7, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 10, 7, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, 10, 7, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, 10, 7, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, 10, 7, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, 10, 7, 10, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, 10, 7, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, 10, 7, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 10, 7, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, 10, 7, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, 10, 7, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, 10, 7, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, 10, 7, 11, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, 10, 7, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 10, 7, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 10, 7, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, 10, 7, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, 10, 7, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, 10, 7, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, 10, 7, 12, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, 10, 7, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, 10, 7, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 10, 7, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, 10, 7, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, 10, 7, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, 10, 7, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, 10, 7, 13, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, 10, 7, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, 10, 7, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 10, 7, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, 10, 7, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, 10, 7, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, 10, 7, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, 10, 7);
    }

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resize(9, 8);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, 9, 8, 8, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, 9, 8, 8, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, 9, 8, 8, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 10, 9, 8, 8, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 11, 9, 8, 8, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, 9, 8, 8);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, 9, 8, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, 9, 8, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, 9, 8, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 10, 9, 8, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 11, 9, 8, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, 9, 8, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, 9, 8, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, 9, 8, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 9, 8, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, 9, 8, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, 9, 8, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, 9, 8, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 9, 8, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 9, 8, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 9, 8, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, 9, 8, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, 9, 8, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 9, 8, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, 9, 8, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, 9, 8, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 9, 8, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, 9, 8, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, 9, 8, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, 9, 8, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, 9, 8, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, 9, 8, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 9, 8, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, 9, 8, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, 9, 8, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, 9, 8, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, 9, 8);
    }

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resize(9, 7);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 7, 9, 7, 8, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 7, 9, 7, 8, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, 9, 7, 8, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, 9, 7, 8, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 10, 9, 7, 8, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 11, 9, 7, 8, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 7, 9, 7, 8);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 7, 9, 7, 9, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 7, 9, 7, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, 9, 7, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, 9, 7, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 10, 9, 7, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 11, 9, 7, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 7, 9, 7, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, 9, 7, 10, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, 9, 7, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, 9, 7, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 9, 7, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, 9, 7, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, 9, 7, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, 9, 7, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, 9, 7, 11, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, 9, 7, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 9, 7, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 9, 7, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, 9, 7, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, 9, 7, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, 9, 7, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, 9, 7, 12, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, 9, 7, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, 9, 7, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 9, 7, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, 9, 7, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, 9, 7, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, 9, 7, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, 9, 7, 13, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, 9, 7, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, 9, 7, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 9, 7, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, 9, 7, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, 9, 7, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, 9, 7, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 7, 9, 7);
    }

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resize(10, 8);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, 10, 8, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, 10, 8, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 10, 8, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, 10, 8, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, 10, 8, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, 10, 8, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, 10, 8, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, 10, 8, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 10, 8, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, 10, 8, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, 10, 8, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, 10, 8, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 10, 8, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 10, 8, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 10, 8, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, 10, 8, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, 10, 8, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 10, 8, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, 10, 8, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, 10, 8, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 10, 8, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, 10, 8, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, 10, 8, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, 10, 8, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, 10, 8, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, 10, 8, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 10, 8, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, 10, 8, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, 10, 8, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, 10, 8, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, 10, 8);
    }

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resize(11, 8);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 11, 8, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 11, 8, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 8, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, 11, 8, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, 11, 8, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 11, 8, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 11, 8, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 11, 8, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 8, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, 11, 8, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, 11, 8, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 11, 8, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 11, 8, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 11, 8, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 8, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, 11, 8, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, 11, 8, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 11, 8, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, 11, 8, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, 11, 8, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 11, 8, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, 11, 8, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, 11, 8, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, 11, 8, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, 11, 8, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, 11, 8, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 11, 8, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, 11, 8, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, 11, 8, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, 11, 8, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 11, 8);
    }

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resize(10, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 10, 9, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 10, 9, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 10, 9, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, 10, 9, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, 10, 9, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 10, 9, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 10, 9, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 10, 9, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 10, 9, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, 10, 9, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, 10, 9, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 10, 9, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 10, 9, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 10, 9, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 10, 9, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, 10, 9, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, 10, 9, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 10, 9, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 10, 9, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 10, 9, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 10, 9, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, 10, 9, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, 10, 9, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 10, 9, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 10, 9, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 10, 9, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 10, 9, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, 10, 9, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, 10, 9, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 10, 9, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 10, 9);
    }

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resize(11, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 9, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 9, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 9, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, 11, 9, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, 11, 9, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 9, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 9, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 9, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 9, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, 11, 9, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, 11, 9, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 9, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 9, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 9, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 9, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, 11, 9, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, 11, 9, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 9, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 11, 9, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 11, 9, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 11, 9, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, 11, 9, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, 11, 9, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 11, 9, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 11, 9, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 11, 9, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 11, 9, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, 11, 9, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, 11, 9, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 11, 9, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 9);
    }

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resize(11, 7);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, 11, 7, 9, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, 11, 7, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 11, 7, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 7, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, 11, 7, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, 11, 7, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, 11, 7, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, 11, 7, 10, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, 11, 7, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 11, 7, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 7, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, 11, 7, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, 11, 7, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, 11, 7, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, 11, 7, 11, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, 11, 7, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, 11, 7, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 11, 7, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, 11, 7, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, 11, 7, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, 11, 7, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, 11, 7, 12, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, 11, 7, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, 11, 7, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 11, 7, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, 11, 7, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, 11, 7, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, 11, 7, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, 11, 7, 13, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, 11, 7, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, 11, 7, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 11, 7, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, 11, 7, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, 11, 7, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, 11, 7, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, 11, 7);
    }

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resize(9, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, 9, 9, 8, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, 9, 9, 8, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, 9, 9, 8, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 10, 9, 9, 8, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 11, 9, 9, 8, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, 9, 9, 8);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, 9, 9, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, 9, 9, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, 9, 9, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 10, 9, 9, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 11, 9, 9, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, 9, 9, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 9, 9, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 9, 9, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 9, 9, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, 9, 9, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, 9, 9, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, 9, 9, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 9, 9, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 9, 9, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 9, 9, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, 9, 9, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, 9, 9, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, 9, 9, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 9, 9, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 9, 9, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 9, 9, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, 9, 9, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, 9, 9, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, 9, 9, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 9, 9, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 9, 9, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 9, 9, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, 9, 9, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, 9, 9, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, 9, 9, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, 9, 9);
    }
}

void CommonTests::testResizeAndFillInNewValues()
{
    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.resizeWithValue(4, 2, -1);

        if (matrix.getRowCapacity() != 4 || matrix.getColumnCapacity() != 2)
        {
            QFAIL("Resizing failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 4 || matrix.getNrOfColumns() != 2)
        {
            QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 8 &&
                 matrix.at(3, 0) == 10 &&
                 matrix.at(3, 1) == 11,

                "Resizing failed, the matrix does not have the correct values!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.resizeWithValue(2, 3, -1);

        if (matrix.getRowCapacity() != 2 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Resizing failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 2 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6,

                "Resizing failed, the matrix does not have the correct values!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.resizeWithValue(3, 2, -1);

        if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 2)
        {
            QFAIL("Resizing failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 3 || matrix.getNrOfColumns() != 2)
        {
            QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 8,

                "Resizing failed, the matrix does not have the correct values!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.resizeWithValue(4, 5, -1);

        if (matrix.getRowCapacity() != 4 || matrix.getColumnCapacity() != 5)
        {
            QFAIL("Resizing failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 4 || matrix.getNrOfColumns() != 5)
        {
            QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(0, 3) == -1 &&
                 matrix.at(0, 4) == -1 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6 &&
                 matrix.at(1, 3) == -1 &&
                 matrix.at(1, 4) == -1 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 8 &&
                 matrix.at(2, 2) == 9 &&
                 matrix.at(2, 3) == -1 &&
                 matrix.at(2, 4) == -1 &&
                 matrix.at(3, 0) == 10 &&
                 matrix.at(3, 1) == 11 &&
                 matrix.at(3, 2) == 12 &&
                 matrix.at(3, 3) == -1 &&
                 matrix.at(3, 4) == -1,

                "Resizing failed, the matrix does not have the correct values!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.resizeWithValue(5, 3, -1);

        if (matrix.getRowCapacity() != 5 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Resizing failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 5 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 8 &&
                 matrix.at(2, 2) == 9 &&
                 matrix.at(3, 0) == 10 &&
                 matrix.at(3, 1) == 11 &&
                 matrix.at(3, 2) == 12 &&
                 matrix.at(4, 0) == -1 &&
                 matrix.at(4, 1) == -1 &&
                 matrix.at(4, 2) == -1,

                "Resizing failed, the matrix does not have the correct values!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.resizeWithValue(5, 4, -1);

        if (matrix.getRowCapacity() != 5 || matrix.getColumnCapacity() != 4)
        {
            QFAIL("Resizing failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 5 || matrix.getNrOfColumns() != 4)
        {
            QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(0, 3) == -1 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6 &&
                 matrix.at(1, 3) == -1 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 8 &&
                 matrix.at(2, 2) == 9 &&
                 matrix.at(2, 3) == -1 &&
                 matrix.at(3, 0) == 10 &&
                 matrix.at(3, 1) == 11 &&
                 matrix.at(3, 2) == 12 &&
                 matrix.at(3, 3) == -1 &&
                 matrix.at(4, 0) == -1 &&
                 matrix.at(4, 1) == -1 &&
                 matrix.at(4, 2) == -1 &&
                 matrix.at(4, 3) == -1,

                "Resizing failed, the matrix does not have the correct values!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.resizeWithValue(4, 3, -1);

        if (matrix.getRowCapacity() != 4 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Resizing failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 4 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 8 &&
                 matrix.at(2, 2) == 9 &&
                 matrix.at(3, 0) == 10 &&
                 matrix.at(3, 1) == 11 &&
                 matrix.at(3, 2) == 12,

                "Resizing failed, the matrix does not retain its values if dimensions are unchanged!");
    }
}

void CommonTests::testCapacityWithResizeAndFillInNewValues()
{
    using namespace std;

    auto resizeAndTestCapacity = [](string testNumber,
                           IntMatrix& matrix,
                           const IntMatrix& matrixCopy,
                           int desiredRowCapacity,
                           int desiredColumnCapacity,
                           int fillValue,
                           int nrOfRows,
                           int nrOfColumns,
                           int inputRowCapacity=0,
                           int inputColumnCapacity=0
                          )
    {
        IntMatrix secondMatrixCopy{matrixCopy};

        secondMatrixCopy.resizeWithValue(nrOfRows, nrOfColumns, fillValue, inputRowCapacity, inputColumnCapacity);

        if (secondMatrixCopy.getRowCapacity() != desiredRowCapacity || secondMatrixCopy.getColumnCapacity() != desiredColumnCapacity)
        {
            QFAIL(string{"Resizing failed, capacity of the matrix is not correct! Test number: " + testNumber}.c_str());
        }

        if (secondMatrixCopy.getNrOfRows() != nrOfRows || secondMatrixCopy.getNrOfColumns() != nrOfColumns)
        {
            QFAIL(string{"Resizing failed, number of rows or columns of the matrix is not correct! Test number: " + testNumber}.c_str());
        }

        QVERIFY2(secondMatrixCopy == matrix, string{"Resizing failed, the matrix does not have the correct values! Test number: " + testNumber}.c_str());
    };

    int testNumber{1};

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resizeWithValue(10, 7, -5);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, -5, 10, 7, 9, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, -5, 10, 7, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, -5, 10, 7, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 10, 7, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, -5, 10, 7, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, -5, 10, 7, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, -5, 10, 7, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, -5, 10, 7, 10, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, -5, 10, 7, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, -5, 10, 7, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 10, 7, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, -5, 10, 7, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, -5, 10, 7, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, -5, 10, 7, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, -5, 10, 7, 11, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, -5, 10, 7, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 10, 7, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 10, 7, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, -5, 10, 7, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, -5, 10, 7, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, -5, 10, 7, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, -5, 10, 7, 12, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, -5, 10, 7, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, -5, 10, 7, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 10, 7, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, -5, 10, 7, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, -5, 10, 7, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, -5, 10, 7, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, -5, 10, 7, 13, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, -5, 10, 7, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, -5, 10, 7, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 10, 7, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, -5, 10, 7, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, -5, 10, 7, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, -5, 10, 7, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, -5, 10, 7);
    }

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resizeWithValue(9, 8, -5);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, -5, 9, 8, 8, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, -5, 9, 8, 8, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, -5, 9, 8, 8, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 10, -5, 9, 8, 8, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 11, -5, 9, 8, 8, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, -5, 9, 8, 8);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, -5, 9, 8, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, -5, 9, 8, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, -5, 9, 8, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 10, -5, 9, 8, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 11, -5, 9, 8, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, -5, 9, 8, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, -5, 9, 8, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, -5, 9, 8, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 9, 8, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, -5, 9, 8, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, -5, 9, 8, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, -5, 9, 8, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 9, 8, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 9, 8, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 9, 8, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, -5, 9, 8, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, -5, 9, 8, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 9, 8, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, -5, 9, 8, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, -5, 9, 8, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 9, 8, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, -5, 9, 8, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, -5, 9, 8, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, -5, 9, 8, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, -5, 9, 8, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, -5, 9, 8, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 9, 8, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, -5, 9, 8, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, -5, 9, 8, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, -5, 9, 8, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, -5, 9, 8);
    }

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resizeWithValue(9, 7, -5);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 7, -5, 9, 7, 8, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 7, -5, 9, 7, 8, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, -5, 9, 7, 8, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, -5, 9, 7, 8, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 10, -5, 9, 7, 8, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 11, -5, 9, 7, 8, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 7, -5, 9, 7, 8);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 7, -5, 9, 7, 9, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 7, -5, 9, 7, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 8, -5, 9, 7, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, -5, 9, 7, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 10, -5, 9, 7, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 11, -5, 9, 7, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 7, -5, 9, 7, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, -5, 9, 7, 10, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, -5, 9, 7, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, -5, 9, 7, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 9, 7, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, -5, 9, 7, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, -5, 9, 7, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 7, -5, 9, 7, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, -5, 9, 7, 11, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, -5, 9, 7, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 9, 7, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 9, 7, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, -5, 9, 7, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, -5, 9, 7, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, -5, 9, 7, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, -5, 9, 7, 12, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, -5, 9, 7, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, -5, 9, 7, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 9, 7, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, -5, 9, 7, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, -5, 9, 7, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, -5, 9, 7, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, -5, 9, 7, 13, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, -5, 9, 7, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, -5, 9, 7, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 9, 7, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, -5, 9, 7, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, -5, 9, 7, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, -5, 9, 7, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 7, -5, 9, 7);
    }

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resizeWithValue(10, 8, -5);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, -5, 10, 8, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, -5, 10, 8, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 10, 8, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, -5, 10, 8, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, -5, 10, 8, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, -5, 10, 8, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, -5, 10, 8, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, -5, 10, 8, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 10, 8, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, -5, 10, 8, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, -5, 10, 8, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, -5, 10, 8, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 10, 8, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 10, 8, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 10, 8, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, -5, 10, 8, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, -5, 10, 8, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 10, 8, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, -5, 10, 8, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, -5, 10, 8, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 10, 8, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, -5, 10, 8, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, -5, 10, 8, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, -5, 10, 8, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, -5, 10, 8, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, -5, 10, 8, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 10, 8, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, -5, 10, 8, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, -5, 10, 8, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, -5, 10, 8, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 8, -5, 10, 8);
    }

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resizeWithValue(11, 8, -5);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 11, 8, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 11, 8, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 8, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, -5, 11, 8, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, -5, 11, 8, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 11, 8, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 11, 8, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 11, 8, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 8, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, -5, 11, 8, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, -5, 11, 8, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 11, 8, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 11, 8, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 11, 8, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 8, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, -5, 11, 8, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, -5, 11, 8, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 11, 8, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, -5, 11, 8, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, -5, 11, 8, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 11, 8, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, -5, 11, 8, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, -5, 11, 8, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, -5, 11, 8, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, -5, 11, 8, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, -5, 11, 8, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 11, 8, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, -5, 11, 8, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, -5, 11, 8, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, -5, 11, 8, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 11, 8);
    }

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resizeWithValue(10, 9, -5);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 10, 9, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 10, 9, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 10, 9, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, -5, 10, 9, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, -5, 10, 9, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 10, 9, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 10, 9, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 10, 9, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 10, 9, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, -5, 10, 9, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, -5, 10, 9, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 10, 9, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 10, 9, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 10, 9, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 10, 9, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, -5, 10, 9, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, -5, 10, 9, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 10, 9, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 10, 9, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 10, 9, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 10, 9, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, -5, 10, 9, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, -5, 10, 9, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 10, 9, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 10, 9, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 10, 9, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 10, 9, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, -5, 10, 9, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, -5, 10, 9, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 10, 9, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 10, 9);
    }

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resizeWithValue(11, 9, -5);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 9, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 9, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 9, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, -5, 11, 9, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, -5, 11, 9, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 9, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 9, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 9, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 9, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, -5, 11, 9, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, -5, 11, 9, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 9, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 9, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 9, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 9, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, -5, 11, 9, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, -5, 11, 9, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 9, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 11, 9, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 11, 9, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 11, 9, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, -5, 11, 9, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, -5, 11, 9, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 11, 9, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 11, 9, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 11, 9, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 11, 9, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, -5, 11, 9, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, -5, 11, 9, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 11, 9, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 9);
    }

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resizeWithValue(11, 7, -5);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, -5, 11, 7, 9, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, -5, 11, 7, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 11, 7, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 7, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, -5, 11, 7, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, -5, 11, 7, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, -5, 11, 7, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, -5, 11, 7, 10, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, -5, 11, 7, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 11, 7, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 7, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, -5, 11, 7, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, -5, 11, 7, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, -5, 11, 7, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, -5, 11, 7, 11, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, -5, 11, 7, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 8, -5, 11, 7, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 11, 7, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, -5, 11, 7, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, -5, 11, 7, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, -5, 11, 7, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, -5, 11, 7, 12, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, -5, 11, 7, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 8, -5, 11, 7, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 11, 7, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, -5, 11, 7, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, -5, 11, 7, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 7, -5, 11, 7, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, -5, 11, 7, 13, 6);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, -5, 11, 7, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 8, -5, 11, 7, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 11, 7, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, -5, 11, 7, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, -5, 11, 7, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 7, -5, 11, 7, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 7, -5, 11, 7);
    }

    {
        IntMatrix matrix{10, 8, -2};
        IntMatrix matrixCopy{matrix};

        matrix.resizeWithValue(9, 9, -5);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, -5, 9, 9, 8, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, -5, 9, 9, 8, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, -5, 9, 9, 8, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 10, -5, 9, 9, 8, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 11, -5, 9, 9, 8, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, -5, 9, 9, 8);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, -5, 9, 9, 9, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, -5, 9, 9, 9, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, -5, 9, 9, 9, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 10, -5, 9, 9, 9, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 11, -5, 9, 9, 9, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, -5, 9, 9, 9);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 9, 9, 10, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 9, 9, 10, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 9, 9, 10, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 10, -5, 9, 9, 10, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 11, -5, 9, 9, 10, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 10, 9, -5, 9, 9, 10);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 9, 9, 11, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 9, 9, 11, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 9, 9, 11, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 10, -5, 9, 9, 11, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 11, -5, 9, 9, 11, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 11, 9, -5, 9, 9, 11);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 9, 9, 12, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 9, 9, 12, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 9, 9, 12, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 10, -5, 9, 9, 12, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 11, -5, 9, 9, 12, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 12, 9, -5, 9, 9, 12);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 9, 9, 13, 7);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 9, 9, 13, 8);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 9, 9, 13, 9);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 10, -5, 9, 9, 13, 10);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 11, -5, 9, 9, 13, 11);
        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 13, 9, -5, 9, 9, 13);

        resizeAndTestCapacity(QString::number(testNumber++).toStdString(), matrix, matrixCopy, 9, 9, -5, 9, 9);
    }
}

void CommonTests::testShrinkToFit()
{
    {
        IntMatrix matrix{};

        matrix.shrinkToFit();

        QVERIFY2(matrix.getRowCapacity() == 0 && matrix.getColumnCapacity() == 0, "Shrinking to fit failed, capacity of the empty matrix is not correct!");
        QVERIFY2(matrix.getNrOfRows() == 0 && matrix.getNrOfColumns() == 0, "Shrinking to fit failed, number of rows or columns of the empty matrix is not correct!");
    }

    {
        IntMatrix matrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};

        matrix.shrinkToFit();

        if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Shrinking to fit failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 3 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Shrinking to fit failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 8 &&
                 matrix.at(2, 2) == 9,

                 "Shrinking to fit failed, the matrix does not retain its values!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.shrinkToFit();

        if (matrix.getRowCapacity() != 4 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Shrinking to fit failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 4 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Shrinking to fit failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 8 &&
                 matrix.at(2, 2) == 9 &&
                 matrix.at(3, 0) == 10 &&
                 matrix.at(3, 1) == 11 &&
                 matrix.at(3, 2) == 12,

                 "Shrinking to fit failed, the matrix does not retain its values!");
    }

    {
        IntMatrix matrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.shrinkToFit();

        if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 4)
        {
            QFAIL("Shrinking to fit failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 3 || matrix.getNrOfColumns() != 4)
        {
            QFAIL("Shrinking to fit failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(0, 3) == 4 &&
                 matrix.at(1, 0) == 5 &&
                 matrix.at(1, 1) == 6 &&
                 matrix.at(1, 2) == 7 &&
                 matrix.at(1, 3) == 8 &&
                 matrix.at(2, 0) == 9 &&
                 matrix.at(2, 1) == 10 &&
                 matrix.at(2, 2) == 11 &&
                 matrix.at(2, 3) == 12,

                 "Shrinking to fit failed, the matrix does not retain its values!");
    }

    {
        IntMatrix matrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};

        matrix.shrinkToFit();

        if (matrix.getRowCapacity() != 4 || matrix.getColumnCapacity() != 4)
        {
            QFAIL("Shrinking to fit failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 4 || matrix.getNrOfColumns() != 4)
        {
            QFAIL("Shrinking to fit failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(0, 3) == 4 &&
                 matrix.at(1, 0) == 5 &&
                 matrix.at(1, 1) == 6 &&
                 matrix.at(1, 2) == 7 &&
                 matrix.at(1, 3) == 8 &&
                 matrix.at(2, 0) == 9 &&
                 matrix.at(2, 1) == 10 &&
                 matrix.at(2, 2) == 11 &&
                 matrix.at(2, 3) == 12 &&
                 matrix.at(3, 0) == 13 &&
                 matrix.at(3, 1) == 14 &&
                 matrix.at(3, 2) == 15 &&
                 matrix.at(3, 3) == 16,

                 "Shrinking to fit failed, the matrix does not retain its values!");
    }
}

void CommonTests::testInsertRowNoSetValue()
{
    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.insertRow(2);

        if (matrix.getRowCapacity() != 5 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Insert row failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 5 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Insert row failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6 &&
                 matrix.at(3, 0) == 7 &&
                 matrix.at(3, 1) == 8 &&
                 matrix.at(3, 2) == 9 &&
                 matrix.at(4, 0) == 10 &&
                 matrix.at(4, 1) == 11 &&
                 matrix.at(4, 2) == 12,

                 "Insert row failed, the matrix doesn't have the right values on the existing rows!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.insertRow(0);

        if (matrix.getRowCapacity() != 5 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Insert row failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 5 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Insert row failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(1, 0) == 1 &&
                 matrix.at(1, 1) == 2 &&
                 matrix.at(1, 2) == 3 &&
                 matrix.at(2, 0) == 4 &&
                 matrix.at(2, 1) == 5 &&
                 matrix.at(2, 2) == 6 &&
                 matrix.at(3, 0) == 7 &&
                 matrix.at(3, 1) == 8 &&
                 matrix.at(3, 2) == 9 &&
                 matrix.at(4, 0) == 10 &&
                 matrix.at(4, 1) == 11 &&
                 matrix.at(4, 2) == 12,

                 "Insert row failed, the matrix doesn't have the right values on the existing rows!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.insertRow(4);

        if (matrix.getRowCapacity() != 5 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Insert row failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 5 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Insert row failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 8 &&
                 matrix.at(2, 2) == 9 &&
                 matrix.at(3, 0) == 10 &&
                 matrix.at(3, 1) == 11 &&
                 matrix.at(3, 2) == 12,

                 "Insert row failed, the matrix doesn't have the right values on the existing rows!");
    }
}

void CommonTests::testInsertRowSetValue()
{
    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.insertRow(2, -1);

        if (matrix.getRowCapacity() != 5 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Insert row failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 5 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Insert row failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6 &&
                 matrix.at(2, 0) == -1 &&
                 matrix.at(2, 1) == -1 &&
                 matrix.at(2, 2) == -1 &&
                 matrix.at(3, 0) == 7 &&
                 matrix.at(3, 1) == 8 &&
                 matrix.at(3, 2) == 9 &&
                 matrix.at(4, 0) == 10 &&
                 matrix.at(4, 1) == 11 &&
                 matrix.at(4, 2) == 12,

                 "Insert row failed, the matrix doesn't have the right values!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.insertRow(0, -1);

        if (matrix.getRowCapacity() != 5 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Insert row failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 5 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Insert row failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == -1 &&
                 matrix.at(0, 1) == -1 &&
                 matrix.at(0, 2) == -1 &&
                 matrix.at(1, 0) == 1 &&
                 matrix.at(1, 1) == 2 &&
                 matrix.at(1, 2) == 3 &&
                 matrix.at(2, 0) == 4 &&
                 matrix.at(2, 1) == 5 &&
                 matrix.at(2, 2) == 6 &&
                 matrix.at(3, 0) == 7 &&
                 matrix.at(3, 1) == 8 &&
                 matrix.at(3, 2) == 9 &&
                 matrix.at(4, 0) == 10 &&
                 matrix.at(4, 1) == 11 &&
                 matrix.at(4, 2) == 12,

                 "Insert row failed, the matrix doesn't have the right values!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.insertRow(4, -1);

        if (matrix.getRowCapacity() != 5 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Insert row failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 5 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Insert row failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 8 &&
                 matrix.at(2, 2) == 9 &&
                 matrix.at(3, 0) == 10 &&
                 matrix.at(3, 1) == 11 &&
                 matrix.at(3, 2) == 12 &&
                 matrix.at(4, 0) == -1 &&
                 matrix.at(4, 1) == -1 &&
                 matrix.at(4, 2) == -1,

                 "Insert row failed, the matrix doesn't have the right values!");
    }
}

void CommonTests::testCapacityWithInsertRow()
{
    {
        IntMatrix matrix{3, 4, -2};
        matrix.insertRow(1);

        QVERIFY2(matrix.getRowCapacity() == 6 && matrix.getColumnCapacity() == 5, "Insert row failed, capacity of the matrix is not correct!");
    }

    {
        IntMatrix matrix{3, 4, -2};
        matrix.insertRow(1, 5);

        QVERIFY2(matrix.getRowCapacity() == 6 && matrix.getColumnCapacity() == 5, "Insert row failed, capacity of the matrix is not correct!");
    }

    {
        IntMatrix matrix{6, 5, -2};
        matrix.insertRow(3);

        QVERIFY2(matrix.getRowCapacity() == 7 && matrix.getColumnCapacity() == 6, "Insert row failed, capacity of the matrix is not correct!");
    }

    {
        IntMatrix matrix{6, 5, -2};
        matrix.insertRow(3, 5);

        QVERIFY2(matrix.getRowCapacity() == 7 && matrix.getColumnCapacity() == 6, "Insert row failed, capacity of the matrix is not correct!");
    }

    {
        IntMatrix matrix{8, 2, -2};
        matrix.insertRow(5);

        QVERIFY2(matrix.getRowCapacity() == 10 && matrix.getColumnCapacity() == 2, "Insert row failed, capacity of the matrix is not correct!");
    }

    {
        IntMatrix matrix{8, 2, -2};
        matrix.insertRow(5, 5);

        QVERIFY2(matrix.getRowCapacity() == 10 && matrix.getColumnCapacity() == 2, "Insert row failed, capacity of the matrix is not correct!");
    }
}

void CommonTests::testInsertColumnNoSetValue()
{
    {
        IntMatrix matrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.insertColumn(2);

        if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 5)
        {
            QFAIL("Insert column failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 3 || matrix.getNrOfColumns() != 5)
        {
            QFAIL("Insert column failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 3) == 3 &&
                 matrix.at(0, 4) == 4 &&
                 matrix.at(1, 0) == 5 &&
                 matrix.at(1, 1) == 6 &&
                 matrix.at(1, 3) == 7 &&
                 matrix.at(1, 4) == 8 &&
                 matrix.at(2, 0) == 9 &&
                 matrix.at(2, 1) == 10 &&
                 matrix.at(2, 3) == 11 &&
                 matrix.at(2, 4) == 12,

                 "Insert column failed, the matrix doesn't have the right values on the existing columns!");
    }

    {
        IntMatrix matrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.insertColumn(0);

        if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 5)
        {
            QFAIL("Insert column failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 3 || matrix.getNrOfColumns() != 5)
        {
            QFAIL("Insert column failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 1) == 1 &&
                 matrix.at(0, 2) == 2 &&
                 matrix.at(0, 3) == 3 &&
                 matrix.at(0, 4) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6 &&
                 matrix.at(1, 3) == 7 &&
                 matrix.at(1, 4) == 8 &&
                 matrix.at(2, 1) == 9 &&
                 matrix.at(2, 2) == 10 &&
                 matrix.at(2, 3) == 11 &&
                 matrix.at(2, 4) == 12,

                 "Insert column failed, the matrix doesn't have the right values on the existing columns!");
    }

    {
        IntMatrix matrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.insertColumn(4);

        if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 5)
        {
            QFAIL("Insert column failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 3 || matrix.getNrOfColumns() != 5)
        {
            QFAIL("Insert column failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(0, 3) == 4 &&
                 matrix.at(1, 0) == 5 &&
                 matrix.at(1, 1) == 6 &&
                 matrix.at(1, 2) == 7 &&
                 matrix.at(1, 3) == 8 &&
                 matrix.at(2, 0) == 9 &&
                 matrix.at(2, 1) == 10 &&
                 matrix.at(2, 2) == 11 &&
                 matrix.at(2, 3) == 12,

                 "Insert column failed, the matrix doesn't have the right values on the existing columns!");
    }
}

void CommonTests::testInsertColumnSetValue()
{
    {
        IntMatrix matrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.insertColumn(2, -1);

        if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 5)
        {
            QFAIL("Insert column failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 3 || matrix.getNrOfColumns() != 5)
        {
            QFAIL("Insert column failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == -1 &&
                 matrix.at(0, 3) == 3 &&
                 matrix.at(0, 4) == 4 &&
                 matrix.at(1, 0) == 5 &&
                 matrix.at(1, 2) == -1 &&
                 matrix.at(1, 1) == 6 &&
                 matrix.at(1, 3) == 7 &&
                 matrix.at(1, 4) == 8 &&
                 matrix.at(2, 0) == 9 &&
                 matrix.at(2, 1) == 10 &&
                 matrix.at(2, 2) == -1 &&
                 matrix.at(2, 3) == 11 &&
                 matrix.at(2, 4) == 12,

                 "Insert column failed, the matrix doesn't have the right values!");
    }

    {
        IntMatrix matrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.insertColumn(0, -1);

        if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 5)
        {
            QFAIL("Insert column failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 3 || matrix.getNrOfColumns() != 5)
        {
            QFAIL("Insert column failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == -1 &&
                 matrix.at(0, 1) == 1 &&
                 matrix.at(0, 2) == 2 &&
                 matrix.at(0, 3) == 3 &&
                 matrix.at(0, 4) == 4 &&
                 matrix.at(1, 0) == -1 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6 &&
                 matrix.at(1, 3) == 7 &&
                 matrix.at(1, 4) == 8 &&
                 matrix.at(2, 0) == -1 &&
                 matrix.at(2, 1) == 9 &&
                 matrix.at(2, 2) == 10 &&
                 matrix.at(2, 3) == 11 &&
                 matrix.at(2, 4) == 12,

                 "Insert column failed, the matrix doesn't have the right values!");
    }

    {
        IntMatrix matrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.insertColumn(4, -1);

        if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 5)
        {
            QFAIL("Insert column failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 3 || matrix.getNrOfColumns() != 5)
        {
            QFAIL("Insert column failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(0, 3) == 4 &&
                 matrix.at(0, 4) == -1 &&
                 matrix.at(1, 0) == 5 &&
                 matrix.at(1, 1) == 6 &&
                 matrix.at(1, 2) == 7 &&
                 matrix.at(1, 3) == 8 &&
                 matrix.at(1, 4) == -1 &&
                 matrix.at(2, 0) == 9 &&
                 matrix.at(2, 1) == 10 &&
                 matrix.at(2, 2) == 11 &&
                 matrix.at(2, 3) == 12 &&
                 matrix.at(2, 4) == -1,

                 "Insert column failed, the matrix doesn't have the right values!");
    }
}

void CommonTests::testCapacityWithInsertColumn()
{
    {
        IntMatrix matrix{5, 3, 4};
        matrix.insertColumn(1);

        QVERIFY2(matrix.getRowCapacity() == 6 && matrix.getColumnCapacity() == 6, "Insert column failed, capacity of the matrix is not correct!");
    }

    {
        IntMatrix matrix{5, 3, 4};
        matrix.insertColumn(1, 1);

        QVERIFY2(matrix.getRowCapacity() == 6 && matrix.getColumnCapacity() == 6, "Insert column failed, capacity of the matrix is not correct!");
    }

    {
        IntMatrix matrix{5, 7, 4};
        matrix.insertColumn(1);

        QVERIFY2(matrix.getRowCapacity() == 6 && matrix.getColumnCapacity() == 8, "Insert column failed, capacity of the matrix is not correct!");
    }

    {
        IntMatrix matrix{5, 7, 4};
        matrix.insertColumn(1, 1);

        QVERIFY2(matrix.getRowCapacity() == 6 && matrix.getColumnCapacity() == 8, "Insert column failed, capacity of the matrix is not correct!");
    }

    {
        IntMatrix matrix{5, 14, 4};
        matrix.insertColumn(1);

        QVERIFY2(matrix.getRowCapacity() == 6 && matrix.getColumnCapacity() == 17, "Insert column failed, capacity of the matrix is not correct!");
    }

    {
        IntMatrix matrix{5, 14, 4};
        matrix.insertColumn(1, 1);

        QVERIFY2(matrix.getRowCapacity() == 6 && matrix.getColumnCapacity() == 17, "Insert column failed, capacity of the matrix is not correct!");
    }
}

void CommonTests::testEraseRow()
{
    {
        IntMatrix matrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.eraseRow(0);

        if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 5)
        {
            QFAIL("Erase row failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 2 || matrix.getNrOfColumns() != 4)
        {
            QFAIL("Erase row failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 5 &&
                 matrix.at(0, 1) == 6 &&
                 matrix.at(0, 2) == 7 &&
                 matrix.at(0, 3) == 8 &&
                 matrix.at(1, 0) == 9 &&
                 matrix.at(1, 1) == 10 &&
                 matrix.at(1, 2) == 11 &&
                 matrix.at(1, 3) == 12,

                 "Erase row failed, the matrix doesn't have the right values on the remaining rows!");
    }

    {
        IntMatrix matrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.eraseRow(1);

        if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 5)
        {
            QFAIL("Erase row failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 2 || matrix.getNrOfColumns() != 4)
        {
            QFAIL("Erase row failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(0, 3) == 4 &&
                 matrix.at(1, 0) == 9 &&
                 matrix.at(1, 1) == 10 &&
                 matrix.at(1, 2) == 11 &&
                 matrix.at(1, 3) == 12,

                 "Erase row failed, the matrix doesn't have the right values on the remaining rows!");
    }

    {
        IntMatrix matrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.eraseRow(2);

        if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 5)
        {
            QFAIL("Erase row failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 2 || matrix.getNrOfColumns() != 4)
        {
            QFAIL("Erase row failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(0, 3) == 4 &&
                 matrix.at(1, 0) == 5 &&
                 matrix.at(1, 1) == 6 &&
                 matrix.at(1, 2) == 7 &&
                 matrix.at(1, 3) == 8,

                 "Erase row failed, the matrix doesn't have the right values on the remaining rows!");
    }

    {
        IntMatrix matrix{1, 4, {1, 2, 3, 4}};
        matrix.eraseRow(0);

        QVERIFY2(matrix.getRowCapacity() == 0 && matrix.getColumnCapacity() == 0, "Erase row failed, capacity of the matrix is not correct!");
        QVERIFY2(matrix.getNrOfRows() == 0 && matrix.getNrOfColumns() == 0, "Erase row failed, number of rows or columns of the matrix is not correct!");
    }
}

void CommonTests::testCapacityWithEraseRow()
{
    {
        IntMatrix matrix{3, 4, -2};
        matrix.eraseRow(1);

        QVERIFY2(matrix.getRowCapacity() == 3 && matrix.getColumnCapacity() == 5, "Erase row failed, capacity of the matrix is not correct!");

        matrix.eraseRow(1);

        QVERIFY2(matrix.getRowCapacity() == 3 && matrix.getColumnCapacity() == 5, "Erase row failed, capacity of the matrix is not correct!");

        matrix.eraseRow(0);

        QVERIFY2(matrix.getRowCapacity() == 0 && matrix.getColumnCapacity() == 0, "Erase row failed, capacity of the matrix is not correct!");
    }

    {
        IntMatrix matrix{4, 4, -2};
        matrix.eraseRow(1);

        QVERIFY2(matrix.getRowCapacity() == 5 && matrix.getColumnCapacity() == 5, "Erase row failed, capacity of the matrix is not correct!");

        matrix.eraseRow(1);

        QVERIFY2(matrix.getRowCapacity() == 5 && matrix.getColumnCapacity() == 5, "Erase row failed, capacity of the matrix is not correct!");

        matrix.eraseRow(1);

        QVERIFY2(matrix.getRowCapacity() == 2 && matrix.getColumnCapacity() == 5, "Erase row failed, capacity of the matrix is not correct!");

        matrix.eraseRow(0);

        QVERIFY2(matrix.getRowCapacity() == 0 && matrix.getColumnCapacity() == 0, "Erase row failed, capacity of the matrix is not correct!");
    }

    {
        IntMatrix matrix{7, 5, -2};
        matrix.eraseRow(1);

        QVERIFY2(matrix.getRowCapacity() == 8 && matrix.getColumnCapacity() == 6, "Erase row failed, capacity of the matrix is not correct!");

        matrix.eraseRow(1);

        QVERIFY2(matrix.getRowCapacity() == 8 && matrix.getColumnCapacity() == 6, "Erase row failed, capacity of the matrix is not correct!");

        matrix.eraseRow(1);

        QVERIFY2(matrix.getRowCapacity() == 8 && matrix.getColumnCapacity() == 6, "Erase row failed, capacity of the matrix is not correct!");

        matrix.eraseRow(1);

        QVERIFY2(matrix.getRowCapacity() == 8 && matrix.getColumnCapacity() == 6, "Erase row failed, capacity of the matrix is not correct!");

        matrix.eraseRow(1);

        QVERIFY2(matrix.getRowCapacity() == 4 && matrix.getColumnCapacity() == 6, "Erase row failed, capacity of the matrix is not correct!");

        matrix.eraseRow(1);

        QVERIFY2(matrix.getRowCapacity() == 2 && matrix.getColumnCapacity() == 6, "Erase row failed, capacity of the matrix is not correct!");

        matrix.eraseRow(0);

        QVERIFY2(matrix.getRowCapacity() == 0 && matrix.getColumnCapacity() == 0, "Erase row failed, capacity of the matrix is not correct!");
    }
}

void CommonTests::testEraseColumn()
{
    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.eraseColumn(0);

        if (matrix.getRowCapacity() != 5 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Erase column failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 4 || matrix.getNrOfColumns() != 2)
        {
            QFAIL("Erase column failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 2 &&
                 matrix.at(0, 1) == 3 &&
                 matrix.at(1, 0) == 5 &&
                 matrix.at(1, 1) == 6 &&
                 matrix.at(2, 0) == 8 &&
                 matrix.at(2, 1) == 9 &&
                 matrix.at(3, 0) == 11 &&
                 matrix.at(3, 1) == 12,

                 "Erase column failed, the matrix doesn't have the right values on the remaining columns!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.eraseColumn(1);

        if (matrix.getRowCapacity() != 5 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Erase column failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 4 || matrix.getNrOfColumns() != 2)
        {
            QFAIL("Erase column failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 6 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 9 &&
                 matrix.at(3, 0) == 10 &&
                 matrix.at(3, 1) == 12,

                 "Erase column failed, the matrix doesn't have the right values on the remaining columns!");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        matrix.eraseColumn(2);

        if (matrix.getRowCapacity() != 5 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Erase column failed, capacity of the matrix is not correct!");
        }

        if (matrix.getNrOfRows() != 4 || matrix.getNrOfColumns() != 2)
        {
            QFAIL("Erase column failed, number of rows or columns of the matrix is not correct!");
        }

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(2, 0) == 7 &&
                 matrix.at(2, 1) == 8 &&
                 matrix.at(3, 0) == 10 &&
                 matrix.at(3, 1) == 11,

                 "Erase column failed, the matrix doesn't have the right values on the remaining columns!");
    }

    {
        IntMatrix matrix{4, 1, {1, 2, 3, 4}};
        matrix.eraseColumn(0);

        QVERIFY2(matrix.getRowCapacity() == 0 && matrix.getColumnCapacity() == 0, "Erase row failed, capacity of the matrix is not correct!");
        QVERIFY2(matrix.getNrOfRows() == 0 && matrix.getNrOfColumns() == 0, "Erase row failed, number of rows or columns of the matrix is not correct!");
    }
}

void CommonTests::testCapacityWithEraseColumn()
{
    {
        IntMatrix matrix{4, 3, 4};
        matrix.eraseColumn(1);

        QVERIFY2(matrix.getRowCapacity() == 5 && matrix.getColumnCapacity() == 3, "Erase column failed, capacity of the matrix is not correct!");

        matrix.eraseColumn(1);

        QVERIFY2(matrix.getRowCapacity() == 5 && matrix.getColumnCapacity() == 3, "Erase column failed, capacity of the matrix is not correct!");

        matrix.eraseColumn(0);

        QVERIFY2(matrix.getRowCapacity() == 0 && matrix.getColumnCapacity() == 0, "Erase column failed, capacity of the matrix is not correct!");
    }

    {
        IntMatrix matrix{4, 4, 4};
        matrix.eraseColumn(1);

        QVERIFY2(matrix.getRowCapacity() == 5 && matrix.getColumnCapacity() == 5, "Erase column failed, capacity of the matrix is not correct!");

        matrix.eraseColumn(1);

        QVERIFY2(matrix.getRowCapacity() == 5 && matrix.getColumnCapacity() == 5, "Erase column failed, capacity of the matrix is not correct!");

        matrix.eraseColumn(1);

        QVERIFY2(matrix.getRowCapacity() == 5 && matrix.getColumnCapacity() == 2, "Erase column failed, capacity of the matrix is not correct!");

        matrix.eraseColumn(0);

        QVERIFY2(matrix.getRowCapacity() == 0 && matrix.getColumnCapacity() == 0, "Erase column failed, capacity of the matrix is not correct!");
    }

    {
        IntMatrix matrix{5, 7, -2};
        matrix.eraseColumn(1);

        QVERIFY2(matrix.getRowCapacity() == 6 && matrix.getColumnCapacity() == 8, "Erase column failed, capacity of the matrix is not correct!");

        matrix.eraseColumn(1);

        QVERIFY2(matrix.getRowCapacity() == 6 && matrix.getColumnCapacity() == 8, "Erase column failed, capacity of the matrix is not correct!");

        matrix.eraseColumn(1);

        QVERIFY2(matrix.getRowCapacity() == 6 && matrix.getColumnCapacity() == 8, "Erase column failed, capacity of the matrix is not correct!");

        matrix.eraseColumn(1);

        QVERIFY2(matrix.getRowCapacity() == 6 && matrix.getColumnCapacity() == 8, "Erase column failed, capacity of the matrix is not correct!");

        matrix.eraseColumn(1);

        QVERIFY2(matrix.getRowCapacity() == 6 && matrix.getColumnCapacity() == 4, "Erase column failed, capacity of the matrix is not correct!");

        matrix.eraseColumn(1);

        QVERIFY2(matrix.getRowCapacity() == 6 && matrix.getColumnCapacity() == 2, "Erase column failed, capacity of the matrix is not correct!");

        matrix.eraseColumn(0);

        QVERIFY2(matrix.getRowCapacity() == 0 && matrix.getColumnCapacity() == 0, "Erase column failed, capacity of the matrix is not correct!");
    }
}

void CommonTests::testCatByRow()
{
    {
        IntMatrix firstMatrix{2, 2, {1, 2, 3, 4}};
        IntMatrix secondMatrix{1, 2, {5, 6}};
        IntMatrix thirdMatrix{};

        thirdMatrix.catByRow(firstMatrix, secondMatrix);

        if (thirdMatrix.getRowCapacity() != 3 || thirdMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Vertical concatenation failed, capacity of the destination matrix is not correct!");
        }

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

        firstMatrix.catByRow(firstMatrix, secondMatrix);

        if (firstMatrix.getRowCapacity() != 3 || firstMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Vertical concatenation failed, capacity of the destination matrix is not correct!");
        }

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

        secondMatrix.catByRow(firstMatrix, secondMatrix);

        if (secondMatrix.getRowCapacity() != 3 || secondMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Vertical concatenation failed, capacity of the destination matrix is not correct!");
        }

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

        firstMatrix.catByRow(firstMatrix, firstMatrix);

        if (firstMatrix.getRowCapacity() != 5 || firstMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Vertical concatenation failed, capacity of the destination matrix is not correct!");
        }

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

        secondMatrix.catByRow(firstMatrix, firstMatrix);

        if (secondMatrix.getRowCapacity() != 5 || secondMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Vertical concatenation failed, capacity of the destination matrix is not correct!");
        }

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

void CommonTests::testCapacityWithCatByRow()
{
    {
        IntMatrix firstMatrix{4, 7, 5};
        IntMatrix secondMatrix{5, 7, -2};
        firstMatrix.catByRow(firstMatrix, secondMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 11 && firstMatrix.getColumnCapacity() == 8,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};
        IntMatrix secondMatrix{5, 7, -2};

        firstMatrix.resize(4, 7, 8, 8);
        firstMatrix.catByRow(firstMatrix, secondMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 11 && firstMatrix.getColumnCapacity() == 8,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};
        IntMatrix secondMatrix{5, 7, -2};

        firstMatrix.resize(4, 7, 9, 8);
        firstMatrix.catByRow(firstMatrix, secondMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 9 && firstMatrix.getColumnCapacity() == 8,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};
        IntMatrix secondMatrix{5, 7, -2};

        firstMatrix.resize(4, 7, 10, 8);
        firstMatrix.catByRow(firstMatrix, secondMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 8,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};
        IntMatrix secondMatrix{5, 7, -2};
        secondMatrix.catByRow(firstMatrix, secondMatrix);

        QVERIFY2(secondMatrix.getRowCapacity() == 11 && secondMatrix.getColumnCapacity() == 8,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};
        IntMatrix secondMatrix{5, 7, -2};

        secondMatrix.resize(5, 7, 8, 8);
        secondMatrix.catByRow(firstMatrix, secondMatrix);

        QVERIFY2(secondMatrix.getRowCapacity() == 11 && secondMatrix.getColumnCapacity() == 8,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};
        IntMatrix secondMatrix{5, 7, -2};

        secondMatrix.resize(5, 7, 9, 8);
        secondMatrix.catByRow(firstMatrix, secondMatrix);

        QVERIFY2(secondMatrix.getRowCapacity() == 9 && secondMatrix.getColumnCapacity() == 8,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};
        IntMatrix secondMatrix{5, 7, -2};

        secondMatrix.resize(5, 7, 10, 8);
        secondMatrix.catByRow(firstMatrix, secondMatrix);

        QVERIFY2(secondMatrix.getRowCapacity() == 10 && secondMatrix.getColumnCapacity() == 8,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};

        firstMatrix.catByRow(firstMatrix, firstMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 8,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};

        firstMatrix.resize(4, 7, 7, 8);
        firstMatrix.catByRow(firstMatrix, firstMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 8,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};

        firstMatrix.resize(4, 7, 8, 8);
        firstMatrix.catByRow(firstMatrix, firstMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 8,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};

        firstMatrix.resize(4, 7, 9, 8);
        firstMatrix.catByRow(firstMatrix, firstMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 9 && firstMatrix.getColumnCapacity() == 8,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};
        IntMatrix secondMatrix{5, 7, -2};
        IntMatrix thirdMatrix{};

        thirdMatrix.catByRow(firstMatrix, secondMatrix);

        QVERIFY2(thirdMatrix.getRowCapacity() == 11 && thirdMatrix.getColumnCapacity() == 8,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};
        IntMatrix secondMatrix{5, 7, -2};
        IntMatrix thirdMatrix{7, 5, -1};

        thirdMatrix.catByRow(firstMatrix, secondMatrix);

        QVERIFY2(thirdMatrix.getRowCapacity() == 11 && thirdMatrix.getColumnCapacity() == 8,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};
        IntMatrix secondMatrix{5, 7, -2};
        IntMatrix thirdMatrix{10, 5, -1};

        thirdMatrix.catByRow(firstMatrix, secondMatrix);

        QVERIFY2(thirdMatrix.getRowCapacity() == 12 && thirdMatrix.getColumnCapacity() == 8,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};
        IntMatrix secondMatrix{5, 7, -2};
        IntMatrix thirdMatrix{6, 6, -1};

        thirdMatrix.catByRow(firstMatrix, secondMatrix);

        QVERIFY2(thirdMatrix.getRowCapacity() == 11 && thirdMatrix.getColumnCapacity() == 7,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};
        IntMatrix secondMatrix{5, 7, -2};
        IntMatrix thirdMatrix{7, 6, -1};
        thirdMatrix.resize(7, 6, 9, 7);

        thirdMatrix.catByRow(firstMatrix, secondMatrix);

        QVERIFY2(thirdMatrix.getRowCapacity() == 9 && thirdMatrix.getColumnCapacity() == 7,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};
        IntMatrix secondMatrix{5, 7, -2};
        IntMatrix thirdMatrix{7, 6, -1};
        thirdMatrix.resize(7, 6, 9, 8);

        thirdMatrix.catByRow(firstMatrix, secondMatrix);

        QVERIFY2(thirdMatrix.getRowCapacity() == 9 && thirdMatrix.getColumnCapacity() == 8,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};
        IntMatrix secondMatrix{5, 7, -2};
        IntMatrix thirdMatrix{7, 6, -1};
        thirdMatrix.resize(7, 6, 10, 7);

        thirdMatrix.catByRow(firstMatrix, secondMatrix);

        QVERIFY2(thirdMatrix.getRowCapacity() == 10 && thirdMatrix.getColumnCapacity() == 7,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{4, 7, 5};
        IntMatrix secondMatrix{5, 7, -2};
        IntMatrix thirdMatrix{7, 6, -1};
        thirdMatrix.resize(7, 6, 10, 8);

        thirdMatrix.catByRow(firstMatrix, secondMatrix);

        QVERIFY2(thirdMatrix.getRowCapacity() == 10 && thirdMatrix.getColumnCapacity() == 8,
                 "Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }
}

void CommonTests::testCatByColumn()
{
    {
        IntMatrix firstMatrix{2, 2, {1, 2, 3, 4}};
        IntMatrix secondMatrix{2, 1, {5, 6}};
        IntMatrix thirdMatrix{};

        thirdMatrix.catByColumn(firstMatrix, secondMatrix);

        if (thirdMatrix.getRowCapacity() != 2 || thirdMatrix.getColumnCapacity() != 3)
        {
            QFAIL("Horizontal concatenation failed, capacity of the destination matrix is not correct!");
        }

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

        firstMatrix.catByColumn(firstMatrix, secondMatrix);

        if (firstMatrix.getRowCapacity() != 2 || firstMatrix.getColumnCapacity() != 3)
        {
            QFAIL("Horizontal concatenation failed, capacity of the destination matrix is not correct!");
        }

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

        secondMatrix.catByColumn(firstMatrix, secondMatrix);

        if (secondMatrix.getRowCapacity() != 2 || secondMatrix.getColumnCapacity() != 3)
        {
            QFAIL("Horizontal concatenation failed, capacity of the destination matrix is not correct!");
        }

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

        firstMatrix.catByColumn(firstMatrix, firstMatrix);

        if (firstMatrix.getRowCapacity() != 2 || firstMatrix.getColumnCapacity() != 5)
        {
            QFAIL("Horizontal concatenation failed, capacity of the destination matrix is not correct!");
        }

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

        secondMatrix.catByColumn(firstMatrix, firstMatrix);

        if (secondMatrix.getRowCapacity() != 2 || secondMatrix.getColumnCapacity() != 5)
        {
            QFAIL("Horizontal concatenation failed, capacity of the destination matrix is not correct!");
        }

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

void CommonTests::testCapacityWithCatByColumn()
{
    {
        IntMatrix firstMatrix{7, 4, 5};
        IntMatrix secondMatrix{7, 5, -2};
        firstMatrix.catByColumn(firstMatrix, secondMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 11,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};
        IntMatrix secondMatrix{7, 5, -2};

        firstMatrix.resize(7, 4, 8, 8);
        firstMatrix.catByColumn(firstMatrix, secondMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 11,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};
        IntMatrix secondMatrix{7, 5, -2};

        firstMatrix.resize(7, 4, 8, 9);
        firstMatrix.catByColumn(firstMatrix, secondMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 9,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};
        IntMatrix secondMatrix{7, 5, -2};

        firstMatrix.resize(7, 4, 8, 10);
        firstMatrix.catByColumn(firstMatrix, secondMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};
        IntMatrix secondMatrix{7, 5, -2};
        secondMatrix.catByColumn(firstMatrix, secondMatrix);

        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 11,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};
        IntMatrix secondMatrix{7, 5, -2};

        secondMatrix.resize(7, 5, 8, 8);
        secondMatrix.catByColumn(firstMatrix, secondMatrix);

        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 11,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};
        IntMatrix secondMatrix{7, 5, -2};

        secondMatrix.resize(7, 5, 8, 9);
        secondMatrix.catByColumn(firstMatrix, secondMatrix);

        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 9,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};
        IntMatrix secondMatrix{7, 5, -2};

        secondMatrix.resize(7, 5, 8, 10);
        secondMatrix.catByColumn(firstMatrix, secondMatrix);

        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 10,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};

        firstMatrix.catByColumn(firstMatrix, firstMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};

        firstMatrix.resize(7, 4, 8, 7);
        firstMatrix.catByColumn(firstMatrix, firstMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};

        firstMatrix.resize(7, 4, 8, 8);
        firstMatrix.catByColumn(firstMatrix, firstMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};

        firstMatrix.resize(7, 4, 8, 9);
        firstMatrix.catByColumn(firstMatrix, firstMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 9,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};
        IntMatrix secondMatrix{7, 5, -2};
        IntMatrix thirdMatrix{};

        thirdMatrix.catByColumn(firstMatrix, secondMatrix);

        QVERIFY2(thirdMatrix.getRowCapacity() == 8 && thirdMatrix.getColumnCapacity() == 11,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};
        IntMatrix secondMatrix{7, 5, -2};
        IntMatrix thirdMatrix{5, 7, -1};

        thirdMatrix.catByColumn(firstMatrix, secondMatrix);

        QVERIFY2(thirdMatrix.getRowCapacity() == 8 && thirdMatrix.getColumnCapacity() == 11,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};
        IntMatrix secondMatrix{7, 5, -2};
        IntMatrix thirdMatrix{5, 10, -1};

        thirdMatrix.catByColumn(firstMatrix, secondMatrix);

        QVERIFY2(thirdMatrix.getRowCapacity() == 8 && thirdMatrix.getColumnCapacity() == 12,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};
        IntMatrix secondMatrix{7, 5, -2};
        IntMatrix thirdMatrix{6, 6, -1};

        thirdMatrix.catByColumn(firstMatrix, secondMatrix);

        QVERIFY2(thirdMatrix.getRowCapacity() == 7 && thirdMatrix.getColumnCapacity() == 11,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};
        IntMatrix secondMatrix{7, 5, -2};
        IntMatrix thirdMatrix{6, 7, -1};
        thirdMatrix.resize(6, 7, 7, 9);

        thirdMatrix.catByColumn(firstMatrix, secondMatrix);

        QVERIFY2(thirdMatrix.getRowCapacity() == 7 && thirdMatrix.getColumnCapacity() == 9,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};
        IntMatrix secondMatrix{7, 5, -2};
        IntMatrix thirdMatrix{6, 7, -1};
        thirdMatrix.resize(6, 7, 8, 9);

        thirdMatrix.catByColumn(firstMatrix, secondMatrix);

        QVERIFY2(thirdMatrix.getRowCapacity() == 8 && thirdMatrix.getColumnCapacity() == 9,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};
        IntMatrix secondMatrix{7, 5, -2};
        IntMatrix thirdMatrix{6, 7, -1};
        thirdMatrix.resize(6, 7, 7, 10);

        thirdMatrix.catByColumn(firstMatrix, secondMatrix);

        QVERIFY2(thirdMatrix.getRowCapacity() == 7 && thirdMatrix.getColumnCapacity() == 10,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 4, 5};
        IntMatrix secondMatrix{7, 5, -2};
        IntMatrix thirdMatrix{6, 7, -1};
        thirdMatrix.resize(6, 7, 8, 10);

        thirdMatrix.catByColumn(firstMatrix, secondMatrix);

        QVERIFY2(thirdMatrix.getRowCapacity() == 8 && thirdMatrix.getColumnCapacity() == 10,
                 "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }
}

void CommonTests::testSplitByRow()
{
    {
        IntMatrix firstMatrix{3, 2, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{};

        firstMatrix.splitByRow(secondMatrix, thirdMatrix, 2);

        if (secondMatrix.getRowCapacity() != 2 || secondMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Vertical split failed, capacity of the first destination matrix is not correct!");
        }

        if (secondMatrix.getNrOfRows() != 2 || secondMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Vertical split failed, number of rows or columns of the first destination matrix is not correct!");
        }

        if (thirdMatrix.getRowCapacity() != 1 || thirdMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Vertical split failed, capacity of the second destination matrix is not correct!");
        }

        if (thirdMatrix.getNrOfRows() != 1 || thirdMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Vertical split failed, number of rows or columns of the second destination matrix is not correct!");
        }

        QVERIFY2(secondMatrix.at(0, 0) == 1 &&
                 secondMatrix.at(0, 1) == 2 &&
                 secondMatrix.at(1, 0) == 3 &&
                 secondMatrix.at(1, 1) == 4,

                 "Vertical split failed, first destination matrix has incorrect values!");

        QVERIFY2(thirdMatrix.at(0, 0) == 5 &&
                 thirdMatrix.at(0, 1) == 6,

                 "Vertical split failed, second destination matrix has incorrect values!");
    }

    {
        IntMatrix firstMatrix{3, 2, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{};

        firstMatrix.splitByRow(firstMatrix, secondMatrix, 2);

        if (firstMatrix.getRowCapacity() != 3 || firstMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Vertical split failed, capacity of the first destination matrix is not correct!");
        }

        if (firstMatrix.getNrOfRows() != 2 || firstMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Vertical split failed, number of rows or columns of the first destination matrix is not correct!");
        }

        if (secondMatrix.getRowCapacity() != 1 || secondMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Vertical split failed, capacity of the second destination matrix is not correct!");
        }

        if (secondMatrix.getNrOfRows() != 1 || secondMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Vertical split failed, number of rows or columns of the second destination matrix is not correct!");
        }

        QVERIFY2(firstMatrix.at(0, 0) == 1 &&
                 firstMatrix.at(0, 1) == 2 &&
                 firstMatrix.at(1, 0) == 3 &&
                 firstMatrix.at(1, 1) == 4,

                 "Vertical split failed, first destination matrix has incorrect values!");

        QVERIFY2(secondMatrix.at(0, 0) == 5 &&
                 secondMatrix.at(0, 1) == 6,

                 "Vertical split failed, second destination matrix has incorrect values!");
    }

    {
        IntMatrix firstMatrix{3, 2, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{};

        firstMatrix.splitByRow(secondMatrix, firstMatrix, 2);

        if (secondMatrix.getRowCapacity() != 2 || secondMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Vertical split failed, capacity of the first destination matrix is not correct!");
        }

        if (secondMatrix.getNrOfRows() != 2 || secondMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Vertical split failed, number of rows or columns of the first destination matrix is not correct!");
        }

        if (firstMatrix.getRowCapacity() != 3 || firstMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Vertical split failed, capacity of the second destination matrix is not correct!");
        }

        if (firstMatrix.getNrOfRows() != 1 || firstMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Vertical split failed, number of rows or columns of the second destination matrix is not correct!");
        }

        QVERIFY2(secondMatrix.at(0, 0) == 1 &&
                 secondMatrix.at(0, 1) == 2 &&
                 secondMatrix.at(1, 0) == 3 &&
                 secondMatrix.at(1, 1) == 4,

                 "Vertical split failed, first destination matrix has incorrect values!");

        QVERIFY2(firstMatrix.at(0, 0) == 5 &&
                 firstMatrix.at(0, 1) == 6,

                 "Vertical split failed, second destination matrix has incorrect values!");
    }
}

void CommonTests::testCapacityWithSplitByRow()
{
    {
        IntMatrix firstMatrix{15, 17, -3};
        IntMatrix secondMatrix{};
        firstMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{15, 17, -3};
        IntMatrix secondMatrix{5, 8, 2};
        firstMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{15, 17, -3};
        IntMatrix secondMatrix{5, 8, 2};
        secondMatrix.resize(5, 8, 6, 17);
        firstMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 17,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{15, 17, -3};
        IntMatrix secondMatrix{5, 8, 2};
        secondMatrix.resize(5, 8, 6, 18);
        firstMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 18,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{15, 17, -3};
        IntMatrix secondMatrix{6, 15, 2};
        firstMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 7 && secondMatrix.getColumnCapacity() == 18,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{15, 17, -3};
        IntMatrix secondMatrix{7, 17, 2};
        firstMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{15, 17, -3};
        secondMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{5, 8, 2};
        IntMatrix secondMatrix{15, 17, -3};
        secondMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{6, 8, 2};
        IntMatrix secondMatrix{15, 17, -3};
        firstMatrix.resize(6, 8, 7, 17);
        secondMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 17,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{6, 8, 2};
        IntMatrix secondMatrix{15, 17, -3};
        firstMatrix.resize(6, 8, 7, 18);
        secondMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 18,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 15, 2};
        IntMatrix secondMatrix{15, 17, -3};
        secondMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 18,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{8, 17, 2};
        IntMatrix secondMatrix{15, 17, -3};
        secondMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{15, 17, -3};
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{5, 8, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{15, 17, -3};
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{6, 8, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{15, 17, -3};
        firstMatrix.resize(6, 8, 7, 17);
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 17,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{6, 8, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{15, 17, -3};
        firstMatrix.resize(6, 8, 7, 18);
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 18,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 15, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{15, 17, -3};
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 18,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{8, 17, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{15, 17, -3};
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{5, 8, 2};
        IntMatrix thirdMatrix{15, 17, -3};
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{5, 8, 2};
        IntMatrix thirdMatrix{15, 17, -3};
        secondMatrix.resize(5, 8, 6, 17);
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 17,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{5, 8, 2};
        IntMatrix thirdMatrix{15, 17, -3};
        secondMatrix.resize(5, 8, 6, 18);
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 18,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{6, 15, 2};
        IntMatrix thirdMatrix{15, 17, -3};
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 7 && secondMatrix.getColumnCapacity() == 18,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{7, 17, 2};
        IntMatrix thirdMatrix{15, 17, -3};
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{8, 17, 2};
        IntMatrix secondMatrix{7, 17, 2};
        IntMatrix thirdMatrix{15, 17, -3};
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 10 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{15, 17, -3};
        IntMatrix secondMatrix{};
        firstMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 10 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{15, 17, -3};
        IntMatrix secondMatrix{6, 8, 2};
        firstMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 10 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{15, 17, -3};
        IntMatrix secondMatrix{6, 8, 2};
        secondMatrix.resize(6, 8, 7, 17);
        firstMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 10 && secondMatrix.getColumnCapacity() == 17,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{15, 17, -3};
        IntMatrix secondMatrix{6, 8, 2};
        secondMatrix.resize(6, 8, 7, 18);
        firstMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 10 && secondMatrix.getColumnCapacity() == 18,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{15, 17, -3};
        IntMatrix secondMatrix{7, 15, 2};
        firstMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 18,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{15, 17, -3};
        IntMatrix secondMatrix{8, 17, 2};
        firstMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 10 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{15, 17, -3};
        secondMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{5, 8, 2};
        IntMatrix secondMatrix{15, 17, -3};
        secondMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{5, 8, 2};
        IntMatrix secondMatrix{15, 17, -3};
        firstMatrix.resize(5, 8, 6, 17);
        secondMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 17,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{5, 8, 2};
        IntMatrix secondMatrix{15, 17, -3};
        firstMatrix.resize(5, 8, 6, 18);
        secondMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 18,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{6, 15, 2};
        IntMatrix secondMatrix{15, 17, -3};
        secondMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 7 && firstMatrix.getColumnCapacity() == 18,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 17, 2};
        IntMatrix secondMatrix{15, 17, -3};
        secondMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{15, 17, -3};
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 10 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{5, 8, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{15, 17, -3};
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 10 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{5, 8, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{15, 17, -3};
        firstMatrix.resize(5, 8, 6, 17);
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 17,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 10 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{5, 8, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{15, 17, -3};
        firstMatrix.resize(5, 8, 6, 18);
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 18,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 10 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{6, 15, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{15, 17, -3};
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 7 && firstMatrix.getColumnCapacity() == 18,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 10 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 17, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{15, 17, -3};
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 10 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{6, 8, 2};
        IntMatrix thirdMatrix{15, 17, -3};
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 10 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{6, 8, 2};
        IntMatrix thirdMatrix{15, 17, -3};
        secondMatrix.resize(6, 8, 7, 17);
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 10 && secondMatrix.getColumnCapacity() == 17,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{6, 8, 2};
        IntMatrix thirdMatrix{15, 17, -3};
        secondMatrix.resize(6, 8, 7, 18);
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 10 && secondMatrix.getColumnCapacity() == 18,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{7, 15, 2};
        IntMatrix thirdMatrix{15, 17, -3};
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 8 && secondMatrix.getColumnCapacity() == 18,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{8, 17, 2};
        IntMatrix thirdMatrix{15, 17, -3};
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 10 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{7, 17, 2};
        IntMatrix secondMatrix{8, 17, 2};
        IntMatrix thirdMatrix{15, 17, -3};
        thirdMatrix.splitByRow(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 8 && firstMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 10 && secondMatrix.getColumnCapacity() == 21,
                 "Vertical split failed, capacity of the second destination matrix is not correct!");
    }
}

void CommonTests::testSplitByColumn()
{
    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{};

        firstMatrix.splitByColumn(secondMatrix, thirdMatrix, 2);

        if (secondMatrix.getRowCapacity() != 2 || secondMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Horizontal split failed, capacity of the first destination matrix is not correct!");
        }

        if (secondMatrix.getNrOfRows() != 2 || secondMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Horizontal split failed, number of rows or columns of the first destination matrix is not correct!");
        }

        if (thirdMatrix.getRowCapacity() != 2 || thirdMatrix.getColumnCapacity() != 1)
        {
            QFAIL("Horizontal split failed, capacity of the second destination matrix is not correct!");
        }

        if (thirdMatrix.getNrOfRows() != 2 || thirdMatrix.getNrOfColumns() != 1)
        {
            QFAIL("Horizontal split failed, number of rows or columns of the second destination matrix is not correct!");
        }

        QVERIFY2(secondMatrix.at(0, 0) == 1 &&
                 secondMatrix.at(0, 1) == 2 &&
                 secondMatrix.at(1, 0) == 4 &&
                 secondMatrix.at(1, 1) == 5,

                 "Horizontal split failed, first destination matrix has incorrect values!");

        QVERIFY2(thirdMatrix.at(0, 0) == 3 &&
                 thirdMatrix.at(1, 0) == 6,

                 "Horizontal split failed, second destination matrix has incorrect values!");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{};

        firstMatrix.splitByColumn(firstMatrix, secondMatrix, 2);

        if (firstMatrix.getRowCapacity() != 2 || firstMatrix.getColumnCapacity() != 3)
        {
            QFAIL("Horizontal split failed, capacity of the first destination matrix is not correct!");
        }

        if (firstMatrix.getNrOfRows() != 2 || firstMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Horizontal split failed, number of rows or columns of the first destination matrix is not correct!");
        }

        if (secondMatrix.getRowCapacity() != 2 || secondMatrix.getColumnCapacity() != 1)
        {
            QFAIL("Horizontal split failed, capacity of the second destination matrix is not correct!");
        }

        if (secondMatrix.getNrOfRows() != 2 || secondMatrix.getNrOfColumns() != 1)
        {
            QFAIL("Horizontal split failed, number of rows or columns of the second destination matrix is not correct!");
        }

        QVERIFY2(firstMatrix.at(0, 0) == 1 &&
                 firstMatrix.at(0, 1) == 2 &&
                 firstMatrix.at(1, 0) == 4 &&
                 firstMatrix.at(1, 1) == 5,

                 "Horizontal split failed, first destination matrix has incorrect values!");

        QVERIFY2(secondMatrix.at(0, 0) == 3 &&
                 secondMatrix.at(1, 0) == 6,

                 "Horizontal split failed, second destination matrix has incorrect values!");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{};

        firstMatrix.splitByColumn(secondMatrix, firstMatrix, 2);

        if (secondMatrix.getRowCapacity() != 2 || secondMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Horizontal split failed, capacity of the first destination matrix is not correct!");
        }

        if (secondMatrix.getNrOfRows() != 2 || secondMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Horizontal split failed, number of rows or columns of the first destination matrix is not correct!");
        }

        if (firstMatrix.getRowCapacity() != 2 || firstMatrix.getColumnCapacity() != 3)
        {
            QFAIL("Horizontal split failed, capacity of the second destination matrix is not correct!");
        }

        if (firstMatrix.getNrOfRows() != 2 || firstMatrix.getNrOfColumns() != 1)
        {
            QFAIL("Horizontal split failed, number of rows or columns of the second destination matrix is not correct!");
        }

        QVERIFY2(secondMatrix.at(0, 0) == 1 &&
                 secondMatrix.at(0, 1) == 2 &&
                 secondMatrix.at(1, 0) == 4 &&
                 secondMatrix.at(1, 1) == 5,

                 "Horizontal split failed, first destination matrix has incorrect values!");

        QVERIFY2(firstMatrix.at(0, 0) == 3 &&
                 firstMatrix.at(1, 0) == 6,

                 "Horizontal split failed, second destination matrix has incorrect values!");
    }
}

void CommonTests::testCapacityWithSplitByColumn()
{
    {
        IntMatrix firstMatrix{17, 15, -3};
        IntMatrix secondMatrix{};
        firstMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{17, 15, -3};
        IntMatrix secondMatrix{8, 5, 2};
        firstMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{17, 15, -3};
        IntMatrix secondMatrix{8, 5, 2};
        secondMatrix.resize(8, 5, 17, 6);
        firstMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 17 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{17, 15, -3};
        IntMatrix secondMatrix{8, 5, 2};
        secondMatrix.resize(8, 5, 18, 6);
        firstMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{17, 15, -3};
        IntMatrix secondMatrix{15, 6, 2};
        firstMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 7,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{17, 15, -3};
        IntMatrix secondMatrix{17, 7, 2};
        firstMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{17, 15, -3};
        secondMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{8, 5, 2};
        IntMatrix secondMatrix{17, 15, -3};
        secondMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{8, 6, 2};
        IntMatrix secondMatrix{17, 15, -3};
        firstMatrix.resize(8, 6, 17, 7);
        secondMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 17 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{8, 6, 2};
        IntMatrix secondMatrix{17, 15, -3};
        firstMatrix.resize(8, 6, 18, 7);
        secondMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{15, 7, 2};
        IntMatrix secondMatrix{17, 15, -3};
        secondMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{17, 8, 2};
        IntMatrix secondMatrix{17, 15, -3};
        secondMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{17, 15, -3};
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{8, 5, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{17, 15, -3};
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{8, 6, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{17, 15, -3};
        firstMatrix.resize(8, 6, 17, 7);
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 17 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{8, 6, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{17, 15, -3};
        firstMatrix.resize(8, 6, 18, 7);
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{15, 7, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{17, 15, -3};
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{17, 8, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{17, 15, -3};
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{8, 5, 2};
        IntMatrix thirdMatrix{17, 15, -3};
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{8, 5, 2};
        IntMatrix thirdMatrix{17, 15, -3};
        secondMatrix.resize(8, 5, 17, 6);
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 17 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{8, 5, 2};
        IntMatrix thirdMatrix{17, 15, -3};
        secondMatrix.resize(8, 5, 18, 6);
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{15, 6, 2};
        IntMatrix thirdMatrix{17, 15, -3};
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 7,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{17, 7, 2};
        IntMatrix thirdMatrix{17, 15, -3};
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{17, 8, 2};
        IntMatrix secondMatrix{17, 7, 2};
        IntMatrix thirdMatrix{17, 15, -3};
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 8);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{17, 15, -3};
        IntMatrix secondMatrix{};
        firstMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{17, 15, -3};
        IntMatrix secondMatrix{8, 6, 2};
        firstMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{17, 15, -3};
        IntMatrix secondMatrix{8, 6, 2};
        secondMatrix.resize(8, 6, 17, 7);
        firstMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 17 && secondMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{17, 15, -3};
        IntMatrix secondMatrix{8, 6, 2};
        secondMatrix.resize(8, 6, 18, 7);
        firstMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{17, 15, -3};
        IntMatrix secondMatrix{15, 7, 2};
        firstMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{17, 15, -3};
        IntMatrix secondMatrix{17, 8, 2};
        firstMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{17, 15, -3};
        secondMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{8, 5, 2};
        IntMatrix secondMatrix{17, 15, -3};
        secondMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{8, 5, 2};
        IntMatrix secondMatrix{17, 15, -3};
        firstMatrix.resize(8, 5, 17, 6);
        secondMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 17 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{8, 5, 2};
        IntMatrix secondMatrix{17, 15, -3};
        firstMatrix.resize(8, 5, 18, 6);
        secondMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{15, 6, 2};
        IntMatrix secondMatrix{17, 15, -3};
        secondMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 7,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{17, 7, 2};
        IntMatrix secondMatrix{17, 15, -3};
        secondMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 18,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{17, 15, -3};
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{8, 5, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{17, 15, -3};
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{8, 5, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{17, 15, -3};
        firstMatrix.resize(8, 5, 17, 6);
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 17 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{8, 5, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{17, 15, -3};
        firstMatrix.resize(8, 5, 18, 6);
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{15, 6, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{17, 15, -3};
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 18 && firstMatrix.getColumnCapacity() == 7,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{17, 7, 2};
        IntMatrix secondMatrix{};
        IntMatrix thirdMatrix{17, 15, -3};
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{8, 6, 2};
        IntMatrix thirdMatrix{17, 15, -3};
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{8, 6, 2};
        IntMatrix thirdMatrix{17, 15, -3};
        secondMatrix.resize(8, 6, 17, 7);
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 17 && secondMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{8, 6, 2};
        IntMatrix thirdMatrix{17, 15, -3};
        secondMatrix.resize(8, 6, 18, 7);
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{15, 7, 2};
        IntMatrix thirdMatrix{17, 15, -3};
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 18 && secondMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{17, 8, 2};
        IntMatrix thirdMatrix{17, 15, -3};
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }

    {
        IntMatrix firstMatrix{17, 7, 2};
        IntMatrix secondMatrix{17, 8, 2};
        IntMatrix thirdMatrix{17, 15, -3};
        thirdMatrix.splitByColumn(firstMatrix, secondMatrix, 7);

        QVERIFY2(firstMatrix.getRowCapacity() == 21 && firstMatrix.getColumnCapacity() == 8,
                 "Horizontal split failed, capacity of the first destination matrix is not correct!");
        QVERIFY2(secondMatrix.getRowCapacity() == 21 && secondMatrix.getColumnCapacity() == 10,
                 "Horizontal split failed, capacity of the second destination matrix is not correct!");
    }
}

void CommonTests::testSwapMatrixes()
{
    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, 9, 10, 11, 12}};

        std::swap(firstMatrix, secondMatrix);

        if (firstMatrix.getNrOfRows() != 3 || firstMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Incorrect number of rows and/or columns in the first matrix after swap");
        }

        if (firstMatrix.getRowCapacity() != 3 || firstMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Incorrect capacity of the first matrix after swap");
        }

        if (secondMatrix.getNrOfRows() != 2 || secondMatrix.getNrOfColumns() != 3)
        {
            QFAIL("Incorrect number of rows and/or columns in the second matrix after swap");
        }

        if (secondMatrix.getNrOfRows() != 2 || secondMatrix.getNrOfColumns() != 3)
        {
            QFAIL("Incorrect capacity of the second matrix after swap");
        }

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

    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{};

        std::swap(firstMatrix, secondMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 0 && firstMatrix.getColumnCapacity() == 0, "Incorrect capacity of the first matrix after swap");
        QVERIFY2(firstMatrix.getNrOfRows() == 0 && firstMatrix.getNrOfColumns() == 0, "Incorrect number of rows and/or columns in the first matrix after swap");

        if (secondMatrix.getRowCapacity() != 2 || secondMatrix.getColumnCapacity() != 3)
        {
            QFAIL("Incorrect capacity of the second matrix after swap");
        }

        if (secondMatrix.getNrOfRows() != 2 || secondMatrix.getNrOfColumns() != 3)
        {
            QFAIL("Incorrect number of rows and/or columns in the second matrix after swap");
        }

        QVERIFY2(secondMatrix.at(0, 0) == 1 &&
                 secondMatrix.at(0, 1) == 2 &&
                 secondMatrix.at(0, 2) == 3 &&
                 secondMatrix.at(1, 0) == 4 &&
                 secondMatrix.at(1, 1) == 5 &&
                 secondMatrix.at(1, 2) == 6,

                 "Second matrix has incorrect element values after swap");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{};

        std::swap(firstMatrix, secondMatrix);

        QVERIFY2(firstMatrix.getRowCapacity() == 0 && firstMatrix.getColumnCapacity() == 0, "Incorrect capacity of the first matrix after swap");
        QVERIFY2(firstMatrix.getNrOfRows() == 0 && firstMatrix.getNrOfColumns() == 0, "Incorrect number of rows and/or columns in the first matrix after swap");
        QVERIFY2(secondMatrix.getRowCapacity() == 0 && secondMatrix.getColumnCapacity() == 0, "Incorrect capacity of the second matrix after swap");
        QVERIFY2(secondMatrix.getNrOfRows() == 0 && secondMatrix.getNrOfColumns() == 0, "Incorrect number of rows and/or columns in the second matrix after swap");
    }
}

void CommonTests::testSwapItems()
{
    {
        IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};

        matrix.swapItems(1, 2, matrix, 0, 1);

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 6 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 2,

                 "Items are incorrectly swapped within same matrix");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, 9, 10, 11, 12}};

        firstMatrix.swapItems(1, 2, secondMatrix, 2, 0);

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
}

void CommonTests::testSwapRows()
{
    {
        IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.swapRows(0, matrix, 2);

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

    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{4, 3, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}};

        firstMatrix.swapRows(0, secondMatrix, 3);

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
}

void CommonTests::testSwapColumns()
{
    {
        IntMatrix matrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        matrix.swapColumns(0, matrix, 2);

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

    {
        IntMatrix firstMatrix{3, 2, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}};

        firstMatrix.swapColumns(0, secondMatrix, 3);

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
}

void CommonTests::testSwapRowColumn()
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

void CommonTests::testSetAllItemsToValue()
{
    IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};
    matrix.setAllItemsToValue(7);

    QVERIFY2(matrix.at(0, 0) == 7 &&
             matrix.at(0, 1) == 7 &&
             matrix.at(0, 2) == 7 &&
             matrix.at(1, 0) == 7 &&
             matrix.at(1, 1) == 7 &&
             matrix.at(1, 2) == 7,

             "Setting all matrix items to same value failed, matrix has incorrect values!");
}

void CommonTests::testCopy()
{
    {
        IntMatrix destMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        IntMatrix srcMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}};
        destMatrix.copy(srcMatrix, 3, 2, 2, 1, 1, 0);

        QVERIFY2(destMatrix.at(0, 0) == 1 &&
                 destMatrix.at(0, 1) == 2 &&
                 destMatrix.at(0, 2) == 3 &&
                 destMatrix.at(1, 0) == 22 &&
                 destMatrix.at(1, 1) == 23 &&
                 destMatrix.at(1, 2) == 6 &&
                 destMatrix.at(2, 0) == 26 &&
                 destMatrix.at(2, 1) == 27 &&
                 destMatrix.at(2, 2) == 9 &&
                 destMatrix.at(3, 0) == 30 &&
                 destMatrix.at(3, 1) == 31 &&
                 destMatrix.at(3, 2) == 12,

                 "Copying items failed, destination matrix has incorrect values!");
    }

    {
        IntMatrix destMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        IntMatrix srcMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}};
        destMatrix.copy(srcMatrix, 0, 2, 2, 1, 1, 0);

        QVERIFY2(destMatrix.at(0, 0) == 1 &&
                 destMatrix.at(0, 1) == 2 &&
                 destMatrix.at(0, 2) == 3 &&
                 destMatrix.at(1, 0) == 4 &&
                 destMatrix.at(1, 1) == 5 &&
                 destMatrix.at(1, 2) == 6 &&
                 destMatrix.at(2, 0) == 7 &&
                 destMatrix.at(2, 1) == 8 &&
                 destMatrix.at(2, 2) == 9 &&
                 destMatrix.at(3, 0) == 10 &&
                 destMatrix.at(3, 1) == 11 &&
                 destMatrix.at(3, 2) == 12,

                 "Copying items failed, destination matrix has incorrect values!");
    }

    {
        IntMatrix destMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        IntMatrix srcMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}};
        destMatrix.copy(srcMatrix, 3, 0, 2, 1, 1, 0);

        QVERIFY2(destMatrix.at(0, 0) == 1 &&
                 destMatrix.at(0, 1) == 2 &&
                 destMatrix.at(0, 2) == 3 &&
                 destMatrix.at(1, 0) == 4 &&
                 destMatrix.at(1, 1) == 5 &&
                 destMatrix.at(1, 2) == 6 &&
                 destMatrix.at(2, 0) == 7 &&
                 destMatrix.at(2, 1) == 8 &&
                 destMatrix.at(2, 2) == 9 &&
                 destMatrix.at(3, 0) == 10 &&
                 destMatrix.at(3, 1) == 11 &&
                 destMatrix.at(3, 2) == 12,

                 "Copying items failed, destination matrix has incorrect values!");
    }

    {
        IntMatrix destMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
        IntMatrix srcMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}};
        destMatrix.copy(srcMatrix, 0, 0, 2, 1, 1, 0);

        QVERIFY2(destMatrix.at(0, 0) == 1 &&
                 destMatrix.at(0, 1) == 2 &&
                 destMatrix.at(0, 2) == 3 &&
                 destMatrix.at(1, 0) == 4 &&
                 destMatrix.at(1, 1) == 5 &&
                 destMatrix.at(1, 2) == 6 &&
                 destMatrix.at(2, 0) == 7 &&
                 destMatrix.at(2, 1) == 8 &&
                 destMatrix.at(2, 2) == 9 &&
                 destMatrix.at(3, 0) == 10 &&
                 destMatrix.at(3, 1) == 11 &&
                 destMatrix.at(3, 2) == 12,

                 "Copying items failed, destination matrix has incorrect values!");
    }
}

QTEST_APPLESS_MAIN(CommonTests)

#include "tst_commontests.moc"
