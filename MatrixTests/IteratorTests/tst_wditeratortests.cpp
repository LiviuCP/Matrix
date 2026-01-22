#include <QTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntWDIter)
Q_DECLARE_METATYPE(StringWDIter)

class WDIteratorTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testIteratorCreation();
};

void WDIteratorTests::testIteratorCreation()
{
    IntMatrix matrix{4, 3, {-2, 1, 5,
                             8, 10, 12,
                            14, 5, 8,
                            7, 7, 0
                     }};

    IntWDIter it = matrix.wdBegin();
    QVERIFY(it.getRowNr() == 0 && it.getColumnNr() == 0);

    it = matrix.wdEnd();
    QVERIFY(it.getRowNr() == 4 && it.getColumnNr() == 3);

    it = matrix.getWDIterator(2, 1);
    QVERIFY(it.getRowNr() == 2 && it.getColumnNr() == 1);
}

QTEST_APPLESS_MAIN(WDIteratorTests)

#include "tst_wditeratortests.moc"
