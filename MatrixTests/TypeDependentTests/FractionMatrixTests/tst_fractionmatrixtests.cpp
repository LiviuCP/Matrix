#include <QtTest>
#include "../../../MatrixLib/matrix.h"

// uncomment the below #define after the Fraction library has been correctly setup

//#define FRACTION_MATRIX_TEST

class tst_fractionmatrixtests : public QObject
{
    Q_OBJECT

public:
    tst_fractionmatrixtests();
    ~tst_fractionmatrixtests();

private slots:
#ifdef FRACTION_MATRIX_TEST
    void test_case1();
#endif

};



tst_fractionmatrixtests::tst_fractionmatrixtests()
{

}

tst_fractionmatrixtests::~tst_fractionmatrixtests()
{

}

#ifdef FRACTION_MATRIX_TEST

#include "fraction.h"

using FractMatrix = Matrix<Fraction>;

void tst_fractionmatrixtests::test_case1()
{
}

#endif

QTEST_APPLESS_MAIN(tst_fractionmatrixtests)

#include "tst_fractionmatrixtests.moc"
