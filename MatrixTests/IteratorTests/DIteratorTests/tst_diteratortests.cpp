#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixDIterator = Matrix<int>::DIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixDIterator = Matrix<std::string>::DIterator;

class DIteratorTests : public QObject
{
    Q_OBJECT

public:
    DIteratorTests();
    ~DIteratorTests();

private slots:
    void testIteratorCreation();
};

DIteratorTests::DIteratorTests()
{

}

DIteratorTests::~DIteratorTests()
{

}

void DIteratorTests::testIteratorCreation()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(-2)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -2 && it.getDiagonalIndex() == 0, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(-2)};

        QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == -2  && it.getDiagonalIndex() == 2, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(0)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(0)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(1)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(1)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(0, 0)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(0, 0)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 3, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(1, 2)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(1, 2)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(1, 0)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(0, 2)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(2, 2)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 2, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(-1, 0, true)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(2, 0, true)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(-1, 1, true)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1, "The DIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(0, 2, true)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 2, "The DIterator has not been correctly created");
    }
}

QTEST_APPLESS_MAIN(DIteratorTests)

#include "tst_diteratortests.moc"
