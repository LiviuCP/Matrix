#include <QtTest>

#include "matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixSizeType = IntMatrix::size_type;

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
Q_DECLARE_METATYPE(ConcatMode)
Q_DECLARE_METATYPE(SplitMode)

class FunctionalityTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testDefaultConstructor();
    void testInitListConstructor();
    void testIdenticalMatrixConstructor();
    void testDiagonalMatrixConstructor();
    void testCopyConstructor();
    void testMoveConstructor();
    void testCopyAssignmentOperator();
    void testMoveAssignmentOperator();
    void testBooleanOperator();
    void testMatrixesAreEqual();
    void testMatrixesAreNotEqual();
    void testFunctionAt();
    void testSquareBracketsOperator();
    void testGetBaseArray();
    void testTranspose();
    void testClear();
    void testResizeWithoutFillingInNewValues();
    void testResizeAndFillInNewValues();
    void testShrinkToFit();
    void testInsertRowNoSetValue();
    void testInsertRowSetValue();
    void testInsertColumnNoSetValue();
    void testInsertColumnSetValue();
    void testEraseRow();
    void testEraseColumn();
    void testCatByRow();
    void testCatByColumn();
    void testSplitByRow();
    void testSplitByColumn();
    void testSwapMatrixes();
    void testSwapItems();
    void testSwapRows();
    void testSwapColumns();
    void testSwapRowColumn();
    void testSetAllItemsToValue();
    void testCopy();

    // test data
    void testBooleanOperator_data();
    void testMatrixesAreEqual_data();
    void testMatrixesAreNotEqual_data();
    void testTranspose_data();
    void testClear_data();
    void testResizeWithoutFillingInNewValues_data();
    void testResizeAndFillInNewValues_data();
    void testShrinkToFit_data();
    void testInsertRowNoSetValue_data();
    void testInsertRowSetValue_data();
    void testInsertColumnNoSetValue_data();
    void testInsertColumnSetValue_data();
    void testEraseRow_data();
    void testEraseColumn_data();
    void testCatByRow_data();
    void testCatByColumn_data();
    void testSplitByRow_data();
    void testSplitByColumn_data();
    void testSwapMatrixes_data();
    void testSwapItems_data();
    void testSwapRows_data();
    void testSwapColumns_data();
    void testSetAllItemsToValue_data();
    void testCopy_data();

private:
    // test data helper methods
    void _buildInsertRowTestingTable();
    void _buildInsertColumnTestingTable();

    IntMatrix mPrimaryIntMatrix;
    IntMatrix mSecondaryIntMatrix;
};

void FunctionalityTests::testDefaultConstructor()
{
    IntMatrix matrix{};

    QVERIFY2(matrix.getNrOfRows() == 0 &&
             matrix.getNrOfColumns() == 0, "Default constructor initialized matrix with wrong number of rows and columns");

    QVERIFY2(matrix.getRowCapacity() == 0 &&
             matrix.getColumnCapacity() == 0, "Default constructor initialized matrix with wrong capacity");
}

void FunctionalityTests::testInitListConstructor()
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

void FunctionalityTests::testIdenticalMatrixConstructor()
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

void FunctionalityTests::testDiagonalMatrixConstructor()
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

void FunctionalityTests::testCopyConstructor()
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

void FunctionalityTests::testMoveConstructor()
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

void FunctionalityTests::testCopyAssignmentOperator()
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

void FunctionalityTests::testMoveAssignmentOperator()
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

void FunctionalityTests::testBooleanOperator()
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

void FunctionalityTests::testMatrixesAreEqual()
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

void FunctionalityTests::testMatrixesAreNotEqual()
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
void FunctionalityTests::testFunctionAt()
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

void FunctionalityTests::testSquareBracketsOperator()
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

void FunctionalityTests::testGetBaseArray()
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

void FunctionalityTests::testTranspose()
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

void FunctionalityTests::testClear()
{
    QFETCH(IntMatrix, matrix);

    mPrimaryIntMatrix = matrix;
    mPrimaryIntMatrix.clear();

    QVERIFY2(mPrimaryIntMatrix.getRowCapacity() == 0 &&
             mPrimaryIntMatrix.getColumnCapacity() == 0, "Clear failed, capacity is not correct!");

    QVERIFY2(mPrimaryIntMatrix.getNrOfRows() == 0 &&
             mPrimaryIntMatrix.getNrOfColumns() == 0, "Clear failed, number of rows and columns is not correct!");
}

void FunctionalityTests::testResizeWithoutFillingInNewValues()
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

void FunctionalityTests::testResizeAndFillInNewValues()
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

void FunctionalityTests::testShrinkToFit()
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

void FunctionalityTests::testInsertRowNoSetValue()
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

void FunctionalityTests::testInsertRowSetValue()
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

void FunctionalityTests::testInsertColumnNoSetValue()
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

void FunctionalityTests::testInsertColumnSetValue()
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

void FunctionalityTests::testEraseRow()
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

void FunctionalityTests::testEraseColumn()
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

void FunctionalityTests::testCatByRow()
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

void FunctionalityTests::testCatByColumn()
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

void FunctionalityTests::testSplitByRow()
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

void FunctionalityTests::testSplitByColumn()
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

void FunctionalityTests::testSwapMatrixes()
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

void FunctionalityTests::testSwapItems()
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

void FunctionalityTests::testSwapRows()
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

void FunctionalityTests::testSwapColumns()
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

void FunctionalityTests::testSwapRowColumn()
{
    mPrimaryIntMatrix = {4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    mSecondaryIntMatrix = {3, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24}};

    mPrimaryIntMatrix.swapRowColumn(0, mSecondaryIntMatrix, 3);

    QVERIFY2(mPrimaryIntMatrix == IntMatrix(4, 3, {16, 20, 24, 4, 5, 6, 7, 8, 9, 10, 11, 12}),
             "Row from first matrix is incorrectly swapped with column from the second, first matrix does not have the desired value after swap!");

    QVERIFY2(mSecondaryIntMatrix == IntMatrix(3, 4, {13, 14, 15, 1, 17, 18, 19, 2, 21, 22, 23, 3}),
             "Row from first matrix is incorrectly swapped with column from the second, second matrix does not have the desired value after swap!");
}

void FunctionalityTests::testSetAllItemsToValue()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(int, value);
    QFETCH(IntMatrix, expectedMatrix);

    matrix.setAllItemsToValue(value);

    QVERIFY2(matrix == expectedMatrix, "Setting all matrix items to same value failed, matrix has incorrect values!");
}

void FunctionalityTests::testCopy()
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

void FunctionalityTests::testBooleanOperator_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<bool>("checkTrue");

    QTest::newRow("check false") << IntMatrix{} << false;
    QTest::newRow("check false") << IntMatrix{2, 3, {0, 0, 0, 0, 0, 0}} << false;
    QTest::newRow("check true") << IntMatrix{2, 3, {3, -25, 26, -38, 0, -1}} << true;
    QTest::newRow("check true") << IntMatrix{2, 3, {0, 0, 0, 0, -25, 0}} << true;
}

void FunctionalityTests::testMatrixesAreEqual_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<bool>("checkEqualityToItself");

    QTest::newRow("distinct matrixes equality") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << false;
    QTest::newRow("equality to itself") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << true;
    QTest::newRow("distinct matrixes equality") << IntMatrix{} << IntMatrix{} << false;
    QTest::newRow("equality to itself") << IntMatrix{} << IntMatrix{} << true;
}

void FunctionalityTests::testMatrixesAreNotEqual_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");

    QTest::newRow("same size matrixes") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 3, {5, 125, -5, 15, 833, -8333}};
    QTest::newRow("different columns count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 2, {5, 75, 15, 833}};
    QTest::newRow("different rows count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{3, 3, {5, 75, -5, 15, 833, -8333, 5, 5, -125}};
    QTest::newRow("different rows/columns count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{3, 2, {5, 75, 15, 833, -5, -8333}};
    QTest::newRow("different rows/columns count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{};
}

void FunctionalityTests::testTranspose_data()
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

void FunctionalityTests::testClear_data()
{
    QTest::addColumn<IntMatrix>("matrix");

    QTest::newRow("non-empty matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("empty matrix") << IntMatrix{};
}

void FunctionalityTests::testResizeWithoutFillingInNewValues_data()
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

void FunctionalityTests::testResizeAndFillInNewValues_data()
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

void FunctionalityTests::testShrinkToFit_data()
{
    QTest::addColumn<IntMatrix>("matrix");

    QTest::newRow("empty matrix") << IntMatrix{};
    QTest::newRow("square matrix") << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
    QTest::newRow("more rows than columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("less rows than columns") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("square matrix") << IntMatrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
}

void FunctionalityTests::testInsertRowNoSetValue_data()
{
    _buildInsertRowTestingTable();
}

void FunctionalityTests::testInsertRowSetValue_data()
{
    _buildInsertRowTestingTable();
}

void FunctionalityTests::testInsertColumnNoSetValue_data()
{
    _buildInsertColumnTestingTable();
}

void FunctionalityTests::testInsertColumnSetValue_data()
{
    _buildInsertColumnTestingTable();
}

void FunctionalityTests::testEraseRow_data()
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

void FunctionalityTests::testEraseColumn_data()
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

void FunctionalityTests::testCatByRow_data()
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

void FunctionalityTests::testCatByColumn_data()
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

void FunctionalityTests::testSplitByRow_data()
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

void FunctionalityTests::testSplitByColumn_data()
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

void FunctionalityTests::testSwapMatrixes_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");

    QTest::newRow("non-empty matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
    QTest::newRow("one empty matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{};
    QTest::newRow("one empty matrix") << IntMatrix{} << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
    QTest::newRow("both matrixes empty") << IntMatrix{} << IntMatrix{};
}

void FunctionalityTests::testSwapItems_data()
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

void FunctionalityTests::testSwapRows_data()
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

void FunctionalityTests::testSwapColumns_data()
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

void FunctionalityTests::testSetAllItemsToValue_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<int>("value");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("non-empty matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 7 << IntMatrix{2, 3, 7};
    QTest::newRow("empty matrix") << IntMatrix{} << 7 << IntMatrix{};
}

void FunctionalityTests::testCopy_data()
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

void FunctionalityTests::_buildInsertRowTestingTable()
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

void FunctionalityTests::_buildInsertColumnTestingTable()
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

QTEST_APPLESS_MAIN(FunctionalityTests)

#include "tst_functionalitytests.moc"
