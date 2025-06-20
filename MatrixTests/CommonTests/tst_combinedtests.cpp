#include <QTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(StringMatrix)

class CombinedTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testIntMatrixCatByColumnWithModifiedColumnCapacityOffset();
    void testStringMatrixCatByColumnWithModifiedColumnCapacityOffset();
};

void CombinedTests::testIntMatrixCatByColumnWithModifiedColumnCapacityOffset()
{
    // case 1a: number of shifted positions lower than the number of destination columns before concatenation, resulting column capacity offset is 0
    {
        IntMatrix destMatrix{2, 3, {-1, 2, -3, 4, -5, 6}};
        IntMatrix srcMatrix{2, 2, {7, -8, 9, -10}};
        const IntMatrix c_ResultingMatrix{2, 5, {-1, 2, -3, 7, -8, 4, -5, 6, 9, -10}};

        destMatrix.reserve(2, 5);

        QVERIFY(srcMatrix.getNrOfColumns() == 2);
        QVERIFY(destMatrix.getNrOfColumns() == 3);
        QVERIFY(destMatrix.getColumnCapacity() == 5 && destMatrix.getColumnCapacityOffset() == 1);

        destMatrix.catByColumn(srcMatrix);

        QVERIFY(destMatrix == c_ResultingMatrix);
        QVERIFY(destMatrix.getColumnCapacity() == 5 && destMatrix.getColumnCapacityOffset() == 0);
        QVERIFY(srcMatrix.isEmpty());
    }

    // case 1b: number of shifted positions lower than the number of destination columns before concatenation, resulting column capacity offset is > 0
    {
        IntMatrix destMatrix{2, 2, {-1, 2, 4, -5}};
        IntMatrix srcMatrix{2, 2, {7, -8, 9, -10}};
        const IntMatrix c_ResultingMatrix{2, 5, {-1, 2, -3, 7, -8, 4, -5, 6, 9, -10}};

        destMatrix.reserve(2, 6);
        destMatrix.insertColumn(2);
        destMatrix.at(0, 2) = -3;
        destMatrix.at(1, 2) = 6;

        QVERIFY(srcMatrix.getNrOfColumns() == 2);
        QVERIFY(destMatrix.getNrOfColumns() == 3);
        QVERIFY(destMatrix.getColumnCapacity() == 6 && destMatrix.getColumnCapacityOffset() == 2);

        destMatrix.catByColumn(srcMatrix);

        QVERIFY(destMatrix == c_ResultingMatrix);
        QVERIFY(destMatrix.getColumnCapacity() == 6 && destMatrix.getColumnCapacityOffset() == 1);
        QVERIFY(srcMatrix.isEmpty());
    }

    // case 2a: number of shifted positions equals the number of destination columns before concatenation, resulting column capacity offset is 0
    {
        IntMatrix destMatrix{2, 2, {-1, 2, -3, 4}};
        IntMatrix srcMatrix{2, 4, {5, -6, 7, -8, 9, -10, 11, -12}};
        const IntMatrix c_ResultingMatrix{2, 6, {-1, 2, 5, -6, 7, -8, -3, 4, 9, -10, 11, -12}};

        destMatrix.reserve(2, 6);

        QVERIFY(srcMatrix.getNrOfColumns() == 4);
        QVERIFY(destMatrix.getNrOfColumns() == 2);
        QVERIFY(destMatrix.getColumnCapacity() == 6 && destMatrix.getColumnCapacityOffset() == 2);

        destMatrix.catByColumn(srcMatrix);

        QVERIFY(destMatrix == c_ResultingMatrix);
        QVERIFY(destMatrix.getColumnCapacity() == 6 && destMatrix.getColumnCapacityOffset() == 0);
        QVERIFY(srcMatrix.isEmpty());
    }

    // case 2b: number of shifted positions equals the number of destination columns before concatenation, resulting column capacity offset is > 0
    {
        IntMatrix destMatrix{2, 2, {-1, 2, -3, 4}};
        IntMatrix srcMatrix{2, 4, {5, -6, 7, -8, 9, -10, 11, -12}};
        const IntMatrix c_ResultingMatrix{2, 6, {2, 0, 5, -6, 7, -8, 4, 0, 9, -10, 11, -12}};

        destMatrix.reserve(2, 7);
        destMatrix.insertColumn(2, 0);
        destMatrix.eraseColumn(0);

        QVERIFY(srcMatrix.getNrOfColumns() == 4);
        QVERIFY(destMatrix.getNrOfColumns() == 2);
        QVERIFY(destMatrix.getColumnCapacity() == 7 && destMatrix.getColumnCapacityOffset() == 3);

        destMatrix.catByColumn(srcMatrix);

        QVERIFY(destMatrix == c_ResultingMatrix);
        QVERIFY(destMatrix.getColumnCapacity() == 7 && destMatrix.getColumnCapacityOffset() == 1);
        QVERIFY(srcMatrix.isEmpty());
    }

    // case 3a: number of shifted positions is greater than the number of destination columns before concatenation, resulting column capacity offset is 0
    {
        IntMatrix destMatrix{2, 2, {-1, 2, -3, 4}};
        IntMatrix srcMatrix{2, 4, {5, -6, 7, -8, 9, -10, 11, -12}};
        const IntMatrix c_ResultingMatrix{2, 6, {2, 0, 5, -6, 7, -8, 4, 0, 9, -10, 11, -12}};

        destMatrix.reserve(2, 6);
        destMatrix.insertColumn(2, 0);
        destMatrix.eraseColumn(0);

        QVERIFY(srcMatrix.getNrOfColumns() == 4);
        QVERIFY(destMatrix.getNrOfColumns() == 2);
        QVERIFY(destMatrix.getColumnCapacity() == 6 && destMatrix.getColumnCapacityOffset() == 3);

        destMatrix.catByColumn(srcMatrix);

        QVERIFY(destMatrix == c_ResultingMatrix);
        QVERIFY(destMatrix.getColumnCapacity() == 6 && destMatrix.getColumnCapacityOffset() == 0);
        QVERIFY(srcMatrix.isEmpty());
    }

    // case 3b: number of shifted positions is greater than the number of destination columns before concatenation, resulting column capacity offset is > 0
    {
        IntMatrix destMatrix{2, 2, {-1, 2, -3, 4}};
        IntMatrix srcMatrix{2, 4, {5, -6, 7, -8, 9, -10, 11, -12}};
        const IntMatrix c_ResultingMatrix{2, 6, {0, -25, 5, -6, 7, -8, 0, -25, 9, -10, 11, -12}};

        destMatrix.reserve(2, 7);
        destMatrix.insertColumn(2, 0);
        destMatrix.eraseColumn(0);
        destMatrix.insertColumn(2, -25);
        destMatrix.eraseColumn(0);

        QVERIFY(srcMatrix.getNrOfColumns() == 4);
        QVERIFY(destMatrix.getNrOfColumns() == 2);
        QVERIFY(destMatrix.getColumnCapacity() == 7 && destMatrix.getColumnCapacityOffset() == 4);

        destMatrix.catByColumn(srcMatrix);

        QVERIFY(destMatrix == c_ResultingMatrix);
        QVERIFY(destMatrix.getColumnCapacity() == 7 && destMatrix.getColumnCapacityOffset() == 1);
        QVERIFY(srcMatrix.isEmpty());
    }
}

void CombinedTests::testStringMatrixCatByColumnWithModifiedColumnCapacityOffset()
{
    // case 1a: number of shifted positions lower than the number of destination columns before concatenation, resulting column capacity offset is 0
    {
        StringMatrix destMatrix{2, 3, {"-1a", "2B", "-3C", "4d", "-5E", "6f"}};
        StringMatrix srcMatrix{2, 2, {"7g", "-8h", "9I", "-10J"}};
        const StringMatrix c_ResultingMatrix{2, 5, {"-1a", "2B", "-3C", "7g", "-8h", "4d", "-5E", "6f", "9I", "-10J"}};

        destMatrix.reserve(2, 5);

        QVERIFY(srcMatrix.getNrOfColumns() == 2);
        QVERIFY(destMatrix.getNrOfColumns() == 3);
        QVERIFY(destMatrix.getColumnCapacity() == 5 && destMatrix.getColumnCapacityOffset() == 1);

        destMatrix.catByColumn(srcMatrix);

        QVERIFY(destMatrix == c_ResultingMatrix);
        QVERIFY(destMatrix.getColumnCapacity() == 5 && destMatrix.getColumnCapacityOffset() == 0);
        QVERIFY(srcMatrix.isEmpty());
    }

    // case 1b: number of shifted positions lower than the number of destination columns before concatenation, resulting column capacity offset is > 0
    {
        StringMatrix destMatrix{2, 2, {"-1a", "2B", "4d", "-5E"}};
        StringMatrix srcMatrix{2, 2, {"7g", "-8h", "9I", "-10J"}};
        const StringMatrix c_ResultingMatrix{2, 5, {"-1a", "2B", "-3C", "7g", "-8h", "4d", "-5E", "6f", "9I", "-10J"}};

        destMatrix.reserve(2, 6);
        destMatrix.insertColumn(2);
        destMatrix.at(0, 2) = "-3C";
        destMatrix.at(1, 2) = "6f";

        QVERIFY(srcMatrix.getNrOfColumns() == 2);
        QVERIFY(destMatrix.getNrOfColumns() == 3);
        QVERIFY(destMatrix.getColumnCapacity() == 6 && destMatrix.getColumnCapacityOffset() == 2);

        destMatrix.catByColumn(srcMatrix);

        QVERIFY(destMatrix == c_ResultingMatrix);
        QVERIFY(destMatrix.getColumnCapacity() == 6 && destMatrix.getColumnCapacityOffset() == 1);
        QVERIFY(srcMatrix.isEmpty());
    }

    // case 2a: number of shifted positions equals the number of destination columns before concatenation, resulting column capacity offset is 0
    {
        StringMatrix destMatrix{2, 2, {"-1a", "2B", "-3C", "4d"}};
        StringMatrix srcMatrix{2, 4, {"5_five", "-6_minus_six", "7g", "-8h", "9I", "-10J", "11k", "-12L"}};
        const StringMatrix c_ResultingMatrix{2, 6, {"-1a", "2B", "5_five", "-6_minus_six", "7g", "-8h", "-3C", "4d", "9I", "-10J", "11k", "-12L"}};

        destMatrix.reserve(2, 6);

        QVERIFY(srcMatrix.getNrOfColumns() == 4);
        QVERIFY(destMatrix.getNrOfColumns() == 2);
        QVERIFY(destMatrix.getColumnCapacity() == 6 && destMatrix.getColumnCapacityOffset() == 2);

        destMatrix.catByColumn(srcMatrix);

        QVERIFY(destMatrix == c_ResultingMatrix);
        QVERIFY(destMatrix.getColumnCapacity() == 6 && destMatrix.getColumnCapacityOffset() == 0);
        QVERIFY(srcMatrix.isEmpty());
    }

    // case 2b: number of shifted positions equals the number of destination columns before concatenation, resulting column capacity offset is > 0
    {
        StringMatrix destMatrix{2, 2, {"-1a", "2B", "-3C", "4d"}};
        StringMatrix srcMatrix{2, 4, {"5_five", "-6_minus_six", "7g", "-8h", "9I", "-10J", "11k", "-12L"}};
        const StringMatrix c_ResultingMatrix{2, 6, {"2B", "0_null", "5_five", "-6_minus_six", "7g", "-8h", "4d", "0_null", "9I", "-10J", "11k", "-12L"}};

        destMatrix.reserve(2, 7);
        destMatrix.insertColumn(2, "0_null");
        destMatrix.eraseColumn(0);

        QVERIFY(srcMatrix.getNrOfColumns() == 4);
        QVERIFY(destMatrix.getNrOfColumns() == 2);
        QVERIFY(destMatrix.getColumnCapacity() == 7 && destMatrix.getColumnCapacityOffset() == 3);

        destMatrix.catByColumn(srcMatrix);

        QVERIFY(destMatrix == c_ResultingMatrix);
        QVERIFY(destMatrix.getColumnCapacity() == 7 && destMatrix.getColumnCapacityOffset() == 1);
        QVERIFY(srcMatrix.isEmpty());
    }

    // case 3a: number of shifted positions is greater than the number of destination columns before concatenation, resulting column capacity offset is 0
    {
        StringMatrix destMatrix{2, 2, {"-1a", "2B", "-3C", "4d"}};
        StringMatrix srcMatrix{2, 4, {"5_five", "-6_minus_six", "7g", "-8h", "9I", "-10J", "11k", "-12L"}};
        const StringMatrix c_ResultingMatrix{2, 6, {"2B", "0_null", "5_five", "-6_minus_six", "7g", "-8h", "4d", "0_null", "9I", "-10J", "11k", "-12L"}};

        destMatrix.reserve(2, 6);
        destMatrix.insertColumn(2, "0_null");
        destMatrix.eraseColumn(0);

        QVERIFY(srcMatrix.getNrOfColumns() == 4);
        QVERIFY(destMatrix.getNrOfColumns() == 2);
        QVERIFY(destMatrix.getColumnCapacity() == 6 && destMatrix.getColumnCapacityOffset() == 3);

        destMatrix.catByColumn(srcMatrix);

        QVERIFY(destMatrix == c_ResultingMatrix);
        QVERIFY(destMatrix.getColumnCapacity() == 6 && destMatrix.getColumnCapacityOffset() == 0);
        QVERIFY(srcMatrix.isEmpty());
    }

    // case 3b: number of shifted positions is greater than the number of destination columns before concatenation, resulting column capacity offset is > 0
    {
        StringMatrix destMatrix{2, 2, {"-1a", "2B", "-3C", "4d"}};
        StringMatrix srcMatrix{2, 4, {"5_five", "-6_minus_six", "7g", "-8h", "9I", "-10J", "11k", "-12L"}};
        const StringMatrix c_ResultingMatrix{2, 6, {"0_null", "-25_NEGATIVE", "5_five", "-6_minus_six", "7g", "-8h", "0_null", "-25_NEGATIVE", "9I", "-10J", "11k", "-12L"}};

        destMatrix.reserve(2, 7);
        destMatrix.insertColumn(2, "0_null");
        destMatrix.eraseColumn(0);
        destMatrix.insertColumn(2, "-25_NEGATIVE");
        destMatrix.eraseColumn(0);

        QVERIFY(srcMatrix.getNrOfColumns() == 4);
        QVERIFY(destMatrix.getNrOfColumns() == 2);
        QVERIFY(destMatrix.getColumnCapacity() == 7 && destMatrix.getColumnCapacityOffset() == 4);

        destMatrix.catByColumn(srcMatrix);

        QVERIFY(destMatrix == c_ResultingMatrix);
        QVERIFY(destMatrix.getColumnCapacity() == 7 && destMatrix.getColumnCapacityOffset() == 1);
        QVERIFY(srcMatrix.isEmpty());
    }
}

QTEST_APPLESS_MAIN(CombinedTests)

#include "tst_combinedtests.moc"
