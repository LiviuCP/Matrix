#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrix)

class ConstructionAndAssignmentTests : public QObject
{
    Q_OBJECT

private slots:
    void testDefaultConstructor();
    void testInitListConstructor();
    void testIdenticalMatrixConstructor();
    void testDiagonalMatrixConstructor();
    void testCopyConstructor();
    void testMoveConstructor();
    void testCopyAssignmentOperator();
    void testMoveAssignmentOperator();
};

void ConstructionAndAssignmentTests::testDefaultConstructor()
{
    IntMatrix matrix{};

    QVERIFY2(matrix.getNrOfRows() == 0 &&
             matrix.getNrOfColumns() == 0, "Default constructor initialized matrix with wrong number of rows and columns");

    QVERIFY2(matrix.getRowCapacity() == 0 &&
             matrix.getColumnCapacity() == 0, "Default constructor initialized matrix with wrong capacity");
}

void ConstructionAndAssignmentTests::testInitListConstructor()
{
    IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};

    if (matrix.getRowCapacity() != 2 || matrix.getColumnCapacity() != 3)
    {
        QFAIL("Init list constructor initialized matrix with wrong capacity");
    }
    else if (matrix.getNrOfRows() != 2 || matrix.getNrOfColumns() != 3)
    {
        QFAIL("Init list constructor initialized matrix with wrong number of rows and columns");
    }
    else
    {
        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6, "Matrix elements have not been correctly initialized by the init list constructor");
    }
}

void ConstructionAndAssignmentTests::testIdenticalMatrixConstructor()
{
    IntMatrix matrix{3, 2, 4};

    if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 2)
    {
        QFAIL("Identical matrix constructor initialized matrix with wrong capacity");
    }
    else if (matrix.getNrOfRows() != 3 || matrix.getNrOfColumns() != 2)
    {
        QFAIL("Identical matrix constructor initialized matrix with wrong number of rows and columns");
    }
    else
    {
        QVERIFY2(matrix.at(0, 0) == 4 &&
                 matrix.at(0, 1) == 4 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 4 &&
                 matrix.at(2, 0) == 4 &&
                 matrix.at(2, 1) == 4, "Matrix elements have not been correctly initialized by the identical matrix constructor");
    }
}

void ConstructionAndAssignmentTests::testDiagonalMatrixConstructor()
{
    IntMatrix matrix{3, std::pair<int, int>{2, 1}};

    if (matrix.getRowCapacity() != 3 || matrix.getColumnCapacity() != 3)
    {
        QFAIL("Diagonal matrix constructor initialized matrix with wrong capacity");
    }
    else if (matrix.getNrOfRows() != 3 || matrix.getNrOfColumns() != 3)
    {
        QFAIL("Diagonal matrix constructor initialized matrix with wrong number of rows and columns");
    }
    else
    {
        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 2 &&
                 matrix.at(1, 0) == 2 &&
                 matrix.at(1, 1) == 1 &&
                 matrix.at(1, 2) == 2 &&
                 matrix.at(2, 0) == 2 &&
                 matrix.at(2, 1) == 2 &&
                 matrix.at(2, 2) == 1, "Matrix elements have not been correctly initialized by the diagonal matrix constructor");
    }
}

void ConstructionAndAssignmentTests::testCopyConstructor()
{
    {
        IntMatrix srcMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix destMatrix{srcMatrix};

        if (destMatrix.getRowCapacity() != 2 || destMatrix.getColumnCapacity() != 3)
        {
            QFAIL("Copy constructor initialized matrix with wrong capacity");
        }
        else if (destMatrix.getNrOfRows() != 2 || destMatrix.getNrOfColumns() != 3)
        {
            QFAIL("Copy constructor initialized matrix with wrong number of rows and columns");
        }
        else
        {
            QVERIFY2(destMatrix.at(0, 0) == 1 &&
                     destMatrix.at(0, 1) == 2 &&
                     destMatrix.at(0, 2) == 3 &&
                     destMatrix.at(1, 0) == 4 &&
                     destMatrix.at(1, 1) == 5 &&
                     destMatrix.at(1, 2) == 6, "Matrix elements have not been correctly initialized by the copy constructor");
        }
    }

    {
        IntMatrix srcMatrix{};
        IntMatrix destMatrix{srcMatrix};

        QVERIFY2(destMatrix.getRowCapacity() == 0 &&
                 destMatrix.getColumnCapacity() == 0, "Copy constructor initialized matrix with wrong capacity");

        QVERIFY2(destMatrix.getNrOfRows() == 0 &&
                 destMatrix.getNrOfColumns() == 0, "Copy constructor initialized matrix with wrong number of rows and columns");
    }
}

void ConstructionAndAssignmentTests::testMoveConstructor()
{
    IntMatrix srcMatrix{2, 3, {1, 2, 3, 4, 5, 6} };
    IntMatrix destMatrix{std::move(srcMatrix)};

    if (destMatrix.getRowCapacity() != 2 || destMatrix.getColumnCapacity() != 3)
    {
        QFAIL("Move constructor initialized matrix with wrong capacity");
    }
    else if (destMatrix.getNrOfRows() != 2 || destMatrix.getNrOfColumns() != 3)
    {
        QFAIL("Move constructor initialized matrix with wrong number of rows and columns");
    }
    else
    {
        QVERIFY2(destMatrix.at(0, 0) == 1 &&
                 destMatrix.at(0, 1) == 2 &&
                 destMatrix.at(0, 2) == 3 &&
                 destMatrix.at(1, 0) == 4 &&
                 destMatrix.at(1, 1) == 5 &&
                 destMatrix.at(1, 2) == 6, "Matrix elements have not been correctly initialized by the move constructor");

        QVERIFY2(srcMatrix.getRowCapacity() == 0 &&
                 srcMatrix.getColumnCapacity() == 0, "Move constructor set the wrong number of rows and columns to the source matrix");

        QVERIFY2(srcMatrix.getNrOfRows() == 0 &&
                 srcMatrix.getNrOfColumns() == 0, "Move constructor set the wrong number of rows and columns to the source matrix");
    }
}

void ConstructionAndAssignmentTests::testCopyAssignmentOperator()
{
    {
        IntMatrix srcMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix destMatrix{3, 2, {7, 8, 9, 10, 11, 12}};

        destMatrix = srcMatrix;

        if (destMatrix.getRowCapacity() != 2 || destMatrix.getColumnCapacity() != 3)
        {
            QFAIL("Copy assignment failed, capacity of the destination matrix is not correct!");
        }
        else if (destMatrix.getNrOfRows() != 2 || destMatrix.getNrOfColumns() != 3)
        {
            QFAIL("Copy assignment failed, number of rows or columns of the destination matrix is not correct!");
        }
        else
        {
            QVERIFY2(destMatrix.at(0, 0) == 1 &&
                     destMatrix.at(0, 1) == 2 &&
                     destMatrix.at(0, 2) == 3 &&
                     destMatrix.at(1, 0) == 4 &&
                     destMatrix.at(1, 1) == 5 &&
                     destMatrix.at(1, 2) == 6, "Copy assignment failed, the destination matrix doesn't have the right values!");
        }
    }

    {
        IntMatrix srcMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix destMatrix{};

        destMatrix = srcMatrix;

        if (destMatrix.getRowCapacity() != 2 || destMatrix.getColumnCapacity() != 3)
        {
            QFAIL("Copy assignment failed, capacity of the destination matrix is not correct!");
        }
        else if (destMatrix.getNrOfRows() != 2 || destMatrix.getNrOfColumns() != 3)
        {
            QFAIL("Copy assignment failed, number of rows or columns of the destination matrix is not correct!");
        }
        else
        {
            QVERIFY2(destMatrix.at(0, 0) == 1 &&
                     destMatrix.at(0, 1) == 2 &&
                     destMatrix.at(0, 2) == 3 &&
                     destMatrix.at(1, 0) == 4 &&
                     destMatrix.at(1, 1) == 5 &&
                     destMatrix.at(1, 2) == 6, "Copy assignment failed, the destination matrix doesn't have the right values!");
        }
    }

    {
        IntMatrix srcMatrix{};
        IntMatrix destMatrix{3, 2, {7, 8, 9, 10, 11, 12}};

        destMatrix = srcMatrix;

        QVERIFY2(destMatrix.getRowCapacity() == 0 &&
                 destMatrix.getColumnCapacity() == 0, "Copy assignment failed, capacity of the destination matrix is not correct!");

        QVERIFY2(destMatrix.getNrOfRows() == 0 &&
                 destMatrix.getNrOfColumns() == 0, "Copy assignment failed, number of rows or columns of the destination matrix is not correct!");
    }

    {
        IntMatrix srcMatrix{};
        IntMatrix destMatrix{};

        destMatrix = srcMatrix;

        QVERIFY2(destMatrix.getRowCapacity() == 0 &&
                 destMatrix.getColumnCapacity() == 0, "Copy assignment failed, capacity of the destination matrix is not correct!");

        QVERIFY2(destMatrix.getNrOfRows() == 0 &&
                 destMatrix.getNrOfColumns() == 0, "Copy assignment failed, number of rows or columns of the destination matrix is not correct!");
    }

    {
        IntMatrix srcMatrix{3, 4, 7};
        IntMatrix destMatrix{2, 3, 8};

        destMatrix = srcMatrix;

        if (destMatrix.getRowCapacity() != 3 || destMatrix.getColumnCapacity() != 5)
        {
            QFAIL("Copy assignment failed, capacity of the destination matrix is not correct!");
        }
        else if (destMatrix.getNrOfRows() != 3 || destMatrix.getNrOfColumns() != 4)
        {
            QFAIL("Copy assignment failed, number of rows or columns of the destination matrix is not correct!");
        }
        else
        {
            for (int row{0}; row < destMatrix.getNrOfRows(); ++row)
            {
                for (int col{0}; col < destMatrix.getNrOfColumns(); ++col)
                {
                    if (destMatrix.at(row, col) != 7)
                    {
                        QFAIL("Copy assignment failed, the destination matrix doesn't have the right values!");
                        break;
                    }
                }
            }
        }
    }

    {
        IntMatrix srcMatrix{4, 3, 9};
        IntMatrix destMatrix{2, 3, 8};

        destMatrix = srcMatrix;

        if (destMatrix.getRowCapacity() != 5 || destMatrix.getColumnCapacity() != 3)
        {
            QFAIL("Copy assignment failed, capacity of the destination matrix is not correct!");
        }
        else if (destMatrix.getNrOfRows() != 4 || destMatrix.getNrOfColumns() != 3)
        {
            QFAIL("Copy assignment failed, number of rows or columns of the destination matrix is not correct!");
        }
        else
        {
            for (int row{0}; row < destMatrix.getNrOfRows(); ++row)
            {
                for (int col{0}; col < destMatrix.getNrOfColumns(); ++col)
                {
                    if (destMatrix.at(row, col) != 9)
                    {
                        QFAIL("Copy assignment failed, the destination matrix doesn't have the right values!");
                        break;
                    }
                }
            }
        }
    }

    {
        IntMatrix srcMatrix{20, 20, 11};
        IntMatrix destMatrix{2, 3, 8};

        destMatrix = srcMatrix;

        if (destMatrix.getRowCapacity() != 25 || destMatrix.getColumnCapacity() != 25)
        {
            QFAIL("Copy assignment failed, capacity of the destination matrix is not correct!");
        }
        else if (destMatrix.getNrOfRows() != 20 || destMatrix.getNrOfColumns() != 20)
        {
            QFAIL("Copy assignment failed, number of rows or columns of the destination matrix is not correct!");
        }
        else
        {
            for (int row{0}; row < destMatrix.getNrOfRows(); ++row)
            {
                for (int col{0}; col < destMatrix.getNrOfColumns(); ++col)
                {
                    if (destMatrix.at(row, col) != 11)
                    {
                        QFAIL("Copy assignment failed, the destination matrix doesn't have the right values!");
                        break;
                    }
                }
            }
        }
    }

    {
        IntMatrix srcMatrix{22, 22, 12};
        IntMatrix destMatrix{2, 3, 8};

        destMatrix = srcMatrix;

        if (destMatrix.getRowCapacity() != 27 || destMatrix.getColumnCapacity() != 27)
        {
            QFAIL("Copy assignment failed, capacity of the destination matrix is not correct!");
        }
        else if (destMatrix.getNrOfRows() != 22 || destMatrix.getNrOfColumns() != 22)
        {
            QFAIL("Copy assignment failed, number of rows or columns of the destination matrix is not correct!");
        }
        else
        {
            for (int row{0}; row < destMatrix.getNrOfRows(); ++row)
            {
                for (int col{0}; col < destMatrix.getNrOfColumns(); ++col)
                {
                    if (destMatrix.at(row, col) != 12)
                    {
                        QFAIL("Copy assignment failed, the destination matrix doesn't have the right values!");
                        break;
                    }
                }
            }
        }
    }

    {
        IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};

        matrix = matrix;

        if (matrix.getRowCapacity() != 2 || matrix.getColumnCapacity() != 3)
        {
            QFAIL("Same matrix copy assignment failed, capacity is not correct!");
        }
        else if (matrix.getNrOfRows() != 2 || matrix.getNrOfColumns() != 3)
        {
            QFAIL("Same matrix copy assignment failed, number of rows or columns is not correct!");
        }
        else
        {
            QVERIFY2(matrix.at(0, 0) == 1 &&
                     matrix.at(0, 1) == 2 &&
                     matrix.at(0, 2) == 3 &&
                     matrix.at(1, 0) == 4 &&
                     matrix.at(1, 1) == 5 &&
                     matrix.at(1, 2) == 6, "Same matrix copy assignment failed, the matrix doesn't have the right values!");
        }
    }

    {
        IntMatrix matrix{};

        matrix = matrix;

        QVERIFY2(matrix.getRowCapacity() == 0 &&
                 matrix.getColumnCapacity() == 0, "Same matrix copy assignment failed, capacity is not correct!");

        QVERIFY2(matrix.getNrOfRows() == 0 &&
                 matrix.getNrOfColumns() == 0, "Same matrix copy assignment failed, number of rows or columns is not correct!");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
        IntMatrix thirdMatrix{2, 2, {13, 14, 15, 16}};

        firstMatrix = secondMatrix = thirdMatrix;

        if (firstMatrix.getRowCapacity() != 2 || firstMatrix.getColumnCapacity() != 2)
        {
            QFAIL("Copy assignment failed, capacity of the first matrix is not correct!");
        }
        else if (firstMatrix.getNrOfRows() != 2 || firstMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Copy assignment failed, number of rows or columns of the first matrix is not correct!");
        }
        else
        {
            QVERIFY2(firstMatrix.at(0, 0) == 13 &&
                     firstMatrix.at(0, 1) == 14 &&
                     firstMatrix.at(1, 0) == 15 &&
                     firstMatrix.at(1, 1) == 16, "Copy assignment failed, the first matrix doesn't have the right values!");
        }
    }
}

void ConstructionAndAssignmentTests::testMoveAssignmentOperator()
{
    {
        IntMatrix srcMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix destMatrix{3, 2, {7, 8, 9, 10, 11, 12}};

        destMatrix = std::move(srcMatrix);

        if (destMatrix.getRowCapacity() != 2 || destMatrix.getColumnCapacity() != 3)
        {
            QFAIL("Move assignment failed, capacity of the destination matrix is not correct!");
        }
        else if (destMatrix.getNrOfRows() != 2 || destMatrix.getNrOfColumns() != 3)
        {
            QFAIL("Move assignment failed, number of rows or columns of the destination matrix is not correct!");
        }
        else
        {
            QVERIFY2(destMatrix.at(0, 0) == 1 &&
                     destMatrix.at(0, 1) == 2 &&
                     destMatrix.at(0, 2) == 3 &&
                     destMatrix.at(1, 0) == 4 &&
                     destMatrix.at(1, 1) == 5 &&
                     destMatrix.at(1, 2) == 6, "Move assignment failed, the destination matrix doesn't have the right values!");

            QVERIFY2(srcMatrix.getRowCapacity() == 0 &&
                     srcMatrix.getColumnCapacity() == 0, "Move assignment failed, capacity of the source matrix is not correct!");

            QVERIFY2(srcMatrix.getNrOfRows() == 0 &&
                     srcMatrix.getNrOfColumns() == 0, "Move assignment failed, number of rows or columns of the source matrix is not correct!");
        }
    }

    {
        IntMatrix srcMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix destMatrix{};

        destMatrix = std::move(srcMatrix);

        if (destMatrix.getRowCapacity() != 2 || destMatrix.getColumnCapacity() != 3)
        {
            QFAIL("Move assignment failed, capacity of the destination matrix is not correct!");
        }
        else if (destMatrix.getNrOfRows() != 2 || destMatrix.getNrOfColumns() != 3)
        {
            QFAIL("Move assignment failed, number of rows or columns of the destination matrix is not correct!");
        }
        else
        {
            QVERIFY2(destMatrix.at(0, 0) == 1 &&
                     destMatrix.at(0, 1) == 2 &&
                     destMatrix.at(0, 2) == 3 &&
                     destMatrix.at(1, 0) == 4 &&
                     destMatrix.at(1, 1) == 5 &&
                     destMatrix.at(1, 2) == 6, "Move assignment failed, the destination matrix doesn't have the right values!");

            QVERIFY2(srcMatrix.getRowCapacity() == 0 &&
                     srcMatrix.getColumnCapacity() == 0, "Move assignment failed, capacity of the source matrix is not correct!");

            QVERIFY2(srcMatrix.getNrOfRows() == 0 &&
                     srcMatrix.getNrOfColumns() == 0, "Move assignment failed, number of rows or columns of the source matrix is not correct!");
        }
    }

    {
        IntMatrix srcMatrix{};
        IntMatrix destMatrix{3, 2, {7, 8, 9, 10, 11, 12}};

        destMatrix = std::move(srcMatrix);

        QVERIFY2(destMatrix.getRowCapacity() == 0 &&
                 destMatrix.getColumnCapacity() == 0, "Move assignment failed, capacity of the destination matrix is not correct!");

        QVERIFY2(destMatrix.getNrOfRows() == 0 &&
                 destMatrix.getNrOfColumns() == 0, "Move assignment failed, number of rows or columns of the destination matrix is not correct!");

        QVERIFY2(srcMatrix.getRowCapacity() == 0 &&
                 srcMatrix.getColumnCapacity() == 0, "Move assignment failed, capacity of the source matrix is not correct!");

        QVERIFY2(srcMatrix.getNrOfRows() == 0 &&
                 srcMatrix.getNrOfColumns() == 0, "Move assignment failed, number of rows or columns of the source matrix is not correct!");
    }

    {
        IntMatrix srcMatrix{};
        IntMatrix destMatrix{};

        destMatrix = std::move(srcMatrix);

        QVERIFY2(destMatrix.getRowCapacity() == 0 &&
                 destMatrix.getColumnCapacity() == 0, "Move assignment failed, capacity of the destination matrix is not correct!");

        QVERIFY2(destMatrix.getNrOfRows() == 0 &&
                 destMatrix.getNrOfColumns() == 0, "Move assignment failed, number of rows or columns of the destination matrix is not correct!");

        QVERIFY2(srcMatrix.getRowCapacity() == 0 &&
                 srcMatrix.getColumnCapacity() == 0, "Move assignment failed, capacity of the source matrix is not correct!");

        QVERIFY2(srcMatrix.getNrOfRows() == 0 &&
                 srcMatrix.getNrOfColumns() == 0, "Move assignment failed, number of rows or columns of the source matrix is not correct!");
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
        else if (firstMatrix.getNrOfRows() != 2 || firstMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Copy and/or move assignment failed, number of rows or columns of the first matrix is not correct!");
        }
        else
        {
            QVERIFY2(firstMatrix.at(0, 0) == 13 &&
                     firstMatrix.at(0, 1) == 14 &&
                     firstMatrix.at(1, 0) == 15 &&
                     firstMatrix.at(1, 1) == 16, "Copy and/or move assignment failed, the first matrix doesn't have the right values!");
        }
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
        else if (firstMatrix.getNrOfRows() != 2 || firstMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Copy and/or move assignment failed, number of rows or columns of the first matrix is not correct!");
        }
        else
        {
            QVERIFY2(firstMatrix.at(0, 0) == 13 &&
                     firstMatrix.at(0, 1) == 14 &&
                     firstMatrix.at(1, 0) == 15 &&
                     firstMatrix.at(1, 1) == 16, "Copy and/or move assignment failed, the first matrix doesn't have the right values!");
        }
    }
}

QTEST_APPLESS_MAIN(ConstructionAndAssignmentTests)

#include "tst_constructionandassignmenttests.moc"
