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
    QVERIFY2(matrix.isWrappedByRow(), "Default constructor set the wrong wrap mode");

    int nrOfRows, nrOfColumns;
    int** matrixPtr{matrix.getBaseArrayPtr(nrOfRows, nrOfColumns)};

    QVERIFY2(!matrixPtr, "Default constructor allocated the wrong number of elements to the matrix");
}

void CommonTests::testInitListConstructor()
{
    IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6} };

    QVERIFY2(matrix.getNrOfRows() == 2 && matrix.getNrOfColumns() == 3, "Init list constructor initialized matrix with wrong number of rows and columns");
    QVERIFY2(matrix.isWrappedByRow(), "Init list constructor set the wrong wrap mode");
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
    QVERIFY2(matrix.isWrappedByRow(), "Identical matrix constructor set the wrong wrap mode");
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
    QVERIFY2(matrix.isWrappedByRow(), "Diagonal matrix constructor set the wrong wrap mode");
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
    QVERIFY2(matrixCopy.isWrappedByRow(), "Copy constructor set the wrong wrap mode");
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
    QVERIFY2(matrixMove.isWrappedByRow(), "Move constructor set the wrong wrap mode");
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

QTEST_APPLESS_MAIN(CommonTests)

#include "tst_commontests.moc"
