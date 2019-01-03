#include <QtTest>
#include "../../../MatrixLib/matrix.h"

// uncomment the below #define after the Fraction library has been correctly setup

//#define FRACTION_MATRIX_TEST

class FractionMatrixTests : public QObject
{
    Q_OBJECT

public:
    FractionMatrixTests();
    ~FractionMatrixTests();

private slots:
#ifdef FRACTION_MATRIX_TEST
    void test_case1();
#endif

};



FractionMatrixTests::FractionMatrixTests()
{

}

FractionMatrixTests::~FractionMatrixTests()
{

}

#ifdef FRACTION_MATRIX_TEST

#include "fraction.h"

using FractMatrix = Matrix<Fraction>;

void FractionMatrixTests::test_case1()
{
}

#endif

QTEST_APPLESS_MAIN(FractionMatrixTests)

#include "tst_fractionmatrixtests.moc"
