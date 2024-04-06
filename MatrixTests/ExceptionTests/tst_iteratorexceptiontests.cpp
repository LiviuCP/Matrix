#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(IntMatrixZIterator)
Q_DECLARE_METATYPE(IntMatrixConstZIterator)
Q_DECLARE_METATYPE(IntMatrixReverseZIterator)
Q_DECLARE_METATYPE(IntMatrixConstReverseZIterator)
Q_DECLARE_METATYPE(IntMatrixNIterator)
Q_DECLARE_METATYPE(IntMatrixConstNIterator)
Q_DECLARE_METATYPE(IntMatrixReverseNIterator)
Q_DECLARE_METATYPE(IntMatrixConstReverseNIterator)
Q_DECLARE_METATYPE(IntMatrixDIterator)
Q_DECLARE_METATYPE(IntMatrixConstDIterator)
Q_DECLARE_METATYPE(IntMatrixReverseDIterator)
Q_DECLARE_METATYPE(IntMatrixConstReverseDIterator)
Q_DECLARE_METATYPE(IntMatrixMIterator)
Q_DECLARE_METATYPE(IntMatrixConstMIterator)
Q_DECLARE_METATYPE(IntMatrixReverseMIterator)
Q_DECLARE_METATYPE(IntMatrixConstReverseMIterator)
Q_DECLARE_METATYPE(StringMatrixZIterator)
Q_DECLARE_METATYPE(StringMatrixConstZIterator)
Q_DECLARE_METATYPE(StringMatrixReverseZIterator)
Q_DECLARE_METATYPE(StringMatrixConstReverseZIterator)
Q_DECLARE_METATYPE(StringMatrixNIterator)
Q_DECLARE_METATYPE(StringMatrixConstNIterator)
Q_DECLARE_METATYPE(StringMatrixReverseNIterator)
Q_DECLARE_METATYPE(StringMatrixConstReverseNIterator)
Q_DECLARE_METATYPE(StringMatrixDIterator)
Q_DECLARE_METATYPE(StringMatrixConstDIterator)
Q_DECLARE_METATYPE(StringMatrixReverseDIterator)
Q_DECLARE_METATYPE(StringMatrixConstReverseDIterator)
Q_DECLARE_METATYPE(StringMatrixMIterator)
Q_DECLARE_METATYPE(StringMatrixConstMIterator)
Q_DECLARE_METATYPE(StringMatrixReverseMIterator)
Q_DECLARE_METATYPE(StringMatrixConstReverseMIterator)
Q_DECLARE_METATYPE(std::string)

static_assert(std::random_access_iterator<IntMatrixZIterator>);
static_assert(std::random_access_iterator<IntMatrixConstZIterator>);
static_assert(std::random_access_iterator<IntMatrixReverseZIterator>);
static_assert(std::random_access_iterator<IntMatrixConstReverseZIterator>);
static_assert(std::random_access_iterator<IntMatrixNIterator>);
static_assert(std::random_access_iterator<IntMatrixConstNIterator>);
static_assert(std::random_access_iterator<IntMatrixReverseNIterator>);
static_assert(std::random_access_iterator<IntMatrixConstReverseNIterator>);
static_assert(std::random_access_iterator<IntMatrixDIterator>);
static_assert(std::random_access_iterator<IntMatrixConstDIterator>);
static_assert(std::random_access_iterator<IntMatrixReverseDIterator>);
static_assert(std::random_access_iterator<IntMatrixConstReverseDIterator>);
static_assert(std::random_access_iterator<IntMatrixMIterator>);
static_assert(std::random_access_iterator<IntMatrixConstMIterator>);
static_assert(std::random_access_iterator<IntMatrixReverseMIterator>);
static_assert(std::random_access_iterator<IntMatrixConstReverseMIterator>);
static_assert(std::random_access_iterator<StringMatrixZIterator>);
static_assert(std::random_access_iterator<StringMatrixConstZIterator>);
static_assert(std::random_access_iterator<StringMatrixReverseZIterator>);
static_assert(std::random_access_iterator<StringMatrixConstReverseZIterator>);
static_assert(std::random_access_iterator<StringMatrixNIterator>);
static_assert(std::random_access_iterator<StringMatrixConstNIterator>);
static_assert(std::random_access_iterator<StringMatrixReverseNIterator>);
static_assert(std::random_access_iterator<StringMatrixConstReverseNIterator>);
static_assert(std::random_access_iterator<StringMatrixDIterator>);
static_assert(std::random_access_iterator<StringMatrixConstDIterator>);
static_assert(std::random_access_iterator<StringMatrixReverseDIterator>);
static_assert(std::random_access_iterator<StringMatrixConstReverseDIterator>);
static_assert(std::random_access_iterator<StringMatrixMIterator>);
static_assert(std::random_access_iterator<StringMatrixConstMIterator>);
static_assert(std::random_access_iterator<StringMatrixReverseMIterator>);
static_assert(std::random_access_iterator<StringMatrixConstReverseMIterator>);

class IteratorExceptionTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testZIteratorTwoOperandsExceptions();
    void testNIteratorTwoOperandsExceptions();
    void testDiagIteratorTwoOperandsExceptions();
    void testNonDiagBeginEndIteratorExceptions();
    void testDiagBeginEndIteratorExceptions();
    void testNonDiagRandomIteratorExceptions();
    void testDiagRandomIteratorExceptions();
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
    void testDiagBeginEndIteratorExceptions_data();
    void testNonDiagRandomIteratorExceptions_data();
    void testDiagRandomIteratorExceptions_data();
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
    QFETCH(IntMatrixZIterator, firstZIterator);
    QFETCH(IntMatrixZIterator, secondZIterator);
    QFETCH(IntMatrixConstZIterator, firstConstZIterator);
    QFETCH(IntMatrixConstZIterator, secondConstZIterator);
    QFETCH(IntMatrixReverseZIterator, firstReverseZIterator);
    QFETCH(IntMatrixReverseZIterator, secondReverseZIterator);
    QFETCH(IntMatrixConstReverseZIterator, firstConstReverseZIterator);
    QFETCH(IntMatrixConstReverseZIterator, secondConstReverseZIterator);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstZIterator == secondZIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstZIterator != secondZIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstZIterator < secondZIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstZIterator <= secondZIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstZIterator > secondZIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstZIterator >= secondZIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDiffType diff{firstZIterator - secondZIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstConstZIterator == secondConstZIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstConstZIterator != secondConstZIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstConstZIterator < secondConstZIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstConstZIterator <= secondConstZIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstConstZIterator > secondConstZIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstConstZIterator >= secondConstZIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDiffType diff{firstConstZIterator - secondConstZIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstReverseZIterator == secondReverseZIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstReverseZIterator != secondReverseZIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstReverseZIterator < secondReverseZIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstReverseZIterator <= secondReverseZIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstReverseZIterator > secondReverseZIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstReverseZIterator >= secondReverseZIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDiffType diff{firstReverseZIterator - secondReverseZIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstConstReverseZIterator == secondConstReverseZIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstConstReverseZIterator != secondConstReverseZIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstConstReverseZIterator < secondConstReverseZIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstConstReverseZIterator <= secondConstReverseZIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstConstReverseZIterator > secondConstReverseZIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstConstReverseZIterator >= secondConstReverseZIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDiffType diff{firstConstReverseZIterator - secondConstReverseZIterator}; Q_UNUSED(diff);});
}

void IteratorExceptionTests::testNIteratorTwoOperandsExceptions()
{
    QFETCH(IntMatrixNIterator, firstNIterator);
    QFETCH(IntMatrixNIterator, secondNIterator);
    QFETCH(IntMatrixConstNIterator, firstConstNIterator);
    QFETCH(IntMatrixConstNIterator, secondConstNIterator);
    QFETCH(IntMatrixReverseNIterator, firstReverseNIterator);
    QFETCH(IntMatrixReverseNIterator, secondReverseNIterator);
    QFETCH(IntMatrixConstReverseNIterator, firstConstReverseNIterator);
    QFETCH(IntMatrixConstReverseNIterator, secondConstReverseNIterator);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstNIterator == secondNIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstNIterator != secondNIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstNIterator < secondNIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstNIterator <= secondNIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstNIterator > secondNIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstNIterator >= secondNIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDiffType diff{firstNIterator - secondNIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstConstNIterator == secondConstNIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstConstNIterator != secondConstNIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstConstNIterator < secondConstNIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstConstNIterator <= secondConstNIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstConstNIterator > secondConstNIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstConstNIterator >= secondConstNIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDiffType diff{firstConstNIterator - secondConstNIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstReverseNIterator == secondReverseNIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstReverseNIterator != secondReverseNIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstReverseNIterator < secondReverseNIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstReverseNIterator <= secondReverseNIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstReverseNIterator > secondReverseNIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstReverseNIterator >= secondReverseNIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDiffType diff{firstReverseNIterator - secondReverseNIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstConstReverseNIterator == secondConstReverseNIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstConstReverseNIterator != secondConstReverseNIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstConstReverseNIterator < secondConstReverseNIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstConstReverseNIterator <= secondConstReverseNIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstConstReverseNIterator > secondConstReverseNIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstConstReverseNIterator >= secondConstReverseNIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDiffType diff{firstConstReverseNIterator - secondConstReverseNIterator}; Q_UNUSED(diff);});
}

void IteratorExceptionTests::testDiagIteratorTwoOperandsExceptions()
{
    QFETCH(IntMatrixDIterator, firstDIterator);
    QFETCH(IntMatrixDIterator, secondDIterator);
    QFETCH(IntMatrixConstDIterator, firstConstDIterator);
    QFETCH(IntMatrixConstDIterator, secondConstDIterator);
    QFETCH(IntMatrixReverseDIterator, firstReverseDIterator);
    QFETCH(IntMatrixReverseDIterator, secondReverseDIterator);
    QFETCH(IntMatrixConstReverseDIterator, firstConstReverseDIterator);
    QFETCH(IntMatrixConstReverseDIterator, secondConstReverseDIterator);
    QFETCH(IntMatrixMIterator, firstMIterator);
    QFETCH(IntMatrixMIterator, secondMIterator);
    QFETCH(IntMatrixConstMIterator, firstConstMIterator);
    QFETCH(IntMatrixConstMIterator, secondConstMIterator);
    QFETCH(IntMatrixReverseMIterator, firstReverseMIterator);
    QFETCH(IntMatrixReverseMIterator, secondReverseMIterator);
    QFETCH(IntMatrixConstReverseMIterator, firstConstReverseMIterator);
    QFETCH(IntMatrixConstReverseMIterator, secondConstReverseMIterator);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstDIterator == secondDIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstDIterator != secondDIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstDIterator < secondDIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstDIterator <= secondDIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstDIterator > secondDIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstDIterator >= secondDIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDiffType diff{firstDIterator - secondDIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstConstDIterator == secondConstDIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstConstDIterator != secondConstDIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstConstDIterator < secondConstDIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstConstDIterator <= secondConstDIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstConstDIterator > secondConstDIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstConstDIterator >= secondConstDIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDiffType diff{firstConstDIterator - secondConstDIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstReverseDIterator == secondReverseDIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstReverseDIterator != secondReverseDIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstReverseDIterator < secondReverseDIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstReverseDIterator <= secondReverseDIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstReverseDIterator > secondReverseDIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstReverseDIterator >= secondReverseDIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDiffType diff{firstReverseDIterator - secondReverseDIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstConstReverseDIterator == secondConstReverseDIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstConstReverseDIterator != secondConstReverseDIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstConstReverseDIterator < secondConstReverseDIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstConstReverseDIterator <= secondConstReverseDIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstConstReverseDIterator > secondConstReverseDIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstConstReverseDIterator >= secondConstReverseDIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDiffType diff{firstConstReverseDIterator - secondConstReverseDIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstMIterator == secondMIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstMIterator != secondMIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstMIterator < secondMIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstMIterator <= secondMIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstMIterator > secondMIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstMIterator >= secondMIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDiffType diff{firstMIterator - secondMIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstConstMIterator == secondConstMIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstConstMIterator != secondConstMIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstConstMIterator < secondConstMIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstConstMIterator <= secondConstMIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstConstMIterator > secondConstMIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstConstMIterator >= secondConstMIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDiffType diff{firstConstMIterator - secondConstMIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstReverseMIterator == secondReverseMIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstReverseMIterator != secondReverseMIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstReverseMIterator < secondReverseMIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstReverseMIterator <= secondReverseMIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstReverseMIterator > secondReverseMIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstReverseMIterator >= secondReverseMIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDiffType diff{firstReverseMIterator - secondReverseMIterator}; Q_UNUSED(diff);});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areEqual{firstConstReverseMIterator == secondConstReverseMIterator}; Q_UNUSED(areEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool areNotEqual{firstConstReverseMIterator != secondConstReverseMIterator}; Q_UNUSED(areNotEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThan{firstConstReverseMIterator < secondConstReverseMIterator}; Q_UNUSED(isSmallerThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isSmallerThanOrEqual{firstConstReverseMIterator <= secondConstReverseMIterator}; Q_UNUSED(isSmallerThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThan{firstConstReverseMIterator > secondConstReverseMIterator}; Q_UNUSED(isGreaterThan);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {bool isGreaterThanOrEqual{firstConstReverseMIterator >= secondConstReverseMIterator}; Q_UNUSED(isGreaterThanOrEqual);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDiffType diff{firstConstReverseMIterator - secondConstReverseMIterator}; Q_UNUSED(diff);});
}

void IteratorExceptionTests::testNonDiagBeginEndIteratorExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, rowColumnNr);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixZIterator it{matrix.zRowBegin(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixZIterator it{matrix.zRowEnd(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstZIterator it{matrix.constZRowBegin(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstZIterator it{matrix.constZRowEnd(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseZIterator it{matrix.reverseZRowBegin(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseZIterator it{matrix.reverseZRowEnd(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseZIterator it{matrix.constReverseZRowBegin(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseZIterator it{matrix.constReverseZRowEnd(rowColumnNr)}; Q_UNUSED(it)});

    matrix.transpose(matrix);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixNIterator it{matrix.nColumnBegin(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixNIterator it{matrix.nColumnEnd(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstNIterator it{matrix.constNColumnBegin(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstNIterator it{matrix.constNColumnEnd(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseNIterator it{matrix.reverseNColumnBegin(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseNIterator it{matrix.reverseNColumnEnd(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseNIterator it{matrix.constReverseNColumnBegin(rowColumnNr)}; Q_UNUSED(it)});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseNIterator it{matrix.constReverseNColumnEnd(rowColumnNr)}; Q_UNUSED(it)});
}

void IteratorExceptionTests::testDiagBeginEndIteratorExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, diagonalNr);
    QFETCH(IntMatrixSizeType, rowNr);
    QFETCH(IntMatrixSizeType, columnNr);
    QFETCH(bool, isDiagonalNr);

    if (isDiagonalNr)
    {
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDIterator it{matrix.dBegin(diagonalNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDIterator it{matrix.dEnd(diagonalNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstDIterator it{matrix.constDBegin(diagonalNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstDIterator it{matrix.constDEnd(diagonalNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseDIterator it{matrix.reverseDBegin(diagonalNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseDIterator it{matrix.reverseDEnd(diagonalNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(diagonalNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseDIterator it{matrix.constReverseDEnd(diagonalNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixMIterator it{matrix.mBegin(diagonalNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixMIterator it{matrix.mEnd(diagonalNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstMIterator it{matrix.constMBegin(diagonalNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstMIterator it{matrix.constMEnd(diagonalNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseMIterator it{matrix.reverseMBegin(diagonalNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseMIterator it{matrix.reverseMEnd(diagonalNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(diagonalNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseMIterator it{matrix.constReverseMEnd(diagonalNr)}; Q_UNUSED(it);});
    }
    else
    {
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDIterator it{matrix.dBegin(rowNr, columnNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDIterator it{matrix.dEnd(rowNr, columnNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstDIterator it{matrix.constDBegin(rowNr, columnNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstDIterator it{matrix.constDEnd(rowNr, columnNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseDIterator it{matrix.reverseDBegin(rowNr, columnNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseDIterator it{matrix.reverseDEnd(rowNr, columnNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(rowNr, columnNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseDIterator it{matrix.constReverseDEnd(rowNr, columnNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixMIterator it{matrix.mBegin(rowNr, columnNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixMIterator it{matrix.mEnd(rowNr, columnNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstMIterator it{matrix.constMBegin(rowNr, columnNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstMIterator it{matrix.constMEnd(rowNr, columnNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseMIterator it{matrix.reverseMBegin(rowNr, columnNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseMIterator it{matrix.reverseMEnd(rowNr, columnNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(rowNr, columnNr)}; Q_UNUSED(it);});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseMIterator it{matrix.constReverseMEnd(rowNr, columnNr)}; Q_UNUSED(it);});
    }
}

void IteratorExceptionTests::testNonDiagRandomIteratorExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, rowNr);
    QFETCH(IntMatrixSizeType, columnNr);
    QFETCH(IntMatrixSizeType, index);
    QFETCH(bool, isIndex);

    if (isIndex)
    {
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixZIterator it{matrix.getZIterator(index)}; Q_UNUSED(it)});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstZIterator it{matrix.getConstZIterator(index)}; Q_UNUSED(it)});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseZIterator it{matrix.getReverseZIterator(index)}; Q_UNUSED(it)});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(index)}; Q_UNUSED(it)});

        matrix.transpose(matrix);

        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixNIterator it{matrix.getNIterator(index)}; Q_UNUSED(it)});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstNIterator it{matrix.getConstNIterator(index)}; Q_UNUSED(it)});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseNIterator it{matrix.getReverseNIterator(index)}; Q_UNUSED(it)});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseNIterator it{matrix.getConstReverseNIterator(index)}; Q_UNUSED(it)});
    }
    else
    {
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixZIterator it{matrix.getZIterator(rowNr, columnNr)}; Q_UNUSED(it)});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstZIterator it{matrix.getConstZIterator(rowNr, columnNr)}; Q_UNUSED(it)});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseZIterator it{matrix.getReverseZIterator(rowNr, columnNr)}; Q_UNUSED(it)});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(rowNr, columnNr)}; Q_UNUSED(it)});

        matrix.transpose(matrix);

        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixNIterator it{matrix.getNIterator(columnNr, rowNr)}; Q_UNUSED(it)});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstNIterator it{matrix.getConstNIterator(columnNr, rowNr)}; Q_UNUSED(it)});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseNIterator it{matrix.getReverseNIterator(columnNr, rowNr)}; Q_UNUSED(it)});
        QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseNIterator it{matrix.getConstReverseNIterator(columnNr, rowNr)}; Q_UNUSED(it)});
    }
}

void IteratorExceptionTests::testDiagRandomIteratorExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, firstCoordinate);
    QFETCH(IntMatrixSizeType, secondCoordinate);
    QFETCH(bool, areRelativeCoordinates);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixDIterator it{matrix.getDIterator(firstCoordinate, secondCoordinate, areRelativeCoordinates)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstDIterator it{matrix.getConstDIterator(firstCoordinate, secondCoordinate, areRelativeCoordinates)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseDIterator it{matrix.getReverseDIterator(firstCoordinate, secondCoordinate, areRelativeCoordinates)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(firstCoordinate, secondCoordinate, areRelativeCoordinates)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixMIterator it{matrix.getMIterator(firstCoordinate, secondCoordinate, areRelativeCoordinates)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstMIterator it{matrix.getConstMIterator(firstCoordinate, secondCoordinate, areRelativeCoordinates)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixReverseMIterator it{matrix.getReverseMIterator(firstCoordinate, secondCoordinate, areRelativeCoordinates)}; Q_UNUSED(it);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(firstCoordinate, secondCoordinate, areRelativeCoordinates)}; Q_UNUSED(it);});
}

void IteratorExceptionTests::testZIteratorAsteriskOperatorExceptions()
{
    QFETCH(IntMatrixZIterator, zIterator);
    QFETCH(IntMatrixConstZIterator, constZIterator);
    QFETCH(IntMatrixReverseZIterator, reverseZIterator);
    QFETCH(IntMatrixConstReverseZIterator, constReverseZIterator);
    QFETCH(int, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {*zIterator = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(*constZIterator);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {*reverseZIterator = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(*constReverseZIterator);});
}

void IteratorExceptionTests::testNIteratorAsteriskOperatorExceptions()
{
    QFETCH(IntMatrixNIterator, nIterator);
    QFETCH(IntMatrixConstNIterator, constNIterator);
    QFETCH(IntMatrixReverseNIterator, reverseNIterator);
    QFETCH(IntMatrixConstReverseNIterator, constReverseNIterator);
    QFETCH(int, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {*nIterator = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(*constNIterator);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {*reverseNIterator = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(*constReverseNIterator);});
}

void IteratorExceptionTests::testDiagIteratorAsteriskOperatorExceptions()
{
    QFETCH(IntMatrixDIterator, dIterator);
    QFETCH(IntMatrixConstDIterator, constDIterator);
    QFETCH(IntMatrixReverseDIterator, reverseDIterator);
    QFETCH(IntMatrixConstReverseDIterator, constReverseDIterator);
    QFETCH(IntMatrixMIterator, mIterator);
    QFETCH(IntMatrixConstMIterator, constMIterator);
    QFETCH(IntMatrixReverseMIterator, reverseMIterator);
    QFETCH(IntMatrixConstReverseMIterator, constReverseMIterator);
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
    QFETCH(StringMatrixZIterator, zIterator);
    QFETCH(StringMatrixConstZIterator, constZIterator);
    QFETCH(StringMatrixReverseZIterator, reverseZIterator);
    QFETCH(StringMatrixConstReverseZIterator, constReverseZIterator);
    QFETCH(std::string, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {zIterator->assign(value);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constZIterator->size());});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {reverseZIterator->assign(value);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constReverseZIterator->size());});
}

void IteratorExceptionTests::testNIteratorArrowOperatorExceptions()
{
    QFETCH(StringMatrixNIterator, nIterator);
    QFETCH(StringMatrixConstNIterator, constNIterator);
    QFETCH(StringMatrixReverseNIterator, reverseNIterator);
    QFETCH(StringMatrixConstReverseNIterator, constReverseNIterator);
    QFETCH(std::string, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {nIterator->assign(value);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constNIterator->size());});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {reverseNIterator->assign(value);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constReverseNIterator->size());});
}

void IteratorExceptionTests::testDiagIteratorArrowOperatorExceptions()
{
    QFETCH(StringMatrixDIterator, dIterator);
    QFETCH(StringMatrixConstDIterator, constDIterator);
    QFETCH(StringMatrixReverseDIterator, reverseDIterator);
    QFETCH(StringMatrixConstReverseDIterator, constReverseDIterator);
    QFETCH(StringMatrixMIterator, mIterator);
    QFETCH(StringMatrixConstMIterator, constMIterator);
    QFETCH(StringMatrixReverseMIterator, reverseMIterator);
    QFETCH(StringMatrixConstReverseMIterator, constReverseMIterator);
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
    QFETCH(IntMatrixZIterator, zIterator);
    QFETCH(IntMatrixConstZIterator, constZIterator);
    QFETCH(IntMatrixReverseZIterator, reverseZIterator);
    QFETCH(IntMatrixConstReverseZIterator, constReverseZIterator);
    QFETCH(IntMatrixSizeType, forwardIndex);
    QFETCH(IntMatrixSizeType, reverseIndex);
    QFETCH(int, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {zIterator[forwardIndex] = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constZIterator[forwardIndex]);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {reverseZIterator[reverseIndex] = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constReverseZIterator[reverseIndex]);});
}

void IteratorExceptionTests::testNIteratorSquareBracketsOperatorExceptions()
{
    QFETCH(IntMatrixNIterator, nIterator);
    QFETCH(IntMatrixConstNIterator, constNIterator);
    QFETCH(IntMatrixReverseNIterator, reverseNIterator);
    QFETCH(IntMatrixConstReverseNIterator, constReverseNIterator);
    QFETCH(IntMatrixSizeType, forwardIndex);
    QFETCH(IntMatrixSizeType, reverseIndex);
    QFETCH(int, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {nIterator[forwardIndex] = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constNIterator[forwardIndex]);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {reverseNIterator[reverseIndex] = value;});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {Q_UNUSED(constReverseNIterator[reverseIndex]);});
}

void IteratorExceptionTests::testDiagIteratorSquareBracketsOperatorExceptions()
{
    QFETCH(IntMatrixDIterator, dIterator);
    QFETCH(IntMatrixConstDIterator, constDIterator);
    QFETCH(IntMatrixReverseDIterator, reverseDIterator);
    QFETCH(IntMatrixConstReverseDIterator, constReverseDIterator);
    QFETCH(IntMatrixMIterator, mIterator);
    QFETCH(IntMatrixConstMIterator, constMIterator);
    QFETCH(IntMatrixReverseMIterator, reverseMIterator);
    QFETCH(IntMatrixConstReverseMIterator, constReverseMIterator);
    QFETCH(IntMatrixSizeType, forwardIndex);
    QFETCH(IntMatrixSizeType, reverseIndex);
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
    QTest::addColumn<IntMatrixZIterator>("firstZIterator");
    QTest::addColumn<IntMatrixZIterator>("secondZIterator");
    QTest::addColumn<IntMatrixConstZIterator>("firstConstZIterator");
    QTest::addColumn<IntMatrixConstZIterator>("secondConstZIterator");
    QTest::addColumn<IntMatrixReverseZIterator>("firstReverseZIterator");
    QTest::addColumn<IntMatrixReverseZIterator>("secondReverseZIterator");
    QTest::addColumn<IntMatrixConstReverseZIterator>("firstConstReverseZIterator");
    QTest::addColumn<IntMatrixConstReverseZIterator>("secondConstReverseZIterator");

    m_PrimaryIntMatrix = {2, 3, 4};
    m_SecondaryIntMatrix = {2, 3, -5};
    m_ThirdIntMatrix = {2, 3, 4};
    m_FourthIntMatrix = m_PrimaryIntMatrix;
    m_FifthIntMatrix = std::move(m_ThirdIntMatrix);

    QTest::newRow("end iterator, random iterator") << m_PrimaryIntMatrix.zEnd() << m_SecondaryIntMatrix.getZIterator(1, 0) << m_PrimaryIntMatrix.constZEnd() << m_SecondaryIntMatrix.getConstZIterator(1, 0) << m_PrimaryIntMatrix.reverseZEnd() << m_SecondaryIntMatrix.getReverseZIterator(1, 0) << m_PrimaryIntMatrix.constReverseZEnd() << m_SecondaryIntMatrix.getConstReverseZIterator(1, 0);
    QTest::newRow("end iterator, begin iterator") << m_PrimaryIntMatrix.zEnd() << m_FourthIntMatrix.zBegin() << m_PrimaryIntMatrix.constZEnd() << m_FourthIntMatrix.constZBegin() << m_PrimaryIntMatrix.reverseZEnd() << m_FourthIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.constReverseZEnd() << m_FourthIntMatrix.constReverseZBegin();
    QTest::newRow("begin iterator, end iterator") << m_ThirdIntMatrix.zBegin() << m_FifthIntMatrix.zEnd() << m_ThirdIntMatrix.constZBegin() << m_FifthIntMatrix.constZEnd() << m_ThirdIntMatrix.reverseZBegin() << m_FifthIntMatrix.reverseZEnd() << m_ThirdIntMatrix.constReverseZBegin() << m_FifthIntMatrix.constReverseZEnd();
}

void IteratorExceptionTests::testNIteratorTwoOperandsExceptions_data()
{
    QTest::addColumn<IntMatrixNIterator>("firstNIterator");
    QTest::addColumn<IntMatrixNIterator>("secondNIterator");
    QTest::addColumn<IntMatrixConstNIterator>("firstConstNIterator");
    QTest::addColumn<IntMatrixConstNIterator>("secondConstNIterator");
    QTest::addColumn<IntMatrixReverseNIterator>("firstReverseNIterator");
    QTest::addColumn<IntMatrixReverseNIterator>("secondReverseNIterator");
    QTest::addColumn<IntMatrixConstReverseNIterator>("firstConstReverseNIterator");
    QTest::addColumn<IntMatrixConstReverseNIterator>("secondConstReverseNIterator");

    m_PrimaryIntMatrix = {3, 2, 4};
    m_SecondaryIntMatrix = {3, 2, -5};
    m_ThirdIntMatrix = {3, 2, 4};
    m_FourthIntMatrix = m_PrimaryIntMatrix;
    m_FifthIntMatrix = std::move(m_ThirdIntMatrix);

    QTest::newRow("end iterator, random iterator") << m_PrimaryIntMatrix.nEnd() << m_SecondaryIntMatrix.getNIterator(0, 1) << m_PrimaryIntMatrix.constNEnd() << m_SecondaryIntMatrix.getConstNIterator(0, 1) << m_PrimaryIntMatrix.reverseNEnd() << m_SecondaryIntMatrix.getReverseNIterator(0, 1) << m_PrimaryIntMatrix.constReverseNEnd() << m_SecondaryIntMatrix.getConstReverseNIterator(0, 1);
    QTest::newRow("end iterator, begin iterator") << m_PrimaryIntMatrix.nEnd() << m_FourthIntMatrix.nBegin() << m_PrimaryIntMatrix.constNEnd() << m_FourthIntMatrix.constNBegin() << m_PrimaryIntMatrix.reverseNEnd() << m_FourthIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.constReverseNEnd() << m_FourthIntMatrix.constReverseNBegin();
    QTest::newRow("begin iterator, end iterator") << m_ThirdIntMatrix.nBegin() << m_FifthIntMatrix.nEnd() << m_ThirdIntMatrix.constNBegin() << m_FifthIntMatrix.constNEnd() << m_ThirdIntMatrix.reverseNBegin() << m_FifthIntMatrix.reverseNEnd() << m_ThirdIntMatrix.constReverseNBegin() << m_FifthIntMatrix.constReverseNEnd();
}

void IteratorExceptionTests::testDiagIteratorTwoOperandsExceptions_data()
{
    QTest::addColumn<IntMatrixDIterator>("firstDIterator");
    QTest::addColumn<IntMatrixDIterator>("secondDIterator");
    QTest::addColumn<IntMatrixConstDIterator>("firstConstDIterator");
    QTest::addColumn<IntMatrixConstDIterator>("secondConstDIterator");
    QTest::addColumn<IntMatrixReverseDIterator>("firstReverseDIterator");
    QTest::addColumn<IntMatrixReverseDIterator>("secondReverseDIterator");
    QTest::addColumn<IntMatrixConstReverseDIterator>("firstConstReverseDIterator");
    QTest::addColumn<IntMatrixConstReverseDIterator>("secondConstReverseDIterator");
    QTest::addColumn<IntMatrixMIterator>("firstMIterator");
    QTest::addColumn<IntMatrixMIterator>("secondMIterator");
    QTest::addColumn<IntMatrixConstMIterator>("firstConstMIterator");
    QTest::addColumn<IntMatrixConstMIterator>("secondConstMIterator");
    QTest::addColumn<IntMatrixReverseMIterator>("firstReverseMIterator");
    QTest::addColumn<IntMatrixReverseMIterator>("secondReverseMIterator");
    QTest::addColumn<IntMatrixConstReverseMIterator>("firstConstReverseMIterator");
    QTest::addColumn<IntMatrixConstReverseMIterator>("secondConstReverseMIterator");

    m_PrimaryIntMatrix = {3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix = {3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::newRow("random iterator, random iterator") << m_PrimaryIntMatrix.getDIterator(2, 1) << m_PrimaryIntMatrix.getDIterator(1, 1, true) << m_PrimaryIntMatrix.getConstDIterator(2, 1) << m_PrimaryIntMatrix.getConstDIterator(1, 1, true) << m_PrimaryIntMatrix.getReverseDIterator(2, 1) << m_PrimaryIntMatrix.getReverseDIterator(1, 1, true) <<  m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) << m_PrimaryIntMatrix.getConstReverseDIterator(1, 1, true) << m_PrimaryIntMatrix.getMIterator(2, 2) << m_PrimaryIntMatrix.getMIterator(1, 1, true) << m_PrimaryIntMatrix.getConstMIterator(2, 2) << m_PrimaryIntMatrix.getConstMIterator(1, 1, true) << m_PrimaryIntMatrix.getReverseMIterator(2, 2) << m_PrimaryIntMatrix.getReverseMIterator(1, 1, true) <<  m_PrimaryIntMatrix.getConstReverseMIterator(2, 2) << m_PrimaryIntMatrix.getConstReverseMIterator(1, 1, true);
    QTest::newRow("end iterator, end iterator") << m_PrimaryIntMatrix.dEnd(1, 2) << m_PrimaryIntMatrix.dEnd(-1) << m_PrimaryIntMatrix.constDEnd(1, 2) << m_PrimaryIntMatrix.constDEnd(-1) << m_PrimaryIntMatrix.reverseDEnd(1, 2) << m_PrimaryIntMatrix.reverseDEnd(-1) <<  m_PrimaryIntMatrix.constReverseDEnd(1, 2) << m_PrimaryIntMatrix.constReverseDEnd(-1) << m_PrimaryIntMatrix.mEnd(1, 1) << m_PrimaryIntMatrix.mEnd(-1) << m_PrimaryIntMatrix.constMEnd(1, 1) << m_PrimaryIntMatrix.constMEnd(-1) << m_PrimaryIntMatrix.reverseMEnd(1, 1) <<  m_PrimaryIntMatrix.reverseMEnd(-1) << m_PrimaryIntMatrix.constReverseMEnd(1, 1) << m_PrimaryIntMatrix.constReverseMEnd(-1);
    QTest::newRow("random iterator, random iterator") << m_PrimaryIntMatrix.getDIterator(1, 2) << m_SecondaryIntMatrix.getDIterator(1, 1, true) << m_PrimaryIntMatrix.getConstDIterator(1, 2) << m_SecondaryIntMatrix.getConstDIterator(1, 1, true) << m_PrimaryIntMatrix.getReverseDIterator(1, 2) << m_SecondaryIntMatrix.getReverseDIterator(1, 1, true) <<  m_PrimaryIntMatrix.getConstReverseDIterator(1, 2) << m_SecondaryIntMatrix.getConstReverseDIterator(1, 1, true) << m_PrimaryIntMatrix.getMIterator(1, 1) << m_SecondaryIntMatrix.getMIterator(1, 1, true) << m_PrimaryIntMatrix.getConstMIterator(1, 1) << m_SecondaryIntMatrix.getConstMIterator(1, 1, true) << m_PrimaryIntMatrix.getReverseMIterator(1, 1) << m_SecondaryIntMatrix.getReverseMIterator(1, 1, true) <<  m_PrimaryIntMatrix.getConstReverseMIterator(1, 1) << m_SecondaryIntMatrix.getConstReverseMIterator(1, 1, true);

    // test same diagonal iterator after matrix update
    m_ThirdIntMatrix = {3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    IntMatrixDIterator dIterator{m_ThirdIntMatrix.getDIterator(1, 1, true)};
    IntMatrixConstDIterator constDIterator{m_ThirdIntMatrix.getConstDIterator(1, 1, true)};
    IntMatrixReverseDIterator reverseDIterator{m_ThirdIntMatrix.getReverseDIterator(1, 1, true)};
    IntMatrixConstReverseDIterator constReverseDIterator{m_ThirdIntMatrix.getConstReverseDIterator(1, 1, true)};
    IntMatrixMIterator mIterator{m_ThirdIntMatrix.getMIterator(1, 1, true)};
    IntMatrixConstMIterator constMIterator{m_ThirdIntMatrix.getConstMIterator(1, 1, true)};
    IntMatrixReverseMIterator reverseMIterator{m_ThirdIntMatrix.getReverseMIterator(1, 1, true)};
    IntMatrixConstReverseMIterator constReverseMIterator{m_ThirdIntMatrix.getConstReverseMIterator(1, 1, true)};

    m_ThirdIntMatrix.insertRow(1);

    QTest::newRow("random iterator, random iterator") << IntMatrixDIterator{dIterator} << m_ThirdIntMatrix.getDIterator(1, 2) << IntMatrixConstDIterator{constDIterator} << m_ThirdIntMatrix.getConstDIterator(1, 2) << IntMatrixReverseDIterator{reverseDIterator} << m_ThirdIntMatrix.getReverseDIterator(1, 2) << IntMatrixConstReverseDIterator{constReverseDIterator} << m_ThirdIntMatrix.getConstReverseDIterator(1, 2) << IntMatrixMIterator{mIterator} << m_ThirdIntMatrix.getMIterator(1, 1) << IntMatrixConstMIterator{constMIterator} << m_ThirdIntMatrix.getConstMIterator(1, 1) << IntMatrixReverseMIterator{reverseMIterator} << m_ThirdIntMatrix.getReverseMIterator(1, 1) << IntMatrixConstReverseMIterator{constReverseMIterator} << m_ThirdIntMatrix.getConstReverseMIterator(1, 1);

    m_FourthIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    dIterator = m_FourthIntMatrix.getDIterator(-1, 1, true);
    constDIterator = m_FourthIntMatrix.getConstDIterator(-1, 1, true);
    reverseDIterator = m_FourthIntMatrix.getReverseDIterator(-1, 1, true);
    constReverseDIterator = m_FourthIntMatrix.getConstReverseDIterator(-1, 1, true);
    mIterator = m_FourthIntMatrix.getMIterator(-1, 1, true);
    constMIterator = m_FourthIntMatrix.getConstMIterator(-1, 1, true);
    reverseMIterator = m_FourthIntMatrix.getReverseMIterator(-1, 1, true);
    constReverseMIterator = m_FourthIntMatrix.getConstReverseMIterator(-1, 1, true);

    m_FourthIntMatrix.insertColumn(1);

    QTest::newRow("random iterator, random iterator") << IntMatrixDIterator{dIterator} << m_FourthIntMatrix.getDIterator(2, 1) << IntMatrixConstDIterator{constDIterator} << m_FourthIntMatrix.getConstDIterator(2, 1) << IntMatrixReverseDIterator{reverseDIterator} << m_FourthIntMatrix.getReverseDIterator(2, 1) << IntMatrixConstReverseDIterator{constReverseDIterator} << m_FourthIntMatrix.getConstReverseDIterator(2, 1) << IntMatrixMIterator{mIterator} << m_FourthIntMatrix.getMIterator(2, 1) << IntMatrixConstMIterator{constMIterator} << m_FourthIntMatrix.getConstMIterator(2, 1) << IntMatrixReverseMIterator{reverseMIterator} << m_FourthIntMatrix.getReverseMIterator(2, 1) << IntMatrixConstReverseMIterator{constReverseMIterator} << m_FourthIntMatrix.getConstReverseMIterator(2, 1);

    m_FifthIntMatrix = {4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16}};

    dIterator = m_FifthIntMatrix.getDIterator(-1, 0, true);
    constDIterator = m_FifthIntMatrix.getConstDIterator(-1, 0, true);
    reverseDIterator = m_FifthIntMatrix.getReverseDIterator(-1, 0, true);
    constReverseDIterator = m_FifthIntMatrix.getConstReverseDIterator(-1, 0, true);
    mIterator = m_FifthIntMatrix.getMIterator(-1, 0, true);
    constMIterator = m_FifthIntMatrix.getConstMIterator(-1, 0, true);
    reverseMIterator = m_FifthIntMatrix.getReverseMIterator(-1, 0, true);
    constReverseMIterator = m_FifthIntMatrix.getConstReverseMIterator(-1, 0, true);

    m_FifthIntMatrix.insertRow(1);

    QTest::newRow("random iterator, random iterator") << IntMatrixDIterator{dIterator} << m_FifthIntMatrix.getDIterator(-1, 0, true) << IntMatrixConstDIterator{constDIterator} << m_FifthIntMatrix.getConstDIterator(-1, 0, true) << IntMatrixReverseDIterator{reverseDIterator} << m_FifthIntMatrix.getReverseDIterator(-1, 0, true) << IntMatrixConstReverseDIterator{constReverseDIterator} << m_FifthIntMatrix.getConstReverseDIterator(-1, 0, true) << IntMatrixMIterator{mIterator} << m_FifthIntMatrix.getMIterator(-1, 0, true) << IntMatrixConstMIterator{constMIterator} << m_FifthIntMatrix.getConstMIterator(-1, 0, true) << IntMatrixReverseMIterator{reverseMIterator} << m_FifthIntMatrix.getReverseMIterator(-1, 0, true) << IntMatrixConstReverseMIterator{constReverseMIterator} << m_FifthIntMatrix.getConstReverseMIterator(-1, 0, true);

    m_SixthIntMatrix = {4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16}};

    dIterator = m_SixthIntMatrix.getDIterator(1, 0, true);
    constDIterator = m_SixthIntMatrix.getConstDIterator(1, 0, true);
    reverseDIterator = m_SixthIntMatrix.getReverseDIterator(1, 0, true);
    constReverseDIterator = m_SixthIntMatrix.getConstReverseDIterator(1, 0, true);
    mIterator = m_SixthIntMatrix.getMIterator(1, 0, true);
    constMIterator = m_SixthIntMatrix.getConstMIterator(1, 0, true);
    reverseMIterator = m_SixthIntMatrix.getReverseMIterator(1, 0, true);
    constReverseMIterator = m_SixthIntMatrix.getConstReverseMIterator(1, 0, true);

    m_SixthIntMatrix.insertColumn(1);

    QTest::newRow("random iterator, random iterator") << IntMatrixDIterator{dIterator} << m_SixthIntMatrix.getDIterator(1, 0, true) << IntMatrixConstDIterator{constDIterator} << m_SixthIntMatrix.getConstDIterator(1, 0, true) << IntMatrixReverseDIterator{reverseDIterator} << m_SixthIntMatrix.getReverseDIterator(1, 0, true) << IntMatrixConstReverseDIterator{constReverseDIterator} << m_SixthIntMatrix.getConstReverseDIterator(1, 0, true) << IntMatrixMIterator{mIterator} << m_SixthIntMatrix.getMIterator(1, 0, true) << IntMatrixConstMIterator{constMIterator} << m_SixthIntMatrix.getConstMIterator(1, 0, true) << IntMatrixReverseMIterator{reverseMIterator} << m_SixthIntMatrix.getReverseMIterator(1, 0, true) << IntMatrixConstReverseMIterator{constReverseMIterator} << m_SixthIntMatrix.getConstReverseMIterator(1, 0, true);
}

void IteratorExceptionTests::testNonDiagBeginEndIteratorExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("rowColumnNr");

    QTest::newRow("negative index") << IntMatrix{} << -1;
    QTest::newRow("index out of range") << IntMatrix{} << 0;
    QTest::newRow("negative index") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << -1;
    QTest::newRow("index out of range") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4;
}

void IteratorExceptionTests::testDiagBeginEndIteratorExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("diagonalNr");
    QTest::addColumn<IntMatrixSizeType>("rowNr");
    QTest::addColumn<IntMatrixSizeType>("columnNr");
    QTest::addColumn<bool>("isDiagonalNr");

    QTest::newRow("diagonal number") << IntMatrix{} << 0 << 0 << 0 << true;
    QTest::newRow("diagonal number") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << -2 << 0 << 0 << true;
    QTest::newRow("diagonal number") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 3 << 0 << 0 << true;
    QTest::newRow("row/column number") << IntMatrix{} << 0 << 0 << 0 << false;
    QTest::newRow("row/column number") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 0 << 0 << 3 << false;
    QTest::newRow("row/column number") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 0 << 2 << 0 << false;
    QTest::newRow("row/column number") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 0 << 2 << 3 << false;
    QTest::newRow("row/column number") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 0 << -1 << 0 << false;
    QTest::newRow("row/column number") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 0 << 0 << -1 << false;
    QTest::newRow("row/column number") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 0 << -1 << -1 << false;
    QTest::newRow("row/column number") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 0 << -1 << 3 << false;
    QTest::newRow("row/column number") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 0 << 2 << -1 << false;
}

void IteratorExceptionTests::testNonDiagRandomIteratorExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("rowNr");
    QTest::addColumn<IntMatrixSizeType>("columnNr");
    QTest::addColumn<IntMatrixSizeType>("index");
    QTest::addColumn<bool>("isIndex");

    QTest::newRow("row/column number random iterator") << IntMatrix{} << -1 << -1 << 0 << false;
    QTest::newRow("row/column number random iterator") << IntMatrix{} << -1 << 0 << 0 << false;
    QTest::newRow("row/column number random iterator") << IntMatrix{} << 0 << -1 << 0 << false;
    QTest::newRow("row/column number random iterator") << IntMatrix{} << 0 << 0 << 0 << false;
    QTest::newRow("row/column number random iterator") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1 << -1 << 0 << false;
    QTest::newRow("row/column number random iterator") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1 << 1 << 0 << false;
    QTest::newRow("row/column number random iterator") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1 << 3 << 0 << false;
    QTest::newRow("row/column number random iterator") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 1 << -1 << 0 << false;
    QTest::newRow("row/column number random iterator") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 1 << 3 << 0 << false;
    QTest::newRow("row/column number random iterator") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2 << -1 << 0 << false;
    QTest::newRow("row/column number random iterator") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2 << 1 << 0 << false;
    QTest::newRow("row/column number random iterator") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2 << 3 << 0 << false;
    QTest::newRow("index random iterator") << IntMatrix{} << 0 << 0 << -1 << true;
    QTest::newRow("index random iterator") << IntMatrix{} << 0 << 0 << 0 << true;
    QTest::newRow("index random iterator") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 0 << 0 << -1 << true;
    QTest::newRow("index random iterator") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 0 << 0 << 6 << true;
}

void IteratorExceptionTests::testDiagRandomIteratorExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("firstCoordinate");
    QTest::addColumn<IntMatrixSizeType>("secondCoordinate");
    QTest::addColumn<bool>("areRelativeCoordinates");

    QTest::newRow("absolute coordinates") << IntMatrix{} << 0 << 0 << false;
    QTest::newRow("absolute coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 0 << 3 << false;
    QTest::newRow("absolute coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 2 << 0 << false;
    QTest::newRow("absolute coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 2 << 3 << false;
    QTest::newRow("absolute coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << -1 << 0 << false;
    QTest::newRow("absolute coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 0 << -1 << false;
    QTest::newRow("absolute coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << -1 << -1 << false;
    QTest::newRow("absolute coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << -1 << 3 << false;
    QTest::newRow("absolute coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 2 << -1 << false;
    QTest::newRow("relative coordinates") << IntMatrix{} << 0 << 0 << true;
    QTest::newRow("relative coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << -2 << 0 << true;
    QTest::newRow("relative coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << -2 << -1 << true;
    QTest::newRow("relative coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 3 << 0 << true;
    QTest::newRow("relative coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 3 << -1 << true;
    QTest::newRow("relative coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 0 << 2 << true;
    QTest::newRow("relative coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 0 << -1 << true;
    QTest::newRow("relative coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 1 << 2 << true;
    QTest::newRow("relative coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << 1 << -1 << true;
    QTest::newRow("relative coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << -1 << 1 << true;
    QTest::newRow("relative coordinates") << IntMatrix{2, 3, {1, 2, -3, 4, -5, 6}} << -1 << -1 << true;
}

void IteratorExceptionTests::testZIteratorAsteriskOperatorExceptions_data()
{
    QTest::addColumn<IntMatrixZIterator>("zIterator");
    QTest::addColumn<IntMatrixConstZIterator>("constZIterator");
    QTest::addColumn<IntMatrixReverseZIterator>("reverseZIterator");
    QTest::addColumn<IntMatrixConstReverseZIterator>("constReverseZIterator");
    QTest::addColumn<int>("value");

    m_PrimaryIntMatrix.clear();
    m_SecondaryIntMatrix = {4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

    QTest::newRow("begin iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.constReverseZBegin() << -9;
    QTest::newRow("end iterator") << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.constReverseZEnd() << -14;
    QTest::newRow("end iterator") << m_SecondaryIntMatrix.zEnd() << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.constReverseZEnd() << -14;
}

void IteratorExceptionTests::testNIteratorAsteriskOperatorExceptions_data()
{
    QTest::addColumn<IntMatrixNIterator>("nIterator");
    QTest::addColumn<IntMatrixConstNIterator>("constNIterator");
    QTest::addColumn<IntMatrixReverseNIterator>("reverseNIterator");
    QTest::addColumn<IntMatrixConstReverseNIterator>("constReverseNIterator");
    QTest::addColumn<int>("value");

    m_PrimaryIntMatrix.clear();
    m_SecondaryIntMatrix = {3, 4, {1, 4, 7, 10, 2, 5, 8, 11, 3, 6, 9, 12}};

    QTest::newRow("begin iterator") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.constReverseNBegin() << -9;
    QTest::newRow("end iterator") << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd() << -14;
    QTest::newRow("end iterator") << m_SecondaryIntMatrix.nEnd() << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd() << -14;
}

void IteratorExceptionTests::testDiagIteratorAsteriskOperatorExceptions_data()
{
    QTest::addColumn<IntMatrixDIterator>("dIterator");
    QTest::addColumn<IntMatrixConstDIterator>("constDIterator");
    QTest::addColumn<IntMatrixReverseDIterator>("reverseDIterator");
    QTest::addColumn<IntMatrixConstReverseDIterator>("constReverseDIterator");
    QTest::addColumn<IntMatrixMIterator>("mIterator");
    QTest::addColumn<IntMatrixConstMIterator>("constMIterator");
    QTest::addColumn<IntMatrixReverseMIterator>("reverseMIterator");
    QTest::addColumn<IntMatrixConstReverseMIterator>("constReverseMIterator");
    QTest::addColumn<int>("value");

    m_PrimaryIntMatrix = {4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

    QTest::newRow("end iterator") << m_PrimaryIntMatrix.dEnd(-1) << m_PrimaryIntMatrix.constDEnd(-1) << m_PrimaryIntMatrix.reverseDEnd(-1) << m_PrimaryIntMatrix.constReverseDEnd(-1) << m_PrimaryIntMatrix.mEnd(-1) << m_PrimaryIntMatrix.constMEnd(-1) << m_PrimaryIntMatrix.reverseMEnd(-1) << m_PrimaryIntMatrix.constReverseMEnd(-1) << -14;
    QTest::newRow("end iterator") << m_PrimaryIntMatrix.dEnd(0, 2) << m_PrimaryIntMatrix.constDEnd(0, 2) << m_PrimaryIntMatrix.reverseDEnd(0, 2) << m_PrimaryIntMatrix.constReverseDEnd(0, 2) << m_PrimaryIntMatrix.mEnd(0, 0) << m_PrimaryIntMatrix.constMEnd(0, 0) << m_PrimaryIntMatrix.reverseMEnd(0, 0) << m_PrimaryIntMatrix.constReverseMEnd(0, 0) << -14;
}

void IteratorExceptionTests::testZIteratorArrowOperatorExceptions_data()
{
    QTest::addColumn<StringMatrixZIterator>("zIterator");
    QTest::addColumn<StringMatrixConstZIterator>("constZIterator");
    QTest::addColumn<StringMatrixReverseZIterator>("reverseZIterator");
    QTest::addColumn<StringMatrixConstReverseZIterator>("constReverseZIterator");
    QTest::addColumn<std::string>("value");

    m_PrimaryStringMatrix.clear();
    m_SecondaryStringMatrix = {2, 3, {"abc", "def", "ghi", "jkl", "mno", "pqr"}};

    QTest::newRow("begin iterator") << m_PrimaryStringMatrix.zBegin() << m_PrimaryStringMatrix.constZBegin() << m_PrimaryStringMatrix.reverseZBegin() << m_PrimaryStringMatrix.constReverseZBegin() << std::string{"zzz"};
    QTest::newRow("end iterator") << m_PrimaryStringMatrix.zEnd() << m_PrimaryStringMatrix.constZEnd() << m_PrimaryStringMatrix.reverseZEnd() << m_PrimaryStringMatrix.constReverseZEnd() << std::string{"zzz"};
    QTest::newRow("end itertator") << m_SecondaryStringMatrix.zEnd() << m_SecondaryStringMatrix.constZEnd() << m_SecondaryStringMatrix.reverseZEnd() << m_SecondaryStringMatrix.constReverseZEnd() << std::string{"zzz"};
}

void IteratorExceptionTests::testNIteratorArrowOperatorExceptions_data()
{
    QTest::addColumn<StringMatrixNIterator>("nIterator");
    QTest::addColumn<StringMatrixConstNIterator>("constNIterator");
    QTest::addColumn<StringMatrixReverseNIterator>("reverseNIterator");
    QTest::addColumn<StringMatrixConstReverseNIterator>("constReverseNIterator");
    QTest::addColumn<std::string>("value");

    m_PrimaryStringMatrix.clear();
    m_SecondaryStringMatrix = {3, 2, {"abc", "jkl", "def", "mno", "ghi", "pqr"}};

    QTest::newRow("begin iterator") << m_PrimaryStringMatrix.nBegin() << m_PrimaryStringMatrix.constNBegin() << m_PrimaryStringMatrix.reverseNBegin() << m_PrimaryStringMatrix.constReverseNBegin() << std::string{"zzz"};
    QTest::newRow("end iterator") << m_PrimaryStringMatrix.nEnd() << m_PrimaryStringMatrix.constNEnd() << m_PrimaryStringMatrix.reverseNEnd() << m_PrimaryStringMatrix.constReverseNEnd() << std::string{"zzz"};
    QTest::newRow("end itertator") << m_SecondaryStringMatrix.nEnd() << m_SecondaryStringMatrix.constNEnd() << m_SecondaryStringMatrix.reverseNEnd() << m_SecondaryStringMatrix.constReverseNEnd() << std::string{"zzz"};
}

void IteratorExceptionTests::testDiagIteratorArrowOperatorExceptions_data()
{
    QTest::addColumn<StringMatrixDIterator>("dIterator");
    QTest::addColumn<StringMatrixConstDIterator>("constDIterator");
    QTest::addColumn<StringMatrixReverseDIterator>("reverseDIterator");
    QTest::addColumn<StringMatrixConstReverseDIterator>("constReverseDIterator");
    QTest::addColumn<StringMatrixMIterator>("mIterator");
    QTest::addColumn<StringMatrixConstMIterator>("constMIterator");
    QTest::addColumn<StringMatrixReverseMIterator>("reverseMIterator");
    QTest::addColumn<StringMatrixConstReverseMIterator>("constReverseMIterator");
    QTest::addColumn<std::string>("value");

    m_PrimaryStringMatrix = {4, 3, {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l"}};

    QTest::newRow("end iterator") << m_PrimaryStringMatrix.dEnd(-1) << m_PrimaryStringMatrix.constDEnd(-1) << m_PrimaryStringMatrix.reverseDEnd(-1) << m_PrimaryStringMatrix.constReverseDEnd(-1) << m_PrimaryStringMatrix.mEnd(-1) << m_PrimaryStringMatrix.constMEnd(-1) << m_PrimaryStringMatrix.reverseMEnd(-1) << m_PrimaryStringMatrix.constReverseMEnd(-1) << std::string{"m"};
    QTest::newRow("end iterator") << m_PrimaryStringMatrix.dEnd(0, 2) << m_PrimaryStringMatrix.constDEnd(0, 2) << m_PrimaryStringMatrix.reverseDEnd(0, 2) << m_PrimaryStringMatrix.constReverseDEnd(0, 2) << m_PrimaryStringMatrix.mEnd(0, 0) << m_PrimaryStringMatrix.constMEnd(0, 0) << m_PrimaryStringMatrix.reverseMEnd(0, 0) << m_PrimaryStringMatrix.constReverseMEnd(0, 0) << std::string{"m"};
}

void IteratorExceptionTests::testZIteratorSquareBracketsOperatorExceptions_data()
{
    QTest::addColumn<IntMatrixZIterator>("zIterator");
    QTest::addColumn<IntMatrixConstZIterator>("constZIterator");
    QTest::addColumn<IntMatrixReverseZIterator>("reverseZIterator");
    QTest::addColumn<IntMatrixConstReverseZIterator>("constReverseZIterator");
    QTest::addColumn<IntMatrixSizeType>("forwardIndex");
    QTest::addColumn<IntMatrixSizeType>("reverseIndex");
    QTest::addColumn<int>("value");

    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_SecondaryIntMatrix.clear();

    QTest::newRow("begin iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.constReverseZBegin() << -2 << -2 << 7;
    QTest::newRow("begin iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.constReverseZBegin() << -1 << -1 << 7;
    QTest::newRow("begin iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.constReverseZBegin() << 6 << 6 << 7;
    QTest::newRow("begin iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.constReverseZBegin() << 7 << 7 << 7;
    QTest::newRow("random iterator") << m_PrimaryIntMatrix.getZIterator(1, 0) << m_PrimaryIntMatrix.getConstZIterator(1, 0) << m_PrimaryIntMatrix.getReverseZIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 0) << -5 << -4 << 7;
    QTest::newRow("random iterator") << m_PrimaryIntMatrix.getZIterator(1, 0) << m_PrimaryIntMatrix.getConstZIterator(1, 0) << m_PrimaryIntMatrix.getReverseZIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 0) << -4 << -3 << 7;
    QTest::newRow("random iterator") << m_PrimaryIntMatrix.getZIterator(1, 0) << m_PrimaryIntMatrix.getConstZIterator(1, 0) << m_PrimaryIntMatrix.getReverseZIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 0) << 3 << 4 << 7;
    QTest::newRow("random iterator") << m_PrimaryIntMatrix.getZIterator(1, 0) << m_PrimaryIntMatrix.getConstZIterator(1, 0) << m_PrimaryIntMatrix.getReverseZIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 0) << 4 << 5 << 7;
    QTest::newRow("end iterator") << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.constReverseZEnd() << -8 << -8 << 7;
    QTest::newRow("end iterator") << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.constReverseZEnd() << -7 << -7 << 7;
    QTest::newRow("end iterator") << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.constReverseZEnd() << 0 << 0 << 7;
    QTest::newRow("end iterator") << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.constReverseZEnd() << 1 << 1 << 7;
    QTest::newRow("begin iterator") << m_SecondaryIntMatrix.zBegin() << m_SecondaryIntMatrix.constZBegin() << m_SecondaryIntMatrix.reverseZBegin() << m_SecondaryIntMatrix.constReverseZBegin() << -1 << -1 << 7;
    QTest::newRow("begin iterator") << m_SecondaryIntMatrix.zBegin() << m_SecondaryIntMatrix.constZBegin() << m_SecondaryIntMatrix.reverseZBegin() << m_SecondaryIntMatrix.constReverseZBegin() << 0 << 0 << 7;
    QTest::newRow("begin iterator") << m_SecondaryIntMatrix.zBegin() << m_SecondaryIntMatrix.constZBegin() << m_SecondaryIntMatrix.reverseZBegin() << m_SecondaryIntMatrix.constReverseZBegin() << 1 << 1 << 7;
    QTest::newRow("end iterator") << m_SecondaryIntMatrix.zEnd() << m_SecondaryIntMatrix.constZEnd() << m_SecondaryIntMatrix.reverseZEnd() << m_SecondaryIntMatrix.constReverseZEnd() << -1 << -1 << 7;
    QTest::newRow("end iterator") << m_SecondaryIntMatrix.zEnd() << m_SecondaryIntMatrix.constZEnd() << m_SecondaryIntMatrix.reverseZEnd() << m_SecondaryIntMatrix.constReverseZEnd() << 0 << 0 << 7;
    QTest::newRow("end iterator") << m_SecondaryIntMatrix.zEnd() << m_SecondaryIntMatrix.constZEnd() << m_SecondaryIntMatrix.reverseZEnd() << m_SecondaryIntMatrix.constReverseZEnd() << 1 << 1 << 7;

}

void IteratorExceptionTests::testNIteratorSquareBracketsOperatorExceptions_data()
{
    QTest::addColumn<IntMatrixNIterator>("nIterator");
    QTest::addColumn<IntMatrixConstNIterator>("constNIterator");
    QTest::addColumn<IntMatrixReverseNIterator>("reverseNIterator");
    QTest::addColumn<IntMatrixConstReverseNIterator>("constReverseNIterator");
    QTest::addColumn<IntMatrixSizeType>("forwardIndex");
    QTest::addColumn<IntMatrixSizeType>("reverseIndex");
    QTest::addColumn<int>("value");

    m_PrimaryIntMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    m_SecondaryIntMatrix.clear();

    QTest::newRow("begin iterator") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.constReverseNBegin() << -2 << -2 << 7;
    QTest::newRow("begin iterator") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.constReverseNBegin() << -1 << -1 << 7;
    QTest::newRow("begin iterator") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.constReverseNBegin() << 6 << 6 << 7;
    QTest::newRow("begin iterator") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.constReverseNBegin() << 7 << 7 << 7;
    QTest::newRow("random iterator") << m_PrimaryIntMatrix.getNIterator(0, 1) << m_PrimaryIntMatrix.getConstNIterator(0, 1) << m_PrimaryIntMatrix.getReverseNIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 1) << -5 << -4 << 7;
    QTest::newRow("random iterator") << m_PrimaryIntMatrix.getNIterator(0, 1) << m_PrimaryIntMatrix.getConstNIterator(0, 1) << m_PrimaryIntMatrix.getReverseNIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 1) << -4 << -3 << 7;
    QTest::newRow("random iterator") << m_PrimaryIntMatrix.getNIterator(0, 1) << m_PrimaryIntMatrix.getConstNIterator(0, 1) << m_PrimaryIntMatrix.getReverseNIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 1) << 3 << 4 << 7;
    QTest::newRow("random iterator") << m_PrimaryIntMatrix.getNIterator(0, 1) << m_PrimaryIntMatrix.getConstNIterator(0, 1) << m_PrimaryIntMatrix.getReverseNIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 1) << 4 << 5 << 7;
    QTest::newRow("end iterator") << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd() << -8 << -8 << 7;
    QTest::newRow("end iterator") << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd() << -7 << -7 << 7;
    QTest::newRow("end iterator") << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd() << 0 << 0 << 7;
    QTest::newRow("end iterator") << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd() << 1 << 1 << 7;
    QTest::newRow("begin iterator") << m_SecondaryIntMatrix.nBegin() << m_SecondaryIntMatrix.constNBegin() << m_SecondaryIntMatrix.reverseNBegin() << m_SecondaryIntMatrix.constReverseNBegin() << -1 << -1 << 7;
    QTest::newRow("begin iterator") << m_SecondaryIntMatrix.nBegin() << m_SecondaryIntMatrix.constNBegin() << m_SecondaryIntMatrix.reverseNBegin() << m_SecondaryIntMatrix.constReverseNBegin() << 0 << 0 << 7;
    QTest::newRow("begin iterator") << m_SecondaryIntMatrix.nBegin() << m_SecondaryIntMatrix.constNBegin() << m_SecondaryIntMatrix.reverseNBegin() << m_SecondaryIntMatrix.constReverseNBegin() << 1 << 1 << 7;
    QTest::newRow("end iterator") << m_SecondaryIntMatrix.nEnd() << m_SecondaryIntMatrix.constNEnd() << m_SecondaryIntMatrix.reverseNEnd() << m_SecondaryIntMatrix.constReverseNEnd() << -1 << -1 << 7;
    QTest::newRow("end iterator") << m_SecondaryIntMatrix.nEnd() << m_SecondaryIntMatrix.constNEnd() << m_SecondaryIntMatrix.reverseNEnd() << m_SecondaryIntMatrix.constReverseNEnd() << 0 << 0 << 7;
    QTest::newRow("end iterator") << m_SecondaryIntMatrix.nEnd() << m_SecondaryIntMatrix.constNEnd() << m_SecondaryIntMatrix.reverseNEnd() << m_SecondaryIntMatrix.constReverseNEnd() << 1 << 1 << 7;
}

void IteratorExceptionTests::testDiagIteratorSquareBracketsOperatorExceptions_data()
{
    QTest::addColumn<IntMatrixDIterator>("dIterator");
    QTest::addColumn<IntMatrixConstDIterator>("constDIterator");
    QTest::addColumn<IntMatrixReverseDIterator>("reverseDIterator");
    QTest::addColumn<IntMatrixConstReverseDIterator>("constReverseDIterator");
    QTest::addColumn<IntMatrixMIterator>("mIterator");
    QTest::addColumn<IntMatrixConstMIterator>("constMIterator");
    QTest::addColumn<IntMatrixReverseMIterator>("reverseMIterator");
    QTest::addColumn<IntMatrixConstReverseMIterator>("constReverseMIterator");
    QTest::addColumn<IntMatrixSizeType>("forwardIndex");
    QTest::addColumn<IntMatrixSizeType>("reverseIndex");
    QTest::addColumn<int>("value");

    m_PrimaryIntMatrix = {4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

    QTest::newRow("begin iterator") << m_PrimaryIntMatrix.dBegin(0, 1) << m_PrimaryIntMatrix.constDBegin(0, 1) << m_PrimaryIntMatrix.reverseDBegin(0, 1) << m_PrimaryIntMatrix.constReverseDBegin(0, 1) << m_PrimaryIntMatrix.mBegin(0, 1) << m_PrimaryIntMatrix.constMBegin(0, 1) << m_PrimaryIntMatrix.reverseMBegin(0, 1) << m_PrimaryIntMatrix.constReverseMBegin(0, 1) << -1 << -1 << -14;
    QTest::newRow("end iterator") << m_PrimaryIntMatrix.dEnd(0, 0) << m_PrimaryIntMatrix.constDEnd(0, 0) << m_PrimaryIntMatrix.reverseDEnd(0, 0) << m_PrimaryIntMatrix.constReverseDEnd(0, 0) << m_PrimaryIntMatrix.mEnd(0, 2) << m_PrimaryIntMatrix.constMEnd(0, 2) << m_PrimaryIntMatrix.reverseMEnd(0, 2) << m_PrimaryIntMatrix.constReverseMEnd(0, 2) << 0 << 0 << 14;
    QTest::newRow("random iterator") << m_PrimaryIntMatrix.getDIterator(2, 1) << m_PrimaryIntMatrix.getConstDIterator(2, 1) << m_PrimaryIntMatrix.getReverseDIterator(2, 1) << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) << m_PrimaryIntMatrix.getMIterator(2, 1) << m_PrimaryIntMatrix.getConstMIterator(2, 1) << m_PrimaryIntMatrix.getReverseMIterator(2, 1) << m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) << 2 << 2 << -14;
    QTest::newRow("random iterator") << m_PrimaryIntMatrix.getDIterator(0, 1, true) << m_PrimaryIntMatrix.getConstDIterator(0, 1, true) << m_PrimaryIntMatrix.getReverseDIterator(0, 1, true) << m_PrimaryIntMatrix.getConstReverseDIterator(0, 1, true) << m_PrimaryIntMatrix.getMIterator(0, 1, true) << m_PrimaryIntMatrix.getConstMIterator(0, 1, true) << m_PrimaryIntMatrix.getReverseMIterator(0, 1, true) << m_PrimaryIntMatrix.getConstReverseMIterator(0, 1, true) << -2 << -2 << 14;
    QTest::newRow("random iterator") << m_PrimaryIntMatrix.getDIterator(1, 0, true) << m_PrimaryIntMatrix.getConstDIterator(1, 0, true) << m_PrimaryIntMatrix.getReverseDIterator(1, 0, true) << m_PrimaryIntMatrix.getConstReverseDIterator(1, 0, true) << m_PrimaryIntMatrix.getMIterator(1, 0, true) << m_PrimaryIntMatrix.getConstMIterator(1, 0, true) << m_PrimaryIntMatrix.getReverseMIterator(1, 0, true) << m_PrimaryIntMatrix.getConstReverseMIterator(1, 0, true) << 3 << 3 << -14;
    QTest::newRow("begin iterator") << m_PrimaryIntMatrix.dBegin(-1) << m_PrimaryIntMatrix.constDBegin(-1) << m_PrimaryIntMatrix.reverseDBegin(-1) << m_PrimaryIntMatrix.constReverseDBegin(-1) << m_PrimaryIntMatrix.mBegin(-1) << m_PrimaryIntMatrix.constMBegin(-1) << m_PrimaryIntMatrix.reverseMBegin(-1) << m_PrimaryIntMatrix.constReverseMBegin(-1) << -2 << -2 << 14;
}

QTEST_APPLESS_MAIN(IteratorExceptionTests)

#include "tst_iteratorexceptiontests.moc"
