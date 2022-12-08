#include <QtTest>

#include "testutils.h"
#include "tst_transformationtests.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(StringMatrix)
Q_DECLARE_METATYPE(ConcatMode)
Q_DECLARE_METATYPE(SplitMode)

class TransformationTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testIntMatrixTranspose();
    void testIntMatrixCatByRow();
    void testIntMatrixCatByColumn();
    void testIntMatrixSplitByRow();
    void testIntMatrixSplitByColumn();
    void testIntMatrixSetAllItemsToValue();
    void testIntMatrixCopy();

    void testStringMatrixTranspose();
    void testStringMatrixCatByRow();
    void testStringMatrixCatByColumn();
    void testStringMatrixSplitByRow();
    void testStringMatrixSplitByColumn();
    void testStringMatrixSetAllItemsToValue();
    void testStringMatrixCopy();

    // test data
    void testIntMatrixTranspose_data();
    void testIntMatrixCatByRow_data();
    void testIntMatrixCatByColumn_data();
    void testIntMatrixSplitByRow_data();
    void testIntMatrixSplitByColumn_data();
    void testIntMatrixSetAllItemsToValue_data();
    void testIntMatrixCopy_data();

    void testStringMatrixTranspose_data();
    void testStringMatrixCatByRow_data();
    void testStringMatrixCatByColumn_data();
    void testStringMatrixSplitByRow_data();
    void testStringMatrixSplitByColumn_data();
    void testStringMatrixSetAllItemsToValue_data();
    void testStringMatrixCopy_data();

private:
    IntMatrix mPrimaryIntMatrix;
    IntMatrix mSecondaryIntMatrix;
    StringMatrix mPrimaryStringMatrix;
    StringMatrix mSecondaryStringMatrix;
};

void TransformationTests::testIntMatrixTranspose()
{
    TEST_MATRIX_TRANSPOSE(int, mPrimaryIntMatrix, mSecondaryIntMatrix);
}

void TransformationTests::testIntMatrixCatByRow()
{
    TEST_MATRIX_CAT_BY_ROW(int);
}

void TransformationTests::testIntMatrixCatByColumn()
{
    TEST_MATRIX_CAT_BY_COLUMN(int);
}

void TransformationTests::testIntMatrixSplitByRow()
{
    TEST_MATRIX_SPLIT_BY_ROW(int);
}

void TransformationTests::testIntMatrixSplitByColumn()
{
    TEST_MATRIX_SPLIT_BY_COLUMN(int);
}

void TransformationTests::testIntMatrixSetAllItemsToValue()
{
    TEST_MATRIX_SET_ALL_ITEMS_TO_VALUE(int);
}

void TransformationTests::testIntMatrixCopy()
{
    TEST_MATRIX_COPY(int);
}

void TransformationTests::testStringMatrixTranspose()
{
    TEST_MATRIX_TRANSPOSE(std::string, mPrimaryStringMatrix, mSecondaryStringMatrix);
}

void TransformationTests::testStringMatrixCatByRow()
{
    TEST_MATRIX_CAT_BY_ROW(std::string);
}

void TransformationTests::testStringMatrixCatByColumn()
{
    TEST_MATRIX_CAT_BY_COLUMN(std::string);
}

void TransformationTests::testStringMatrixSplitByRow()
{
    TEST_MATRIX_SPLIT_BY_ROW(std::string);
}

void TransformationTests::testStringMatrixSplitByColumn()
{
    TEST_MATRIX_SPLIT_BY_COLUMN(std::string);
}

void TransformationTests::testStringMatrixSetAllItemsToValue()
{
    TEST_MATRIX_SET_ALL_ITEMS_TO_VALUE(std::string);
}

void TransformationTests::testStringMatrixCopy()
{
    TEST_MATRIX_COPY(std::string);
}

void TransformationTests::testIntMatrixTranspose_data()
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

void TransformationTests::testIntMatrixCatByRow_data()
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

void TransformationTests::testIntMatrixCatByColumn_data()
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

void TransformationTests::testIntMatrixSplitByRow_data()
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

void TransformationTests::testIntMatrixSplitByColumn_data()
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

void TransformationTests::testIntMatrixSetAllItemsToValue_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<int>("value");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("non-empty matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 7 << IntMatrix{2, 3, 7};
    QTest::newRow("empty matrix") << IntMatrix{} << 7 << IntMatrix{};
}

void TransformationTests::testIntMatrixCopy_data()
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

void TransformationTests::testStringMatrixTranspose_data()
{
    QTest::addColumn<StringMatrix>("initialSrcMatrix");
    QTest::addColumn<StringMatrix>("initialDestMatrix");
    QTest::addColumn<StringMatrix>("expectedDestMatrix");
    QTest::addColumn<StringMatrixSizeType>("expectedSrcRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedSrcColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedDestRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedDestColumnCapacity");
    QTest::addColumn<bool>("isTransposedToItself");

    QTest::newRow("same matrix") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{3, 2, {"1", "4", "2", "5", "3", "6"}} << 3 << 3 << 3 << 3 << true;
    QTest::newRow("same matrix") << StringMatrix{} << StringMatrix{} << StringMatrix{} << 0 << 0 << 0 << 0 << true;
    QTest::newRow("different matrixes") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{2, 2, {"7", "8", "9", "10"}} << StringMatrix{3, 2, {"1", "4", "2", "5", "3", "6"}} << 2 << 3 << 3 << 2 << false;
    QTest::newRow("different matrixes") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{} << StringMatrix{3, 2, {"1", "4", "2", "5", "3", "6"}} << 2 << 3 << 3 << 2 << false;
    QTest::newRow("different matrixes") << StringMatrix{} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{} << 0 << 0 << 0 << 0 << false;
    QTest::newRow("different matrixes") << StringMatrix{} << StringMatrix{} << StringMatrix{} << 0 << 0 << 0 << 0 << false;
}

void TransformationTests::testStringMatrixCatByRow_data()
{
    QTest::addColumn<StringMatrix>("destMatrix");
    QTest::addColumn<StringMatrix>("firstSrcMatrix");
    QTest::addColumn<StringMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrix>("expectedDestMatrix");

    QTest::newRow("scenario: all different") << StringMatrix{} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{1, 2, {"5", "6"}} << ConcatMode::ALL_DIFFERENT << 3 << 2 << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}};
    QTest::newRow("scenario: all different") << StringMatrix{2, 3, {"7", "8", "9", "10", "11", "12"}} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{1, 2, {"5", "6"}} << ConcatMode::ALL_DIFFERENT << 3 << 2 << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}};
    QTest::newRow("scenario: all different") << StringMatrix{4, 1, {"7", "8", "9", "10"}} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{1, 2, {"5", "6"}} << ConcatMode::ALL_DIFFERENT << 3 << 2 << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}};
    QTest::newRow("scenario: all different") << StringMatrix{3, 2, {"7", "8", "9", "10", "11", "12"}} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{1, 2, {"5", "6"}} << ConcatMode::ALL_DIFFERENT << 3 << 2 << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}};
    QTest::newRow("scenario: all different") << StringMatrix{} << StringMatrix{} << StringMatrix{} << ConcatMode::ALL_DIFFERENT << 0 << 0 << StringMatrix{};
    QTest::newRow("scenario: destination first") << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{1, 2, {"5", "6"}} << ConcatMode::DESTINATION_FIRST << 3 << 2 << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}};
    QTest::newRow("scenario: destination first") << StringMatrix{} << StringMatrix{} << StringMatrix{} << ConcatMode::DESTINATION_FIRST << 0 << 0 << StringMatrix{};
    QTest::newRow("scenario: destination second") << StringMatrix{1, 2, {"5", "6"}} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{1, 2, {"5", "6"}} << ConcatMode::DESTINATION_SECOND << 3 << 2 << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}};
    QTest::newRow("scenario: destination second") << StringMatrix{} << StringMatrix{} << StringMatrix{} << ConcatMode::DESTINATION_SECOND << 0 << 0 << StringMatrix{};
    QTest::newRow("scenario: destination all") << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << ConcatMode::DESTINATION_ALL << 5 << 2 << StringMatrix{4, 2, {"1", "2", "3", "4", "1", "2", "3", "4"}};
    QTest::newRow("scenario: destination all") << StringMatrix{} << StringMatrix{} << StringMatrix{} << ConcatMode::DESTINATION_ALL << 0 << 0 << StringMatrix{};
    QTest::newRow("scenario: source both") << StringMatrix{} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << ConcatMode::SOURCE_BOTH << 5 << 2 << StringMatrix{4, 2, {"1", "2", "3", "4", "1", "2", "3", "4"}};
    QTest::newRow("scenario: source both") << StringMatrix{} << StringMatrix{} << StringMatrix{} << ConcatMode::SOURCE_BOTH << 0 << 0 << StringMatrix{};
}

void TransformationTests::testStringMatrixCatByColumn_data()
{
    QTest::addColumn<StringMatrix>("destMatrix");
    QTest::addColumn<StringMatrix>("firstSrcMatrix");
    QTest::addColumn<StringMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrix>("expectedDestMatrix");

    QTest::newRow("scenario: all different") << StringMatrix{} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{2, 1, {"5", "6"}} << ConcatMode::ALL_DIFFERENT << 2 << 3 << StringMatrix{2, 3, {"1", "2", "5", "3", "4", "6"}};
    QTest::newRow("scenario: all different") << StringMatrix{3, 2, {"7", "8", "9", "10", "11", "12"}} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{2, 1, {"5", "6"}} << ConcatMode::ALL_DIFFERENT << 2 << 3 << StringMatrix{2, 3, {"1", "2", "5", "3", "4", "6"}};
    QTest::newRow("scenario: all different") << StringMatrix{1, 4, {"7", "8", "9", "10"}} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{2, 1, {"5", "6"}} << ConcatMode::ALL_DIFFERENT << 2 << 3 << StringMatrix{2, 3, {"1", "2", "5", "3", "4", "6"}};
    QTest::newRow("scenario: all different") << StringMatrix{2, 3, {"7", "8", "9", "10", "11", "12"}} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{2, 1, {"5", "6"}} << ConcatMode::ALL_DIFFERENT << 2 << 3 << StringMatrix{2, 3, {"1", "2", "5", "3", "4", "6"}};
    QTest::newRow("scenario: all different") << StringMatrix{} << StringMatrix{} << StringMatrix{} << ConcatMode::ALL_DIFFERENT << 0 << 0 << StringMatrix{};
    QTest::newRow("scenario: destination first") << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{2, 1, {"5", "6"}} << ConcatMode::DESTINATION_FIRST << 2 << 3 << StringMatrix{2, 3, {"1", "2", "5", "3", "4", "6"}};
    QTest::newRow("scenario: destination first") << StringMatrix{} << StringMatrix{} << StringMatrix{} << ConcatMode::DESTINATION_FIRST << 0 << 0 << StringMatrix{};
    QTest::newRow("scenario: destination second") << StringMatrix{2, 1, {"5", "6"}} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{2, 1, {"5", "6"}} << ConcatMode::DESTINATION_SECOND << 2 << 3 << StringMatrix{2, 3, {"1", "2", "5", "3", "4", "6"}};
    QTest::newRow("scenario: destination second") << StringMatrix{} << StringMatrix{} << StringMatrix{} << ConcatMode::DESTINATION_SECOND << 0 << 0 << StringMatrix{};
    QTest::newRow("scenario: destination all") << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << ConcatMode::DESTINATION_ALL << 2 << 5 << StringMatrix{2, 4, {"1", "2", "1", "2", "3", "4", "3", "4"}};
    QTest::newRow("scenario: destination all") << StringMatrix{} << StringMatrix{} << StringMatrix{} << ConcatMode::DESTINATION_ALL << 0 << 0 << StringMatrix{};
    QTest::newRow("scenario: source both") << StringMatrix{} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{2, 2, {"1", "2", "3", "4"}} << ConcatMode::SOURCE_BOTH << 2 << 5 << StringMatrix{2, 4, {"1", "2", "1", "2", "3", "4", "3", "4"}};
    QTest::newRow("scenario: source both") << StringMatrix{} << StringMatrix{} << StringMatrix{} << ConcatMode::SOURCE_BOTH << 0 << 0 << StringMatrix{};
}

void TransformationTests::testStringMatrixSplitByRow_data()
{
    QTest::addColumn<StringMatrix>("srcMatrix");
    QTest::addColumn<StringMatrix>("firstDestMatrix");
    QTest::addColumn<StringMatrix>("secondDestMatrix");
    QTest::addColumn<StringMatrixSizeType>("splitPosition");
    QTest::addColumn<SplitMode>("mode");
    QTest::addColumn<StringMatrixSizeType>("expectedFirstDestRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedFirstDestColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedSecondDestRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedSecondDestColumnCapacity");
    QTest::addColumn<StringMatrix>("expectedFirstDestMatrix");
    QTest::addColumn<StringMatrix>("expectedSecondDestMatrix");

    QTest::newRow("scenario: all different") << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{} << StringMatrix{} << 2 << SplitMode::ALL_DIFFERENT << 2 << 2 << 1 << 2 << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{1, 2, {"5", "6"}};
    QTest::newRow("scenario: all different") << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{1, 2, {"7", "8"}} << StringMatrix{} << 2 << SplitMode::ALL_DIFFERENT << 2 << 2 << 1 << 2 << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{1, 2, {"5", "6"}};
    QTest::newRow("scenario: all different") << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{} << StringMatrix{2, 2, {"9", "10", "11", "12"}} << 2 << SplitMode::ALL_DIFFERENT << 2 << 2 << 2 << 2 << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{1, 2, {"5", "6"}};
    QTest::newRow("scenario: all different") << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{1, 2, {7, 8}} << StringMatrix{2, 2, {"9", "10", "11", "12"}} << 2 << SplitMode::ALL_DIFFERENT << 2 << 2 << 2 << 2 << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{1, 2, {"5", "6"}};
    QTest::newRow("scenario: source first") << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{} << 2 << SplitMode::SOURCE_FIRST << 3 << 2 << 1 << 2 << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{1, 2, {"5", "6"}};
    QTest::newRow("scenario: source first") << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{2, 2, {"9", "10", "11", "12"}} << 2 << SplitMode::SOURCE_FIRST << 3 << 2 << 2 << 2 << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{1, 2, {"5", "6"}};
    QTest::newRow("scenario: source second") << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{} << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}} << 2 << SplitMode::SOURCE_SECOND << 2 << 2 << 3 << 2 << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{1, 2, {"5", "6"}};
    QTest::newRow("scenario: source second") << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{1, 2, {"7", "8"}} << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}} << 2 << SplitMode::SOURCE_SECOND << 2 << 2 << 3 << 2 << StringMatrix{2, 2, {"1", "2", "3", "4"}} << StringMatrix{1, 2, {"5", "6"}};
}

void TransformationTests::testStringMatrixSplitByColumn_data()
{
    QTest::addColumn<StringMatrix>("srcMatrix");
    QTest::addColumn<StringMatrix>("firstDestMatrix");
    QTest::addColumn<StringMatrix>("secondDestMatrix");
    QTest::addColumn<StringMatrixSizeType>("splitPosition");
    QTest::addColumn<SplitMode>("mode");
    QTest::addColumn<StringMatrixSizeType>("expectedFirstDestRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedFirstDestColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedSecondDestRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedSecondDestColumnCapacity");
    QTest::addColumn<StringMatrix>("expectedFirstDestMatrix");
    QTest::addColumn<StringMatrix>("expectedSecondDestMatrix");

    QTest::newRow("scenario: all different") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{} << StringMatrix{} << 2 << SplitMode::ALL_DIFFERENT << 2 << 2 << 2 << 1 << StringMatrix{2, 2, {"1", "2", "4", "5"}} << StringMatrix{2, 1, {"3", "6"}};
    QTest::newRow("scenario: all different") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{2, 1, {"7", "8"}} << StringMatrix{} << 2 << SplitMode::ALL_DIFFERENT << 2 << 2 << 2 << 1 << StringMatrix{2, 2, {"1", "2", "4", "5"}} << StringMatrix{2, 1, {"3", "6"}};
    QTest::newRow("scenario: all different") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{} << StringMatrix{2, 2, {"9", "10", "11", "12"}} << 2 << SplitMode::ALL_DIFFERENT << 2 << 2 << 2 << 2 << StringMatrix{2, 2, {"1", "2", "4", "5"}} << StringMatrix{2, 1, {"3", "6"}};
    QTest::newRow("scenario: all different") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{2, 1, {"7", "8"}} << StringMatrix{2, 2, {"9", "10", "11", "12"}} << 2 << SplitMode::ALL_DIFFERENT << 2 << 2 << 2 << 2 << StringMatrix{2, 2, {"1", "2", "4", "5"}} << StringMatrix{2, 1, {"3", "6"}};
    QTest::newRow("scenario: source first") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{} << 2 << SplitMode::SOURCE_FIRST << 2 << 3 << 2 << 1 << StringMatrix{2, 2, {"1", "2", "4", "5"}} << StringMatrix{2, 1, {"3", "6"}};
    QTest::newRow("scenario: source first") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{2, 2, {"9", "10", "11", "12"}} << 2 << SplitMode::SOURCE_FIRST << 2 << 3 << 2 << 2 << StringMatrix{2, 2, {"1", "2", "4", "5"}} << StringMatrix{2, 1, {"3", "6"}};
    QTest::newRow("scenario: source second") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{} << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << 2 << SplitMode::SOURCE_SECOND << 2 << 2 << 2 << 3 << StringMatrix{2, 2, {"1", "2", "4", "5"}} << StringMatrix{2, 1, {"3", "6"}};
    QTest::newRow("scenario: source second") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{1, 2, {"7", "8"}} << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << 2 << SplitMode::SOURCE_SECOND << 2 << 2 << 2 << 3 << StringMatrix{2, 2, {"1", "2", "4", "5"}} << StringMatrix{2, 1, {"3", "6"}};
}

void TransformationTests::testStringMatrixSetAllItemsToValue_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<std::string>("value");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("non-empty matrix") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << std::string{"7"} << StringMatrix{2, 3, "7"};
    QTest::newRow("empty matrix") << StringMatrix{} << std::string{"7"} << StringMatrix{};
}

void TransformationTests::testStringMatrixCopy_data()
{
    QTest::addColumn<StringMatrix>("srcMatrix");
    QTest::addColumn<StringMatrix>("destMatrix");
    QTest::addColumn<StringMatrixSizeType>("copiedRowsCount");
    QTest::addColumn<StringMatrixSizeType>("copiedColumnsCount");
    QTest::addColumn<StringMatrixSizeType>("srcCopyRowNr");
    QTest::addColumn<StringMatrixSizeType>("srcCopyColumnNr");
    QTest::addColumn<StringMatrixSizeType>("destCopyRowNr");
    QTest::addColumn<StringMatrixSizeType>("destCopyColumnNr");
    QTest::addColumn<StringMatrix>("expectedDestMatrix");

    QTest::newRow("elements copied") << StringMatrix{5, 4, {"13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32"}} << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 3 << 2 << 2 << 1 << 1 << 0 << StringMatrix{4, 3, {"1", "2", "3", "22", "23", "6", "26", "27", "9", "30", "31", "12"}};
    QTest::newRow("no rows to be copied") << StringMatrix{5, 4, {"13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32"}} << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 0 << 2 << 2 << 1 << 1 << 0 << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}};
    QTest::newRow("no columns to be copied") << StringMatrix{5, 4, {"13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32"}} << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 3 << 0 << 2 << 1 << 1 << 0 << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}};
    QTest::newRow("no elements to be copied") << StringMatrix{5, 4, {"13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32"}} << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 0 << 0 << 2 << 1 << 1 << 0 << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}};
}

QTEST_APPLESS_MAIN(TransformationTests)

#include "tst_transformationtests.moc"
