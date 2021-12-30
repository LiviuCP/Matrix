#include <QtTest>

#include <vector>
#include <tuple>

#include "matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixSizeType = IntMatrix::size_type;
using TripleSizeTypeTuple = std::tuple<IntMatrixSizeType, IntMatrixSizeType, IntMatrixSizeType>;
using TripleSizeTypeTupleArray = std::vector<TripleSizeTypeTuple>;

enum class ConcatMode : unsigned short
{
    ALL_DIFFERENT,
    DESTINATION_FIRST,
    DESTINATION_SECOND,
    SOURCE_BOTH,
    DESTINATION_ALL
};

enum class SplitMode : unsigned short
{
    ALL_DIFFERENT,
    SOURCE_FIRST,
    SOURCE_SECOND
};

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(TripleSizeTypeTuple)
Q_DECLARE_METATYPE(TripleSizeTypeTupleArray)
Q_DECLARE_METATYPE(ConcatMode)
Q_DECLARE_METATYPE(SplitMode)

class CommonTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testDefaultConstructor();
    void testInitListConstructor();
    void testCapacityWithInitListConstructor();
    void testIdenticalMatrixConstructor();
    void testCapacityWithIdenticalMatrixConstructor();
    void testDiagonalMatrixConstructor();
    void testCapacityWithDiagonalMatrixConstructor();
    void testCopyConstructor();
    void testCapacityWithCopyConstructor();
    void testMoveConstructor();
    void testCapacityWithMoveConstructor();
    void testCopyAssignmentOperator();
    void testCapacityWithCopyAssignmentOperator();
    void testMoveAssignmentOperator();
    void testCapacityWithMoveAssignmentOperator();
    void testBooleanOperator();
    void testMatrixesAreEqual();
    void testMatrixesAreNotEqual();
    void testFunctionAt();
    void testSquareBracketsOperator();
    void testGetBaseArray();
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

    // test data
    void testCapacityWithIdenticalMatrixConstructor_data();
    void testCapacityWithDiagonalMatrixConstructor_data();
    void testCapacityWithCopyConstructor_data();
    void testCapacityWithMoveConstructor_data();
    void testCapacityWithCopyAssignmentOperator_data();
    void testCapacityWithMoveAssignmentOperator_data();
    void testBooleanOperator_data();
    void testMatrixesAreEqual_data();
    void testMatrixesAreNotEqual_data();
    void testTranspose_data();
    void testCapacityWithTranspose_data();
    void testClear_data();
    void testResizeWithoutFillingInNewValues_data();
    void testCapacityWithResizeWithoutFillingInNewValues_data();
    void testResizeAndFillInNewValues_data();
    void testCapacityWithResizeAndFillInNewValues_data();
    void testShrinkToFit_data();
    void testInsertRowNoSetValue_data();
    void testInsertRowSetValue_data();
    void testCapacityWithInsertRow_data();
    void testInsertColumnNoSetValue_data();
    void testInsertColumnSetValue_data();
    void testCapacityWithInsertColumn_data();
    void testEraseRow_data();
    void testCapacityWithEraseRow_data();
    void testEraseColumn_data();
    void testCapacityWithEraseColumn_data();
    void testCatByRow_data();
    void testCapacityWithCatByRow_data();
    void testCatByColumn_data();
    void testCapacityWithCatByColumn_data();
    void testSplitByRow_data();
    void testCapacityWithSplitByRow_data();
    void testSplitByColumn_data();
    void testCapacityWithSplitByColumn_data();
    void testSwapMatrixes_data();
    void testSwapItems_data();
    void testSwapRows_data();
    void testSwapColumns_data();
    void testSetAllItemsToValue_data();
    void testCopy_data();

private:
    // test data helper methods
    void _buildCapacityWithMoveCopyConstructorsTestingTable();
    void _buildCapacityWithAssignmentOperatorsTestingTable();
    void _buildCapacityWithResizeTestingTable();
    void _buildInsertRowTestingTable();
    void _buildInsertColumnTestingTable();

    IntMatrix mPrimaryIntMatrix;
    IntMatrix mSecondaryIntMatrix;
};

void CommonTests::testDefaultConstructor()
{
    IntMatrix matrix{};

    QVERIFY2(matrix.getNrOfRows() == 0 &&
             matrix.getNrOfColumns() == 0, "Default constructor initialized matrix with wrong number of rows and columns");

    QVERIFY2(matrix.getRowCapacity() == 0 &&
             matrix.getColumnCapacity() == 0, "Default constructor initialized matrix with wrong capacity");
}

void CommonTests::testInitListConstructor()
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

void CommonTests::testCapacityWithInitListConstructor()
{
    {
        IntMatrix matrix{3, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

        QVERIFY2(matrix.getRowCapacity() == 3 &&
                 matrix.getColumnCapacity() == 5, "Init list constructor initialized matrix with wrong capacity");
    }

    {
        IntMatrix matrix{4, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

        QVERIFY2(matrix.getRowCapacity() == 5 &&
                 matrix.getColumnCapacity() == 3, "Init list constructor initialized matrix with wrong capacity");
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

        QVERIFY2(matrix.getRowCapacity() == 10 &&
                 matrix.getColumnCapacity() == 12, "Init list constructor initialized matrix with wrong capacity");
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

        QVERIFY2(matrix.getRowCapacity() == 12 &&
                 matrix.getColumnCapacity() == 10, "Init list constructor initialized matrix with wrong capacity");
    }
}

void CommonTests::testIdenticalMatrixConstructor()
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

void CommonTests::testCapacityWithIdenticalMatrixConstructor()
{
    QFETCH(IntMatrixSizeType, rowsCount);
    QFETCH(IntMatrixSizeType, columnsCount);
    QFETCH(int, elementValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    IntMatrix matrix{rowsCount, columnsCount, elementValue};

    QVERIFY2(matrix.getRowCapacity() == expectedRowCapacity &&
             matrix.getColumnCapacity() == expectedColumnCapacity, "Identical matrix constructor initialized matrix with wrong capacity");
}

void CommonTests::testDiagonalMatrixConstructor()
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

void CommonTests::testCapacityWithDiagonalMatrixConstructor()
{
    QFETCH(IntMatrixSizeType, rowsColumnsCount);
    QFETCH(int, nonDiagonalValue);
    QFETCH(int, diagonalValue);
    QFETCH(IntMatrixSizeType, expectedRowColumnCapacity);

    IntMatrix matrix{rowsColumnsCount, std::pair<int, int>{nonDiagonalValue, diagonalValue}};

    QVERIFY2(matrix.getRowCapacity() == expectedRowColumnCapacity &&
             matrix.getColumnCapacity() == expectedRowColumnCapacity, "Diag matrix constructor initialized matrix with wrong capacity");
}

void CommonTests::testCopyConstructor()
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

void CommonTests::testCapacityWithCopyConstructor()
{
    QFETCH(IntMatrixSizeType, rowsCount);
    QFETCH(IntMatrixSizeType, columnsCount);
    QFETCH(int, elementValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    IntMatrix srcMatrix{rowsCount, columnsCount, elementValue};
    IntMatrix destMatrix{srcMatrix};

    QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity &&
             destMatrix.getColumnCapacity() == expectedColumnCapacity, "Copy constructor failed, capacity of the destination matrix is not correct!");
}

void CommonTests::testMoveConstructor()
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

void CommonTests::testCapacityWithMoveConstructor()
{
    QFETCH(IntMatrixSizeType, rowsCount);
    QFETCH(IntMatrixSizeType, columnsCount);
    QFETCH(int, elementValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    IntMatrix srcMatrix{rowsCount, columnsCount, elementValue};
    IntMatrix destMatrix{std::move(srcMatrix)};

    QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity &&
             destMatrix.getColumnCapacity() == expectedColumnCapacity, "Move constructor failed, capacity of the destination matrix is not correct!");
}

void CommonTests::testCopyAssignmentOperator()
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

void CommonTests::testCapacityWithCopyAssignmentOperator()
{
    QFETCH(IntMatrixSizeType, srcMatrixRowsCount);
    QFETCH(IntMatrixSizeType, srcMatrixColumnsCount);
    QFETCH(int, srcMatrixElementValue);
    QFETCH(IntMatrixSizeType, destMatrixRowsCount);
    QFETCH(IntMatrixSizeType, destMatrixColumnsCount);
    QFETCH(int, destMatrixElementValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    IntMatrix srcMatrix{srcMatrixRowsCount, srcMatrixColumnsCount, srcMatrixElementValue};

    if (destMatrixRowsCount != 0 && destMatrixColumnsCount != 0)
    {
        IntMatrix destMatrix{destMatrixRowsCount, destMatrixColumnsCount, destMatrixElementValue};
        destMatrix = srcMatrix;

        QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity &&
                 destMatrix.getColumnCapacity() == expectedColumnCapacity, "Copy assignment failed, capacity of the destination matrix is not correct!");
    }
    else
    {
        IntMatrix destMatrix;
        destMatrix = srcMatrix;

        QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity &&
                 destMatrix.getColumnCapacity() == expectedColumnCapacity, "Copy assignment failed, capacity of the destination matrix is not correct!");
    }
}

void CommonTests::testMoveAssignmentOperator()
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

void CommonTests::testCapacityWithMoveAssignmentOperator()
{
    QFETCH(IntMatrixSizeType, srcMatrixRowsCount);
    QFETCH(IntMatrixSizeType, srcMatrixColumnsCount);
    QFETCH(int, srcMatrixElementValue);
    QFETCH(IntMatrixSizeType, destMatrixRowsCount);
    QFETCH(IntMatrixSizeType, destMatrixColumnsCount);
    QFETCH(int, destMatrixElementValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    IntMatrix srcMatrix{srcMatrixRowsCount, srcMatrixColumnsCount, srcMatrixElementValue};

    if (destMatrixRowsCount != 0 && destMatrixColumnsCount != 0)
    {
        IntMatrix destMatrix{destMatrixRowsCount, destMatrixColumnsCount, destMatrixElementValue};
        destMatrix = std::move(srcMatrix);

        QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity &&
                 destMatrix.getColumnCapacity() == expectedColumnCapacity, "Copy assignment failed, capacity of the destination matrix is not correct!");
    }
    else
    {
        IntMatrix destMatrix;
        destMatrix = std::move(srcMatrix);

        QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity &&
                 destMatrix.getColumnCapacity() == expectedColumnCapacity, "Copy assignment failed, capacity of the destination matrix is not correct!");
    }
}

void CommonTests::testBooleanOperator()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(bool, checkTrue);

    if (checkTrue)
    {
        QVERIFY2(matrix, "The boolean operator does not return the expected value (true)!");
    }
    else
    {
        QVERIFY2(!matrix, "The boolean operator does not return the expected value (false)!");
    }
}

void CommonTests::testMatrixesAreEqual()
{
    QFETCH(IntMatrix, firstMatrix);
    QFETCH(IntMatrix, secondMatrix);
    QFETCH(bool, checkEqualityToItself);

    if (checkEqualityToItself)
    {
        QVERIFY2(firstMatrix == firstMatrix &&
                 !(firstMatrix != firstMatrix), "The matrix should be equal to itself!");
    }
    else
    {
        QVERIFY2(firstMatrix == secondMatrix &&
                 !(firstMatrix != secondMatrix), "The matrixes should be equal!");
    }
}

void CommonTests::testMatrixesAreNotEqual()
{
    QFETCH(IntMatrix, firstMatrix);
    QFETCH(IntMatrix, secondMatrix);

    QVERIFY2(firstMatrix != secondMatrix &&
            !(firstMatrix == secondMatrix), "The matrixes should not be equal!");
}

/* This test exercises the write-only and the "const" at() method
   For read-only at() operations of writable matrixes it is considered trivial (getter-like method)
   and is used in many tests for checking that other methods work correctly (see above and below)
*/
void CommonTests::testFunctionAt()
{
    mPrimaryIntMatrix = {2, 3, 5};

    mPrimaryIntMatrix.at(0, 0) = 10;
    mPrimaryIntMatrix.at(0, 1) = 20;
    mPrimaryIntMatrix.at(0, 2) = 30;
    mPrimaryIntMatrix.at(1, 0) = 40;
    mPrimaryIntMatrix.at(1, 1) = 50;
    mPrimaryIntMatrix.at(1, 2) = 60;

    QVERIFY2(mPrimaryIntMatrix == IntMatrix(2, 3, {10, 20, 30, 40, 50, 60}), "The write at() method does not work properly, values are not correctly written!");

    // "const" at() - trivial too but tested here just to ensure it exists (it is required for reading values from const matrixes)
    const IntMatrix matrix{2, 3, {70, 80, 90, 100, 110, 120}};

    QVERIFY2(matrix.at(0, 0) == 70 &&
             matrix.at(0, 1) == 80 &&
             matrix.at(0, 2) == 90 &&
             matrix.at(1, 0) == 100 &&
             matrix.at(1, 1) == 110 &&
             matrix.at(1, 2) == 120, "The const at() method does not work correctly, read values are wrong!");
}

void CommonTests::testSquareBracketsOperator()
{
    mPrimaryIntMatrix = {4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

    QVERIFY2(mPrimaryIntMatrix[0] == 1 &&
             mPrimaryIntMatrix[1] == 2 &&
             mPrimaryIntMatrix[2] == 3 &&
             mPrimaryIntMatrix[3] == 4 &&
             mPrimaryIntMatrix[4] == 5 &&
             mPrimaryIntMatrix[5] == 6 &&
             mPrimaryIntMatrix[6] == 7 &&
             mPrimaryIntMatrix[7] == 8 &&
             mPrimaryIntMatrix[8] == 9 &&
             mPrimaryIntMatrix[9] == 10 &&
             mPrimaryIntMatrix[10] == 11 &&
             mPrimaryIntMatrix[11] == 12, "The square brackets operator did not return the right values!");


    mPrimaryIntMatrix = {2, 3, 5};

    mPrimaryIntMatrix[0] = 70;
    mPrimaryIntMatrix[1] = 80;
    mPrimaryIntMatrix[2] = 90;
    mPrimaryIntMatrix[3] = 100;
    mPrimaryIntMatrix[4] = 110;
    mPrimaryIntMatrix[5] = 120;

    QVERIFY2(mPrimaryIntMatrix == IntMatrix(2, 3, {70, 80, 90, 100, 110, 120}), "The square brackets operator did not write the right values!");

    // test the "const" square brackets operator too (similar to "const" at() - just to ensure it has been created)
    const IntMatrix matrix{4, 3, {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120}};

    QVERIFY2(matrix[0] == 10 &&
             matrix[1] == 20 &&
             matrix[2] == 30 &&
             matrix[3] == 40 &&
             matrix[4] == 50 &&
             matrix[5] == 60 &&
             matrix[6] == 70 &&
             matrix[7] == 80 &&
             matrix[8] == 90 &&
             matrix[9] == 100 &&
             matrix[10] == 110 &&
             matrix[11] == 120, "The const square brackets operator does not work correctly, read values are wrong!");
}

void CommonTests::testGetBaseArray()
{
    mPrimaryIntMatrix = {};

    int nrOfElements;
    int* baseArrayPtr{mPrimaryIntMatrix.getBaseArray(nrOfElements)};

    if (baseArrayPtr || nrOfElements != 0)
    {
        QFAIL("Passing resources outside the matrix failed, either the pointer is not null or the number of elements is different from 0!");
    }

    mPrimaryIntMatrix = {2, 3, {1, 2, 3, 4, 5, 6}};

    baseArrayPtr = mPrimaryIntMatrix.getBaseArray(nrOfElements);

    if (!baseArrayPtr || nrOfElements != 6)
    {
        QFAIL("Passing resources outside the matrix failed, either the pointer is null or the number of elements is not correct!");
    }

    QVERIFY2(baseArrayPtr[0] == 1 &&
             baseArrayPtr[1] == 2 &&
             baseArrayPtr[2] == 3 &&
             baseArrayPtr[3] == 4 &&
             baseArrayPtr[4] == 5 &&
             baseArrayPtr[5] == 6, "Passing resources outside the matrix failed, the element values are not correct!");

    QVERIFY(mPrimaryIntMatrix == IntMatrix{});

    delete []baseArrayPtr;
    baseArrayPtr = nullptr;
}

void CommonTests::testTranspose()
{
    QFETCH(IntMatrix, initialSrcMatrix);
    QFETCH(IntMatrix, initialDestMatrix);
    QFETCH(IntMatrix, expectedDestMatrix);
    QFETCH(IntMatrixSizeType, expectedSrcRowCapacity);
    QFETCH(IntMatrixSizeType, expectedSrcColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedDestRowCapacity);
    QFETCH(IntMatrixSizeType, expectedDestColumnCapacity);
    QFETCH(bool, isTransposedToItself);

    mPrimaryIntMatrix = initialSrcMatrix;

    if (isTransposedToItself)
    {
        mPrimaryIntMatrix.transpose(mPrimaryIntMatrix);

        QVERIFY2(mPrimaryIntMatrix == expectedDestMatrix &&
                 mPrimaryIntMatrix.getRowCapacity() == expectedDestRowCapacity &&
                 mPrimaryIntMatrix.getColumnCapacity() == expectedDestColumnCapacity, "Transposing failed, the resulting capacity, dimensions and/or values are incorrect!");
    }
    else
    {
        mSecondaryIntMatrix = initialDestMatrix;

        mPrimaryIntMatrix.transpose(mSecondaryIntMatrix);

        QVERIFY2(mPrimaryIntMatrix == initialSrcMatrix &&
                 mPrimaryIntMatrix.getRowCapacity() == expectedSrcRowCapacity &&
                 mPrimaryIntMatrix.getColumnCapacity() == expectedSrcColumnCapacity, "Transposing failed, the source matrix shouldn't change!");

        QVERIFY2(mSecondaryIntMatrix == expectedDestMatrix &&
                 mSecondaryIntMatrix.getRowCapacity() == expectedDestRowCapacity &&
                 mSecondaryIntMatrix.getColumnCapacity() == expectedDestColumnCapacity, "Transposing failed, the resulting capacity, dimensions and/or values of the transposed matrix are incorrect!");
    }
}

void CommonTests::testCapacityWithTranspose()
{
    QFETCH(IntMatrixSizeType, srcMatrixRowsCount);
    QFETCH(IntMatrixSizeType, srcMatrixColumnsCount);
    QFETCH(int, srcMatrixElementValue);
    QFETCH(IntMatrixSizeType, destMatrixRowsCount);
    QFETCH(IntMatrixSizeType, destMatrixColumnsCount);
    QFETCH(int, destMatrixElementValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(bool, isTransposedToItself);

    mPrimaryIntMatrix = {srcMatrixRowsCount, srcMatrixColumnsCount, srcMatrixElementValue};

    if (isTransposedToItself)
    {
        mPrimaryIntMatrix.transpose(mPrimaryIntMatrix);

        QVERIFY2(mPrimaryIntMatrix.getRowCapacity() == expectedRowCapacity &&
                 mPrimaryIntMatrix.getColumnCapacity() == expectedColumnCapacity, "Calculating transposed matrix failed, capacity of the destination (transposed) matrix is not correct!");
    }
    else if (destMatrixRowsCount != 0 && destMatrixColumnsCount != 0)
    {
        mSecondaryIntMatrix = {destMatrixRowsCount, destMatrixColumnsCount, destMatrixElementValue};
        mPrimaryIntMatrix.transpose(mSecondaryIntMatrix);

        QVERIFY2(mSecondaryIntMatrix.getRowCapacity() == expectedRowCapacity &&
                 mSecondaryIntMatrix.getColumnCapacity() == expectedColumnCapacity, "Calculating transposed matrix failed, capacity of the destination (transposed) matrix is not correct!");
    }
    else
    {
        mSecondaryIntMatrix = {};
        mPrimaryIntMatrix.transpose(mSecondaryIntMatrix);

        QVERIFY2(mSecondaryIntMatrix.getRowCapacity() == expectedRowCapacity &&
                 mSecondaryIntMatrix.getColumnCapacity() == expectedColumnCapacity, "Calculating transposed matrix failed, capacity of the destination (transposed) matrix is not correct!");
    }
}

void CommonTests::testClear()
{
    QFETCH(IntMatrix, matrix);

    mPrimaryIntMatrix = matrix;
    mPrimaryIntMatrix.clear();

    QVERIFY2(mPrimaryIntMatrix.getRowCapacity() == 0 &&
             mPrimaryIntMatrix.getColumnCapacity() == 0, "Clear failed, capacity is not correct!");

    QVERIFY2(mPrimaryIntMatrix.getNrOfRows() == 0 &&
             mPrimaryIntMatrix.getNrOfColumns() == 0, "Clear failed, number of rows and columns is not correct!");
}

void CommonTests::testResizeWithoutFillingInNewValues()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, expectedRetainedElementsMatrix);

    matrix.resize(resizeRowsCount, resizeColumnsCount);

    if (matrix.getRowCapacity() != expectedRowCapacity || matrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Resizing failed, capacity of the matrix is not correct!");
    }
    else if (matrix.getNrOfRows() != resizeRowsCount || matrix.getNrOfColumns() != resizeColumnsCount)
    {
        QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
    }
    else
    {
        bool areRetainedValuesCorrect{true};

        for(IntMatrixSizeType rowNr{0}; rowNr < expectedRetainedElementsMatrix.getNrOfRows(); ++rowNr)
        {
            for(IntMatrixSizeType columnNr{0}; columnNr < expectedRetainedElementsMatrix.getNrOfColumns(); ++columnNr)
            {
                areRetainedValuesCorrect = areRetainedValuesCorrect && (matrix.at(rowNr, columnNr) == expectedRetainedElementsMatrix.at(rowNr, columnNr));
            }
        }

        QVERIFY2(areRetainedValuesCorrect, "Resizing failed, the retained element values are not correct!");
    }
}

/* In addition to testing resulting capacity a consistency check (size and retained element values comparison) is required in order to ensure
   the resizing with explicitly given capacity is consistent with the one where the capacity is not explicitly provided as argument
*/
void CommonTests::testCapacityWithResizeWithoutFillingInNewValues()
{
    QFETCH(IntMatrixSizeType, initialRowsCount);
    QFETCH(IntMatrixSizeType, initialColumnsCount);
    QFETCH(int, initialElementValue);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(IntMatrixSizeType, requestedRowCapacity);
    QFETCH(IntMatrixSizeType, requestedColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    mPrimaryIntMatrix = {initialRowsCount, initialColumnsCount, initialElementValue};
    mSecondaryIntMatrix = mPrimaryIntMatrix;

    const IntMatrixSizeType c_RetainedNrOfRows{std::min(resizeRowsCount, mSecondaryIntMatrix.getNrOfRows())};
    const IntMatrixSizeType c_RetainedNrOfColumns{std::min(resizeColumnsCount, mSecondaryIntMatrix.getNrOfColumns())};

    mPrimaryIntMatrix.resize(resizeRowsCount, resizeColumnsCount);
    mSecondaryIntMatrix.resize(resizeRowsCount, resizeColumnsCount, requestedRowCapacity, requestedColumnCapacity);

    if (mSecondaryIntMatrix.getRowCapacity() != expectedRowCapacity || mSecondaryIntMatrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Resizing failed, capacity of the matrix is not correct!");
    }
    else if (mSecondaryIntMatrix.getNrOfRows() != mPrimaryIntMatrix.getNrOfRows() || mSecondaryIntMatrix.getNrOfColumns() != mPrimaryIntMatrix.getNrOfColumns())
    {
        QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
    }
    else
    {
        bool areRetainedValuesCorrect{true};

        for (IntMatrixSizeType rowNr{0}; rowNr < c_RetainedNrOfRows; ++rowNr)
        {
            for (IntMatrixSizeType columnNr{0}; columnNr < c_RetainedNrOfColumns; ++columnNr)
            {
                areRetainedValuesCorrect = areRetainedValuesCorrect && (mSecondaryIntMatrix.at(rowNr, columnNr) == mPrimaryIntMatrix.at(rowNr, columnNr));
            }
        }

        QVERIFY2(areRetainedValuesCorrect, "Resizing failed, the matrix does not have the correct values for the retained items!");
    }
}

void CommonTests::testResizeAndFillInNewValues()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(int, fillValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, expectedMatrix);

    matrix.resizeWithValue(resizeRowsCount, resizeColumnsCount, fillValue);

    if (matrix.getRowCapacity() != expectedRowCapacity || matrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Resizing failed, capacity of the matrix is not correct!");
    }
    else
    {
        QVERIFY2(matrix == expectedMatrix, "Resizing failed, the matrix does not have the correct values!");
    }
}

/* In addition to testing resulting capacity a consistency check (size and element values comparison) is required in order to ensure
   the resizing with explicitly given capacity is consistent with the one where the capacity is not explicitly provided as argument
*/
void CommonTests::testCapacityWithResizeAndFillInNewValues()
{
    QFETCH(IntMatrixSizeType, initialRowsCount);
    QFETCH(IntMatrixSizeType, initialColumnsCount);
    QFETCH(IntMatrixSizeType, initialElementValue);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(int, resizeElementValue);
    QFETCH(IntMatrixSizeType, requestedRowCapacity);
    QFETCH(IntMatrixSizeType, requestedColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    mPrimaryIntMatrix = {initialRowsCount, initialColumnsCount, initialElementValue};
    mSecondaryIntMatrix = mPrimaryIntMatrix;

    mPrimaryIntMatrix.resizeWithValue(resizeRowsCount, resizeColumnsCount, resizeElementValue);
    mSecondaryIntMatrix.resizeWithValue(resizeRowsCount, resizeColumnsCount, resizeElementValue, requestedRowCapacity, requestedColumnCapacity);

    if (mSecondaryIntMatrix.getRowCapacity() != expectedRowCapacity || mSecondaryIntMatrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Resizing failed, capacity of the matrix is not correct!");
    }
    else
    {
        QVERIFY2(mSecondaryIntMatrix == mPrimaryIntMatrix, "Resizing failed, the matrix does not have the correct size and/or values!");
    }
}

void CommonTests::testShrinkToFit()
{
    QFETCH(IntMatrix, matrix);

    mPrimaryIntMatrix = matrix;
    mPrimaryIntMatrix.shrinkToFit();

    if (mPrimaryIntMatrix.getRowCapacity() != matrix.getNrOfRows() || mPrimaryIntMatrix.getColumnCapacity() != matrix.getNrOfColumns())
    {
        QFAIL("Shrinking to fit failed, capacity of the matrix is not correct!");
    }
    else
    {
        QVERIFY2(mPrimaryIntMatrix == matrix, "Shrinking to fit failed, the matrix does not retain its values!");
    }
}

void CommonTests::testInsertRowNoSetValue()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, referenceMatrix);

    matrix.insertRow(insertPosition);

    if (matrix.getRowCapacity() != expectedRowCapacity || matrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Insert row failed, capacity of the matrix is not correct!");
    }
    else if (matrix.getNrOfRows() != referenceMatrix.getNrOfRows() || matrix.getNrOfColumns() != referenceMatrix.getNrOfColumns())
    {
        QFAIL("Insert row failed, number of rows or columns of the matrix is not correct!");
    }
    else
    {
        bool areRetainedValuesCorrect{true};

        for (IntMatrixSizeType rowNr{0}; rowNr < matrix.getNrOfRows(); ++rowNr)
        {
            if (rowNr != insertPosition)
            {
                for (IntMatrixSizeType columnNr{0}; columnNr < matrix.getNrOfColumns(); ++columnNr)
                {
                    if (matrix.at(rowNr, columnNr) != referenceMatrix.at(rowNr, columnNr))
                    {
                        areRetainedValuesCorrect = false;
                        break;
                    }
                }
            }
        }

        QVERIFY2(areRetainedValuesCorrect, "Insert row failed, the matrix doesn't have the right values on the existing rows!");
    }
}

void CommonTests::testInsertRowSetValue()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(int, insertedRowValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, referenceMatrix);

    matrix.insertRow(insertPosition, insertedRowValue);

    if (matrix.getRowCapacity() != expectedRowCapacity || matrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Insert row failed, capacity of the matrix is not correct!");
    }
    else
    {
        QVERIFY2(matrix == referenceMatrix, "Insert row failed, the matrix doesn't have the right values!");
    }
}

void CommonTests::testCapacityWithInsertRow()
{
    QFETCH(IntMatrixSizeType, rowsCount);
    QFETCH(IntMatrixSizeType, columnsCount);
    QFETCH(int, elementValue);
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(int, insertedRowValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(bool, isInsertedRowValueSet);

    mPrimaryIntMatrix = {rowsCount, columnsCount, elementValue};

    if (isInsertedRowValueSet)
    {
        mPrimaryIntMatrix.insertRow(insertPosition, insertedRowValue);
    }
    else
    {
        mPrimaryIntMatrix.insertRow(insertPosition);
    }

    QVERIFY2(mPrimaryIntMatrix.getRowCapacity() == expectedRowCapacity &&
             mPrimaryIntMatrix.getColumnCapacity() == expectedColumnCapacity, "Insert row failed, capacity of the matrix is not correct!");
}

void CommonTests::testInsertColumnNoSetValue()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, referenceMatrix);

    matrix.insertColumn(insertPosition);

    if (matrix.getRowCapacity() != expectedRowCapacity || matrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Insert column failed, capacity of the matrix is not correct!");
    }
    else if (matrix.getNrOfRows() != referenceMatrix.getNrOfRows() || matrix.getNrOfColumns() != referenceMatrix.getNrOfColumns())
    {
        QFAIL("Insert column failed, number of rows or columns of the matrix is not correct!");
    }
    else
    {
        bool areRetainedValuesCorrect{true};

        for (IntMatrixSizeType columnNr{0}; columnNr < matrix.getNrOfColumns(); ++columnNr)
        {
            if (columnNr != insertPosition)
            {
                for (IntMatrixSizeType rowNr{0}; rowNr < matrix.getNrOfRows(); ++rowNr)
                {
                    if (matrix.at(rowNr, columnNr) != referenceMatrix.at(rowNr, columnNr))
                    {
                        areRetainedValuesCorrect = false;
                        break;
                    }
                }
            }
        }

        QVERIFY2(areRetainedValuesCorrect, "Insert column failed, the matrix doesn't have the right values on the existing columns!");
    }
}

void CommonTests::testInsertColumnSetValue()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(int, insertedColumnValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, referenceMatrix);

    matrix.insertColumn(insertPosition, insertedColumnValue);

    if (matrix.getRowCapacity() != expectedRowCapacity || matrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Insert column failed, capacity of the matrix is not correct!");
    }
    else
    {
        QVERIFY2(matrix == referenceMatrix, "Insert column failed, the matrix doesn't have the right values!");
    }
}

void CommonTests::testCapacityWithInsertColumn()
{
    QFETCH(IntMatrixSizeType, rowsCount);
    QFETCH(IntMatrixSizeType, columnsCount);
    QFETCH(int, elementValue);
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(int, insertedColumnValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(bool, isInsertedColumnValueSet);

    mPrimaryIntMatrix = {rowsCount, columnsCount, elementValue};

    if (isInsertedColumnValueSet)
    {
        mPrimaryIntMatrix.insertColumn(insertPosition, insertedColumnValue);
    }
    else
    {
        mPrimaryIntMatrix.insertColumn(insertPosition);
    }

    QVERIFY2(mPrimaryIntMatrix.getRowCapacity() == expectedRowCapacity &&
             mPrimaryIntMatrix.getColumnCapacity() == expectedColumnCapacity, "Insert column failed, capacity of the matrix is not correct!");
}

void CommonTests::testEraseRow()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, erasePosition);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, expectedMatrix);

    matrix.eraseRow(erasePosition);

    if (matrix.getRowCapacity() != expectedRowCapacity || matrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Erase row failed, capacity of the matrix is not correct!");
    }
    else
    {
        QVERIFY2(matrix == expectedMatrix, "Erase row failed, the matrix doesn't have the right values on the remaining rows!");
    }
}

void CommonTests::testCapacityWithEraseRow()
{
    QFETCH(IntMatrixSizeType, rowsCount);
    QFETCH(IntMatrixSizeType, columnsCount);
    QFETCH(int, elementValue);
    QFETCH(TripleSizeTypeTupleArray, erasedRowAndExpectedCapacity);

    mPrimaryIntMatrix = {rowsCount, columnsCount, elementValue};

    for (const auto& data : erasedRowAndExpectedCapacity)
    {
        mPrimaryIntMatrix.eraseRow(std::get<0>(data));

        QVERIFY2(mPrimaryIntMatrix.getRowCapacity() == std::get<1>(data) &&
                 mPrimaryIntMatrix.getColumnCapacity() == std::get<2>(data), "Erase row failed, capacity of the matrix is not correct!");
    }
}

void CommonTests::testEraseColumn()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, erasePosition);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, expectedMatrix);

    matrix.eraseColumn(erasePosition);

    if (matrix.getRowCapacity() != expectedRowCapacity || matrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Erase column failed, capacity of the matrix is not correct!");
    }
    else
    {
        QVERIFY2(matrix == expectedMatrix, "Erase column failed, the matrix doesn't have the right values on the remaining columns!");
    }
}

void CommonTests::testCapacityWithEraseColumn()
{
    QFETCH(IntMatrixSizeType, rowsCount);
    QFETCH(IntMatrixSizeType, columnsCount);
    QFETCH(int, elementValue);
    QFETCH(TripleSizeTypeTupleArray, erasedColumnAndExpectedCapacity);

    mPrimaryIntMatrix = {rowsCount, columnsCount, elementValue};

    for (const auto& data : erasedColumnAndExpectedCapacity)
    {
        mPrimaryIntMatrix.eraseColumn(std::get<0>(data));

        QVERIFY2(mPrimaryIntMatrix.getRowCapacity() == std::get<1>(data) &&
                 mPrimaryIntMatrix.getColumnCapacity() == std::get<2>(data), "Erase row failed, capacity of the matrix is not correct!");
    }
}

void CommonTests::testCatByRow()
{
    QFETCH(IntMatrix, destMatrix);
    QFETCH(IntMatrix, firstSrcMatrix);
    QFETCH(IntMatrix, secondSrcMatrix);
    QFETCH(ConcatMode, mode);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, expectedDestMatrix);

    switch(mode)
    {
    case ConcatMode::ALL_DIFFERENT:
        destMatrix.catByRow(firstSrcMatrix, secondSrcMatrix);
        break;
    case ConcatMode::DESTINATION_FIRST:
        destMatrix.catByRow(destMatrix, secondSrcMatrix);
        break;
    case ConcatMode::DESTINATION_SECOND:
        destMatrix.catByRow(firstSrcMatrix, destMatrix);
        break;
    case ConcatMode::DESTINATION_ALL:
        destMatrix.catByRow(destMatrix, destMatrix);
        break;
    case ConcatMode::SOURCE_BOTH:
        destMatrix.catByRow(firstSrcMatrix, firstSrcMatrix);
        break;
    default:
        break;
    }

    if (destMatrix.getRowCapacity() != expectedRowCapacity || destMatrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Vertical concatenation failed, capacity of the destination matrix is not correct!");
    }
    else
    {
        QVERIFY2(destMatrix == expectedDestMatrix, "Vertical concatenation failed, destination matrix has incorrect values!");
    }
}

void CommonTests::testCapacityWithCatByRow()
{
    QFETCH(IntMatrix, destMatrix);
    QFETCH(IntMatrix, firstSrcMatrix);
    QFETCH(IntMatrix, secondSrcMatrix);
    QFETCH(ConcatMode, mode);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(IntMatrixSizeType, resizeRowCapacity);
    QFETCH(IntMatrixSizeType, resizeColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    if (resizeRowsCount > 0 && resizeColumnsCount > 0)
    {
        destMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity);
    }

    switch(mode)
    {
    case ConcatMode::ALL_DIFFERENT:
        destMatrix.catByRow(firstSrcMatrix, secondSrcMatrix);
        break;
    case ConcatMode::DESTINATION_FIRST:
        destMatrix.catByRow(destMatrix, secondSrcMatrix);
        break;
    case ConcatMode::DESTINATION_SECOND:
        destMatrix.catByRow(firstSrcMatrix, destMatrix);
        break;
    case ConcatMode::DESTINATION_ALL:
        destMatrix.catByRow(destMatrix, destMatrix);
        break;
    case ConcatMode::SOURCE_BOTH:
        destMatrix.catByRow(firstSrcMatrix, firstSrcMatrix);
        break;
    default:
        break;
    }

    QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity &&
             destMatrix.getColumnCapacity() == expectedColumnCapacity, "Vertical concatenation failed, capacity of the destination matrix is not correct!");
}

void CommonTests::testCatByColumn()
{
    QFETCH(IntMatrix, destMatrix);
    QFETCH(IntMatrix, firstSrcMatrix);
    QFETCH(IntMatrix, secondSrcMatrix);
    QFETCH(ConcatMode, mode);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, expectedDestMatrix);

    switch(mode)
    {
    case ConcatMode::ALL_DIFFERENT:
        destMatrix.catByColumn(firstSrcMatrix, secondSrcMatrix);
        break;
    case ConcatMode::DESTINATION_FIRST:
        destMatrix.catByColumn(destMatrix, secondSrcMatrix);
        break;
    case ConcatMode::DESTINATION_SECOND:
        destMatrix.catByColumn(firstSrcMatrix, destMatrix);
        break;
    case ConcatMode::DESTINATION_ALL:
        destMatrix.catByColumn(destMatrix, destMatrix);
        break;
    case ConcatMode::SOURCE_BOTH:
        destMatrix.catByColumn(firstSrcMatrix, firstSrcMatrix);
        break;
    default:
        break;
    }

    if (destMatrix.getRowCapacity() != expectedRowCapacity || destMatrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Horizontal concatenation failed, capacity of the destination matrix is not correct!");
    }
    else
    {
        QVERIFY2(destMatrix == expectedDestMatrix, "Horizontal concatenation failed, destination matrix has incorrect values!");
    }
}

void CommonTests::testCapacityWithCatByColumn()
{
    QFETCH(IntMatrix, destMatrix);
    QFETCH(IntMatrix, firstSrcMatrix);
    QFETCH(IntMatrix, secondSrcMatrix);
    QFETCH(ConcatMode, mode);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(IntMatrixSizeType, resizeRowCapacity);
    QFETCH(IntMatrixSizeType, resizeColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    if (resizeRowsCount > 0 && resizeColumnsCount > 0)
    {
        destMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity);
    }

    switch(mode)
    {
    case ConcatMode::ALL_DIFFERENT:
        destMatrix.catByColumn(firstSrcMatrix, secondSrcMatrix);
        break;
    case ConcatMode::DESTINATION_FIRST:
        destMatrix.catByColumn(destMatrix, secondSrcMatrix);
        break;
    case ConcatMode::DESTINATION_SECOND:
        destMatrix.catByColumn(firstSrcMatrix, destMatrix);
        break;
    case ConcatMode::DESTINATION_ALL:
        destMatrix.catByColumn(destMatrix, destMatrix);
        break;
    case ConcatMode::SOURCE_BOTH:
        destMatrix.catByColumn(firstSrcMatrix, firstSrcMatrix);
        break;
    default:
        break;
    }

    QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity &&
             destMatrix.getColumnCapacity() == expectedColumnCapacity, "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
}

void CommonTests::testSplitByRow()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrix, firstDestMatrix);
    QFETCH(IntMatrix, secondDestMatrix);
    QFETCH(IntMatrixSizeType, splitPosition);
    QFETCH(SplitMode, mode);
    QFETCH(IntMatrixSizeType, expectedFirstDestRowCapacity);
    QFETCH(IntMatrixSizeType, expectedFirstDestColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedSecondDestRowCapacity);
    QFETCH(IntMatrixSizeType, expectedSecondDestColumnCapacity);
    QFETCH(IntMatrix, expectedFirstDestMatrix);
    QFETCH(IntMatrix, expectedSecondDestMatrix);

    switch(mode)
    {
    case SplitMode::ALL_DIFFERENT:
        srcMatrix.splitByRow(firstDestMatrix, secondDestMatrix, splitPosition);
        break;
    case SplitMode::SOURCE_FIRST:
        firstDestMatrix.splitByRow(firstDestMatrix, secondDestMatrix, splitPosition);
        break;
    case SplitMode::SOURCE_SECOND:
        secondDestMatrix.splitByRow(firstDestMatrix, secondDestMatrix, splitPosition);
        break;
    default:
        break;
    }

    if (firstDestMatrix.getRowCapacity() != expectedFirstDestRowCapacity || firstDestMatrix.getColumnCapacity() != expectedFirstDestColumnCapacity)
    {
        QFAIL("Vertical split failed, capacity of the first destination matrix is not correct!");
    }
    else
    {
        QVERIFY2(firstDestMatrix == expectedFirstDestMatrix, "Vertical split failed, first destination matrix has incorrect values!");
    }

    if (secondDestMatrix.getRowCapacity() != expectedSecondDestRowCapacity || secondDestMatrix.getColumnCapacity() != expectedSecondDestColumnCapacity)
    {
        QFAIL("Vertical split failed, capacity of the second destination matrix is not correct!");
    }
    else
    {
        QVERIFY2(secondDestMatrix == expectedSecondDestMatrix, "Vertical split failed, second destination matrix has incorrect values!");
    }
}

void CommonTests::testCapacityWithSplitByRow()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrix, firstDestMatrix);
    QFETCH(IntMatrix, secondDestMatrix);
    QFETCH(IntMatrixSizeType, splitPosition);
    QFETCH(SplitMode, mode);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(IntMatrixSizeType, resizeRowCapacity);
    QFETCH(IntMatrixSizeType, resizeColumnCapacity);
    QFETCH(bool, isFirstDestResized);
    QFETCH(IntMatrixSizeType, expectedFirstDestRowCapacity);
    QFETCH(IntMatrixSizeType, expectedFirstDestColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedSecondDestRowCapacity);
    QFETCH(IntMatrixSizeType, expectedSecondDestColumnCapacity);

    if (resizeRowsCount > 0 && resizeColumnsCount > 0)
    {
        if (isFirstDestResized)
        {
            firstDestMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity);
        }
        else
        {
            secondDestMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity);
        }
    }

    switch(mode)
    {
    case SplitMode::ALL_DIFFERENT:
        srcMatrix.splitByRow(firstDestMatrix, secondDestMatrix, splitPosition);
        break;
    case SplitMode::SOURCE_FIRST:
        firstDestMatrix.splitByRow(firstDestMatrix, secondDestMatrix, splitPosition);
        break;
    case SplitMode::SOURCE_SECOND:
        secondDestMatrix.splitByRow(firstDestMatrix, secondDestMatrix, splitPosition);
        break;
    default:
        break;
    }

    QVERIFY2(firstDestMatrix.getRowCapacity() == expectedFirstDestRowCapacity &&
             firstDestMatrix.getColumnCapacity() == expectedFirstDestColumnCapacity, "Vertical split failed, capacity of the first destination matrix is not correct!");

    QVERIFY2(secondDestMatrix.getRowCapacity() == expectedSecondDestRowCapacity &&
             secondDestMatrix.getColumnCapacity() == expectedSecondDestColumnCapacity, "Vertical split failed, capacity of the second destination matrix is not correct!");
}

void CommonTests::testSplitByColumn()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrix, firstDestMatrix);
    QFETCH(IntMatrix, secondDestMatrix);
    QFETCH(IntMatrixSizeType, splitPosition);
    QFETCH(SplitMode, mode);
    QFETCH(IntMatrixSizeType, expectedFirstDestRowCapacity);
    QFETCH(IntMatrixSizeType, expectedFirstDestColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedSecondDestRowCapacity);
    QFETCH(IntMatrixSizeType, expectedSecondDestColumnCapacity);
    QFETCH(IntMatrix, expectedFirstDestMatrix);
    QFETCH(IntMatrix, expectedSecondDestMatrix);

    switch(mode)
    {
    case SplitMode::ALL_DIFFERENT:
        srcMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, splitPosition);
        break;
    case SplitMode::SOURCE_FIRST:
        firstDestMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, splitPosition);
        break;
    case SplitMode::SOURCE_SECOND:
        secondDestMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, splitPosition);
        break;
    default:
        break;
    }

    if (firstDestMatrix.getRowCapacity() != expectedFirstDestRowCapacity || firstDestMatrix.getColumnCapacity() != expectedFirstDestColumnCapacity)
    {
        QFAIL("Horizontal split failed, capacity of the first destination matrix is not correct!");
    }
    else
    {
        QVERIFY2(firstDestMatrix == expectedFirstDestMatrix, "Horizontal split failed, first destination matrix has incorrect values!");
    }

    if (secondDestMatrix.getRowCapacity() != expectedSecondDestRowCapacity || secondDestMatrix.getColumnCapacity() != expectedSecondDestColumnCapacity)
    {
        QFAIL("Horizontal split failed, capacity of the second destination matrix is not correct!");
    }
    else
    {
        QVERIFY2(secondDestMatrix == expectedSecondDestMatrix, "Horizontal split failed, second destination matrix has incorrect values!");
    }
}

void CommonTests::testCapacityWithSplitByColumn()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrix, firstDestMatrix);
    QFETCH(IntMatrix, secondDestMatrix);
    QFETCH(IntMatrixSizeType, splitPosition);
    QFETCH(SplitMode, mode);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(IntMatrixSizeType, resizeRowCapacity);
    QFETCH(IntMatrixSizeType, resizeColumnCapacity);
    QFETCH(bool, isFirstDestResized);
    QFETCH(IntMatrixSizeType, expectedFirstDestRowCapacity);
    QFETCH(IntMatrixSizeType, expectedFirstDestColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedSecondDestRowCapacity);
    QFETCH(IntMatrixSizeType, expectedSecondDestColumnCapacity);

    if (resizeRowsCount > 0 && resizeColumnsCount > 0)
    {
        if (isFirstDestResized)
        {
            firstDestMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity);
        }
        else
        {
            secondDestMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity);
        }
    }

    switch(mode)
    {
    case SplitMode::ALL_DIFFERENT:
        srcMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, splitPosition);
        break;
    case SplitMode::SOURCE_FIRST:
        firstDestMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, splitPosition);
        break;
    case SplitMode::SOURCE_SECOND:
        secondDestMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, splitPosition);
        break;
    default:
        break;
    }

    QVERIFY2(firstDestMatrix.getRowCapacity() == expectedFirstDestRowCapacity &&
             firstDestMatrix.getColumnCapacity() == expectedFirstDestColumnCapacity, "Horizontal split failed, capacity of the first destination matrix is not correct!");

    QVERIFY2(secondDestMatrix.getRowCapacity() == expectedSecondDestRowCapacity &&
             secondDestMatrix.getColumnCapacity() == expectedSecondDestColumnCapacity, "Horizontal split failed, capacity of the second destination matrix is not correct!");
}

void CommonTests::testSwapMatrixes()
{
    QFETCH(IntMatrix, firstMatrix);
    QFETCH(IntMatrix, secondMatrix);

    mPrimaryIntMatrix = firstMatrix;
    mSecondaryIntMatrix = secondMatrix;

    std::swap(mPrimaryIntMatrix, mSecondaryIntMatrix);

    if (mPrimaryIntMatrix.getRowCapacity() != secondMatrix.getRowCapacity() || mPrimaryIntMatrix.getColumnCapacity() != secondMatrix.getColumnCapacity())
    {
        QFAIL("Incorrect capacity of the first matrix after swap!");
    }

    if (mSecondaryIntMatrix.getRowCapacity() != firstMatrix.getRowCapacity() || mSecondaryIntMatrix.getColumnCapacity() != firstMatrix.getColumnCapacity())
    {
        QFAIL("Incorrect capacity of the second matrix after swap!");
    }

    QVERIFY2(mPrimaryIntMatrix == secondMatrix, "First matrix has incorrect element values after swap!");
    QVERIFY2(mSecondaryIntMatrix == firstMatrix, "Second matrix has incorrect element values after swap!");
}

void CommonTests::testSwapItems()
{
    QFETCH(IntMatrix, firstMatrix);
    QFETCH(IntMatrix, secondMatrix);
    QFETCH(IntMatrixSizeType, firstItemRowNr);
    QFETCH(IntMatrixSizeType, firstItemColumnNr);
    QFETCH(IntMatrixSizeType, secondItemRowNr);
    QFETCH(IntMatrixSizeType, secondItemColumnNr);
    QFETCH(bool, isSwapWithinMatrix);
    QFETCH(IntMatrix, expectedFirstMatrix);
    QFETCH(IntMatrix, expectedSecondMatrix);

    if (isSwapWithinMatrix)
    {
        firstMatrix.swapItems(firstItemRowNr, firstItemColumnNr, firstMatrix, secondItemRowNr, secondItemColumnNr);
        QVERIFY2(firstMatrix == expectedFirstMatrix, "Items are incorrectly swapped within same matrix!");
    }
    else
    {
        firstMatrix.swapItems(firstItemRowNr, firstItemColumnNr, secondMatrix, secondItemRowNr, secondItemColumnNr);

        QVERIFY2(firstMatrix == expectedFirstMatrix, "Items are incorrectly swapped between matrixes, first matrix does not have the desired value after swap!");
        QVERIFY2(secondMatrix == expectedSecondMatrix, "Items are incorrectly swapped between matrixes, second matrix does not have the desired value after swap!");
    }
}

void CommonTests::testSwapRows()
{
    QFETCH(IntMatrix, firstMatrix);
    QFETCH(IntMatrix, secondMatrix);
    QFETCH(IntMatrixSizeType, firstRowNr);
    QFETCH(IntMatrixSizeType, secondRowNr);
    QFETCH(bool, isSwapWithinMatrix);
    QFETCH(IntMatrix, expectedFirstMatrix);
    QFETCH(IntMatrix, expectedSecondMatrix);

    if (isSwapWithinMatrix)
    {
        firstMatrix.swapRows(firstRowNr, firstMatrix, secondRowNr);
        QVERIFY2(firstMatrix == expectedFirstMatrix, "Rows are incorrectly swapped within same matrix!");
    }
    else
    {
        firstMatrix.swapRows(firstRowNr, secondMatrix, secondRowNr);

        QVERIFY2(firstMatrix == expectedFirstMatrix, "Rows are incorrectly swapped between matrixes, first matrix does not have the desired value after swap!");
        QVERIFY2(secondMatrix == expectedSecondMatrix, "Rows are incorrectly swapped between matrixes, second matrix does not have the desired value after swap!");
    }
}

void CommonTests::testSwapColumns()
{
    QFETCH(IntMatrix, firstMatrix);
    QFETCH(IntMatrix, secondMatrix);
    QFETCH(IntMatrixSizeType, firstColumnNr);
    QFETCH(IntMatrixSizeType, secondColumnNr);
    QFETCH(bool, isSwapWithinMatrix);
    QFETCH(IntMatrix, expectedFirstMatrix);
    QFETCH(IntMatrix, expectedSecondMatrix);

    if (isSwapWithinMatrix)
    {
        firstMatrix.swapColumns(firstColumnNr, firstMatrix, secondColumnNr);
        QVERIFY2(firstMatrix == expectedFirstMatrix, "Columns are incorrectly swapped within same matrix!");
    }
    else
    {
        firstMatrix.swapColumns(firstColumnNr, secondMatrix, secondColumnNr);

        QVERIFY2(firstMatrix == expectedFirstMatrix, "Columns are incorrectly swapped between matrixes, first matrix does not have the desired value after swap!");
        QVERIFY2(secondMatrix == expectedSecondMatrix, "Columns are incorrectly swapped between matrixes, second matrix does not have the desired value after swap!");
    }
}

void CommonTests::testSwapRowColumn()
{
    mPrimaryIntMatrix = {4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    mSecondaryIntMatrix = {3, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24}};

    mPrimaryIntMatrix.swapRowColumn(0, mSecondaryIntMatrix, 3);

    QVERIFY2(mPrimaryIntMatrix == IntMatrix(4, 3, {16, 20, 24, 4, 5, 6, 7, 8, 9, 10, 11, 12}),
             "Row from first matrix is incorrectly swapped with column from the second, first matrix does not have the desired value after swap!");

    QVERIFY2(mSecondaryIntMatrix == IntMatrix(3, 4, {13, 14, 15, 1, 17, 18, 19, 2, 21, 22, 23, 3}),
             "Row from first matrix is incorrectly swapped with column from the second, second matrix does not have the desired value after swap!");
}

void CommonTests::testSetAllItemsToValue()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(int, value);
    QFETCH(IntMatrix, expectedMatrix);

    matrix.setAllItemsToValue(value);

    QVERIFY2(matrix == expectedMatrix, "Setting all matrix items to same value failed, matrix has incorrect values!");
}

void CommonTests::testCopy()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrix, destMatrix);
    QFETCH(IntMatrixSizeType, copiedRowsCount);
    QFETCH(IntMatrixSizeType, copiedColumnsCount);
    QFETCH(IntMatrixSizeType, srcCopyRowNr);
    QFETCH(IntMatrixSizeType, srcCopyColumnNr);
    QFETCH(IntMatrixSizeType, destCopyRowNr);
    QFETCH(IntMatrixSizeType, destCopyColumnNr);
    QFETCH(IntMatrix, expectedDestMatrix);

    destMatrix.copy(srcMatrix, copiedRowsCount, copiedColumnsCount, srcCopyRowNr, srcCopyColumnNr, destCopyRowNr, destCopyColumnNr);

    QVERIFY2(destMatrix == expectedDestMatrix, "Copying items failed, destination matrix has incorrect values!");
}

void CommonTests::testCapacityWithIdenticalMatrixConstructor_data()
{
    QTest::addColumn<IntMatrixSizeType>("rowsCount");
    QTest::addColumn<IntMatrixSizeType>("columnsCount");
    QTest::addColumn<int>("elementValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("small size matrix") << 3 << 4 << -5 << 3 << 5;
    QTest::newRow("small size matrix") << 4 << 3 << -5 << 5 << 3;
    QTest::newRow("large size matrix") << 25 << 20 << -2 << 31 << 25;
    QTest::newRow("large size matrix") << 20 << 25 << -2 << 25 << 31;
}

void CommonTests::testCapacityWithDiagonalMatrixConstructor_data()
{
    QTest::addColumn<IntMatrixSizeType>("rowsColumnsCount");
    QTest::addColumn<int>("nonDiagonalValue");
    QTest::addColumn<int>("diagonalValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowColumnCapacity");

    QTest::newRow("small size matrix") << 3 << -2 << -3 << 3;
    QTest::newRow("small size matrix") << 4 << -2 << -3 << 5;
    QTest::newRow("medium size matrix") << 8 << -2 << -3 << 10;
    QTest::newRow("medium size matrix") << 10 << -2 << -3 << 12;
}

void CommonTests::testCapacityWithCopyConstructor_data()
{
    _buildCapacityWithMoveCopyConstructorsTestingTable();
}

void CommonTests::testCapacityWithMoveConstructor_data()
{
    _buildCapacityWithMoveCopyConstructorsTestingTable();
}

void CommonTests::testCapacityWithCopyAssignmentOperator_data()
{
    _buildCapacityWithAssignmentOperatorsTestingTable();
}

void CommonTests::testCapacityWithMoveAssignmentOperator_data()
{
    _buildCapacityWithAssignmentOperatorsTestingTable();
}

void CommonTests::testBooleanOperator_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<bool>("checkTrue");

    QTest::newRow("check false") << IntMatrix{} << false;
    QTest::newRow("check false") << IntMatrix{2, 3, {0, 0, 0, 0, 0, 0}} << false;
    QTest::newRow("check true") << IntMatrix{2, 3, {3, -25, 26, -38, 0, -1}} << true;
    QTest::newRow("check true") << IntMatrix{2, 3, {0, 0, 0, 0, -25, 0}} << true;
}

void CommonTests::testMatrixesAreEqual_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<bool>("checkEqualityToItself");

    QTest::newRow("distinct matrixes equality") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << false;
    QTest::newRow("equality to itself") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << true;
    QTest::newRow("distinct matrixes equality") << IntMatrix{} << IntMatrix{} << false;
    QTest::newRow("equality to itself") << IntMatrix{} << IntMatrix{} << true;
}

void CommonTests::testMatrixesAreNotEqual_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");

    QTest::newRow("same size matrixes") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 3, {5, 125, -5, 15, 833, -8333}};
    QTest::newRow("different columns count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 2, {5, 75, 15, 833}};
    QTest::newRow("different rows count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{3, 3, {5, 75, -5, 15, 833, -8333, 5, 5, -125}};
    QTest::newRow("different rows/columns count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{3, 2, {5, 75, 15, 833, -5, -8333}};
    QTest::newRow("different rows/columns count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{};
}

void CommonTests::testTranspose_data()
{
    QTest::addColumn<IntMatrix>("initialSrcMatrix");
    QTest::addColumn<IntMatrix>("initialDestMatrix");
    QTest::addColumn<IntMatrix>("expectedDestMatrix");
    QTest::addColumn<IntMatrixSizeType>("expectedSrcRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedSrcColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedDestRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedDestColumnCapacity");
    QTest::addColumn<bool>("isTransposedToItself");

    QTest::newRow("same matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}}
                                 << IntMatrix{3, 2, {1, 4, 2, 5, 3, 6}} << 3 << 3 << 3 << 3 << true;

    QTest::newRow("same matrix") << IntMatrix{} << IntMatrix{}
                                 << IntMatrix{} << 0 << 0 << 0 << 0 << true;

    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 2, {7, 8, 9, 10}}
                                        << IntMatrix{3, 2, {1, 4, 2, 5, 3, 6}} << 2 << 3 << 3 << 2 << false;

    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{}
                                        << IntMatrix{3, 2, {1, 4, 2, 5, 3, 6}} << 2 << 3 << 3 << 2 << false;

    QTest::newRow("different matrixes") << IntMatrix{} << IntMatrix{2, 2, {1, 2, 3, 4}}
                                        << IntMatrix{} << 0 << 0 << 0 << 0 << false;

    QTest::newRow("different matrixes") << IntMatrix{} << IntMatrix{}
                                        << IntMatrix{} << 0 << 0 << 0 << 0 << false;
}

void CommonTests::testCapacityWithTranspose_data()
{
    QTest::addColumn<IntMatrixSizeType>("srcMatrixRowsCount");
    QTest::addColumn<IntMatrixSizeType>("srcMatrixColumnsCount");
    QTest::addColumn<int>("srcMatrixElementValue");
    QTest::addColumn<IntMatrixSizeType>("destMatrixRowsCount");
    QTest::addColumn<IntMatrixSizeType>("destMatrixColumnsCount");
    QTest::addColumn<int>("destMatrixElementValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<bool>("isTransposedToItself");

    QTest::newRow("transposed matrix initially empty") << 3 << 4 << 2 << 0 << 0 << 0 << 5 << 3 << false;
    QTest::newRow("transposed matrix initially empty") << 4 << 3 << 2 << 0 << 0 << 0 << 3 << 5 << false;
    QTest::newRow("transposed matrix initially empty") << 7 << 8 << 2 << 0 << 0 << 0 << 10 << 8 << false;
    QTest::newRow("transposed matrix initially empty") << 8 << 7 << 2 << 0 << 0 << 0 << 8 << 10 << false;
    QTest::newRow("transposed matrix initially NOT empty") << 8 << 7 << 2 << 5 << 6 << 2 << 8 << 10 << false;
    QTest::newRow("transposed matrix initially NOT empty") << 8 << 7 << 2 << 6 << 6 << 2 << 7 << 10 << false;
    QTest::newRow("transposed matrix initially NOT empty") << 8 << 7 << 2 << 5 << 7 << 2 << 8 << 8 << false;
    QTest::newRow("transposed matrix initially NOT empty") << 8 << 7 << 2 << 6 << 7 << 2 << 7 << 8 << false;
    QTest::newRow("transposed matrix initially NOT empty") << 8 << 7 << 2 << 7 << 8 << 2 << 8 << 10 << false;
    QTest::newRow("matrix transposed to itself") << 3 << 3 << 2 << 3 << 3 << 2 << 3 << 3 << true;
    QTest::newRow("matrix transposed to itself") << 3 << 4 << 2 << 3 << 4 << 2 << 5 << 5 << true;
    QTest::newRow("matrix transposed to itself") << 4 << 3 << 2 << 4 << 3 << 2 << 5 << 5 << true;
    QTest::newRow("matrix transposed to itself") << 4 << 4 << 2 << 4 << 4 << 2 << 5 << 5 << true;
    QTest::newRow("matrix transposed to itself") << 7 << 8 << 2 << 7 << 8 << 2 << 8 << 10 << true;
    QTest::newRow("matrix transposed to itself") << 8 << 7 << 2 << 8 << 7 << 2 << 10 << 8 << true;
}

void CommonTests::testClear_data()
{
    QTest::addColumn<IntMatrix>("matrix");

    QTest::newRow("non-empty matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("empty matrix") << IntMatrix{};
}

void CommonTests::testResizeWithoutFillingInNewValues_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("expectedRetainedElementsMatrix");

    QTest::newRow("equal rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 2
                                              << 4 << 2 << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};

    QTest::newRow("less rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 3
                                              << 2 << 3 << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};

    QTest::newRow("less rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2
                                             << 3 << 2 << IntMatrix{3, 2, {1, 2, 4, 5, 7, 8}};

    QTest::newRow("equal rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 5
                                              << 4 << 5 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

    QTest::newRow("more rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 3
                                              << 5 << 3 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

    QTest::newRow("more rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 4
                                             << 5 << 4 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

    QTest::newRow("equal rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 3
                                               << 4 << 3 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
}

void CommonTests::testCapacityWithResizeWithoutFillingInNewValues_data()
{
    _buildCapacityWithResizeTestingTable();
}

void CommonTests::testResizeAndFillInNewValues_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<int>("fillValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("equal rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 2 << -1
                                              << 4 << 2 << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};

    QTest::newRow("less rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 3 << -1
                                              << 2 << 3 << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};

    QTest::newRow("less rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -1
                                             << 3 << 2 << IntMatrix{3, 2, {1, 2, 4, 5, 7, 8}};

    QTest::newRow("equal rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 5 << -1
                                              << 4 << 5 << IntMatrix{4, 5, {1, 2, 3, -1, -1, 4, 5, 6, -1, -1, 7, 8, 9, -1, -1, 10, 11, 12, -1, -1}};

    QTest::newRow("more rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 3 << -1
                                              << 5 << 3 << IntMatrix{5, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1, -1}};

    QTest::newRow("more rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 4 << -1
                                             << 5 << 4 << IntMatrix{5, 4, {1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1, 10, 11, 12, -1, -1, -1, -1, -1}};

    QTest::newRow("equal rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 3 << -1
                                               << 4 << 3 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
}

void CommonTests::testCapacityWithResizeAndFillInNewValues_data()
{
    _buildCapacityWithResizeTestingTable();
}

void CommonTests::testShrinkToFit_data()
{
    QTest::addColumn<IntMatrix>("matrix");

    QTest::newRow("empty matrix") << IntMatrix{};
    QTest::newRow("square matrix") << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
    QTest::newRow("more rows than columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("less rows than columns") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("square matrix") << IntMatrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
}

void CommonTests::testInsertRowNoSetValue_data()
{
    _buildInsertRowTestingTable();
}

void CommonTests::testInsertRowSetValue_data()
{
    _buildInsertRowTestingTable();
}

void CommonTests::testCapacityWithInsertRow_data()
{
    QTest::addColumn<IntMatrixSizeType>("rowsCount");
    QTest::addColumn<IntMatrixSizeType>("columnsCount");
    QTest::addColumn<int>("elementValue");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedRowValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<bool>("isInsertedRowValueSet");

    QTest::newRow("inserted row value NOT set") << 3 << 4 << -2 << 1 << 5 << 6 << 5 << false;
    QTest::newRow("inserted row value set") << 3 << 4 << -2 << 1 << 5 << 6 << 5 << true;
    QTest::newRow("inserted row value NOT set") << 6 << 5 << -2 << 3 << 5 << 7 << 6 << false;
    QTest::newRow("inserted row value set") << 6 << 5 << -2 << 3 << 5 << 7 << 6 << true;
    QTest::newRow("inserted row value NOT set") << 8 << 2 << -2 << 5 << 5 << 10 << 2 << false;
    QTest::newRow("inserted row value set") << 8 << 2 << -2 << 5 << 5 << 10 << 2 << true;
}

void CommonTests::testInsertColumnNoSetValue_data()
{
    _buildInsertColumnTestingTable();
}

void CommonTests::testInsertColumnSetValue_data()
{
    _buildInsertColumnTestingTable();
}

void CommonTests::testCapacityWithInsertColumn_data()
{
    QTest::addColumn<IntMatrixSizeType>("rowsCount");
    QTest::addColumn<IntMatrixSizeType>("columnsCount");
    QTest::addColumn<int>("elementValue");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedColumnValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<bool>("isInsertedColumnValueSet");

    QTest::newRow("inserted column value NOT set") << 5 << 3 << 4 << 1 << 1 << 6 << 6 << false;
    QTest::newRow("inserted column value set") << 5 << 3 << 4 << 1 << 1 << 6 << 6 << true;
    QTest::newRow("inserted column value NOT set") << 5 << 7 << 4 << 1 << 1 << 6 << 8 << false;
    QTest::newRow("inserted column value set") << 5 << 7 << 4 << 1 << 1 << 6 << 8 << true;
    QTest::newRow("inserted column value NOT set") << 5 << 14 << 4 << 1 << 1 << 6 << 17 << false;
    QTest::newRow("inserted column value set") << 5 << 14 << 4 << 1 << 1 << 6 << 17 << true;
}

void CommonTests::testEraseRow_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("erasePosition");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("erase at beginning position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 3 << 5 << IntMatrix{2, 4, {5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("erase at random position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 1 << 3 << 5 << IntMatrix{2, 4, {1, 2, 3, 4, 9, 10, 11, 12}};
    QTest::newRow("erase at end position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 3 << 5 << IntMatrix{2, 4, {1, 2, 3, 4, 5, 6, 7, 8}};
    QTest::newRow("erase the only row") << IntMatrix{1, 4, {1, 2, 3, 4}} << 0 << 0 << 0 << IntMatrix{};
}

void CommonTests::testCapacityWithEraseRow_data()
{
    QTest::addColumn<IntMatrixSizeType>("rowsCount");
    QTest::addColumn<IntMatrixSizeType>("columnsCount");
    QTest::addColumn<int>("elementValue");
    QTest::addColumn<TripleSizeTypeTupleArray>("erasedRowAndExpectedCapacity");

    QTest::newRow("less rows than columns") << 3 << 4 << -2 << TripleSizeTypeTupleArray{{1, 3, 5}, {1, 3, 5}, {0, 0, 0}};
    QTest::newRow("square matrix") << 4 << 4 << -2 << TripleSizeTypeTupleArray{{1, 5, 5}, {1, 5, 5}, {1, 2, 5}, {0, 0, 0}};
    QTest::newRow("more rows than columns") << 7 << 5 << -2 << TripleSizeTypeTupleArray{{1, 8, 6}, {1, 8, 6}, {1, 8, 6}, {1, 8, 6}, {1, 4, 6}, {1, 2, 6}, {0, 0, 0}};
}

void CommonTests::testEraseColumn_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("erasePosition");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("erase at beginning position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 5 << 3 << IntMatrix{4, 2, {2, 3, 5, 6, 8, 9, 11, 12}};
    QTest::newRow("erase at random position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 1 << 5 << 3 << IntMatrix{4, 2, {1, 3, 4, 6, 7, 9, 10, 12}};
    QTest::newRow("erase at end position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 5 << 3 << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
    QTest::newRow("erase the only column") << IntMatrix{4, 1, {1, 2, 3, 4}} << 0 << 0 << 0 << IntMatrix{};
}

void CommonTests::testCapacityWithEraseColumn_data()
{
    QTest::addColumn<IntMatrixSizeType>("rowsCount");
    QTest::addColumn<IntMatrixSizeType>("columnsCount");
    QTest::addColumn<int>("elementValue");
    QTest::addColumn<TripleSizeTypeTupleArray>("erasedColumnAndExpectedCapacity");

    QTest::newRow("less columns than rows") << 4 << 3 << 4 << TripleSizeTypeTupleArray{{1, 5, 3}, {1, 5, 3}, {0, 0, 0}};
    QTest::newRow("square matrix") << 4 << 4 << 4 << TripleSizeTypeTupleArray{{1, 5, 5}, {1, 5, 5}, {1, 5, 2}, {0, 0, 0}};
    QTest::newRow("more columns than rows") << 5 << 7 << 4 << TripleSizeTypeTupleArray{{1, 6, 8}, {1, 6, 8}, {1, 6, 8}, {1, 6, 8}, {1, 6, 4}, {1, 6, 2}, {0, 0, 0}};
}

void CommonTests::testCatByRow_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("firstSrcMatrix");
    QTest::addColumn<IntMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("expectedDestMatrix");

    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}} << ConcatMode::ALL_DIFFERENT
                                             << 3 << 2 << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}};

    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}} << ConcatMode::ALL_DIFFERENT
                                             << 3 << 3 << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}};

    QTest::newRow("scenario: all different") << IntMatrix{4, 1, {7, 8, 9, 10}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}} << ConcatMode::ALL_DIFFERENT
                                             << 5 << 2 << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}};

    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}} << ConcatMode::ALL_DIFFERENT
                                             << 3 << 2 << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}};

    QTest::newRow("scenario: destination first") << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}} << ConcatMode::DESTINATION_FIRST
                                                 << 3 << 2 << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}};

    QTest::newRow("scenario: destination second") << IntMatrix{1, 2, {5, 6}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}} << ConcatMode::DESTINATION_SECOND
                                                  << 3 << 2 << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}};

    QTest::newRow("scenario: destination all") << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 2, {1, 2, 3, 4}} << ConcatMode::DESTINATION_ALL
                                               << 5 << 2 << IntMatrix{4, 2, {1, 2, 3, 4, 1, 2, 3, 4}};

    QTest::newRow("scenario: source both") << IntMatrix{} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 2, {1, 2, 3, 4}} << ConcatMode::SOURCE_BOTH
                                           << 5 << 2 << IntMatrix{4, 2, {1, 2, 3, 4, 1, 2, 3, 4}};
}

void CommonTests::testCapacityWithCatByRow_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("firstSrcMatrix");
    QTest::addColumn<IntMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("scenario: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 0 << 0 << 0 << 0
                                                 << 11 << 8;

    QTest::newRow("scenario: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 8 << 8
                                                 << 11 << 8;

    QTest::newRow("scenario: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 9 << 8
                                                 << 9 << 8;

    QTest::newRow("scenario: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 10 << 8
                                                 << 10 << 8;

    QTest::newRow("scenario: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 0 << 0 << 0 << 0
                                                 << 11 << 8;

    QTest::newRow("scenario: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 8 << 8
                                                 << 11 << 8;

    QTest::newRow("scenario: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 9 << 8
                                                 << 9 << 8;

    QTest::newRow("scenario: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 10 << 8
                                                 << 10 << 8;

    QTest::newRow("scenario: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 0 << 0 << 0 << 0
                                                 << 10 << 8;

    QTest::newRow("scenario: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4 << 7 << 7 << 8
                                                 << 10 << 8;

    QTest::newRow("scenario: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4 << 7 << 8 << 8
                                                 << 8 << 8;

    QTest::newRow("scenario: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4 << 7 << 9 << 8
                                                 << 9 << 8;

    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0
                                                 << 11 << 8;

    QTest::newRow("scenario: all different") << IntMatrix{7, 5, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0
                                                 << 11 << 8;

    QTest::newRow("scenario: all different") << IntMatrix{10, 5, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0
                                                 << 12 << 8;

    QTest::newRow("scenario: all different") << IntMatrix{6, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0
                                                 << 11 << 7;

    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 7
                                                 << 9 << 7;

    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 8
                                                 << 9 << 8;

    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 7
                                                 << 10 << 7;

    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 8
                                                 << 10 << 8;
}

void CommonTests::testCatByColumn_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("firstSrcMatrix");
    QTest::addColumn<IntMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("expectedDestMatrix");

    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 1, {5, 6}} << ConcatMode::ALL_DIFFERENT
                                             << 2 << 3 << IntMatrix{2, 3, {1, 2, 5, 3, 4, 6}};

    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 1, {5, 6}} << ConcatMode::ALL_DIFFERENT
                                             << 3 << 3 << IntMatrix{2, 3, {1, 2, 5, 3, 4, 6}};

    QTest::newRow("scenario: all different") << IntMatrix{1, 4, {7, 8, 9, 10}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 1, {5, 6}} << ConcatMode::ALL_DIFFERENT
                                             << 2 << 5 << IntMatrix{2, 3, {1, 2, 5, 3, 4, 6}};

    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 1, {5, 6}} << ConcatMode::ALL_DIFFERENT
                                             << 2 << 3 << IntMatrix{2, 3, {1, 2, 5, 3, 4, 6}};

    QTest::newRow("scenario: destination first") << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 1, {5, 6}} << ConcatMode::DESTINATION_FIRST
                                                 << 2 << 3 << IntMatrix{2, 3, {1, 2, 5, 3, 4, 6}};

    QTest::newRow("scenario: destination second") << IntMatrix{2, 1, {5, 6}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 1, {5, 6}} << ConcatMode::DESTINATION_SECOND
                                                  << 2 << 3 << IntMatrix{2, 3, {1, 2, 5, 3, 4, 6}};

    QTest::newRow("scenario: destination all") << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 2, {1, 2, 3, 4}} << ConcatMode::DESTINATION_ALL
                                               << 2 << 5 << IntMatrix{2, 4, {1, 2, 1, 2, 3, 4, 3, 4}};

    QTest::newRow("scenario: source both") << IntMatrix{} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 2, {1, 2, 3, 4}} << ConcatMode::SOURCE_BOTH
                                           << 2 << 5 << IntMatrix{2, 4, {1, 2, 1, 2, 3, 4, 3, 4}};
}

void CommonTests::testCapacityWithCatByColumn_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("firstSrcMatrix");
    QTest::addColumn<IntMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("scenario: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 0 << 0 << 0 << 0
                                                 << 8 << 11;

    QTest::newRow("scenario: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 8
                                                 << 8 << 11;

    QTest::newRow("scenario: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 9
                                                 << 8 << 9;

    QTest::newRow("scenario: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 10
                                                 << 8 << 10;

    QTest::newRow("scenario: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 0 << 0 << 0 << 0
                                                 << 8 << 11;

    QTest::newRow("scenario: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 8
                                                 << 8 << 11;

    QTest::newRow("scenario: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 9
                                                 << 8 << 9;

    QTest::newRow("scenario: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 10
                                                 << 8 << 10;

    QTest::newRow("scenario: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 0 << 0 << 0 << 0
                                                 << 8 << 10;

    QTest::newRow("scenario: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 7
                                                 << 8 << 10;

    QTest::newRow("scenario: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 8
                                                 << 8 << 8;

    QTest::newRow("scenario: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 9
                                                 << 8 << 9;

    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0
                                                 << 8 << 11;

    QTest::newRow("scenario: all different") << IntMatrix{5, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0
                                                 << 8 << 11;

    QTest::newRow("scenario: all different") << IntMatrix{5, 10, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0
                                                 << 8 << 12;

    QTest::newRow("scenario: all different") << IntMatrix{6, 6, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0
                                                 << 7 << 11;

    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 9
                                                 << 7 << 9;

    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 9
                                                 << 8 << 9;

    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 10
                                                 << 7 << 10;

    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 10
                                                 << 8 << 10;
}

void CommonTests::testSplitByRow_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("firstDestMatrix");
    QTest::addColumn<IntMatrix>("secondDestMatrix");
    QTest::addColumn<IntMatrixSizeType>("splitPosition");
    QTest::addColumn<SplitMode>("mode");
    QTest::addColumn<IntMatrixSizeType>("expectedFirstDestRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedFirstDestColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedSecondDestRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedSecondDestColumnCapacity");
    QTest::addColumn<IntMatrix>("expectedFirstDestMatrix");
    QTest::addColumn<IntMatrix>("expectedSecondDestMatrix");

    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 2 << SplitMode::ALL_DIFFERENT
                                             << 2 << 2 << 1 << 2 << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}};

    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{1, 2, {7, 8}} << IntMatrix{} << 2 << SplitMode::ALL_DIFFERENT
                                             << 2 << 2 << 1 << 2 << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}};

    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{2, 2, {9, 10, 11, 12}} << 2 << SplitMode::ALL_DIFFERENT
                                             << 2 << 2 << 2 << 2 << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}};

    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{1, 2, {7, 8}} << IntMatrix{2, 2, {9, 10, 11, 12}} << 2 << SplitMode::ALL_DIFFERENT
                                             << 2 << 2 << 2 << 2 << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}};

    QTest::newRow("scenario: source first") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << 2 << SplitMode::SOURCE_FIRST
                                            << 3 << 2 << 1 << 2 << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}};

    QTest::newRow("scenario: source first") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 2, {9, 10, 11, 12}} << 2 << SplitMode::SOURCE_FIRST
                                            << 3 << 2 << 2 << 2 << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}};

    QTest::newRow("scenario: source second") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 2 << SplitMode::SOURCE_SECOND
                                             << 2 << 2 << 3 << 2 << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}};

    QTest::newRow("scenario: source second") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{1, 2, {7, 8}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 2 << SplitMode::SOURCE_SECOND
                                             << 2 << 2 << 3 << 2 << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}};
}

void CommonTests::testCapacityWithSplitByRow_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("firstDestMatrix");
    QTest::addColumn<IntMatrix>("secondDestMatrix");
    QTest::addColumn<IntMatrixSizeType>("splitPosition");
    QTest::addColumn<SplitMode>("mode");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnCapacity");
    QTest::addColumn<bool>("isFirstDestResized");
    QTest::addColumn<IntMatrixSizeType>("expectedFirstDestRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedFirstDestColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedSecondDestRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedSecondDestColumnCapacity");

    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false
                                            << 18 << 21 << 8 << 21;

    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false
                                            << 18 << 21 << 8 << 21;

    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << 8 << SplitMode::SOURCE_FIRST << 5 << 8 << 6 << 17 << false
                                            << 18 << 21 << 8 << 17;

    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << 8 << SplitMode::SOURCE_FIRST << 5 << 8 << 6 << 18 << false
                                            << 18 << 21 << 8 << 18;

    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{6, 15, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false
                                            << 18 << 21 << 7 << 18;

    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{7, 17, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false
                                            << 18 << 21 << 8 << 21;

    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false
                                             << 10 << 21 << 18 << 21;

    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false
                                             << 10 << 21 << 18 << 21;

    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 6 << 8 << 7 << 17 << true
                                             << 10 << 17 << 18 << 21;

    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 6 << 8 << 7 << 18 << true
                                             << 10 << 18 << 18 << 21;

    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{7, 15, 2} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false
                                             << 8 << 18 << 18 << 21;

    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{8, 17, 2} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false
                                             << 10 << 21 << 18 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 10 << 21 << 8 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 10 << 21 << 8 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 17 << true
                                             << 10 << 17 << 8 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 18 << true
                                             << 10 << 18 << 8 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{7, 15, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 8 << 18 << 8 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{8, 17, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 10 << 21 << 8 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{5, 8, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 10 << 21 << 8 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{5, 8, 2} << 8 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 17 << false
                                             << 10 << 21 << 8 << 17;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{5, 8, 2} << 8 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 18 << false
                                             << 10 << 21 << 8 << 18;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{6, 15, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 10 << 21 << 7 << 18;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{7, 17, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 10 << 21 << 8 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{8, 17, 2} << IntMatrix{7, 17, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 10 << 21 << 8 << 21;

    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false
                                             << 18 << 21 << 10 << 21;

    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false
                                             << 18 << 21 << 10 << 21;

    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << 7 << SplitMode::SOURCE_FIRST << 6 << 8 << 7 << 17 << false
                                             << 18 << 21 << 10 << 17;

    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << 7 << SplitMode::SOURCE_FIRST << 6 << 8 << 7 << 18 << false
                                             << 18 << 21 << 10 << 18;

    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{7, 15, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false
                                             << 18 << 21 << 8 << 18;

    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{8, 17, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false
                                             << 18 << 21 << 10 << 21;

    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false
                                             << 8 << 21 << 18 << 21;

    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false
                                             << 8 << 21 << 18 << 21;

    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 5 << 8 << 6 << 17 << true
                                             << 8 << 17 << 18 << 21;

    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 5 << 8 << 6 << 18 << true
                                             << 8 << 18 << 18 << 21;

    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{6, 15, 2} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false
                                             << 7 << 18 << 18 << 21;

    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{7, 17, 2} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false
                                             << 8 << 21 << 18 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 8 << 21 << 10 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 8 << 21 << 10 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 17 << true
                                             << 8 << 17 << 10 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 18 << true
                                             << 8 << 18 << 10 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{6, 15, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 7 << 18 << 10 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{7, 17, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 8 << 21 << 10 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{6, 8, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 8 << 21 << 10 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{6, 8, 2} << 7 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 17 << false
                                             << 8 << 21 << 10 << 17;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{6, 8, 2} << 7 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 18 << false
                                             << 8 << 21 << 10 << 18;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{7, 15, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 8 << 21 << 8 << 18;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{8, 17, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 8 << 21 << 10 << 21;

    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{7, 17, 2} << IntMatrix{8, 17, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 8 << 21 << 10 << 21;
}

void CommonTests::testSplitByColumn_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("firstDestMatrix");
    QTest::addColumn<IntMatrix>("secondDestMatrix");
    QTest::addColumn<IntMatrixSizeType>("splitPosition");
    QTest::addColumn<SplitMode>("mode");
    QTest::addColumn<IntMatrixSizeType>("expectedFirstDestRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedFirstDestColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedSecondDestRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedSecondDestColumnCapacity");
    QTest::addColumn<IntMatrix>("expectedFirstDestMatrix");
    QTest::addColumn<IntMatrix>("expectedSecondDestMatrix");

    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 2 << SplitMode::ALL_DIFFERENT
                                             << 2 << 2 << 2 << 1 << IntMatrix{2, 2, {1, 2, 4, 5}} << IntMatrix{2, 1, {3, 6}};

    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 1, {7, 8}} << IntMatrix{} << 2 << SplitMode::ALL_DIFFERENT
                                             << 2 << 2 << 2 << 1 << IntMatrix{2, 2, {1, 2, 4, 5}} << IntMatrix{2, 1, {3, 6}};

    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{2, 2, {9, 10, 11, 12}} << 2 << SplitMode::ALL_DIFFERENT
                                             << 2 << 2 << 2 << 2 << IntMatrix{2, 2, {1, 2, 4, 5}} << IntMatrix{2, 1, {3, 6}};

    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 1, {7, 8}} << IntMatrix{2, 2, {9, 10, 11, 12}} << 2 << SplitMode::ALL_DIFFERENT
                                             << 2 << 2 << 2 << 2 << IntMatrix{2, 2, {1, 2, 4, 5}} << IntMatrix{2, 1, {3, 6}};

    QTest::newRow("scenario: source first") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << 2 << SplitMode::SOURCE_FIRST
                                            << 2 << 3 << 2 << 1 << IntMatrix{2, 2, {1, 2, 4, 5}} << IntMatrix{2, 1, {3, 6}};

    QTest::newRow("scenario: source first") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 2, {9, 10, 11, 12}} << 2 << SplitMode::SOURCE_FIRST
                                            << 2 << 3 << 2 << 2 << IntMatrix{2, 2, {1, 2, 4, 5}} << IntMatrix{2, 1, {3, 6}};

    QTest::newRow("scenario: source second") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2 << SplitMode::SOURCE_SECOND
                                             << 2 << 2 << 2 << 3 << IntMatrix{2, 2, {1, 2, 4, 5}} << IntMatrix{2, 1, {3, 6}};

    QTest::newRow("scenario: source second") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{1, 2, {7, 8}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2 << SplitMode::SOURCE_SECOND
                                             << 2 << 2 << 2 << 3 << IntMatrix{2, 2, {1, 2, 4, 5}} << IntMatrix{2, 1, {3, 6}};
}

void CommonTests::testCapacityWithSplitByColumn_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("firstDestMatrix");
    QTest::addColumn<IntMatrix>("secondDestMatrix");
    QTest::addColumn<IntMatrixSizeType>("splitPosition");
    QTest::addColumn<SplitMode>("mode");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnCapacity");
    QTest::addColumn<bool>("isFirstDestResized");
    QTest::addColumn<IntMatrixSizeType>("expectedFirstDestRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedFirstDestColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedSecondDestRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedSecondDestColumnCapacity");

    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false
                                            << 21 << 18 << 21 << 8;

    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false
                                            << 21 << 18 << 21 << 8;

    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << 8 << SplitMode::SOURCE_FIRST << 8 << 5 << 17 << 6 << false
                                            << 21 << 18 << 17 << 8;

    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << 8 << SplitMode::SOURCE_FIRST << 8 << 5 << 18 << 6 << false
                                            << 21 << 18 << 18 << 8;

    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{15, 6, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false
                                            << 21 << 18 << 18 << 7;

    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{17, 7, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false
                                            << 21 << 18 << 21 << 8;

    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false
                                             << 21 << 10 << 21 << 18;

    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false
                                             << 21 << 10 << 21 << 18;

    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 8 << 6 << 17 << 7 << true
                                             << 17 << 10 << 21 << 18;

    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 8 << 6 << 18 << 7 << true
                                             << 18 << 10 << 21 << 18;

    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{15, 7, 2} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false
                                             << 18 << 8 << 21 << 18;

    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{17, 8, 2} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false
                                             << 21 << 10 << 21 << 18;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 21 << 10 << 21 << 8;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 21 << 10 << 21 << 8;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 8 << 6 << 17 << 7 << true
                                             << 17 << 10 << 21 << 8;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 8 << 6 << 18 << 7 << true
                                             << 18 << 10 << 21 << 8;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{15, 7, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 18 << 8 << 21 << 8;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{17, 8, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 21 << 10 << 21 << 8;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 5, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 21 << 10 << 21 << 8;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 5, 2} << 8 << SplitMode::ALL_DIFFERENT << 8 << 5 << 17 << 6 << false
                                             << 21 << 10 << 17 << 8;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 5, 2} << 8 << SplitMode::ALL_DIFFERENT << 8 << 5 << 18 << 6 << false
                                             << 21 << 10 << 18 << 8;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{15, 6, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 21 << 10 << 18 << 7;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{17, 7, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 21 << 10 << 21 << 8;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{17, 8, 2} << IntMatrix{17, 7, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 21 << 10 << 21 << 8;

    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false
                                             << 21 << 18 << 21 << 10;

    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false
                                             << 21 << 18 << 21 << 10;

    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << 7 << SplitMode::SOURCE_FIRST << 8 << 6 << 17 << 7 << false
                                             << 21 << 18 << 17 << 10;

    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << 7 << SplitMode::SOURCE_FIRST << 8 << 6 << 18 << 7 << false
                                             << 21 << 18 << 18 << 10;

    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{15, 7, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false
                                             << 21 << 18 << 18 << 8;

    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{17, 8, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false
                                             << 21 << 18 << 21 << 10;

    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false
                                             << 21 << 8 << 21 << 18;

    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false
                                             << 21 << 8 << 21 << 18;

    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 8 << 5 << 17 << 6 << true
                                             << 17 << 8 << 21 << 18;

    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 8 << 5 << 18 << 6 << true
                                             << 18 << 8 << 21 << 18;

    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{15, 6, 2} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false
                                             << 18 << 7 << 21 << 18;

    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{17, 7, 2} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false
                                             << 21 << 8 << 21 << 18;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 21 << 8 << 21 << 10;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 21 << 8 << 21 << 10;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 8 << 5 << 17 << 6 << true
                                             << 17 << 8 << 21 << 10;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 8 << 5 << 18 << 6 << true
                                             << 18 << 8 << 21 << 10;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{15, 6, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 18 << 7 << 21 << 10;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{17, 7, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 21 << 8 << 21 << 10;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 6, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 21 << 8 << 21 << 10;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 6, 2} << 7 << SplitMode::ALL_DIFFERENT << 8 << 6 << 17 << 7 << false
                                             << 21 << 8 << 17 << 10;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 6, 2} << 7 << SplitMode::ALL_DIFFERENT << 8 << 6 << 18 << 7 << false
                                             << 21 << 8 << 18 << 10;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{15, 7, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 21 << 8 << 18 << 8;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{17, 8, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 21 << 8 << 21 << 10;

    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{17, 7, 2} << IntMatrix{17, 8, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false
                                             << 21 << 8 << 21 << 10;
}

void CommonTests::testSwapMatrixes_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");

    QTest::newRow("non-empty matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
    QTest::newRow("one empty matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{};
    QTest::newRow("one empty matrix") << IntMatrix{} << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
    QTest::newRow("both matrixes empty") << IntMatrix{} << IntMatrix{};
}

void CommonTests::testSwapItems_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<IntMatrixSizeType>("firstItemRowNr");
    QTest::addColumn<IntMatrixSizeType>("firstItemColumnNr");
    QTest::addColumn<IntMatrixSizeType>("secondItemRowNr");
    QTest::addColumn<IntMatrixSizeType>("secondItemColumnNr");
    QTest::addColumn<bool>("isSwapWithinMatrix");
    QTest::addColumn<IntMatrix>("expectedFirstMatrix");
    QTest::addColumn<IntMatrix>("expectedSecondMatrix");

    QTest::newRow("same matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 1 << 2 << 0 << 1 << true
                                 << IntMatrix{2, 3, {1, 6, 3, 4, 5, 2}} << IntMatrix{2, 3, {1, 6, 3, 4, 5, 2}};

    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}} << 1 << 2 << 2 << 0 << false
                                        << IntMatrix{2, 3, {1, 2, 3, 4, 5, 11}} << IntMatrix{3, 2, {7, 8, 9, 10, 6, 12}};
}

void CommonTests::testSwapRows_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<IntMatrixSizeType>("firstRowNr");
    QTest::addColumn<IntMatrixSizeType>("secondRowNr");
    QTest::addColumn<bool>("isSwapWithinMatrix");
    QTest::addColumn<IntMatrix>("expectedFirstMatrix");
    QTest::addColumn<IntMatrix>("expectedSecondMatrix");

    QTest::newRow("same matrix") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 2 << true
                                 << IntMatrix{4, 3, {7, 8, 9, 4, 5, 6, 1, 2, 3, 10, 11, 12}} << IntMatrix{4, 3, {7, 8, 9, 4, 5, 6, 1, 2, 3, 10, 11, 12}};

    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{4, 3, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 0 << 3 << false
                                        << IntMatrix{2, 3, {16, 17, 18, 4, 5, 6}} << IntMatrix{4, 3, {7, 8, 9, 10, 11, 12, 13, 14, 15, 1, 2, 3}};
}

void CommonTests::testSwapColumns_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<IntMatrixSizeType>("firstColumnNr");
    QTest::addColumn<IntMatrixSizeType>("secondColumnNr");
    QTest::addColumn<bool>("isSwapWithinMatrix");
    QTest::addColumn<IntMatrix>("expectedFirstMatrix");
    QTest::addColumn<IntMatrix>("expectedSecondMatrix");

    QTest::newRow("same matrix") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 2 << true
                                 << IntMatrix{3, 4, {3, 2, 1, 4, 7, 6, 5, 8, 11, 10, 9, 12}} << IntMatrix{3, 4, {3, 2, 1, 4, 7, 6, 5, 8, 11, 10, 9, 12}};

    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 0 << 3 << false
                                        << IntMatrix{3, 2, {10, 2, 14, 4, 18, 6}} << IntMatrix{3, 4, {7, 8, 9, 1, 11, 12, 13, 3, 15, 16, 17, 5}};
}

void CommonTests::testSetAllItemsToValue_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<int>("value");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("non-empty matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 7 << IntMatrix{2, 3, 7};
    QTest::newRow("empty matrix") << IntMatrix{} << 7 << IntMatrix{};
}

void CommonTests::testCopy_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrixSizeType>("copiedRowsCount");
    QTest::addColumn<IntMatrixSizeType>("copiedColumnsCount");
    QTest::addColumn<IntMatrixSizeType>("srcCopyRowNr");
    QTest::addColumn<IntMatrixSizeType>("srcCopyColumnNr");
    QTest::addColumn<IntMatrixSizeType>("destCopyRowNr");
    QTest::addColumn<IntMatrixSizeType>("destCopyColumnNr");
    QTest::addColumn<IntMatrix>("expectedDestMatrix");

    QTest::newRow("elements copied") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                     << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 1 << 1 << 0
                                     << IntMatrix{4, 3, {1, 2, 3, 22, 23, 6, 26, 27, 9, 30, 31, 12}};

    QTest::newRow("no rows to be copied") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                          << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 2 << 2 << 1 << 1 << 0
                                          << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

    QTest::newRow("no columns to be copied") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                             << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 0 << 2 << 1 << 1 << 0
                                             << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

    QTest::newRow("no elements to be copied") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                              << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 0 << 2 << 1 << 1 << 0
                                              << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
}

void CommonTests::_buildCapacityWithMoveCopyConstructorsTestingTable()
{
    QTest::addColumn<IntMatrixSizeType>("rowsCount");
    QTest::addColumn<IntMatrixSizeType>("columnsCount");
    QTest::addColumn<int>("elementValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("") << 3 << 4 << -1 << 3 << 5;
    QTest::newRow("") << 4 << 3 << -1 << 5 << 3;
    QTest::newRow("") << 7 << 8 << -1 << 8 << 10;
    QTest::newRow("") << 8 << 7 << -1 << 10 << 8;
}

void CommonTests::_buildCapacityWithAssignmentOperatorsTestingTable()
{
    QTest::addColumn<IntMatrixSizeType>("srcMatrixRowsCount");
    QTest::addColumn<IntMatrixSizeType>("srcMatrixColumnsCount");
    QTest::addColumn<int>("srcMatrixElementValue");
    QTest::addColumn<IntMatrixSizeType>("destMatrixRowsCount");
    QTest::addColumn<IntMatrixSizeType>("destMatrixColumnsCount");
    QTest::addColumn<int>("destMatrixElementValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("destination matrix initially empty") << 3 << 4 << -1 << 0 << 0 << 0 << 3 << 5;
    QTest::newRow("destination matrix initially empty") << 4 << 3 << -1 << 0 << 0 << 0 << 5 << 3;
    QTest::newRow("destination matrix initially empty") << 7 << 8 << -1 << 0 << 0 << 0 << 8 << 10;
    QTest::newRow("destination matrix initially empty") << 8 << 7 << -1 << 0 << 0 << 0 << 10 << 8;
    QTest::newRow("destination matrix initially NOT empty") << 3 << 4 << -1 << 2 << 3 << -5 << 3 << 5;
    QTest::newRow("destination matrix initially NOT empty") << 4 << 3 << -1 << 2 << 3 << -5 << 5 << 3;
    QTest::newRow("destination matrix initially NOT empty") << 7 << 8 << -1 << 3 << 4 << -5 << 8 << 10;
    QTest::newRow("destination matrix initially NOT empty") << 8 << 7 << -1 << 3 << 4 << -5 << 10 << 8;
}

void CommonTests::_buildCapacityWithResizeTestingTable()
{
    QTest::addColumn<IntMatrixSizeType>("initialRowsCount");
    QTest::addColumn<IntMatrixSizeType>("initialColumnsCount");
    QTest::addColumn<int>("initialElementValue");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<int>("resizeElementValue");
    QTest::addColumn<IntMatrixSizeType>("requestedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("requestedColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 9 << 6 << 10 << 7;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 9 << 7 << 10 << 7;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 9 << 8 << 10 << 8;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 9 << 9 << 10 << 9;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 9 << 10 << 10 << 10;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 9 << 11 << 10 << 11;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 9 << 0 << 10 << 7;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 10 << 6 << 10 << 7;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 10 << 7 << 10 << 7;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 10 << 8 << 10 << 8;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 10 << 9 << 10 << 9;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 10 << 10 << 10 << 10;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 10 << 11 << 10 << 11;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 10 << 0 << 10 << 7;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 11 << 6 << 11 << 7;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 11 << 7 << 11 << 7;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 11 << 8 << 11 << 8;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 11 << 0 << 11 << 7;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 12 << 6 << 12 << 7;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 12 << 7 << 12 << 7;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 12 << 8 << 12 << 8;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 12 << 0 << 12 << 7;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 13 << 6 << 13 << 7;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 13 << 7 << 13 << 7;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 13 << 8 << 13 << 8;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 13 << 0 << 13 << 7;
    QTest::newRow("equal rows, less columns") << 10 << 8 << -2 << 10 << 7 << -5 << 0 << 0 << 10 << 7;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 8 << 7 << 9 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 8 << 8 << 9 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 8 << 9 << 9 << 9;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 8 << 10 << 9 << 10;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 8 << 11 << 9 << 11;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 8 << 0 << 9 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 9 << 7 << 9 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 9 << 8 << 9 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 9 << 9 << 9 << 9;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 9 << 10 << 9 << 10;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 9 << 11 << 9 << 11;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 9 << 0 << 9 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 10 << 7 << 10 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 10 << 8 << 10 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 10 << 9 << 10 << 9;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 10 << 10 << 10 << 10;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 10 << 11 << 10 << 11;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 10 << 0 << 10 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 11 << 7 << 11 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 11 << 8 << 11 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 11 << 0 << 11 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 12 << 7 << 12 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 12 << 8 << 12 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 12 << 0 << 12 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 13 << 7 << 13 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 13 << 8 << 13 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 13 << 0 << 13 << 8;
    QTest::newRow("less rows, equal columns") << 10 << 8 << -2 << 9 << 8 << -5 << 0 << 0 << 9 << 8;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 8 << 6 << 9 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 8 << 7 << 9 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 8 << 8 << 9 << 8;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 8 << 9 << 9 << 9;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 8 << 10 << 9 << 10;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 8 << 11 << 9 << 11;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 8 << 0 << 9 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 9 << 6 << 9 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 9 << 7 << 9 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 9 << 8 << 9 << 8;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 9 << 9 << 9 << 9;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 9 << 10 << 9 << 10;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 9 << 11 << 9 << 11;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 9 << 0 << 9 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 10 << 6 << 10 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 10 << 7 << 10 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 10 << 8 << 10 << 8;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 10 << 9 << 10 << 9;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 10 << 10 << 10 << 10;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 10 << 11 << 10 << 11;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 10 << 0 << 10 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 11 << 6 << 11 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 11 << 7 << 11 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 11 << 8 << 11 << 8;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 11 << 0 << 11 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 12 << 6 << 12 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 12 << 7 << 12 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 12 << 8 << 12 << 8;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 12 << 0 << 12 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 13 << 6 << 13 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 13 << 7 << 13 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 13 << 8 << 13 << 8;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 13 << 0 << 13 << 7;
    QTest::newRow("less rows, less columns") << 10 << 8 << -2 << 9 << 7 << -5 << 0 << 0 << 9 << 7;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 9 << 7 << 10 << 8;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 9 << 8 << 10 << 8;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 9 << 9 << 10 << 9;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 9 << 10 << 10 << 10;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 9 << 11 << 10 << 11;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 9 << 0 << 10 << 8;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 10 << 7 << 10 << 8;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 10 << 8 << 10 << 8;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 10 << 9 << 10 << 9;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 10 << 10 << 10 << 10;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 10 << 11 << 10 << 11;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 10 << 0 << 10 << 8;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 11 << 7 << 11 << 8;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 11 << 8 << 11 << 8;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 11 << 0 << 11 << 8;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 12 << 7 << 12 << 8;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 12 << 8 << 12 << 8;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 12 << 0 << 12 << 8;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 13 << 7 << 13 << 8;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 13 << 8 << 13 << 8;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 13 << 0 << 13 << 8;
    QTest::newRow("same rows, same columns") << 10 << 8 << -2 << 10 << 8 << -5 << 0 << 0 << 10 << 8;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 9 << 7 << 11 << 8;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 9 << 8 << 11 << 8;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 9 << 9 << 11 << 9;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 9 << 10 << 11 << 10;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 9 << 11 << 11 << 11;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 9 << 0 << 11 << 8;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 10 << 7 << 11 << 8;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 10 << 8 << 11 << 8;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 10 << 9 << 11 << 9;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 10 << 10 << 11 << 10;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 10 << 11 << 11 << 11;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 10 << 0 << 11 << 8;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 11 << 7 << 11 << 8;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 11 << 8 << 11 << 8;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 11 << 0 << 11 << 8;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 12 << 7 << 12 << 8;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 12 << 8 << 12 << 8;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 12 << 0 << 12 << 8;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 13 << 7 << 13 << 8;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 13 << 8 << 13 << 8;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 13 << 0 << 13 << 8;
    QTest::newRow("more rows, same columns") << 10 << 8 << -2 << 11 << 8 << -5 << 0 << 0 << 11 << 8;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 9 << 7 << 10 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 9 << 8 << 10 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 9 << 9 << 10 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 9 << 10 << 10 << 10;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 9 << 11 << 10 << 11;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 9 << 0 << 10 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 10 << 7 << 10 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 10 << 8 << 10 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 10 << 9 << 10 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 10 << 10 << 10 << 10;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 10 << 11 << 10 << 11;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 10 << 0 << 10 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 11 << 7 << 11 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 11 << 8 << 11 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 11 << 0 << 11 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 12 << 7 << 12 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 12 << 8 << 12 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 12 << 0 << 12 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 13 << 7 << 13 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 13 << 8 << 13 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 13 << 0 << 13 << 9;
    QTest::newRow("same rows, more columns") << 10 << 8 << -2 << 10 << 9 << -5 << 0 << 0 << 10 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 9 << 7 << 11 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 9 << 8 << 11 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 9 << 9 << 11 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 9 << 10 << 11 << 10;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 9 << 11 << 11 << 11;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 9 << 0 << 11 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 10 << 7 << 11 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 10 << 8 << 11 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 10 << 9 << 11 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 10 << 10 << 11 << 10;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 10 << 11 << 11 << 11;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 10 << 0 << 11 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 11 << 7 << 11 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 11 << 8 << 11 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 11 << 0 << 11 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 12 << 7 << 12 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 12 << 8 << 12 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 12 << 0 << 12 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 13 << 7 << 13 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 13 << 8 << 13 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 13 << 0 << 13 << 9;
    QTest::newRow("more rows, more columns") << 10 << 8 << -2 << 11 << 9 << -5 << 0 << 0 << 11 << 9;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 9 << 6 << 11 << 7;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 9 << 7 << 11 << 7;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 9 << 8 << 11 << 8;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 9 << 9 << 11 << 9;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 9 << 10 << 11 << 10;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 9 << 11 << 11 << 11;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 9 << 0 << 11 << 7;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 10 << 6 << 11 << 7;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 10 << 7 << 11 << 7;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 10 << 8 << 11 << 8;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 10 << 9 << 11 << 9;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 10 << 10 << 11 << 10;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 10 << 11 << 11 << 11;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 10 << 0 << 11 << 7;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 11 << 6 << 11 << 7;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 11 << 7 << 11 << 7;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 11 << 8 << 11 << 8;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 11 << 0 << 11 << 7;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 12 << 6 << 12 << 7;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 12 << 7 << 12 << 7;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 12 << 8 << 12 << 8;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 12 << 0 << 12 << 7;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 13 << 6 << 13 << 7;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 13 << 7 << 13 << 7;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 13 << 8 << 13 << 8;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 13 << 0 << 13 << 7;
    QTest::newRow("more rows, less columns") << 10 << 8 << -2 << 11 << 7 << -5 << 0 << 0 << 11 << 7;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 8 << 7 << 9 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 8 << 8 << 9 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 8 << 9 << 9 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 8 << 10 << 9 << 10;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 8 << 11 << 9 << 11;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 8 << 0 << 9 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 9 << 7 << 9 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 9 << 8 << 9 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 9 << 9 << 9 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 9 << 10 << 9 << 10;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 9 << 11 << 9 << 11;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 9 << 0 << 9 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 10 << 7 << 10 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 10 << 8 << 10 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 10 << 9 << 10 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 10 << 10 << 10 << 10;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 10 << 11 << 10 << 11;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 10 << 0 << 10 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 11 << 7 << 11 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 11 << 8 << 11 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 11 << 0 << 11 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 12 << 7 << 12 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 12 << 8 << 12 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 12 << 0 << 12 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 13 << 7 << 13 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 13 << 8 << 13 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 13 << 0 << 13 << 9;
    QTest::newRow("less rows, more columns") << 10 << 8 << -2 << 9 << 9 << -5 << 0 << 0 << 9 << 9;
}

void CommonTests::_buildInsertRowTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedRowValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("referenceMatrix");

    QTest::newRow("insert at random position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << -1
                                                         << 5 << 3 << IntMatrix{5, 3, {1, 2, 3, 4, 5, 6, -1, -1, -1, 7, 8, 9, 10, 11, 12}};

    QTest::newRow("insert at beginning position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << -1
                                                            << 5 << 3 << IntMatrix{5, 3, {-1, -1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

    QTest::newRow("insert at end position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << -1
                                                      << 5 << 3 << IntMatrix{5, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1, -1}};
}

void CommonTests::_buildInsertColumnTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedColumnValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("referenceMatrix");

    QTest::newRow("insert at random position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << -1
                                                         << 3 << 5 << IntMatrix{3, 5, {1, 2, -1, 3, 4, 5, 6, -1, 7, 8, 9, 10, -1, 11, 12}};

    QTest::newRow("insert at beginning position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << -1
                                                            << 3 << 5 << IntMatrix{3, 5, {-1, 1, 2, 3, 4, -1, 5, 6, 7, 8, -1, 9, 10, 11, 12}};

    QTest::newRow("insert at end position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << -1
                                                      << 3 << 5 << IntMatrix{3, 5, {1, 2, 3, 4, -1, 5, 6, 7, 8, -1, 9, 10, 11, 12, -1}};
}

QTEST_APPLESS_MAIN(CommonTests)

#include "tst_commontests.moc"
