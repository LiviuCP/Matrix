#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(ConcatMode)
Q_DECLARE_METATYPE(SplitMode)

class TransformationTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testTranspose();
    void testCatByRow();
    void testCatByColumn();
    void testSplitByRow();
    void testSplitByColumn();
    void testSetAllItemsToValue();
    void testCopy();

    // test data
    void testTranspose_data();
    void testCatByRow_data();
    void testCatByColumn_data();
    void testSplitByRow_data();
    void testSplitByColumn_data();
    void testSetAllItemsToValue_data();
    void testCopy_data();

private:
    IntMatrix mPrimaryIntMatrix;
    IntMatrix mSecondaryIntMatrix;
};

void TransformationTests::testTranspose()
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

void TransformationTests::testCatByRow()
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

void TransformationTests::testCatByColumn()
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

void TransformationTests::testSplitByRow()
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
        QFAIL("exception scenario");
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

void TransformationTests::testSplitByColumn()
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
        QFAIL("exception scenario");
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

void TransformationTests::testSetAllItemsToValue()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(int, value);
    QFETCH(IntMatrix, expectedMatrix);

    matrix.setAllItemsToValue(value);

    QVERIFY2(matrix == expectedMatrix, "Setting all matrix items to same value failed, matrix has incorrect values!");
}

void TransformationTests::testCopy()
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

void TransformationTests::testTranspose_data()
{
    QTest::addColumn<IntMatrix>("initialSrcMatrix");
    QTest::addColumn<IntMatrix>("initialDestMatrix");
    QTest::addColumn<IntMatrix>("expectedDestMatrix");
    QTest::addColumn<IntMatrixSizeType>("expectedSrcRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedSrcColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedDestRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedDestColumnCapacity");
    QTest::addColumn<bool>("isTransposedToItself");

    QTest::newRow("same matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 4, 2, 5, 3, 6}} << 3 << 3 << 3 << 3 << true;
    QTest::newRow("same matrix") << IntMatrix{} << IntMatrix{} << IntMatrix{} << 0 << 0 << 0 << 0 << true;
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 2, {7, 8, 9, 10}} << IntMatrix{3, 2, {1, 4, 2, 5, 3, 6}} << 2 << 3 << 3 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{3, 2, {1, 4, 2, 5, 3, 6}} << 2 << 3 << 3 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{} << 0 << 0 << 0 << 0 << false;
    QTest::newRow("different matrixes") << IntMatrix{} << IntMatrix{} << IntMatrix{} << 0 << 0 << 0 << 0 << false;
}

void TransformationTests::testCatByRow_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("firstSrcMatrix");
    QTest::addColumn<IntMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("expectedDestMatrix");

    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}} << ConcatMode::ALL_DIFFERENT << 3 << 2 << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}} << ConcatMode::ALL_DIFFERENT << 3 << 2 << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("scenario: all different") << IntMatrix{4, 1, {7, 8, 9, 10}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}} << ConcatMode::ALL_DIFFERENT << 3 << 2 << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}} << ConcatMode::ALL_DIFFERENT << 3 << 2 << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{} << IntMatrix{} << ConcatMode::ALL_DIFFERENT << 0 << 0 << IntMatrix{};
    QTest::newRow("scenario: destination first") << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}} << ConcatMode::DESTINATION_FIRST << 3 << 2 << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("scenario: destination first") << IntMatrix{} << IntMatrix{} << IntMatrix{} << ConcatMode::DESTINATION_FIRST << 0 << 0 << IntMatrix{};
    QTest::newRow("scenario: destination second") << IntMatrix{1, 2, {5, 6}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}} << ConcatMode::DESTINATION_SECOND << 3 << 2 << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("scenario: destination second") << IntMatrix{} << IntMatrix{} << IntMatrix{} << ConcatMode::DESTINATION_SECOND << 0 << 0 << IntMatrix{};
    QTest::newRow("scenario: destination all") << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 2, {1, 2, 3, 4}} << ConcatMode::DESTINATION_ALL << 5 << 2 << IntMatrix{4, 2, {1, 2, 3, 4, 1, 2, 3, 4}};
    QTest::newRow("scenario: destination all") << IntMatrix{} << IntMatrix{} << IntMatrix{} << ConcatMode::DESTINATION_ALL << 0 << 0 << IntMatrix{};
    QTest::newRow("scenario: source both") << IntMatrix{} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 2, {1, 2, 3, 4}} << ConcatMode::SOURCE_BOTH << 5 << 2 << IntMatrix{4, 2, {1, 2, 3, 4, 1, 2, 3, 4}};
    QTest::newRow("scenario: source both") << IntMatrix{} << IntMatrix{} << IntMatrix{} << ConcatMode::SOURCE_BOTH << 0 << 0 << IntMatrix{};
}

void TransformationTests::testCatByColumn_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("firstSrcMatrix");
    QTest::addColumn<IntMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("expectedDestMatrix");

    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 1, {5, 6}} << ConcatMode::ALL_DIFFERENT << 2 << 3 << IntMatrix{2, 3, {1, 2, 5, 3, 4, 6}};
    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 1, {5, 6}} << ConcatMode::ALL_DIFFERENT << 2 << 3 << IntMatrix{2, 3, {1, 2, 5, 3, 4, 6}};
    QTest::newRow("scenario: all different") << IntMatrix{1, 4, {7, 8, 9, 10}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 1, {5, 6}} << ConcatMode::ALL_DIFFERENT << 2 << 3 << IntMatrix{2, 3, {1, 2, 5, 3, 4, 6}};
    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 1, {5, 6}} << ConcatMode::ALL_DIFFERENT << 2 << 3 << IntMatrix{2, 3, {1, 2, 5, 3, 4, 6}};
    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{} << IntMatrix{} << ConcatMode::ALL_DIFFERENT << 0 << 0 << IntMatrix{};
    QTest::newRow("scenario: destination first") << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 1, {5, 6}} << ConcatMode::DESTINATION_FIRST << 2 << 3 << IntMatrix{2, 3, {1, 2, 5, 3, 4, 6}};
    QTest::newRow("scenario: destination first") << IntMatrix{} << IntMatrix{} << IntMatrix{} << ConcatMode::DESTINATION_FIRST << 0 << 0 << IntMatrix{};
    QTest::newRow("scenario: destination second") << IntMatrix{2, 1, {5, 6}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 1, {5, 6}} << ConcatMode::DESTINATION_SECOND << 2 << 3 << IntMatrix{2, 3, {1, 2, 5, 3, 4, 6}};
    QTest::newRow("scenario: destination second") << IntMatrix{} << IntMatrix{} << IntMatrix{} << ConcatMode::DESTINATION_SECOND << 0 << 0 << IntMatrix{};
    QTest::newRow("scenario: destination all") << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 2, {1, 2, 3, 4}} << ConcatMode::DESTINATION_ALL << 2 << 5 << IntMatrix{2, 4, {1, 2, 1, 2, 3, 4, 3, 4}};
    QTest::newRow("scenario: destination all") << IntMatrix{} << IntMatrix{} << IntMatrix{} << ConcatMode::DESTINATION_ALL << 0 << 0 << IntMatrix{};
    QTest::newRow("scenario: source both") << IntMatrix{} << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{2, 2, {1, 2, 3, 4}} << ConcatMode::SOURCE_BOTH << 2 << 5 << IntMatrix{2, 4, {1, 2, 1, 2, 3, 4, 3, 4}};
    QTest::newRow("scenario: source both") << IntMatrix{} << IntMatrix{} << IntMatrix{} << ConcatMode::SOURCE_BOTH << 0 << 0 << IntMatrix{};
}

void TransformationTests::testSplitByRow_data()
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

    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 2 << SplitMode::ALL_DIFFERENT << 2 << 2 << 1 << 2 << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}};
    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{1, 2, {7, 8}} << IntMatrix{} << 2 << SplitMode::ALL_DIFFERENT << 2 << 2 << 1 << 2 << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}};
    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{2, 2, {9, 10, 11, 12}} << 2 << SplitMode::ALL_DIFFERENT << 2 << 2 << 2 << 2 << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}};
    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{1, 2, {7, 8}} << IntMatrix{2, 2, {9, 10, 11, 12}} << 2 << SplitMode::ALL_DIFFERENT << 2 << 2 << 2 << 2 << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}};
    QTest::newRow("scenario: source first") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << 2 << SplitMode::SOURCE_FIRST << 3 << 2 << 1 << 2 << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}};
    QTest::newRow("scenario: source first") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 2, {9, 10, 11, 12}} << 2 << SplitMode::SOURCE_FIRST << 3 << 2 << 2 << 2 << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}};
    QTest::newRow("scenario: source second") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 2 << SplitMode::SOURCE_SECOND << 2 << 2 << 3 << 2 << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}};
    QTest::newRow("scenario: source second") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{1, 2, {7, 8}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 2 << SplitMode::SOURCE_SECOND << 2 << 2 << 3 << 2 << IntMatrix{2, 2, {1, 2, 3, 4}} << IntMatrix{1, 2, {5, 6}};
}

void TransformationTests::testSplitByColumn_data()
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

    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 2 << SplitMode::ALL_DIFFERENT << 2 << 2 << 2 << 1 << IntMatrix{2, 2, {1, 2, 4, 5}} << IntMatrix{2, 1, {3, 6}};
    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 1, {7, 8}} << IntMatrix{} << 2 << SplitMode::ALL_DIFFERENT << 2 << 2 << 2 << 1 << IntMatrix{2, 2, {1, 2, 4, 5}} << IntMatrix{2, 1, {3, 6}};
    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{2, 2, {9, 10, 11, 12}} << 2 << SplitMode::ALL_DIFFERENT << 2 << 2 << 2 << 2 << IntMatrix{2, 2, {1, 2, 4, 5}} << IntMatrix{2, 1, {3, 6}};
    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 1, {7, 8}} << IntMatrix{2, 2, {9, 10, 11, 12}} << 2 << SplitMode::ALL_DIFFERENT << 2 << 2 << 2 << 2 << IntMatrix{2, 2, {1, 2, 4, 5}} << IntMatrix{2, 1, {3, 6}};
    QTest::newRow("scenario: source first") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << 2 << SplitMode::SOURCE_FIRST << 2 << 3 << 2 << 1 << IntMatrix{2, 2, {1, 2, 4, 5}} << IntMatrix{2, 1, {3, 6}};
    QTest::newRow("scenario: source first") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 2, {9, 10, 11, 12}} << 2 << SplitMode::SOURCE_FIRST << 2 << 3 << 2 << 2 << IntMatrix{2, 2, {1, 2, 4, 5}} << IntMatrix{2, 1, {3, 6}};
    QTest::newRow("scenario: source second") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2 << SplitMode::SOURCE_SECOND << 2 << 2 << 2 << 3 << IntMatrix{2, 2, {1, 2, 4, 5}} << IntMatrix{2, 1, {3, 6}};
    QTest::newRow("scenario: source second") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{1, 2, {7, 8}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2 << SplitMode::SOURCE_SECOND << 2 << 2 << 2 << 3 << IntMatrix{2, 2, {1, 2, 4, 5}} << IntMatrix{2, 1, {3, 6}};
}

void TransformationTests::testSetAllItemsToValue_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<int>("value");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("non-empty matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 7 << IntMatrix{2, 3, 7};
    QTest::newRow("empty matrix") << IntMatrix{} << 7 << IntMatrix{};
}

void TransformationTests::testCopy_data()
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

    QTest::newRow("elements copied") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 1 << 1 << 0 << IntMatrix{4, 3, {1, 2, 3, 22, 23, 6, 26, 27, 9, 30, 31, 12}};
    QTest::newRow("no rows to be copied") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 2 << 2 << 1 << 1 << 0 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("no columns to be copied") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 0 << 2 << 1 << 1 << 0 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("no elements to be copied") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 0 << 2 << 1 << 1 << 0 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
}

QTEST_APPLESS_MAIN(TransformationTests)

#include "tst_transformationtests.moc"
