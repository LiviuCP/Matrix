#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(IntZIter)
Q_DECLARE_METATYPE(IntConstZIter)
Q_DECLARE_METATYPE(IntReverseZIter)
Q_DECLARE_METATYPE(IntConstReverseZIter)
Q_DECLARE_METATYPE(IntNIter)
Q_DECLARE_METATYPE(IntConstNIter)
Q_DECLARE_METATYPE(IntReverseNIter)
Q_DECLARE_METATYPE(IntConstReverseNIter)
Q_DECLARE_METATYPE(IntDIter)
Q_DECLARE_METATYPE(IntConstDIter)
Q_DECLARE_METATYPE(IntReverseDIter)
Q_DECLARE_METATYPE(IntConstReverseDIter)
Q_DECLARE_METATYPE(IntMIter)
Q_DECLARE_METATYPE(IntConstMIter)
Q_DECLARE_METATYPE(IntReverseMIter)
Q_DECLARE_METATYPE(IntConstReverseMIter)
Q_DECLARE_METATYPE(StringZIter)
Q_DECLARE_METATYPE(StringConstZIter)
Q_DECLARE_METATYPE(StringReverseZIter)
Q_DECLARE_METATYPE(StringConstReverseZIter)
Q_DECLARE_METATYPE(StringNIter)
Q_DECLARE_METATYPE(StringConstNIter)
Q_DECLARE_METATYPE(StringReverseNIter)
Q_DECLARE_METATYPE(StringConstReverseNIter)
Q_DECLARE_METATYPE(StringDIter)
Q_DECLARE_METATYPE(StringConstDIter)
Q_DECLARE_METATYPE(StringReverseDIter)
Q_DECLARE_METATYPE(StringConstReverseDIter)
Q_DECLARE_METATYPE(StringMIter)
Q_DECLARE_METATYPE(StringConstMIter)
Q_DECLARE_METATYPE(StringReverseMIter)
Q_DECLARE_METATYPE(StringConstReverseMIter)
Q_DECLARE_METATYPE(std::string)

static_assert(std::random_access_iterator<IntZIter>);
static_assert(std::random_access_iterator<IntConstZIter>);
static_assert(std::random_access_iterator<IntReverseZIter>);
static_assert(std::random_access_iterator<IntConstReverseZIter>);
static_assert(std::random_access_iterator<IntNIter>);
static_assert(std::random_access_iterator<IntConstNIter>);
static_assert(std::random_access_iterator<IntReverseNIter>);
static_assert(std::random_access_iterator<IntConstReverseNIter>);
static_assert(std::random_access_iterator<IntDIter>);
static_assert(std::random_access_iterator<IntConstDIter>);
static_assert(std::random_access_iterator<IntReverseDIter>);
static_assert(std::random_access_iterator<IntConstReverseDIter>);
static_assert(std::random_access_iterator<IntMIter>);
static_assert(std::random_access_iterator<IntConstMIter>);
static_assert(std::random_access_iterator<IntReverseMIter>);
static_assert(std::random_access_iterator<IntConstReverseMIter>);
static_assert(std::random_access_iterator<StringZIter>);
static_assert(std::random_access_iterator<StringConstZIter>);
static_assert(std::random_access_iterator<StringReverseZIter>);
static_assert(std::random_access_iterator<StringConstReverseZIter>);
static_assert(std::random_access_iterator<StringNIter>);
static_assert(std::random_access_iterator<StringConstNIter>);
static_assert(std::random_access_iterator<StringReverseNIter>);
static_assert(std::random_access_iterator<StringConstReverseNIter>);
static_assert(std::random_access_iterator<StringDIter>);
static_assert(std::random_access_iterator<StringConstDIter>);
static_assert(std::random_access_iterator<StringReverseDIter>);
static_assert(std::random_access_iterator<StringConstReverseDIter>);
static_assert(std::random_access_iterator<StringMIter>);
static_assert(std::random_access_iterator<StringConstMIter>);
static_assert(std::random_access_iterator<StringReverseMIter>);
static_assert(std::random_access_iterator<StringConstReverseMIter>);

class IteratorExceptionTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testZIteratorTwoOperandsExceptions();
    void testNIteratorTwoOperandsExceptions();
    void testDiagIteratorTwoOperandsExceptions();
    void testNonDiagBeginEndIteratorExceptions();
    void testDiagBeginEndIteratorAbsoluteCoordinatesExceptions();
    void testDiagBeginEndIteratorRelativeCoordinatesExceptions();
    void testNonDiagRandomIteratorRowColumnExceptions();
    void testNonDiagRandomIteratorIndexExceptions();
    void testDiagRandomIteratorAbsoluteCoordinatesExceptions();
    void testDiagRandomIteratorRelativeCoordinatesExceptions();
    void testZIteratorAsteriskOperatorExceptions();
    void testNIteratorAsteriskOperatorExceptions();
    void testDiagIteratorAsteriskOperatorExceptions();
    void testZIteratorArrowOperatorExceptions();
    void testNIteratorArrowOperatorExceptions();
    void testDiagIteratorArrowOperatorExceptions();
    void testZIteratorSquareBracketsOperatorExceptions();
    void testNIteratorSquareBracketsOperatorExceptions();
    void testDiagIteratorSquareBracketsOperatorExceptions();

    // test data
    void testZIteratorTwoOperandsExceptions_data();
    void testNIteratorTwoOperandsExceptions_data();
    void testDiagIteratorTwoOperandsExceptions_data();
    void testNonDiagBeginEndIteratorExceptions_data();
    void testDiagBeginEndIteratorAbsoluteCoordinatesExceptions_data();
    void testDiagBeginEndIteratorRelativeCoordinatesExceptions_data();
    void testNonDiagRandomIteratorRowColumnExceptions_data();
    void testNonDiagRandomIteratorIndexExceptions_data();
    void testDiagRandomIteratorAbsoluteCoordinatesExceptions_data();
    void testDiagRandomIteratorRelativeCoordinatesExceptions_data();
    void testZIteratorAsteriskOperatorExceptions_data();
    void testNIteratorAsteriskOperatorExceptions_data();
    void testDiagIteratorAsteriskOperatorExceptions_data();
    void testZIteratorArrowOperatorExceptions_data();
    void testNIteratorArrowOperatorExceptions_data();
    void testDiagIteratorArrowOperatorExceptions_data();
    void testZIteratorSquareBracketsOperatorExceptions_data();
    void testNIteratorSquareBracketsOperatorExceptions_data();
    void testDiagIteratorSquareBracketsOperatorExceptions_data();

private:
    IntMatrix m_PrimaryIntMatrix;
    IntMatrix m_SecondaryIntMatrix;
    IntMatrix m_ThirdIntMatrix;
    IntMatrix m_FourthIntMatrix;
    IntMatrix m_FifthIntMatrix;
    IntMatrix m_SixthIntMatrix;
    StringMatrix m_PrimaryStringMatrix;
    StringMatrix m_SecondaryStringMatrix;
};

void IteratorExceptionTests::testZIteratorTwoOperandsExceptions()
{
    QFETCH(IntZIter, firstZIterator);
    QFETCH(IntZIter, secondZIterator);
    QFETCH(IntConstZIter, firstConstZIterator);
    QFETCH(IntConstZIter, secondConstZIterator);
    QFETCH(IntReverseZIter, firstReverseZIterator);
    QFETCH(IntReverseZIter, secondReverseZIterator);
    QFETCH(IntConstReverseZIter, firstConstReverseZIterator);
    QFETCH(IntConstReverseZIter, secondConstReverseZIterator);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstZIterator == secondZIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstZIterator != secondZIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstZIterator < secondZIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstZIterator <= secondZIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstZIterator > secondZIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstZIterator >= secondZIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix_diff_t diff{firstZIterator - secondZIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstConstZIterator == secondConstZIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstConstZIterator != secondConstZIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstConstZIterator < secondConstZIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstConstZIterator <= secondConstZIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstConstZIterator > secondConstZIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstConstZIterator >= secondConstZIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix_diff_t diff{firstConstZIterator - secondConstZIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstReverseZIterator == secondReverseZIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstReverseZIterator != secondReverseZIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstReverseZIterator < secondReverseZIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstReverseZIterator <= secondReverseZIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstReverseZIterator > secondReverseZIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstReverseZIterator >= secondReverseZIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix_diff_t diff{firstReverseZIterator - secondReverseZIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstConstReverseZIterator == secondConstReverseZIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstConstReverseZIterator != secondConstReverseZIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstConstReverseZIterator < secondConstReverseZIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstConstReverseZIterator <= secondConstReverseZIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstConstReverseZIterator > secondConstReverseZIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstConstReverseZIterator >= secondConstReverseZIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix_diff_t diff{firstConstReverseZIterator - secondConstReverseZIterator}; Q_UNUSED(diff);});
}

void IteratorExceptionTests::testNIteratorTwoOperandsExceptions()
{
    QFETCH(IntNIter, firstNIterator);
    QFETCH(IntNIter, secondNIterator);
    QFETCH(IntConstNIter, firstConstNIterator);
    QFETCH(IntConstNIter, secondConstNIterator);
    QFETCH(IntReverseNIter, firstReverseNIterator);
    QFETCH(IntReverseNIter, secondReverseNIterator);
    QFETCH(IntConstReverseNIter, firstConstReverseNIterator);
    QFETCH(IntConstReverseNIter, secondConstReverseNIterator);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstNIterator == secondNIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstNIterator != secondNIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstNIterator < secondNIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstNIterator <= secondNIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstNIterator > secondNIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstNIterator >= secondNIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix_diff_t diff{firstNIterator - secondNIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstConstNIterator == secondConstNIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstConstNIterator != secondConstNIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstConstNIterator < secondConstNIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstConstNIterator <= secondConstNIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstConstNIterator > secondConstNIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstConstNIterator >= secondConstNIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix_diff_t diff{firstConstNIterator - secondConstNIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstReverseNIterator == secondReverseNIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstReverseNIterator != secondReverseNIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstReverseNIterator < secondReverseNIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstReverseNIterator <= secondReverseNIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstReverseNIterator > secondReverseNIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstReverseNIterator >= secondReverseNIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix_diff_t diff{firstReverseNIterator - secondReverseNIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstConstReverseNIterator == secondConstReverseNIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstConstReverseNIterator != secondConstReverseNIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstConstReverseNIterator < secondConstReverseNIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstConstReverseNIterator <= secondConstReverseNIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstConstReverseNIterator > secondConstReverseNIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstConstReverseNIterator >= secondConstReverseNIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix_diff_t diff{firstConstReverseNIterator - secondConstReverseNIterator}; Q_UNUSED(diff);});
}

void IteratorExceptionTests::testDiagIteratorTwoOperandsExceptions()
{
    QFETCH(IntDIter, firstDIterator);
    QFETCH(IntDIter, secondDIterator);
    QFETCH(IntConstDIter, firstConstDIterator);
    QFETCH(IntConstDIter, secondConstDIterator);
    QFETCH(IntReverseDIter, firstReverseDIterator);
    QFETCH(IntReverseDIter, secondReverseDIterator);
    QFETCH(IntConstReverseDIter, firstConstReverseDIterator);
    QFETCH(IntConstReverseDIter, secondConstReverseDIterator);
    QFETCH(IntMIter, firstMIterator);
    QFETCH(IntMIter, secondMIterator);
    QFETCH(IntConstMIter, firstConstMIterator);
    QFETCH(IntConstMIter, secondConstMIterator);
    QFETCH(IntReverseMIter, firstReverseMIterator);
    QFETCH(IntReverseMIter, secondReverseMIterator);
    QFETCH(IntConstReverseMIter, firstConstReverseMIterator);
    QFETCH(IntConstReverseMIter, secondConstReverseMIterator);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstDIterator == secondDIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstDIterator != secondDIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstDIterator < secondDIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstDIterator <= secondDIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstDIterator > secondDIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstDIterator >= secondDIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix_diff_t diff{firstDIterator - secondDIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstConstDIterator == secondConstDIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstConstDIterator != secondConstDIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstConstDIterator < secondConstDIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstConstDIterator <= secondConstDIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstConstDIterator > secondConstDIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstConstDIterator >= secondConstDIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix_diff_t diff{firstConstDIterator - secondConstDIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstReverseDIterator == secondReverseDIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstReverseDIterator != secondReverseDIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstReverseDIterator < secondReverseDIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstReverseDIterator <= secondReverseDIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstReverseDIterator > secondReverseDIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstReverseDIterator >= secondReverseDIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix_diff_t diff{firstReverseDIterator - secondReverseDIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstConstReverseDIterator == secondConstReverseDIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstConstReverseDIterator != secondConstReverseDIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstConstReverseDIterator < secondConstReverseDIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstConstReverseDIterator <= secondConstReverseDIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstConstReverseDIterator > secondConstReverseDIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstConstReverseDIterator >= secondConstReverseDIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix_diff_t diff{firstConstReverseDIterator - secondConstReverseDIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstMIterator == secondMIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstMIterator != secondMIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstMIterator < secondMIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstMIterator <= secondMIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstMIterator > secondMIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstMIterator >= secondMIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix_diff_t diff{firstMIterator - secondMIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstConstMIterator == secondConstMIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstConstMIterator != secondConstMIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstConstMIterator < secondConstMIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstConstMIterator <= secondConstMIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstConstMIterator > secondConstMIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstConstMIterator >= secondConstMIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix_diff_t diff{firstConstMIterator - secondConstMIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstReverseMIterator == secondReverseMIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstReverseMIterator != secondReverseMIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstReverseMIterator < secondReverseMIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstReverseMIterator <= secondReverseMIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstReverseMIterator > secondReverseMIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstReverseMIterator >= secondReverseMIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix_diff_t diff{firstReverseMIterator - secondReverseMIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstConstReverseMIterator == secondConstReverseMIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstConstReverseMIterator != secondConstReverseMIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstConstReverseMIterator < secondConstReverseMIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstConstReverseMIterator <= secondConstReverseMIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstConstReverseMIterator > secondConstReverseMIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstConstReverseMIterator >= secondConstReverseMIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix_diff_t diff{firstConstReverseMIterator - secondConstReverseMIterator}; Q_UNUSED(diff);});
}

void IteratorExceptionTests::testNonDiagBeginEndIteratorExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, rowColumnNr);
    
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntZIter it{matrix.zRowBegin(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntZIter it{matrix.zRowEnd(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstZIter it{matrix.constZRowBegin(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstZIter it{matrix.constZRowEnd(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseZIter it{matrix.reverseZRowBegin(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseZIter it{matrix.reverseZRowEnd(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseZIter it{matrix.constReverseZRowBegin(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseZIter it{matrix.constReverseZRowEnd(rowColumnNr)}; Q_UNUSED(it)});

    matrix.transpose(matrix);
    
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntNIter it{matrix.nColumnBegin(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntNIter it{matrix.nColumnEnd(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstNIter it{matrix.constNColumnBegin(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstNIter it{matrix.constNColumnEnd(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseNIter it{matrix.reverseNColumnBegin(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseNIter it{matrix.reverseNColumnEnd(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseNIter it{matrix.constReverseNColumnBegin(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseNIter it{matrix.constReverseNColumnEnd(rowColumnNr)}; Q_UNUSED(it)});
}

void IteratorExceptionTests::testDiagBeginEndIteratorAbsoluteCoordinatesExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, rowNr);
    QFETCH(matrix_size_t, columnNr);
    
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntDIter it{matrix.dBegin(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntDIter it{matrix.dEnd(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstDIter it{matrix.constDBegin(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstDIter it{matrix.constDEnd(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseDIter it{matrix.reverseDBegin(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseDIter it{matrix.reverseDEnd(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseDIter it{matrix.constReverseDBegin(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseDIter it{matrix.constReverseDEnd(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMIter it{matrix.mBegin(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMIter it{matrix.mEnd(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstMIter it{matrix.constMBegin(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstMIter it{matrix.constMEnd(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseMIter it{matrix.reverseMBegin(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseMIter it{matrix.reverseMEnd(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseMIter it{matrix.constReverseMBegin(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseMIter it{matrix.constReverseMEnd(rowNr, columnNr)}; Q_UNUSED(it);});
}

void IteratorExceptionTests::testDiagBeginEndIteratorRelativeCoordinatesExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_diff_t, diagonalNr);
    
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntDIter it{matrix.dBegin(diagonalNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntDIter it{matrix.dEnd(diagonalNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstDIter it{matrix.constDBegin(diagonalNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstDIter it{matrix.constDEnd(diagonalNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseDIter it{matrix.reverseDBegin(diagonalNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseDIter it{matrix.reverseDEnd(diagonalNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseDIter it{matrix.constReverseDBegin(diagonalNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseDIter it{matrix.constReverseDEnd(diagonalNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMIter it{matrix.mBegin(diagonalNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMIter it{matrix.mEnd(diagonalNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstMIter it{matrix.constMBegin(diagonalNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstMIter it{matrix.constMEnd(diagonalNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseMIter it{matrix.reverseMBegin(diagonalNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseMIter it{matrix.reverseMEnd(diagonalNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseMIter it{matrix.constReverseMBegin(diagonalNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseMIter it{matrix.constReverseMEnd(diagonalNr)}; Q_UNUSED(it);});
}

void IteratorExceptionTests::testNonDiagRandomIteratorRowColumnExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, rowNr);
    QFETCH(matrix_size_t, columnNr);
    
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntZIter it{matrix.getZIterator(rowNr, columnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstZIter it{matrix.getConstZIterator(rowNr, columnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseZIter it{matrix.getReverseZIterator(rowNr, columnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseZIter it{matrix.getConstReverseZIterator(rowNr, columnNr)}; Q_UNUSED(it)});

    matrix.transpose(matrix);
    
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntNIter it{matrix.getNIterator(columnNr, rowNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstNIter it{matrix.getConstNIterator(columnNr, rowNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseNIter it{matrix.getReverseNIterator(columnNr, rowNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseNIter it{matrix.getConstReverseNIterator(columnNr, rowNr)}; Q_UNUSED(it)});
}

void IteratorExceptionTests::testNonDiagRandomIteratorIndexExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, index);
    
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntZIter it{matrix.getZIterator(index)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstZIter it{matrix.getConstZIterator(index)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseZIter it{matrix.getReverseZIterator(index)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseZIter it{matrix.getConstReverseZIterator(index)}; Q_UNUSED(it)});

    matrix.transpose(matrix);
    
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntNIter it{matrix.getNIterator(index)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstNIter it{matrix.getConstNIterator(index)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseNIter it{matrix.getReverseNIterator(index)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseNIter it{matrix.getConstReverseNIterator(index)}; Q_UNUSED(it)});
}

void IteratorExceptionTests::testDiagRandomIteratorAbsoluteCoordinatesExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, rowNr);
    QFETCH(matrix_size_t, columnNr);
    
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntDIter it{matrix.getDIterator(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstDIter it{matrix.getConstDIterator(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseDIter it{matrix.getReverseDIterator(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseDIter it{matrix.getConstReverseDIterator(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMIter it{matrix.getMIterator(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstMIter it{matrix.getConstMIterator(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseMIter it{matrix.getReverseMIterator(rowNr, columnNr)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseMIter it{matrix.getConstReverseMIterator(rowNr, columnNr)}; Q_UNUSED(it);});
}

void IteratorExceptionTests::testDiagRandomIteratorRelativeCoordinatesExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_diff_t, diagonalNr);
    QFETCH(matrix_size_t, diagonalIndex);
    
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntDIter it{matrix.getDIterator({diagonalNr, diagonalIndex})}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstDIter it{matrix.getConstDIterator({diagonalNr, diagonalIndex})}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseDIter it{matrix.getReverseDIterator({diagonalNr, diagonalIndex})}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseDIter it{matrix.getConstReverseDIterator({diagonalNr, diagonalIndex})}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMIter it{matrix.getMIterator({diagonalNr, diagonalIndex})}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstMIter it{matrix.getConstMIterator({diagonalNr, diagonalIndex})}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntReverseMIter it{matrix.getReverseMIterator({diagonalNr, diagonalIndex})}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntConstReverseMIter it{matrix.getConstReverseMIterator({diagonalNr, diagonalIndex})}; Q_UNUSED(it);});
}

void IteratorExceptionTests::testZIteratorAsteriskOperatorExceptions()
{
    QFETCH(IntZIter, zIterator);
    QFETCH(IntConstZIter, constZIterator);
    QFETCH(IntReverseZIter, reverseZIterator);
    QFETCH(IntConstReverseZIter, constReverseZIterator);
    QFETCH(int, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {*zIterator = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(*constZIterator);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {*reverseZIterator = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(*constReverseZIterator);});
}

void IteratorExceptionTests::testNIteratorAsteriskOperatorExceptions()
{
    QFETCH(IntNIter, nIterator);
    QFETCH(IntConstNIter, constNIterator);
    QFETCH(IntReverseNIter, reverseNIterator);
    QFETCH(IntConstReverseNIter, constReverseNIterator);
    QFETCH(int, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {*nIterator = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(*constNIterator);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {*reverseNIterator = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(*constReverseNIterator);});
}

void IteratorExceptionTests::testDiagIteratorAsteriskOperatorExceptions()
{
    QFETCH(IntDIter, dIterator);
    QFETCH(IntConstDIter, constDIterator);
    QFETCH(IntReverseDIter, reverseDIterator);
    QFETCH(IntConstReverseDIter, constReverseDIterator);
    QFETCH(IntMIter, mIterator);
    QFETCH(IntConstMIter, constMIterator);
    QFETCH(IntReverseMIter, reverseMIterator);
    QFETCH(IntConstReverseMIter, constReverseMIterator);
    QFETCH(int, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {*dIterator = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(*constDIterator);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {*reverseDIterator = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(*constReverseDIterator);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {*mIterator = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(*constMIterator);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {*reverseMIterator = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(*constReverseMIterator);});
}

void IteratorExceptionTests::testZIteratorArrowOperatorExceptions()
{
    QFETCH(StringZIter, zIterator);
    QFETCH(StringConstZIter, constZIterator);
    QFETCH(StringReverseZIter, reverseZIterator);
    QFETCH(StringConstReverseZIter, constReverseZIterator);
    QFETCH(std::string, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {zIterator->assign(value);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constZIterator->size());});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {reverseZIterator->assign(value);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constReverseZIterator->size());});
}

void IteratorExceptionTests::testNIteratorArrowOperatorExceptions()
{
    QFETCH(StringNIter, nIterator);
    QFETCH(StringConstNIter, constNIterator);
    QFETCH(StringReverseNIter, reverseNIterator);
    QFETCH(StringConstReverseNIter, constReverseNIterator);
    QFETCH(std::string, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {nIterator->assign(value);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constNIterator->size());});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {reverseNIterator->assign(value);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constReverseNIterator->size());});
}

void IteratorExceptionTests::testDiagIteratorArrowOperatorExceptions()
{
    QFETCH(StringDIter, dIterator);
    QFETCH(StringConstDIter, constDIterator);
    QFETCH(StringReverseDIter, reverseDIterator);
    QFETCH(StringConstReverseDIter, constReverseDIterator);
    QFETCH(StringMIter, mIterator);
    QFETCH(StringConstMIter, constMIterator);
    QFETCH(StringReverseMIter, reverseMIterator);
    QFETCH(StringConstReverseMIter, constReverseMIterator);
    QFETCH(std::string, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {dIterator->assign(value);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constDIterator->size());});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {reverseDIterator->assign(value);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constReverseDIterator->size());});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {mIterator->assign(value);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constMIterator->size());});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {reverseMIterator->assign(value);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constReverseMIterator->size());});
}

void IteratorExceptionTests::testZIteratorSquareBracketsOperatorExceptions()
{
    QFETCH(IntZIter, zIterator);
    QFETCH(IntConstZIter, constZIterator);
    QFETCH(IntReverseZIter, reverseZIterator);
    QFETCH(IntConstReverseZIter, constReverseZIterator);
    QFETCH(matrix_diff_t, forwardIndex);
    QFETCH(matrix_diff_t, reverseIndex);
    QFETCH(int, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {zIterator[forwardIndex] = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constZIterator[forwardIndex]);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {reverseZIterator[reverseIndex] = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constReverseZIterator[reverseIndex]);});
}

void IteratorExceptionTests::testNIteratorSquareBracketsOperatorExceptions()
{
    QFETCH(IntNIter, nIterator);
    QFETCH(IntConstNIter, constNIterator);
    QFETCH(IntReverseNIter, reverseNIterator);
    QFETCH(IntConstReverseNIter, constReverseNIterator);
    QFETCH(matrix_diff_t, forwardIndex);
    QFETCH(matrix_diff_t, reverseIndex);
    QFETCH(int, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {nIterator[forwardIndex] = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constNIterator[forwardIndex]);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {reverseNIterator[reverseIndex] = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constReverseNIterator[reverseIndex]);});
}

void IteratorExceptionTests::testDiagIteratorSquareBracketsOperatorExceptions()
{
    QFETCH(IntDIter, dIterator);
    QFETCH(IntConstDIter, constDIterator);
    QFETCH(IntReverseDIter, reverseDIterator);
    QFETCH(IntConstReverseDIter, constReverseDIterator);
    QFETCH(IntMIter, mIterator);
    QFETCH(IntConstMIter, constMIterator);
    QFETCH(IntReverseMIter, reverseMIterator);
    QFETCH(IntConstReverseMIter, constReverseMIterator);
    QFETCH(matrix_diff_t, forwardIndex);
    QFETCH(matrix_diff_t, reverseIndex);
    QFETCH(int, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {dIterator[forwardIndex] = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constDIterator[forwardIndex]);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {reverseDIterator[reverseIndex] = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constReverseDIterator[reverseIndex]);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {mIterator[forwardIndex] = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constMIterator[forwardIndex]);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {reverseMIterator[reverseIndex] = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constReverseMIterator[reverseIndex]);});
}

void IteratorExceptionTests::testZIteratorTwoOperandsExceptions_data()
{
    QTest::addColumn<IntZIter>("firstZIterator");
    QTest::addColumn<IntZIter>("secondZIterator");
    QTest::addColumn<IntConstZIter>("firstConstZIterator");
    QTest::addColumn<IntConstZIter>("secondConstZIterator");
    QTest::addColumn<IntReverseZIter>("firstReverseZIterator");
    QTest::addColumn<IntReverseZIter>("secondReverseZIterator");
    QTest::addColumn<IntConstReverseZIter>("firstConstReverseZIterator");
    QTest::addColumn<IntConstReverseZIter>("secondConstReverseZIterator");

    m_PrimaryIntMatrix = {2, 3, 4};
    m_SecondaryIntMatrix = {2, 3, -5};
    m_ThirdIntMatrix = {2, 3, 4};
    m_FourthIntMatrix = m_PrimaryIntMatrix;
    m_FifthIntMatrix = std::move(m_ThirdIntMatrix);

    QTest::newRow("1: end iterator, random iterator") << m_PrimaryIntMatrix.zEnd() << m_SecondaryIntMatrix.getZIterator(1, 0) << m_PrimaryIntMatrix.constZEnd() << m_SecondaryIntMatrix.getConstZIterator(1, 0) << m_PrimaryIntMatrix.reverseZEnd() << m_SecondaryIntMatrix.getReverseZIterator(1, 0) << m_PrimaryIntMatrix.constReverseZEnd() << m_SecondaryIntMatrix.getConstReverseZIterator(1, 0);
    QTest::newRow("2: end iterator, begin iterator") << m_PrimaryIntMatrix.zEnd() << m_FourthIntMatrix.zBegin() << m_PrimaryIntMatrix.constZEnd() << m_FourthIntMatrix.constZBegin() << m_PrimaryIntMatrix.reverseZEnd() << m_FourthIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.constReverseZEnd() << m_FourthIntMatrix.constReverseZBegin();
    QTest::newRow("3: begin iterator, end iterator") << m_ThirdIntMatrix.zBegin() << m_FifthIntMatrix.zEnd() << m_ThirdIntMatrix.constZBegin() << m_FifthIntMatrix.constZEnd() << m_ThirdIntMatrix.reverseZBegin() << m_FifthIntMatrix.reverseZEnd() << m_ThirdIntMatrix.constReverseZBegin() << m_FifthIntMatrix.constReverseZEnd();
}

void IteratorExceptionTests::testNIteratorTwoOperandsExceptions_data()
{
    QTest::addColumn<IntNIter>("firstNIterator");
    QTest::addColumn<IntNIter>("secondNIterator");
    QTest::addColumn<IntConstNIter>("firstConstNIterator");
    QTest::addColumn<IntConstNIter>("secondConstNIterator");
    QTest::addColumn<IntReverseNIter>("firstReverseNIterator");
    QTest::addColumn<IntReverseNIter>("secondReverseNIterator");
    QTest::addColumn<IntConstReverseNIter>("firstConstReverseNIterator");
    QTest::addColumn<IntConstReverseNIter>("secondConstReverseNIterator");

    m_PrimaryIntMatrix = {3, 2, 4};
    m_SecondaryIntMatrix = {3, 2, -5};
    m_ThirdIntMatrix = {3, 2, 4};
    m_FourthIntMatrix = m_PrimaryIntMatrix;
    m_FifthIntMatrix = std::move(m_ThirdIntMatrix);

    QTest::newRow("1: end iterator, random iterator") << m_PrimaryIntMatrix.nEnd() << m_SecondaryIntMatrix.getNIterator(0, 1) << m_PrimaryIntMatrix.constNEnd() << m_SecondaryIntMatrix.getConstNIterator(0, 1) << m_PrimaryIntMatrix.reverseNEnd() << m_SecondaryIntMatrix.getReverseNIterator(0, 1) << m_PrimaryIntMatrix.constReverseNEnd() << m_SecondaryIntMatrix.getConstReverseNIterator(0, 1);
    QTest::newRow("2: end iterator, begin iterator") << m_PrimaryIntMatrix.nEnd() << m_FourthIntMatrix.nBegin() << m_PrimaryIntMatrix.constNEnd() << m_FourthIntMatrix.constNBegin() << m_PrimaryIntMatrix.reverseNEnd() << m_FourthIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.constReverseNEnd() << m_FourthIntMatrix.constReverseNBegin();
    QTest::newRow("3: begin iterator, end iterator") << m_ThirdIntMatrix.nBegin() << m_FifthIntMatrix.nEnd() << m_ThirdIntMatrix.constNBegin() << m_FifthIntMatrix.constNEnd() << m_ThirdIntMatrix.reverseNBegin() << m_FifthIntMatrix.reverseNEnd() << m_ThirdIntMatrix.constReverseNBegin() << m_FifthIntMatrix.constReverseNEnd();
}

void IteratorExceptionTests::testDiagIteratorTwoOperandsExceptions_data()
{
    QTest::addColumn<IntDIter>("firstDIterator");
    QTest::addColumn<IntDIter>("secondDIterator");
    QTest::addColumn<IntConstDIter>("firstConstDIterator");
    QTest::addColumn<IntConstDIter>("secondConstDIterator");
    QTest::addColumn<IntReverseDIter>("firstReverseDIterator");
    QTest::addColumn<IntReverseDIter>("secondReverseDIterator");
    QTest::addColumn<IntConstReverseDIter>("firstConstReverseDIterator");
    QTest::addColumn<IntConstReverseDIter>("secondConstReverseDIterator");
    QTest::addColumn<IntMIter>("firstMIterator");
    QTest::addColumn<IntMIter>("secondMIterator");
    QTest::addColumn<IntConstMIter>("firstConstMIterator");
    QTest::addColumn<IntConstMIter>("secondConstMIterator");
    QTest::addColumn<IntReverseMIter>("firstReverseMIterator");
    QTest::addColumn<IntReverseMIter>("secondReverseMIterator");
    QTest::addColumn<IntConstReverseMIter>("firstConstReverseMIterator");
    QTest::addColumn<IntConstReverseMIter>("secondConstReverseMIterator");

    m_PrimaryIntMatrix = {3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix = {3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::newRow("1: random iterator, random iterator") << m_PrimaryIntMatrix.getDIterator(2, 1) << m_PrimaryIntMatrix.getDIterator({1, 1}) << m_PrimaryIntMatrix.getConstDIterator(2, 1) << m_PrimaryIntMatrix.getConstDIterator({1, 1}) << m_PrimaryIntMatrix.getReverseDIterator(2, 1) << m_PrimaryIntMatrix.getReverseDIterator({1, 1}) <<  m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) << m_PrimaryIntMatrix.getConstReverseDIterator({1, 1}) << m_PrimaryIntMatrix.getMIterator(2, 2) << m_PrimaryIntMatrix.getMIterator({1, 1}) << m_PrimaryIntMatrix.getConstMIterator(2, 2) << m_PrimaryIntMatrix.getConstMIterator({1, 1}) << m_PrimaryIntMatrix.getReverseMIterator(2, 2) << m_PrimaryIntMatrix.getReverseMIterator({1, 1}) <<  m_PrimaryIntMatrix.getConstReverseMIterator(2, 2) << m_PrimaryIntMatrix.getConstReverseMIterator({1, 1});
    QTest::newRow("2: end iterator, end iterator") << m_PrimaryIntMatrix.dEnd(1, 2) << m_PrimaryIntMatrix.dEnd(-1) << m_PrimaryIntMatrix.constDEnd(1, 2) << m_PrimaryIntMatrix.constDEnd(-1) << m_PrimaryIntMatrix.reverseDEnd(1, 2) << m_PrimaryIntMatrix.reverseDEnd(-1) <<  m_PrimaryIntMatrix.constReverseDEnd(1, 2) << m_PrimaryIntMatrix.constReverseDEnd(-1) << m_PrimaryIntMatrix.mEnd(1, 1) << m_PrimaryIntMatrix.mEnd(-1) << m_PrimaryIntMatrix.constMEnd(1, 1) << m_PrimaryIntMatrix.constMEnd(-1) << m_PrimaryIntMatrix.reverseMEnd(1, 1) <<  m_PrimaryIntMatrix.reverseMEnd(-1) << m_PrimaryIntMatrix.constReverseMEnd(1, 1) << m_PrimaryIntMatrix.constReverseMEnd(-1);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getDIterator(1, 2) << m_SecondaryIntMatrix.getDIterator({1, 1}) << m_PrimaryIntMatrix.getConstDIterator(1, 2) << m_SecondaryIntMatrix.getConstDIterator({1, 1}) << m_PrimaryIntMatrix.getReverseDIterator(1, 2) << m_SecondaryIntMatrix.getReverseDIterator({1, 1}) <<  m_PrimaryIntMatrix.getConstReverseDIterator(1, 2) << m_SecondaryIntMatrix.getConstReverseDIterator({1, 1}) << m_PrimaryIntMatrix.getMIterator(1, 1) << m_SecondaryIntMatrix.getMIterator({1, 1}) << m_PrimaryIntMatrix.getConstMIterator(1, 1) << m_SecondaryIntMatrix.getConstMIterator({1, 1}) << m_PrimaryIntMatrix.getReverseMIterator(1, 1) << m_SecondaryIntMatrix.getReverseMIterator({1, 1}) <<  m_PrimaryIntMatrix.getConstReverseMIterator(1, 1) << m_SecondaryIntMatrix.getConstReverseMIterator({1, 1});

    // test same diagonal iterator after matrix update
    m_ThirdIntMatrix = {3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    IntDIter dIterator{m_ThirdIntMatrix.getDIterator({1, 1})};
    IntConstDIter constDIterator{m_ThirdIntMatrix.getConstDIterator({1, 1})};
    IntReverseDIter reverseDIterator{m_ThirdIntMatrix.getReverseDIterator({1, 1})};
    IntConstReverseDIter constReverseDIterator{m_ThirdIntMatrix.getConstReverseDIterator({1, 1})};
    IntMIter mIterator{m_ThirdIntMatrix.getMIterator({1, 1})};
    IntConstMIter constMIterator{m_ThirdIntMatrix.getConstMIterator({1, 1})};
    IntReverseMIter reverseMIterator{m_ThirdIntMatrix.getReverseMIterator({1, 1})};
    IntConstReverseMIter constReverseMIterator{m_ThirdIntMatrix.getConstReverseMIterator({1, 1})};

    m_ThirdIntMatrix.insertRow(1);
    
    QTest::newRow("4: random iterator, random iterator") << IntDIter{dIterator} << m_ThirdIntMatrix.getDIterator(1, 2) << IntConstDIter{constDIterator} << m_ThirdIntMatrix.getConstDIterator(1, 2) << IntReverseDIter{reverseDIterator} << m_ThirdIntMatrix.getReverseDIterator(1, 2) << IntConstReverseDIter{constReverseDIterator} << m_ThirdIntMatrix.getConstReverseDIterator(1, 2) << IntMIter{mIterator} << m_ThirdIntMatrix.getMIterator(1, 1) << IntConstMIter{constMIterator} << m_ThirdIntMatrix.getConstMIterator(1, 1) << IntReverseMIter{reverseMIterator} << m_ThirdIntMatrix.getReverseMIterator(1, 1) << IntConstReverseMIter{constReverseMIterator} << m_ThirdIntMatrix.getConstReverseMIterator(1, 1);

    m_FourthIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    dIterator = m_FourthIntMatrix.getDIterator({-1, 1});
    constDIterator = m_FourthIntMatrix.getConstDIterator({-1, 1});
    reverseDIterator = m_FourthIntMatrix.getReverseDIterator({-1, 1});
    constReverseDIterator = m_FourthIntMatrix.getConstReverseDIterator({-1, 1});
    mIterator = m_FourthIntMatrix.getMIterator({-1, 1});
    constMIterator = m_FourthIntMatrix.getConstMIterator({-1, 1});
    reverseMIterator = m_FourthIntMatrix.getReverseMIterator({-1, 1});
    constReverseMIterator = m_FourthIntMatrix.getConstReverseMIterator({-1, 1});

    m_FourthIntMatrix.insertColumn(1);
    
    QTest::newRow("5: random iterator, random iterator") << IntDIter{dIterator} << m_FourthIntMatrix.getDIterator(2, 1) << IntConstDIter{constDIterator} << m_FourthIntMatrix.getConstDIterator(2, 1) << IntReverseDIter{reverseDIterator} << m_FourthIntMatrix.getReverseDIterator(2, 1) << IntConstReverseDIter{constReverseDIterator} << m_FourthIntMatrix.getConstReverseDIterator(2, 1) << IntMIter{mIterator} << m_FourthIntMatrix.getMIterator(2, 1) << IntConstMIter{constMIterator} << m_FourthIntMatrix.getConstMIterator(2, 1) << IntReverseMIter{reverseMIterator} << m_FourthIntMatrix.getReverseMIterator(2, 1) << IntConstReverseMIter{constReverseMIterator} << m_FourthIntMatrix.getConstReverseMIterator(2, 1);

    m_FifthIntMatrix = {4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16}};

    dIterator = m_FifthIntMatrix.getDIterator({-1, 0});
    constDIterator = m_FifthIntMatrix.getConstDIterator({-1, 0});
    reverseDIterator = m_FifthIntMatrix.getReverseDIterator({-1, 0});
    constReverseDIterator = m_FifthIntMatrix.getConstReverseDIterator({-1, 0});
    mIterator = m_FifthIntMatrix.getMIterator({-1, 0});
    constMIterator = m_FifthIntMatrix.getConstMIterator({-1, 0});
    reverseMIterator = m_FifthIntMatrix.getReverseMIterator({-1, 0});
    constReverseMIterator = m_FifthIntMatrix.getConstReverseMIterator({-1, 0});

    m_FifthIntMatrix.insertRow(1);
    
    QTest::newRow("6: random iterator, random iterator") << IntDIter{dIterator} << m_FifthIntMatrix.getDIterator({-1, 0}) << IntConstDIter{constDIterator} << m_FifthIntMatrix.getConstDIterator({-1, 0}) << IntReverseDIter{reverseDIterator} << m_FifthIntMatrix.getReverseDIterator({-1, 0}) << IntConstReverseDIter{constReverseDIterator} << m_FifthIntMatrix.getConstReverseDIterator({-1, 0}) << IntMIter{mIterator} << m_FifthIntMatrix.getMIterator({-1, 0}) << IntConstMIter{constMIterator} << m_FifthIntMatrix.getConstMIterator({-1, 0}) << IntReverseMIter{reverseMIterator} << m_FifthIntMatrix.getReverseMIterator({-1, 0}) << IntConstReverseMIter{constReverseMIterator} << m_FifthIntMatrix.getConstReverseMIterator({-1, 0});

    m_SixthIntMatrix = {4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16}};

    dIterator = m_SixthIntMatrix.getDIterator({1, 0});
    constDIterator = m_SixthIntMatrix.getConstDIterator({1, 0});
    reverseDIterator = m_SixthIntMatrix.getReverseDIterator({1, 0});
    constReverseDIterator = m_SixthIntMatrix.getConstReverseDIterator({1, 0});
    mIterator = m_SixthIntMatrix.getMIterator({1, 0});
    constMIterator = m_SixthIntMatrix.getConstMIterator({1, 0});
    reverseMIterator = m_SixthIntMatrix.getReverseMIterator({1, 0});
    constReverseMIterator = m_SixthIntMatrix.getConstReverseMIterator({1, 0});

    m_SixthIntMatrix.insertColumn(1);
    
    QTest::newRow("7: random iterator, random iterator") << IntDIter{dIterator} << m_SixthIntMatrix.getDIterator({1, 0}) << IntConstDIter{constDIterator} << m_SixthIntMatrix.getConstDIterator({1, 0}) << IntReverseDIter{reverseDIterator} << m_SixthIntMatrix.getReverseDIterator({1, 0}) << IntConstReverseDIter{constReverseDIterator} << m_SixthIntMatrix.getConstReverseDIterator({1, 0}) << IntMIter{mIterator} << m_SixthIntMatrix.getMIterator({1, 0}) << IntConstMIter{constMIterator} << m_SixthIntMatrix.getConstMIterator({1, 0}) << IntReverseMIter{reverseMIterator} << m_SixthIntMatrix.getReverseMIterator({1, 0}) << IntConstReverseMIter{constReverseMIterator} << m_SixthIntMatrix.getConstReverseMIterator({1, 0});
}

void IteratorExceptionTests::testNonDiagBeginEndIteratorExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("rowColumnNr");

    QTest::newRow("1: index out of range") << IntMatrix{} << 0u;
    QTest::newRow("2: index out of range") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4u;
}

void IteratorExceptionTests::testDiagBeginEndIteratorAbsoluteCoordinatesExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("rowNr");
    QTest::addColumn<matrix_size_t>("columnNr");

    QTest::newRow("1: row/column number") << IntMatrix{} << 0u << 0u;
    QTest::newRow("2: row/column number") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 0u << 3u;
    QTest::newRow("3: row/column number") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 2u << 0u;
    QTest::newRow("4: row/column number") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 2u << 3u;
}

void IteratorExceptionTests::testDiagBeginEndIteratorRelativeCoordinatesExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_diff_t>("diagonalNr");

    QTest::newRow("1: diagonal number") << IntMatrix{} << 0;
    QTest::newRow("2: diagonal number") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << -2;
    QTest::newRow("3: diagonal number") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 3;
}

void IteratorExceptionTests::testNonDiagRandomIteratorRowColumnExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("rowNr");
    QTest::addColumn<matrix_size_t>("columnNr");

    QTest::newRow("1: row/column number random iterator") << IntMatrix{} << 0u << 0u;
    QTest::newRow("2: row/column number random iterator") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 1u << 3u;
    QTest::newRow("3: row/column number random iterator") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2u << 1u;
    QTest::newRow("4: row/column number random iterator") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2u << 3u;
}

void IteratorExceptionTests::testNonDiagRandomIteratorIndexExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("index");

    QTest::newRow("1: index random iterator") << IntMatrix{} << 0u;
    QTest::newRow("2: index random iterator") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 6u;
}

void IteratorExceptionTests::testDiagRandomIteratorAbsoluteCoordinatesExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("rowNr");
    QTest::addColumn<matrix_size_t>("columnNr");

    QTest::newRow("1: absolute coordinates") << IntMatrix{} << 0u << 0u;
    QTest::newRow("2: absolute coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 0u << 3u;
    QTest::newRow("3: absolute coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 2u << 0u;
    QTest::newRow("4: absolute coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 2u << 3u;
}

void IteratorExceptionTests::testDiagRandomIteratorRelativeCoordinatesExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_diff_t>("diagonalNr");
    QTest::addColumn<matrix_size_t>("diagonalIndex");

    QTest::newRow("1: relative coordinates") << IntMatrix{} << 0 << 0u;
    QTest::newRow("2: relative coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << -2 << 0u;
    QTest::newRow("3: relative coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 3 << 0u;
    QTest::newRow("4: relative coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 0 << 2u;
    QTest::newRow("5: relative coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 1 << 2u;
    QTest::newRow("6: relative coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << -1 << 1u;
}

void IteratorExceptionTests::testZIteratorAsteriskOperatorExceptions_data()
{
    QTest::addColumn<IntZIter>("zIterator");
    QTest::addColumn<IntConstZIter>("constZIterator");
    QTest::addColumn<IntReverseZIter>("reverseZIterator");
    QTest::addColumn<IntConstReverseZIter>("constReverseZIterator");
    QTest::addColumn<int>("value");

    m_PrimaryIntMatrix.clear();
    m_SecondaryIntMatrix = {4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.constReverseZBegin() << -9;
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.constReverseZEnd() << -14;
    QTest::newRow("3: end iterator") << m_SecondaryIntMatrix.zEnd() << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.constReverseZEnd() << -14;
}

void IteratorExceptionTests::testNIteratorAsteriskOperatorExceptions_data()
{
    QTest::addColumn<IntNIter>("nIterator");
    QTest::addColumn<IntConstNIter>("constNIterator");
    QTest::addColumn<IntReverseNIter>("reverseNIterator");
    QTest::addColumn<IntConstReverseNIter>("constReverseNIterator");
    QTest::addColumn<int>("value");

    m_PrimaryIntMatrix.clear();
    m_SecondaryIntMatrix = {3, 4, {1, 4, 7, 10, 2, 5, 8, 11, 3, 6, 9, 12}};

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.constReverseNBegin() << -9;
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd() << -14;
    QTest::newRow("3: end iterator") << m_SecondaryIntMatrix.nEnd() << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd() << -14;
}

void IteratorExceptionTests::testDiagIteratorAsteriskOperatorExceptions_data()
{
    QTest::addColumn<IntDIter>("dIterator");
    QTest::addColumn<IntConstDIter>("constDIterator");
    QTest::addColumn<IntReverseDIter>("reverseDIterator");
    QTest::addColumn<IntConstReverseDIter>("constReverseDIterator");
    QTest::addColumn<IntMIter>("mIterator");
    QTest::addColumn<IntConstMIter>("constMIterator");
    QTest::addColumn<IntReverseMIter>("reverseMIterator");
    QTest::addColumn<IntConstReverseMIter>("constReverseMIterator");
    QTest::addColumn<int>("value");

    m_PrimaryIntMatrix = {4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

    QTest::newRow("1: end iterator") << m_PrimaryIntMatrix.dEnd(-1) << m_PrimaryIntMatrix.constDEnd(-1) << m_PrimaryIntMatrix.reverseDEnd(-1) << m_PrimaryIntMatrix.constReverseDEnd(-1) << m_PrimaryIntMatrix.mEnd(-1) << m_PrimaryIntMatrix.constMEnd(-1) << m_PrimaryIntMatrix.reverseMEnd(-1) << m_PrimaryIntMatrix.constReverseMEnd(-1) << -14;
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.dEnd(0, 2) << m_PrimaryIntMatrix.constDEnd(0, 2) << m_PrimaryIntMatrix.reverseDEnd(0, 2) << m_PrimaryIntMatrix.constReverseDEnd(0, 2) << m_PrimaryIntMatrix.mEnd(0, 0) << m_PrimaryIntMatrix.constMEnd(0, 0) << m_PrimaryIntMatrix.reverseMEnd(0, 0) << m_PrimaryIntMatrix.constReverseMEnd(0, 0) << -14;
}

void IteratorExceptionTests::testZIteratorArrowOperatorExceptions_data()
{
    QTest::addColumn<StringZIter>("zIterator");
    QTest::addColumn<StringConstZIter>("constZIterator");
    QTest::addColumn<StringReverseZIter>("reverseZIterator");
    QTest::addColumn<StringConstReverseZIter>("constReverseZIterator");
    QTest::addColumn<std::string>("value");

    m_PrimaryStringMatrix.clear();
    m_SecondaryStringMatrix = {2, 3, {"abc", "def", "ghi", "jkl", "mno", "pqr"}};

    QTest::newRow("1: begin iterator") << m_PrimaryStringMatrix.zBegin() << m_PrimaryStringMatrix.constZBegin() << m_PrimaryStringMatrix.reverseZBegin() << m_PrimaryStringMatrix.constReverseZBegin() << std::string{"zzz"};
    QTest::newRow("2: end iterator") << m_PrimaryStringMatrix.zEnd() << m_PrimaryStringMatrix.constZEnd() << m_PrimaryStringMatrix.reverseZEnd() << m_PrimaryStringMatrix.constReverseZEnd() << std::string{"zzz"};
    QTest::newRow("3: end itertator") << m_SecondaryStringMatrix.zEnd() << m_SecondaryStringMatrix.constZEnd() << m_SecondaryStringMatrix.reverseZEnd() << m_SecondaryStringMatrix.constReverseZEnd() << std::string{"zzz"};
}

void IteratorExceptionTests::testNIteratorArrowOperatorExceptions_data()
{
    QTest::addColumn<StringNIter>("nIterator");
    QTest::addColumn<StringConstNIter>("constNIterator");
    QTest::addColumn<StringReverseNIter>("reverseNIterator");
    QTest::addColumn<StringConstReverseNIter>("constReverseNIterator");
    QTest::addColumn<std::string>("value");

    m_PrimaryStringMatrix.clear();
    m_SecondaryStringMatrix = {3, 2, {"abc", "jkl", "def", "mno", "ghi", "pqr"}};

    QTest::newRow("1: begin iterator") << m_PrimaryStringMatrix.nBegin() << m_PrimaryStringMatrix.constNBegin() << m_PrimaryStringMatrix.reverseNBegin() << m_PrimaryStringMatrix.constReverseNBegin() << std::string{"zzz"};
    QTest::newRow("2: end iterator") << m_PrimaryStringMatrix.nEnd() << m_PrimaryStringMatrix.constNEnd() << m_PrimaryStringMatrix.reverseNEnd() << m_PrimaryStringMatrix.constReverseNEnd() << std::string{"zzz"};
    QTest::newRow("3: end itertator") << m_SecondaryStringMatrix.nEnd() << m_SecondaryStringMatrix.constNEnd() << m_SecondaryStringMatrix.reverseNEnd() << m_SecondaryStringMatrix.constReverseNEnd() << std::string{"zzz"};
}

void IteratorExceptionTests::testDiagIteratorArrowOperatorExceptions_data()
{
    QTest::addColumn<StringDIter>("dIterator");
    QTest::addColumn<StringConstDIter>("constDIterator");
    QTest::addColumn<StringReverseDIter>("reverseDIterator");
    QTest::addColumn<StringConstReverseDIter>("constReverseDIterator");
    QTest::addColumn<StringMIter>("mIterator");
    QTest::addColumn<StringConstMIter>("constMIterator");
    QTest::addColumn<StringReverseMIter>("reverseMIterator");
    QTest::addColumn<StringConstReverseMIter>("constReverseMIterator");
    QTest::addColumn<std::string>("value");

    m_PrimaryStringMatrix = {4, 3, {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l"}};

    QTest::newRow("1: end iterator") << m_PrimaryStringMatrix.dEnd(-1) << m_PrimaryStringMatrix.constDEnd(-1) << m_PrimaryStringMatrix.reverseDEnd(-1) << m_PrimaryStringMatrix.constReverseDEnd(-1) << m_PrimaryStringMatrix.mEnd(-1) << m_PrimaryStringMatrix.constMEnd(-1) << m_PrimaryStringMatrix.reverseMEnd(-1) << m_PrimaryStringMatrix.constReverseMEnd(-1) << std::string{"m"};
    QTest::newRow("2: end iterator") << m_PrimaryStringMatrix.dEnd(0, 2) << m_PrimaryStringMatrix.constDEnd(0, 2) << m_PrimaryStringMatrix.reverseDEnd(0, 2) << m_PrimaryStringMatrix.constReverseDEnd(0, 2) << m_PrimaryStringMatrix.mEnd(0, 0) << m_PrimaryStringMatrix.constMEnd(0, 0) << m_PrimaryStringMatrix.reverseMEnd(0, 0) << m_PrimaryStringMatrix.constReverseMEnd(0, 0) << std::string{"m"};
}

void IteratorExceptionTests::testZIteratorSquareBracketsOperatorExceptions_data()
{
    QTest::addColumn<IntZIter>("zIterator");
    QTest::addColumn<IntConstZIter>("constZIterator");
    QTest::addColumn<IntReverseZIter>("reverseZIterator");
    QTest::addColumn<IntConstReverseZIter>("constReverseZIterator");
    QTest::addColumn<matrix_diff_t>("forwardIndex");
    QTest::addColumn<matrix_diff_t>("reverseIndex");
    QTest::addColumn<int>("value");

    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_SecondaryIntMatrix.clear();

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.constReverseZBegin() << -2 << -2 << 7;
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.constReverseZBegin() << -1 << -1 << 7;
    QTest::newRow("3: begin iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.constReverseZBegin() << 6 << 6 << 7;
    QTest::newRow("4: begin iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.constReverseZBegin() << 7 << 7 << 7;
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getZIterator(1, 0) << m_PrimaryIntMatrix.getConstZIterator(1, 0) << m_PrimaryIntMatrix.getReverseZIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 0) << -5 << -4 << 7;
    QTest::newRow("6: random iterator") << m_PrimaryIntMatrix.getZIterator(1, 0) << m_PrimaryIntMatrix.getConstZIterator(1, 0) << m_PrimaryIntMatrix.getReverseZIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 0) << -4 << -3 << 7;
    QTest::newRow("7: random iterator") << m_PrimaryIntMatrix.getZIterator(1, 0) << m_PrimaryIntMatrix.getConstZIterator(1, 0) << m_PrimaryIntMatrix.getReverseZIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 0) << 3 << 4 << 7;
    QTest::newRow("8: random iterator") << m_PrimaryIntMatrix.getZIterator(1, 0) << m_PrimaryIntMatrix.getConstZIterator(1, 0) << m_PrimaryIntMatrix.getReverseZIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 0) << 4 << 5 << 7;
    QTest::newRow("9: end iterator") << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.constReverseZEnd() << -8 << -8 << 7;
    QTest::newRow("10: end iterator") << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.constReverseZEnd() << -7 << -7 << 7;
    QTest::newRow("11: end iterator") << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.constReverseZEnd() << 0 << 0 << 7;
    QTest::newRow("12: end iterator") << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.constReverseZEnd() << 1 << 1 << 7;
    QTest::newRow("13: begin iterator") << m_SecondaryIntMatrix.zBegin() << m_SecondaryIntMatrix.constZBegin() << m_SecondaryIntMatrix.reverseZBegin() << m_SecondaryIntMatrix.constReverseZBegin() << -1 << -1 << 7;
    QTest::newRow("14: begin iterator") << m_SecondaryIntMatrix.zBegin() << m_SecondaryIntMatrix.constZBegin() << m_SecondaryIntMatrix.reverseZBegin() << m_SecondaryIntMatrix.constReverseZBegin() << 0 << 0 << 7;
    QTest::newRow("15: begin iterator") << m_SecondaryIntMatrix.zBegin() << m_SecondaryIntMatrix.constZBegin() << m_SecondaryIntMatrix.reverseZBegin() << m_SecondaryIntMatrix.constReverseZBegin() << 1 << 1 << 7;
    QTest::newRow("16: end iterator") << m_SecondaryIntMatrix.zEnd() << m_SecondaryIntMatrix.constZEnd() << m_SecondaryIntMatrix.reverseZEnd() << m_SecondaryIntMatrix.constReverseZEnd() << -1 << -1 << 7;
    QTest::newRow("17: end iterator") << m_SecondaryIntMatrix.zEnd() << m_SecondaryIntMatrix.constZEnd() << m_SecondaryIntMatrix.reverseZEnd() << m_SecondaryIntMatrix.constReverseZEnd() << 0 << 0 << 7;
    QTest::newRow("18: end iterator") << m_SecondaryIntMatrix.zEnd() << m_SecondaryIntMatrix.constZEnd() << m_SecondaryIntMatrix.reverseZEnd() << m_SecondaryIntMatrix.constReverseZEnd() << 1 << 1 << 7;
}

void IteratorExceptionTests::testNIteratorSquareBracketsOperatorExceptions_data()
{
    QTest::addColumn<IntNIter>("nIterator");
    QTest::addColumn<IntConstNIter>("constNIterator");
    QTest::addColumn<IntReverseNIter>("reverseNIterator");
    QTest::addColumn<IntConstReverseNIter>("constReverseNIterator");
    QTest::addColumn<matrix_diff_t>("forwardIndex");
    QTest::addColumn<matrix_diff_t>("reverseIndex");
    QTest::addColumn<int>("value");

    m_PrimaryIntMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    m_SecondaryIntMatrix.clear();

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.constReverseNBegin() << -2 << -2 << 7;
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.constReverseNBegin() << -1 << -1 << 7;
    QTest::newRow("3: begin iterator") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.constReverseNBegin() << 6 << 6 << 7;
    QTest::newRow("4: begin iterator") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.constReverseNBegin() << 7 << 7 << 7;
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getNIterator(0, 1) << m_PrimaryIntMatrix.getConstNIterator(0, 1) << m_PrimaryIntMatrix.getReverseNIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 1) << -5 << -4 << 7;
    QTest::newRow("6: random iterator") << m_PrimaryIntMatrix.getNIterator(0, 1) << m_PrimaryIntMatrix.getConstNIterator(0, 1) << m_PrimaryIntMatrix.getReverseNIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 1) << -4 << -3 << 7;
    QTest::newRow("7: random iterator") << m_PrimaryIntMatrix.getNIterator(0, 1) << m_PrimaryIntMatrix.getConstNIterator(0, 1) << m_PrimaryIntMatrix.getReverseNIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 1) << 3 << 4 << 7;
    QTest::newRow("8: random iterator") << m_PrimaryIntMatrix.getNIterator(0, 1) << m_PrimaryIntMatrix.getConstNIterator(0, 1) << m_PrimaryIntMatrix.getReverseNIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 1) << 4 << 5 << 7;
    QTest::newRow("9: end iterator") << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd() << -8 << -8 << 7;
    QTest::newRow("10: end iterator") << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd() << -7 << -7 << 7;
    QTest::newRow("11: end iterator") << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd() << 0 << 0 << 7;
    QTest::newRow("12: end iterator") << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd() << 1 << 1 << 7;
    QTest::newRow("13: begin iterator") << m_SecondaryIntMatrix.nBegin() << m_SecondaryIntMatrix.constNBegin() << m_SecondaryIntMatrix.reverseNBegin() << m_SecondaryIntMatrix.constReverseNBegin() << -1 << -1 << 7;
    QTest::newRow("14: begin iterator") << m_SecondaryIntMatrix.nBegin() << m_SecondaryIntMatrix.constNBegin() << m_SecondaryIntMatrix.reverseNBegin() << m_SecondaryIntMatrix.constReverseNBegin() << 0 << 0 << 7;
    QTest::newRow("15: begin iterator") << m_SecondaryIntMatrix.nBegin() << m_SecondaryIntMatrix.constNBegin() << m_SecondaryIntMatrix.reverseNBegin() << m_SecondaryIntMatrix.constReverseNBegin() << 1 << 1 << 7;
    QTest::newRow("16: end iterator") << m_SecondaryIntMatrix.nEnd() << m_SecondaryIntMatrix.constNEnd() << m_SecondaryIntMatrix.reverseNEnd() << m_SecondaryIntMatrix.constReverseNEnd() << -1 << -1 << 7;
    QTest::newRow("17: end iterator") << m_SecondaryIntMatrix.nEnd() << m_SecondaryIntMatrix.constNEnd() << m_SecondaryIntMatrix.reverseNEnd() << m_SecondaryIntMatrix.constReverseNEnd() << 0 << 0 << 7;
    QTest::newRow("18: end iterator") << m_SecondaryIntMatrix.nEnd() << m_SecondaryIntMatrix.constNEnd() << m_SecondaryIntMatrix.reverseNEnd() << m_SecondaryIntMatrix.constReverseNEnd() << 1 << 1 << 7;
}

void IteratorExceptionTests::testDiagIteratorSquareBracketsOperatorExceptions_data()
{
    QTest::addColumn<IntDIter>("dIterator");
    QTest::addColumn<IntConstDIter>("constDIterator");
    QTest::addColumn<IntReverseDIter>("reverseDIterator");
    QTest::addColumn<IntConstReverseDIter>("constReverseDIterator");
    QTest::addColumn<IntMIter>("mIterator");
    QTest::addColumn<IntConstMIter>("constMIterator");
    QTest::addColumn<IntReverseMIter>("reverseMIterator");
    QTest::addColumn<IntConstReverseMIter>("constReverseMIterator");
    QTest::addColumn<matrix_diff_t>("forwardIndex");
    QTest::addColumn<matrix_diff_t>("reverseIndex");
    QTest::addColumn<int>("value");

    m_PrimaryIntMatrix = {4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.dBegin(0, 1) << m_PrimaryIntMatrix.constDBegin(0, 1) << m_PrimaryIntMatrix.reverseDBegin(0, 1) << m_PrimaryIntMatrix.constReverseDBegin(0, 1) << m_PrimaryIntMatrix.mBegin(0, 1) << m_PrimaryIntMatrix.constMBegin(0, 1) << m_PrimaryIntMatrix.reverseMBegin(0, 1) << m_PrimaryIntMatrix.constReverseMBegin(0, 1) << -1 << -1 << -14;
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.dEnd(0, 0) << m_PrimaryIntMatrix.constDEnd(0, 0) << m_PrimaryIntMatrix.reverseDEnd(0, 0) << m_PrimaryIntMatrix.constReverseDEnd(0, 0) << m_PrimaryIntMatrix.mEnd(0, 2) << m_PrimaryIntMatrix.constMEnd(0, 2) << m_PrimaryIntMatrix.reverseMEnd(0, 2) << m_PrimaryIntMatrix.constReverseMEnd(0, 2) << 0 << 0 << 14;
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getDIterator(2, 1) << m_PrimaryIntMatrix.getConstDIterator(2, 1) << m_PrimaryIntMatrix.getReverseDIterator(2, 1) << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) << m_PrimaryIntMatrix.getMIterator(2, 1) << m_PrimaryIntMatrix.getConstMIterator(2, 1) << m_PrimaryIntMatrix.getReverseMIterator(2, 1) << m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) << 2 << 2 << -14;
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getDIterator({0, 1}) << m_PrimaryIntMatrix.getConstDIterator({0, 1}) << m_PrimaryIntMatrix.getReverseDIterator({0, 1}) << m_PrimaryIntMatrix.getConstReverseDIterator({0, 1}) << m_PrimaryIntMatrix.getMIterator({0, 1}) << m_PrimaryIntMatrix.getConstMIterator({0, 1}) << m_PrimaryIntMatrix.getReverseMIterator({0, 1}) << m_PrimaryIntMatrix.getConstReverseMIterator({0, 1}) << -2 << -2 << 14;
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getDIterator({1, 0}) << m_PrimaryIntMatrix.getConstDIterator({1, 0}) << m_PrimaryIntMatrix.getReverseDIterator({1, 0}) << m_PrimaryIntMatrix.getConstReverseDIterator({1, 0}) << m_PrimaryIntMatrix.getMIterator({1, 0}) << m_PrimaryIntMatrix.getConstMIterator({1, 0}) << m_PrimaryIntMatrix.getReverseMIterator({1, 0}) << m_PrimaryIntMatrix.getConstReverseMIterator({1, 0}) << 3 << 3 << -14;
    QTest::newRow("6: begin iterator") << m_PrimaryIntMatrix.dBegin(-1) << m_PrimaryIntMatrix.constDBegin(-1) << m_PrimaryIntMatrix.reverseDBegin(-1) << m_PrimaryIntMatrix.constReverseDBegin(-1) << m_PrimaryIntMatrix.mBegin(-1) << m_PrimaryIntMatrix.constMBegin(-1) << m_PrimaryIntMatrix.reverseMBegin(-1) << m_PrimaryIntMatrix.constReverseMBegin(-1) << -2 << -2 << 14;
}

QTEST_APPLESS_MAIN(IteratorExceptionTests)

#include "tst_iteratorexceptiontests.moc"
