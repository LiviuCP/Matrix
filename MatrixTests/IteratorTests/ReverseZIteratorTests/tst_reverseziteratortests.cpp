#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixReverseZIterator = Matrix<int>::ReverseZIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixReverseZIterator = Matrix<std::string>::ReverseZIterator;

class ReverseZIteratorTests : public QObject
{
    Q_OBJECT

public:
    ReverseZIteratorTests();
    ~ReverseZIteratorTests();

private slots:
    void testIteratorCreation();
    void testIteratorsAreEqual();
    void testIteratorsAreNotEqual();
    void testSmallerThanOperator();
    void testSmallerThanOrEqualToOperator();
    void testGreaterThanOperator();
    void testGreaterThanOrEqualToOperator();
    void testIncrementOperators();
    void testDecrementOperators();
    void testOperatorPlus();
    void testOperatorMinus();
    void testOperatorPlusEqual();
    void testOperatorMinusEqual();
    void testDifferenceOperator();
    void testDereferenceAsteriskOperator();
    void testDereferenceArrowOperator();
    void testDereferenceSquareBracketsOperator();

    // "bonus" tests, demonstrate the integration of the Matrix iterators with algorithms of the standard library
    void testStdCount();
    void testStdFind();
    void testStdSort();

private:
    IntMatrix m_MainMatrix;
    IntMatrix m_AuxIntMatrix;
    StringMatrix m_AuxStringMatrix;
};

ReverseZIteratorTests::ReverseZIteratorTests()
{
}

ReverseZIteratorTests::~ReverseZIteratorTests()
{
}

void ReverseZIteratorTests::testIteratorCreation()
{
    m_MainMatrix = {9, 8, -5};

    IntMatrixReverseZIterator it{m_MainMatrix.reverseZBegin()};
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseZEnd();
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseZRowBegin(0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseZRowBegin(1);
    QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseZRowBegin(4);
    QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseZRowBegin(7);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseZRowBegin(8);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseZRowEnd(0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseZRowEnd(1);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseZRowEnd(4);
    QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseZRowEnd(7);
    QVERIFY2(it.getCurrentRowNr() == 6 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseZRowEnd(8);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseZIterator(0, 0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseZIterator(0, 1);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseZIterator(5, 4);
    QVERIFY2(it.getCurrentRowNr() == 5 && it.getCurrentColumnNr() == 4 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseZIterator(8, 6);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 6 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseZIterator(8, 7);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseZIterator(0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseZIterator(1);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseZIterator(44);
    QVERIFY2(it.getCurrentRowNr() == 5 && it.getCurrentColumnNr() == 4 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseZIterator(70);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 6 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseZIterator(71);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // test iterator creation for empty matrix
    m_MainMatrix.clear();
    it = m_MainMatrix.reverseZBegin();
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseZEnd();
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // test empty iterator creation (not bound to any matrix) - an empty iterator should be valid for any empty matrix
    IntMatrixReverseZIterator emptyIt;
    QVERIFY2(emptyIt.getCurrentRowNr() == -1 && emptyIt.getCurrentColumnNr() == -1 && emptyIt.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // additional test
    m_MainMatrix = {9, 8, -5};
    m_AuxIntMatrix = {9, 8, -5};
    it = m_MainMatrix.getReverseZIterator(5, 4);
    QVERIFY(!it.isValidWithMatrix(m_AuxIntMatrix));
    m_AuxIntMatrix.clear();
    QVERIFY(!it.isValidWithMatrix(m_AuxIntMatrix));
    it = m_AuxIntMatrix.reverseZBegin();
    QVERIFY(!it.isValidWithMatrix(m_MainMatrix));
    it = m_AuxIntMatrix.reverseZEnd();
    QVERIFY(!it.isValidWithMatrix(m_MainMatrix));
    m_MainMatrix.clear();
    it = m_MainMatrix.reverseZBegin();
    QVERIFY(it.isValidWithMatrix(m_AuxIntMatrix)); // an iterator of an empty matrix is valid with any other empty matrix
    it = m_MainMatrix.reverseZEnd();
    QVERIFY(it.isValidWithMatrix(m_AuxIntMatrix));
}

void ReverseZIteratorTests::testIteratorsAreEqual()
{

    m_MainMatrix = {9, 8, -5};

    // test different iterators for equality
    QVERIFY2((m_MainMatrix.getReverseZIterator(0) == m_MainMatrix.getReverseZIterator(0, 0)) && !(m_MainMatrix.getReverseZIterator(0) != m_MainMatrix.getReverseZIterator(0, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getReverseZIterator(1) == m_MainMatrix.getReverseZIterator(0, 1)) && !(m_MainMatrix.getReverseZIterator(1) != m_MainMatrix.getReverseZIterator(0, 1)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getReverseZIterator(44) == m_MainMatrix.getReverseZIterator(5, 4)) && !(m_MainMatrix.getReverseZIterator(44) != m_MainMatrix.getReverseZIterator(5, 4)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getReverseZIterator(70) == m_MainMatrix.getReverseZIterator(8, 6)) && !(m_MainMatrix.getReverseZIterator(70) != m_MainMatrix.getReverseZIterator(8, 6)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getReverseZIterator(71) == m_MainMatrix.getReverseZIterator(8, 7)) && !(m_MainMatrix.getReverseZIterator(71) != m_MainMatrix.getReverseZIterator(8, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseZBegin() == m_MainMatrix.getReverseZIterator(8, 7) && !(m_MainMatrix.reverseZBegin() != m_MainMatrix.getReverseZIterator(8, 7))), "The two iterators are not equal");
    QVERIFY2((m_MainMatrix.reverseZRowBegin(0) == m_MainMatrix.getReverseZIterator(0, 7)) && !(m_MainMatrix.reverseZRowBegin(0) != m_MainMatrix.getReverseZIterator(0, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseZRowBegin(1) == m_MainMatrix.getReverseZIterator(1, 7)) && !(m_MainMatrix.reverseZRowBegin(1) != m_MainMatrix.getReverseZIterator(1, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseZRowBegin(5) == m_MainMatrix.getReverseZIterator(5, 7)) && !(m_MainMatrix.reverseZRowBegin(5) != m_MainMatrix.getReverseZIterator(5, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseZRowBegin(7) == m_MainMatrix.getReverseZIterator(7, 7)) && !(m_MainMatrix.reverseZRowBegin(7) != m_MainMatrix.getReverseZIterator(7, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseZRowBegin(8) == m_MainMatrix.getReverseZIterator(8, 7)) && !(m_MainMatrix.reverseZRowBegin(8) != m_MainMatrix.getReverseZIterator(8, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseZRowEnd(0) == m_MainMatrix.reverseZEnd()) && !(m_MainMatrix.reverseZRowEnd(0) != m_MainMatrix.reverseZEnd()), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseZRowEnd(1) == m_MainMatrix.getReverseZIterator(0, 7)) && !(m_MainMatrix.reverseZRowEnd(1) != m_MainMatrix.getReverseZIterator(0, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseZRowEnd(5) == m_MainMatrix.getReverseZIterator(4, 7)) && !(m_MainMatrix.reverseZRowEnd(5) != m_MainMatrix.getReverseZIterator(4, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseZRowEnd(7) == m_MainMatrix.getReverseZIterator(6, 7)) && !(m_MainMatrix.reverseZRowEnd(7) != m_MainMatrix.getReverseZIterator(6, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseZRowEnd(8) == m_MainMatrix.getReverseZIterator(7, 7)) && !(m_MainMatrix.reverseZRowEnd(8) != m_MainMatrix.getReverseZIterator(7, 7)), "The two iterators are NOT equal");

    // test iterator equality to itself
    IntMatrixReverseZIterator it{m_MainMatrix.reverseZEnd()};
    QVERIFY2((it == it) && (it == m_MainMatrix.reverseZEnd()) && !(it != it) && !(it != m_MainMatrix.reverseZEnd()), "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getReverseZIterator(0, 0);
    QVERIFY2((it == it) && (it == m_MainMatrix.getReverseZIterator(0, 0)) && !(it != it) && !(it != m_MainMatrix.getReverseZIterator(0, 0)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getReverseZIterator(0, 1);
    QVERIFY2((it == it) && (it == m_MainMatrix.getReverseZIterator(0, 1)) && !(it != it) && !(it != m_MainMatrix.getReverseZIterator(0, 1)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getReverseZIterator(5, 4);
    QVERIFY2((it == it) && (it == m_MainMatrix.getReverseZIterator(5, 4)) && !(it != it) && !(it != m_MainMatrix.getReverseZIterator(5, 4)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getReverseZIterator(8, 6);
    QVERIFY2((it == it) && (it == m_MainMatrix.getReverseZIterator(8, 6)) && !(it != it) && !(it != m_MainMatrix.getReverseZIterator(8, 6)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.reverseZBegin();
    QVERIFY2((it == it) && (it == m_MainMatrix.reverseZBegin()) && !(it != it) && !(it != m_MainMatrix.reverseZBegin()),  "The iterator is NOT equal to itself and/or to source iterator");

    // test empty matrix iterator equality
    m_MainMatrix.clear();
    QVERIFY2((m_MainMatrix.reverseZBegin() == m_MainMatrix.reverseZEnd()) && !(m_MainMatrix.reverseZBegin() != m_MainMatrix.reverseZEnd()), "The two iterators are NOT equal");
}

void ReverseZIteratorTests::testIteratorsAreNotEqual()
{
    m_MainMatrix = {9, 8, -5};

    QVERIFY2((m_MainMatrix.reverseZEnd() != m_MainMatrix.getReverseZIterator(0, 0)) && !(m_MainMatrix.reverseZEnd() == m_MainMatrix.getReverseZIterator(0, 0)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 0) != m_MainMatrix.getReverseZIterator(0, 1)) && !(m_MainMatrix.getReverseZIterator(0, 0) == m_MainMatrix.getReverseZIterator(0, 1)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 1) != m_MainMatrix.getReverseZIterator(0, 2)) && !(m_MainMatrix.getReverseZIterator(0, 1) == m_MainMatrix.getReverseZIterator(0, 2)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 2) != m_MainMatrix.getReverseZIterator(5, 4)) && !(m_MainMatrix.getReverseZIterator(0, 2) == m_MainMatrix.getReverseZIterator(5, 4)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getReverseZIterator(5, 4) != m_MainMatrix.getReverseZIterator(8, 6)) && !(m_MainMatrix.getReverseZIterator(5, 4) == m_MainMatrix.getReverseZIterator(8, 6)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getReverseZIterator(8, 6) != m_MainMatrix.reverseZBegin()) && !(m_MainMatrix.getReverseZIterator(8, 6) == m_MainMatrix.reverseZBegin()), "The two iterators are NOT different");
}

void ReverseZIteratorTests::testSmallerThanOperator()
{
    m_MainMatrix = {9, 8, -5};

    QVERIFY2((m_MainMatrix.reverseZBegin() < m_MainMatrix.getReverseZIterator(8, 6)) && !(m_MainMatrix.reverseZBegin() >= m_MainMatrix.getReverseZIterator(8, 6)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(8, 6) < m_MainMatrix.getReverseZIterator(5, 4)) && !(m_MainMatrix.getReverseZIterator(8, 6) >= m_MainMatrix.getReverseZIterator(5, 4)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(5, 4) < m_MainMatrix.getReverseZIterator(0, 2)) && !(m_MainMatrix.getReverseZIterator(5, 4) >= m_MainMatrix.getReverseZIterator(0, 2)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 2) < m_MainMatrix.getReverseZIterator(0, 1)) && !(m_MainMatrix.getReverseZIterator(0, 2) >= m_MainMatrix.getReverseZIterator(0, 1)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 1) < m_MainMatrix.getReverseZIterator(0, 0)) && !(m_MainMatrix.getReverseZIterator(0, 1) >= m_MainMatrix.getReverseZIterator(0, 0)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 0) < m_MainMatrix.reverseZEnd()) && !(m_MainMatrix.getReverseZIterator(0, 0) >= m_MainMatrix.reverseZEnd()), "The first iterator is NOT smaller than the second iterator");
}

void ReverseZIteratorTests::testSmallerThanOrEqualToOperator()
{
    m_MainMatrix = {9, 8, -5};

    // test operator with different iterators
    QVERIFY2((m_MainMatrix.reverseZBegin() <= m_MainMatrix.reverseZBegin()) && !(m_MainMatrix.reverseZBegin() > m_MainMatrix.reverseZBegin()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.reverseZBegin() <= m_MainMatrix.getReverseZIterator(8, 6)) && !(m_MainMatrix.reverseZBegin() > m_MainMatrix.getReverseZIterator(8, 6)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(8, 6) <= m_MainMatrix.getReverseZIterator(8, 6)) && !(m_MainMatrix.getReverseZIterator(8, 6) > m_MainMatrix.getReverseZIterator(8, 6)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(8, 6) <= m_MainMatrix.getReverseZIterator(5, 4)) && !(m_MainMatrix.getReverseZIterator(8, 6) > m_MainMatrix.getReverseZIterator(5, 4)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(5, 4) <= m_MainMatrix.getReverseZIterator(5, 4)) && !(m_MainMatrix.getReverseZIterator(5, 4) > m_MainMatrix.getReverseZIterator(5, 4)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(5, 4) <= m_MainMatrix.getReverseZIterator(0, 2)) && !(m_MainMatrix.getReverseZIterator(5, 4) > m_MainMatrix.getReverseZIterator(0, 2)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 2) <= m_MainMatrix.getReverseZIterator(0, 2)) && !(m_MainMatrix.getReverseZIterator(0, 2) > m_MainMatrix.getReverseZIterator(0, 2)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 2) <= m_MainMatrix.getReverseZIterator(0, 1)) && !(m_MainMatrix.getReverseZIterator(0, 2) > m_MainMatrix.getReverseZIterator(0, 1)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 1) <= m_MainMatrix.getReverseZIterator(0, 1)) && !(m_MainMatrix.getReverseZIterator(0, 1) > m_MainMatrix.getReverseZIterator(0, 1)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 1) <= m_MainMatrix.getReverseZIterator(0, 0)) && !(m_MainMatrix.getReverseZIterator(0, 1) > m_MainMatrix.getReverseZIterator(0, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 0) <= m_MainMatrix.getReverseZIterator(0, 0)) && !(m_MainMatrix.getReverseZIterator(0, 0) > m_MainMatrix.getReverseZIterator(0, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 0) <= m_MainMatrix.reverseZEnd()) && !(m_MainMatrix.getReverseZIterator(0, 0) > m_MainMatrix.reverseZEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.reverseZEnd() <= m_MainMatrix.reverseZEnd()) && !(m_MainMatrix.reverseZEnd() > m_MainMatrix.reverseZEnd()), "The first iterator is NOT smaller than or equal to the second iterator");

    // test if iterator is smaller than or equal to itself
    IntMatrixReverseZIterator it{m_MainMatrix.reverseZBegin()};
    QVERIFY2((it <= it) && (it <= m_MainMatrix.reverseZBegin()) && !(it > it) && !(it > m_MainMatrix.reverseZBegin()),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getReverseZIterator(0, 1);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getReverseZIterator(0, 1)) && !(it > it) && !(it > m_MainMatrix.getReverseZIterator(0, 1)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getReverseZIterator(5, 4);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getReverseZIterator(5, 4)) && !(it > it) && !(it > m_MainMatrix.getReverseZIterator(5, 4)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getReverseZIterator(8, 6);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getReverseZIterator(8, 6)) && !(it > it) && !(it > m_MainMatrix.getReverseZIterator(8, 6)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getReverseZIterator(8, 7);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getReverseZIterator(8, 7) && !(it > it) && !(it > m_MainMatrix.getReverseZIterator(8, 7))),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.reverseZEnd();
    QVERIFY2((it <= it) && (it <= m_MainMatrix.reverseZEnd()) && !(it > it) && !(it > m_MainMatrix.reverseZEnd()),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");

    // test with empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.reverseZBegin() <= m_MainMatrix.reverseZEnd(), "The first iterator is NOT smaller than or equal to the second iterator");
}

void ReverseZIteratorTests::testGreaterThanOperator()
{
    m_MainMatrix = {9, 8, -5};

    QVERIFY2((m_MainMatrix.reverseZEnd() > m_MainMatrix.getReverseZIterator(0, 0)) && !(m_MainMatrix.reverseZEnd() <= m_MainMatrix.getReverseZIterator(0, 0)), "TThe first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 0) > m_MainMatrix.getReverseZIterator(0, 1)) && !(m_MainMatrix.getReverseZIterator(0, 0) <= m_MainMatrix.getReverseZIterator(0, 1)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 1) > m_MainMatrix.getReverseZIterator(0, 2)) && !(m_MainMatrix.getReverseZIterator(0, 1) <= m_MainMatrix.getReverseZIterator(0, 2)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 2) > m_MainMatrix.getReverseZIterator(5, 4)) && !(m_MainMatrix.getReverseZIterator(0, 2) <= m_MainMatrix.getReverseZIterator(5, 4)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(5, 4) > m_MainMatrix.getReverseZIterator(8, 6)) && !(m_MainMatrix.getReverseZIterator(5, 4) <= m_MainMatrix.getReverseZIterator(8, 6)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(8, 6) > m_MainMatrix.reverseZBegin()) && !(m_MainMatrix.getReverseZIterator(8, 6) <= m_MainMatrix.reverseZBegin()), "The first iterator is NOT greater than the second iterator");
}

void ReverseZIteratorTests::testGreaterThanOrEqualToOperator()
{
    m_MainMatrix = {9, 8, -5};

    // test operator with different iterators
    QVERIFY2((m_MainMatrix.reverseZEnd() >= m_MainMatrix.reverseZEnd()) && !(m_MainMatrix.reverseZEnd() < m_MainMatrix.reverseZEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.reverseZEnd() >= m_MainMatrix.getReverseZIterator(0, 0)) && !(m_MainMatrix.reverseZEnd() < m_MainMatrix.getReverseZIterator(0, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 0) >= m_MainMatrix.getReverseZIterator(0, 0)) && !(m_MainMatrix.getReverseZIterator(0, 0) < m_MainMatrix.getReverseZIterator(0, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 0) >= m_MainMatrix.getReverseZIterator(0, 1)) && !(m_MainMatrix.getReverseZIterator(0, 0) < m_MainMatrix.getReverseZIterator(0, 1)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 1) >= m_MainMatrix.getReverseZIterator(0, 1)) && !(m_MainMatrix.getReverseZIterator(0, 1) < m_MainMatrix.getReverseZIterator(0, 1)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 1) >= m_MainMatrix.getReverseZIterator(0, 2)) && !(m_MainMatrix.getReverseZIterator(0, 1) < m_MainMatrix.getReverseZIterator(0, 2)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 2) >= m_MainMatrix.getReverseZIterator(0, 2)) && !(m_MainMatrix.getReverseZIterator(0, 2) < m_MainMatrix.getReverseZIterator(0, 2)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(0, 2) >= m_MainMatrix.getReverseZIterator(5, 4)) && !(m_MainMatrix.getReverseZIterator(0, 2) < m_MainMatrix.getReverseZIterator(5, 4)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(5, 4) >= m_MainMatrix.getReverseZIterator(5, 4)) && !(m_MainMatrix.getReverseZIterator(5, 4) < m_MainMatrix.getReverseZIterator(5, 4)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(5, 4) >= m_MainMatrix.getReverseZIterator(8, 6)) && !(m_MainMatrix.getReverseZIterator(5, 4) < m_MainMatrix.getReverseZIterator(8, 6)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(8, 6) >= m_MainMatrix.getReverseZIterator(8, 6)) && !(m_MainMatrix.getReverseZIterator(8, 6) < m_MainMatrix.getReverseZIterator(8, 6)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseZIterator(8, 6) >= m_MainMatrix.reverseZBegin()) && !(m_MainMatrix.getReverseZIterator(8, 6) < m_MainMatrix.reverseZBegin()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.reverseZBegin() >= m_MainMatrix.reverseZBegin()) && !(m_MainMatrix.reverseZBegin() < m_MainMatrix.reverseZBegin()), "The first iterator is NOT smaller than or equal to the second iterator");

    // test if iterator is greater than or equal to itself
    IntMatrixReverseZIterator it{m_MainMatrix.reverseZEnd()};
    QVERIFY2((it >= it) && (it >= m_MainMatrix.reverseZEnd()) && !(it < it) && !(it < m_MainMatrix.reverseZEnd()),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getReverseZIterator(8, 7);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getReverseZIterator(8, 7)) && !(it < it) && !(it < m_MainMatrix.getReverseZIterator(8, 7)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getReverseZIterator(8, 6);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getReverseZIterator(8, 6)) && !(it < it) && !(it < m_MainMatrix.getReverseZIterator(8, 6)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getReverseZIterator(5, 4);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getReverseZIterator(5, 4)) && !(it < it) && !(it < m_MainMatrix.getReverseZIterator(5, 4)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getReverseZIterator(0, 1);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getReverseZIterator(0, 1)) && !(it < it) && !(it < m_MainMatrix.getReverseZIterator(0, 1)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.reverseZBegin();
    QVERIFY2((it >= it) && (it >= m_MainMatrix.reverseZBegin()) && !(it < it) && !(it < m_MainMatrix.reverseZBegin()),  "The iterator is NOT greater than or equal to itself and/or the source iterator");

    // test with empty matrix
    m_MainMatrix.clear();
    QVERIFY2((m_MainMatrix.reverseZBegin() >= m_MainMatrix.reverseZEnd()) && !(m_MainMatrix.reverseZBegin() < m_MainMatrix.reverseZEnd()), "The first iterator is NOT greater than or equal to the second iterator");
}

void ReverseZIteratorTests::testIncrementOperators()
{
    m_MainMatrix = {9, 8, -5};

    // pre-increment
    IntMatrixReverseZIterator it{m_MainMatrix.reverseZBegin()};
    ++it;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 6), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 5), "Incorrect pre-incrementation");
    it = m_MainMatrix.getReverseZIterator(5, 5);
    ++it;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 4), "Incorrect pre-incrementation");
    it = m_MainMatrix.getReverseZIterator(5, 2);
    ++it;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 1), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 0), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(4, 7), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(4, 6), "Incorrect pre-incrementation");
    it = m_MainMatrix.getReverseZIterator(0, 1);
    ++it;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 0), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Incorrect pre-incrementation");

    // post-increment
    it = m_MainMatrix.reverseZBegin();
    it++;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 6), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 5), "Incorrect post-incrementation");
    it = m_MainMatrix.getReverseZIterator(5, 5);
    it++;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 4), "Incorrect post-incrementation");
    it = m_MainMatrix.getReverseZIterator(5, 2);
    it++;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 1), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 0), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(4, 7), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(4, 6), "Incorrect post-incrementation");
    it = m_MainMatrix.getReverseZIterator(0, 1);
    it++;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 0), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Incorrect post-incrementation");

    // test a combination of "pre" and "post" behaviors
    IntMatrixReverseZIterator srcIt{m_MainMatrix.getReverseZIterator(5, 6)};
    IntMatrixReverseZIterator destIt{++(++srcIt)};
    QVERIFY2(srcIt == m_MainMatrix.getReverseZIterator(5, 5) && destIt == m_MainMatrix.getReverseZIterator(5, 4), "Incorrect pre-pre-incrementation");
    srcIt = m_MainMatrix.getReverseZIterator(5, 6);
    destIt = (srcIt++)++;
    QVERIFY2(srcIt == m_MainMatrix.getReverseZIterator(5, 5) && destIt == m_MainMatrix.getReverseZIterator(5, 6), "Incorrect post-post-incrementation");
    srcIt = m_MainMatrix.getReverseZIterator(5, 6);
    destIt = (++srcIt)++;
    QVERIFY2(srcIt == m_MainMatrix.getReverseZIterator(5, 5) && destIt == m_MainMatrix.getReverseZIterator(5, 5), "Incorrect post-pre-incrementation");
    srcIt = m_MainMatrix.getReverseZIterator(5, 6);
    destIt = ++(srcIt++);
    QVERIFY2(srcIt == m_MainMatrix.getReverseZIterator(5, 5) && destIt == m_MainMatrix.getReverseZIterator(5, 5), "Incorrect pre-post-incrementation");
}

void ReverseZIteratorTests::testDecrementOperators()
{
    m_MainMatrix = {9, 8, -5};

    // pre-decrement
    IntMatrixReverseZIterator it{m_MainMatrix.reverseZEnd()};
    --it;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 0), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 1), "Incorrect pre-decrementation");
    it = m_MainMatrix.getReverseZIterator(4, 6);
    --it;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(4, 7), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 0), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 1), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 2), "Incorrect pre-decrementation");
    it = m_MainMatrix.getReverseZIterator(5, 4);
    --it;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 5), "Incorrect pre-decrementation");
    it = m_MainMatrix.getReverseZIterator(8, 5);
    --it;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 6), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Incorrect pre-decrementation");


    // post-decrement
    it = m_MainMatrix.reverseZEnd();
    it--;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 0), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 1), "Incorrect post-decrementation");
    it = m_MainMatrix.getReverseZIterator(5, 4);
    it--;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 5), "Incorrect post-decrementation");
    it = m_MainMatrix.getReverseZIterator(4, 6);
    it--;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(4, 7), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 0), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 1), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 2), "Incorrect post-decrementation");
    it = m_MainMatrix.getReverseZIterator(8, 6);
    it--;
    QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 7), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Incorrect post-decrementation");

    // test a combination of "pre" and "post" behaviors
    IntMatrixReverseZIterator srcIt{m_MainMatrix.getReverseZIterator(5, 4)};
    IntMatrixReverseZIterator destIt{--(--srcIt)};
    QVERIFY2(srcIt == m_MainMatrix.getReverseZIterator(5, 5) && destIt == m_MainMatrix.getReverseZIterator(5, 6), "Incorrect pre-pre-decrementation");
    srcIt = m_MainMatrix.getReverseZIterator(5, 4);
    destIt = (srcIt--)--;
    QVERIFY2(srcIt == m_MainMatrix.getReverseZIterator(5, 5) && destIt == m_MainMatrix.getReverseZIterator(5, 4), "Incorrect post-post-decrementation");
    srcIt = m_MainMatrix.getReverseZIterator(5, 4);
    destIt = (--srcIt)--;
    QVERIFY2(srcIt == m_MainMatrix.getReverseZIterator(5, 5) && destIt == m_MainMatrix.getReverseZIterator(5, 5), "Incorrect post-pre-decrementation");
    srcIt = m_MainMatrix.getReverseZIterator(5, 4);
    destIt = --(srcIt--);
    QVERIFY2(srcIt == m_MainMatrix.getReverseZIterator(5, 5) && destIt == m_MainMatrix.getReverseZIterator(5, 5), "Incorrect pre-post-decrementation");
}

void ReverseZIteratorTests::testOperatorPlus()
{
    m_MainMatrix = {9, 8, -5};

    // test for non-empty matrix
    IntMatrixReverseZIterator it{m_MainMatrix.reverseZEnd()};
    QVERIFY2(it + 3 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.getReverseZIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.getReverseZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-5) == m_MainMatrix.getReverseZIterator(0, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-11) == m_MainMatrix.getReverseZIterator(1, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.getReverseZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-72) == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-73) == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-75) == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getReverseZIterator(0, 0);
    QVERIFY2(it + 4 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getReverseZIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.getReverseZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-4) == m_MainMatrix.getReverseZIterator(0, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-10) == m_MainMatrix.getReverseZIterator(1, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-70) == m_MainMatrix.getReverseZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-72) == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-74) == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getReverseZIterator(0, 1);
    QVERIFY2(it + 5 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.getReverseZIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getReverseZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-3) == m_MainMatrix.getReverseZIterator(0, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-9) == m_MainMatrix.getReverseZIterator(1, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-69) == m_MainMatrix.getReverseZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-70) == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-73) == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getReverseZIterator(5, 4);
    QVERIFY2(it + 48 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 46 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 45 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 44 == m_MainMatrix.getReverseZIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 43 == m_MainMatrix.getReverseZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 6 == m_MainMatrix.getReverseZIterator(4, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.getReverseZIterator(5, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getReverseZIterator(5, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.getReverseZIterator(5, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-6) == m_MainMatrix.getReverseZIterator(6, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-26) == m_MainMatrix.getReverseZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-27) == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-28) == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-30) == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getReverseZIterator(8, 6);
    QVERIFY2(it + 74 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 72 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 71 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 70 == m_MainMatrix.getReverseZIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 69 == m_MainMatrix.getReverseZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 24 == m_MainMatrix.getReverseZIterator(5, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.getReverseZIterator(8, 3), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getReverseZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-4) == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.reverseZBegin();
    QVERIFY2(it + 75 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 73 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 72 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 71 == m_MainMatrix.getReverseZIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 70 == m_MainMatrix.getReverseZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 25 == m_MainMatrix.getReverseZIterator(5, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 4 == m_MainMatrix.getReverseZIterator(8, 3), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.getReverseZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-3) == m_MainMatrix.reverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.reverseZBegin() + (-1) == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.reverseZBegin() + 1 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.reverseZEnd() + 0 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.reverseZEnd() + 1 == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.reverseZEnd() + (-1) == m_MainMatrix.reverseZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");

    // test for empty iterators
    IntMatrixReverseZIterator emptyIt1{};
    IntMatrixReverseZIterator emptyIt2{};
    IntMatrixReverseZIterator emptyIt3{};
    emptyIt1 = emptyIt3 + (-1);
    emptyIt2 = emptyIt3 + 1;
    QVERIFY2(emptyIt1 == emptyIt3, "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(emptyIt2 == emptyIt3, "Operator + does not work correctly, the resulting iterator is not the right one");
}

void ReverseZIteratorTests::testOperatorMinus()
{
    m_MainMatrix = {9, 8, -5};

    // test for non-empty matrix
    IntMatrixReverseZIterator it{m_MainMatrix.reverseZEnd()};
    QVERIFY2(it - (-3) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.getReverseZIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.getReverseZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 5 == m_MainMatrix.getReverseZIterator(0, 4), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 11 == m_MainMatrix.getReverseZIterator(1, 2), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.getReverseZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 72 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 73 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 75 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getReverseZIterator(0, 0);
    QVERIFY2(it - (-4) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getReverseZIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.getReverseZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 4 == m_MainMatrix.getReverseZIterator(0, 4), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 10 == m_MainMatrix.getReverseZIterator(1, 2), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 70 == m_MainMatrix.getReverseZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 72 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 74 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getReverseZIterator(0, 1);
    QVERIFY2(it - (-5) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.getReverseZIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getReverseZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 3 == m_MainMatrix.getReverseZIterator(0, 4), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 9 == m_MainMatrix.getReverseZIterator(1, 2), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 69 == m_MainMatrix.getReverseZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 70 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 73 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getReverseZIterator(5, 4);
    QVERIFY2(it - (-48) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-46) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-45) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-44) == m_MainMatrix.getReverseZIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-43) == m_MainMatrix.getReverseZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-6) == m_MainMatrix.getReverseZIterator(4, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.getReverseZIterator(5, 2), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getReverseZIterator(5, 4), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.getReverseZIterator(5, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 6 == m_MainMatrix.getReverseZIterator(6, 2), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 26 == m_MainMatrix.getReverseZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 27 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 28 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 30 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getReverseZIterator(8, 6);
    QVERIFY2(it - (-74) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-72) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-71) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-70) == m_MainMatrix.getReverseZIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-69) == m_MainMatrix.getReverseZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-24) == m_MainMatrix.getReverseZIterator(5, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.getReverseZIterator(8, 3), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getReverseZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 4 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.reverseZBegin();
    QVERIFY2(it - (-75) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-73) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-72) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-71) == m_MainMatrix.getReverseZIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-70) == m_MainMatrix.getReverseZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-25) == m_MainMatrix.getReverseZIterator(5, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-4) == m_MainMatrix.getReverseZIterator(8, 3), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.getReverseZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 3 == m_MainMatrix.reverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.reverseZBegin() - 1 == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.reverseZBegin() - (-1) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.reverseZEnd() - 0 == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.reverseZEnd() - (-1) == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.reverseZEnd() - 1 == m_MainMatrix.reverseZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");

    // test for empty iterators
    IntMatrixReverseZIterator emptyIt1{};
    IntMatrixReverseZIterator emptyIt2{};
    IntMatrixReverseZIterator emptyIt3{};
    emptyIt1 = emptyIt3 - 1;
    emptyIt2 = emptyIt3 - (-1);
    QVERIFY2(emptyIt1 == emptyIt3, "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(emptyIt2 == emptyIt3, "Operator - does not work correctly, the resulting iterator is not the right one");
}

void ReverseZIteratorTests::testOperatorPlusEqual()
{
    IntMatrixReverseZIterator it;

    // test for non-empty matrix
    m_MainMatrix = {9, 8, -5};

    IntMatrixReverseZIterator referenceIt{m_MainMatrix.reverseZEnd()};
    it = referenceIt; it += 3; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-2); QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-5); QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-11); QVERIFY2(it == m_MainMatrix.getReverseZIterator(1, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-71); QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-72); QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-73); QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-75); QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getReverseZIterator(0, 0);
    it = referenceIt; it += 4; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 2; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-4); QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-10); QVERIFY2(it == m_MainMatrix.getReverseZIterator(1, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-70); QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-71); QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-72); QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-74); QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getReverseZIterator(0, 1);
    it = referenceIt; it += 5; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 3; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 2; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-3); QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-9); QVERIFY2(it == m_MainMatrix.getReverseZIterator(1, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-69); QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-70); QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-71); QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-73); QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getReverseZIterator(5, 4);
    it = referenceIt; it += 48; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 46; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 45; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 44; QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 43; QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 6; QVERIFY2(it == m_MainMatrix.getReverseZIterator(4, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 2; QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-2); QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-6); QVERIFY2(it == m_MainMatrix.getReverseZIterator(6, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-26); QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-27); QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-28); QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-30); QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getReverseZIterator(8, 6);
    it = referenceIt; it += 74; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 72; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 71; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 70; QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 69; QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 24; QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 3; QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 3), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-2); QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-4); QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.reverseZBegin();
    it = referenceIt; it += 75; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 73; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 72; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 71; QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 70; QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 25; QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 4; QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 3), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-3); QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    referenceIt = m_MainMatrix.reverseZBegin();
    referenceIt = m_MainMatrix.reverseZEnd();
    it = referenceIt; it += (-1); QVERIFY2(m_MainMatrix.reverseZBegin() == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += 1; QVERIFY2(m_MainMatrix.reverseZBegin() == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += 0; QVERIFY2(m_MainMatrix.reverseZEnd() == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += 1; QVERIFY2(m_MainMatrix.reverseZEnd() == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += (-1); QVERIFY2(m_MainMatrix.reverseZEnd() == m_MainMatrix.reverseZEnd(), "Operator += does not work correctly, the updated iterator is not the right one");

    // test for empty iterators
    IntMatrixReverseZIterator emptyIt1{};
    IntMatrixReverseZIterator emptyIt2{};
    IntMatrixReverseZIterator emptyIt3{};
    emptyIt2 += (-1); QVERIFY2(emptyIt2 == emptyIt1, "Operator += does not work correctly, the updated iterator is not the right one");
    emptyIt3 += 1; QVERIFY2(emptyIt3 == emptyIt1, "Operator += does not work correctly, the updated iterator is not the right one");
}

void ReverseZIteratorTests::testOperatorMinusEqual()
{
    IntMatrixReverseZIterator it;

    // test for non-empty matrix
    m_MainMatrix = {9, 8, -5};

    IntMatrixReverseZIterator referenceIt{m_MainMatrix.reverseZEnd()};
    it = referenceIt; it -= (-3); QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 2; QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 5; QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 11; QVERIFY2(it == m_MainMatrix.getReverseZIterator(1, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 71; QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 72; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 73; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 75; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getReverseZIterator(0, 0);
    it = referenceIt; it -= (-4); QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-2); QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 4; QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 10; QVERIFY2(it == m_MainMatrix.getReverseZIterator(1, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 70; QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 71; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 72; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 74; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getReverseZIterator(0, 1);
    it = referenceIt; it -= (-5); QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-3); QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-2); QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 3; QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 9; QVERIFY2(it == m_MainMatrix.getReverseZIterator(1, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 69; QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 70; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 71; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 73; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getReverseZIterator(5, 4);
    it = referenceIt; it -= (-48); QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-46); QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-45); QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-44); QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-43); QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-6); QVERIFY2(it == m_MainMatrix.getReverseZIterator(4, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-2); QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 2; QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 6; QVERIFY2(it == m_MainMatrix.getReverseZIterator(6, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 26; QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 27; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 28; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 30; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getReverseZIterator(8, 6);
    it = referenceIt; it -= (-74); QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-72); QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-71); QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-70); QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-69); QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-24); QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-3); QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 3), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 2; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 4; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.reverseZBegin();
    it = referenceIt; it -= (-75); QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-73); QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-72); QVERIFY2(it == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-71); QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-70); QVERIFY2(it == m_MainMatrix.getReverseZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-25); QVERIFY2(it == m_MainMatrix.getReverseZIterator(5, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-4); QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 3), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.getReverseZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 3; QVERIFY2(it == m_MainMatrix.reverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    referenceIt = m_MainMatrix.reverseZBegin();
    referenceIt = m_MainMatrix.reverseZEnd();
    it = referenceIt; it -= 1; QVERIFY2(m_MainMatrix.reverseZBegin() == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= (-1); QVERIFY2(m_MainMatrix.reverseZBegin() == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= 0; QVERIFY2(m_MainMatrix.reverseZEnd() == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= (-1); QVERIFY2(m_MainMatrix.reverseZEnd() == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= 1; QVERIFY2(m_MainMatrix.reverseZEnd() == m_MainMatrix.reverseZEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");

    // test for empty iterators
    IntMatrixReverseZIterator emptyIt1{};
    IntMatrixReverseZIterator emptyIt2{};
    IntMatrixReverseZIterator emptyIt3{};
    emptyIt2 -= 1; QVERIFY2(emptyIt2 == emptyIt1, "Operator -= does not work correctly, the updated iterator is not the right one");
    emptyIt3 -= (-1); QVERIFY2(emptyIt3 == emptyIt1, "Operator -= does not work correctly, the updated iterator is not the right one");
}

void ReverseZIteratorTests::testDifferenceOperator()
{
    // test for non-empty matrix
    m_MainMatrix = {9, 8, -5};

    QVERIFY2(m_MainMatrix.reverseZBegin() - m_MainMatrix.reverseZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseZBegin() - m_MainMatrix.getReverseZIterator(8, 6) == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseZBegin() - m_MainMatrix.getReverseZIterator(5, 4) == -27, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseZBegin() - m_MainMatrix.getReverseZIterator(0, 1) == -70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseZBegin() - m_MainMatrix.getReverseZIterator(0, 0) == -71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseZBegin() - m_MainMatrix.reverseZEnd() == -72, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getReverseZIterator(8, 6) - m_MainMatrix.reverseZBegin() == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(8, 6) - m_MainMatrix.getReverseZIterator(8, 6) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(8, 6) - m_MainMatrix.getReverseZIterator(5, 4) == -26, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(8, 6) - m_MainMatrix.getReverseZIterator(0, 1) == -69, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(8, 6) - m_MainMatrix.getReverseZIterator(0, 0) == -70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(8, 6) - m_MainMatrix.reverseZEnd() == -71, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getReverseZIterator(5, 4) - m_MainMatrix.reverseZBegin() == 27, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(5, 4) - m_MainMatrix.getReverseZIterator(8, 6) == 26, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(5, 4) - m_MainMatrix.getReverseZIterator(5, 4) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(5, 4) - m_MainMatrix.getReverseZIterator(0, 1) == -43, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(5, 4) - m_MainMatrix.getReverseZIterator(0, 0) == -44, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(5, 4) - m_MainMatrix.reverseZEnd() == -45, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getReverseZIterator(0, 1) - m_MainMatrix.reverseZBegin() == 70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(0, 1) - m_MainMatrix.getReverseZIterator(8, 6) == 69, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(0, 1) - m_MainMatrix.getReverseZIterator(5, 4) == 43, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(0, 1) - m_MainMatrix.getReverseZIterator(0, 1) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(0, 1) - m_MainMatrix.getReverseZIterator(0, 0) == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(0, 1) - m_MainMatrix.reverseZEnd() == -2, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getReverseZIterator(0, 0) - m_MainMatrix.reverseZBegin() == 71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(0, 0) - m_MainMatrix.getReverseZIterator(8, 6) == 70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(0, 0) - m_MainMatrix.getReverseZIterator(5, 4) == 44, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(0, 0) - m_MainMatrix.getReverseZIterator(0, 1) == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(0, 0) - m_MainMatrix.getReverseZIterator(0, 0) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(0, 0) - m_MainMatrix.reverseZEnd() == -1, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.reverseZEnd() - m_MainMatrix.reverseZBegin() == 72, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseZEnd() - m_MainMatrix.getReverseZIterator(8, 6) == 71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseZEnd() - m_MainMatrix.getReverseZIterator(5, 4) == 45, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseZEnd() - m_MainMatrix.getReverseZIterator(0, 1) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseZEnd() - m_MainMatrix.getReverseZIterator(0, 0) == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseZEnd() - m_MainMatrix.reverseZEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");

    // additional tests with "random" elements from same row/different rows
    QVERIFY2(m_MainMatrix.getReverseZIterator(5, 4) - m_MainMatrix.getReverseZIterator(7, 2) == 14, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(7, 2) - m_MainMatrix.getReverseZIterator(5, 4) == -14, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(5, 4) - m_MainMatrix.getReverseZIterator(5, 2) == -2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseZIterator(5, 2) - m_MainMatrix.getReverseZIterator(5, 4) == 2, "The difference operator does not work correctly, difference between iterators is wrong");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.reverseZEnd() - m_MainMatrix.reverseZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseZBegin() - m_MainMatrix.reverseZEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseZBegin() - m_MainMatrix.reverseZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseZEnd() - m_MainMatrix.reverseZEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");

    // test for empty iterator
    IntMatrixReverseZIterator emptyIt1{};
    IntMatrixReverseZIterator emptyIt2{};
    QVERIFY2(emptyIt1 - emptyIt2 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(emptyIt2 - emptyIt1 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(emptyIt1 - emptyIt1 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
}

void ReverseZIteratorTests::testDereferenceAsteriskOperator()
{
    // test reading element
    m_MainMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};
    QVERIFY2(*m_MainMatrix.getReverseZIterator(0, 0) == 1, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getReverseZIterator(0, 1) == -2, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getReverseZIterator(1, 2) == -6, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getReverseZIterator(3, 1) == 11, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.reverseZBegin() == -12, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");

    // test writing to element
    m_MainMatrix = {4, 3, -20};
    *m_MainMatrix.getReverseZIterator(0, 0) = 1;
    *m_MainMatrix.getReverseZIterator(0, 1) = -2;
    *m_MainMatrix.getReverseZIterator(1, 2) = -6;
    *m_MainMatrix.getReverseZIterator(3, 1) = 11;
    *m_MainMatrix.reverseZBegin() = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY2(m_MainMatrix.at(0, 1) == -2, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY2(m_MainMatrix.at(1, 2) == -6, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY2(m_MainMatrix.at(3, 1) == 11, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY2(m_MainMatrix.at(3, 2) == -12, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY(m_MainMatrix.at(2, 1) == -20);

    // additional tests
    m_MainMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    IntMatrixReverseZIterator readIter{m_MainMatrix.reverseZBegin()};
    m_MainMatrix.at(1, 0) = 10;
    readIter += 2;
    QVERIFY2(*readIter == 10, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");

    m_MainMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    IntMatrixReverseZIterator writeIter{m_MainMatrix.reverseZBegin()};
    writeIter += 2;
    *writeIter = 10;
    QVERIFY2(m_MainMatrix.at(1, 0) == 10, "The dereference (*) operator does not work correctly, the value is not correctly written to the pointed location");
}

void ReverseZIteratorTests::testDereferenceArrowOperator()
{
    // test reading element
    m_AuxStringMatrix = {4, 3, {"abc", "ba", "abcd", "jihgfedcba", "a", "gfedcba", "abcde", "ihgfedcba", "abcdefgh", "", "abcdefghijk", "fedcba"}};
    QVERIFY2(m_AuxStringMatrix.getReverseZIterator(0, 0)->size() == 3, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getReverseZIterator(0, 1)->size() == 2, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getReverseZIterator(1, 2)->size() == 7, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getReverseZIterator(3, 1)->size() == 11, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.reverseZBegin()->size() == 6, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");

    // test writing to element
    m_AuxStringMatrix = {4, 3, "zzz"};
    m_AuxStringMatrix.getReverseZIterator(0, 0)->assign("abc");
    m_AuxStringMatrix.getReverseZIterator(0, 1)->assign("ba");
    m_AuxStringMatrix.getReverseZIterator(1, 2)->assign("gfedcba");
    m_AuxStringMatrix.getReverseZIterator(3, 1)->assign("abcdefghijk");
    m_AuxStringMatrix.reverseZBegin()->assign("fedcba");
    QVERIFY2(m_AuxStringMatrix.at(0, 0) == "abc", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY2(m_AuxStringMatrix.at(0, 1) == "ba", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY2(m_AuxStringMatrix.at(1, 2) == "gfedcba", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY2(m_AuxStringMatrix.at(3, 1) == "abcdefghijk", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY2(m_AuxStringMatrix.at(3, 2) == "fedcba", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY(m_AuxStringMatrix.at(2, 1) == "zzz");

    // additional tests
    m_AuxStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mnop", "qr"}};
    StringMatrixReverseZIterator it{m_AuxStringMatrix.reverseZBegin()};
    m_AuxStringMatrix.at(1, 0) = "abcdefghi";
    it += 2;
    QVERIFY2(it->size() == 9, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");

    m_AuxStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    it = m_AuxStringMatrix.reverseZBegin();
    it += 2;
    it->assign("abcdefghi");
    QVERIFY2(m_AuxStringMatrix.at(1, 0) == "abcdefghi", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
}

void ReverseZIteratorTests::testDereferenceSquareBracketsOperator()
{
    // test reading element
    m_MainMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};

    IntMatrixReverseZIterator it{m_MainMatrix.reverseZBegin()};
    QVERIFY2(it[11] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[10] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[6] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[1] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getReverseZIterator(3, 1);
    QVERIFY2(it[10] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[9] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[5] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-1] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getReverseZIterator(1, 2);
    QVERIFY2(it[5] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[4] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-5] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-6] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getReverseZIterator(0, 1);
    QVERIFY2(it[1] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-4] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-9] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-10] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getReverseZIterator(0, 0);
    QVERIFY2(it[0] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-1] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-5] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-10] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-11] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    // test writing to element (before running a new scenario the matrix should be reset to its initial value value)
    m_MainMatrix = {4, 3, -20}; // initial

    it = m_MainMatrix.getReverseZIterator(0, 0);
    it[0] = 1;
    it[-1] = -2;
    it[-5] = -6;
    it[-10] = 11;
    it[-11] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(0, 1) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 2) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 1) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 2) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(2, 1) == -20);

    m_MainMatrix = {4, 3, -20}; // reset

    it = m_MainMatrix.getReverseZIterator(0, 1);
    it[1] = 1;
    it[0] = -2;
    it[-4] = -6;
    it[-9] = 11;
    it[-10] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(0, 1) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 2) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 1) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 2) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(2, 1) == -20);

    m_MainMatrix = {4, 3, -20}; // reset

    it = m_MainMatrix.getReverseZIterator(1, 2);
    it[5] = 1;
    it[4] = -2;
    it[0] = -6;
    it[-5] = 11;
    it[-6] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(0, 1) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 2) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 1) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 2) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(2, 1) == -20);

    m_MainMatrix = {4, 3, -20}; // reset

    it = m_MainMatrix.getReverseZIterator(3, 1);
    it[10] = 1;
    it[9] = -2;
    it[5] = -6;
    it[0] = 11;
    it[-1] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(0, 1) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 2) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 1) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 2) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(2, 1) == -20);

    m_MainMatrix = {4, 3, -20}; // reset

    it = m_MainMatrix.reverseZBegin();
    it[11] = 1;
    it[10] = -2;
    it[6] = -6;
    it[1] = 11;
    it[0] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(0, 1) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 2) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 1) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 2) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(2, 1) == -20);
}

void ReverseZIteratorTests::testStdCount()
{
    using namespace std;

    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};

    int matchCount{count(m_MainMatrix.reverseZBegin(), m_MainMatrix.reverseZEnd(), 2)};
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseZBegin(), m_MainMatrix.reverseZEnd(), -5);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseZIterator(1, 4), m_MainMatrix.getReverseZIterator(0, 3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseZIterator(2, 0), m_MainMatrix.getReverseZIterator(0, 2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseZIterator(2, 0), m_MainMatrix.getReverseZIterator(0, 3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseZIterator(1, 4), m_MainMatrix.getReverseZIterator(0, 2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseZBegin(), m_MainMatrix.getReverseZIterator(2, 3), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseZIterator(2, 3), m_MainMatrix.reverseZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseZBegin(), m_MainMatrix.getReverseZIterator(2, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseZIterator(2, 2), m_MainMatrix.reverseZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseZIterator(9), m_MainMatrix.getReverseZIterator(2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseZIterator(10), m_MainMatrix.getReverseZIterator(2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseZIterator(9), m_MainMatrix.getReverseZIterator(3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseZIterator(10), m_MainMatrix.getReverseZIterator(3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseZBegin(), m_MainMatrix.getReverseZIterator(13), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseZIterator(13), m_MainMatrix.reverseZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseZBegin(), m_MainMatrix.getReverseZIterator(12), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseZIterator(12), m_MainMatrix.reverseZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseZRowBegin(1), m_MainMatrix.reverseZRowEnd(1), 5);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseZRowEnd(3), m_MainMatrix.reverseZRowEnd(0), 8);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseZRowBegin(3), m_MainMatrix.reverseZRowEnd(3), 9);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseZRowBegin(3), m_MainMatrix.reverseZRowEnd(2), 9);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseZRowEnd(1), m_MainMatrix.reverseZEnd(), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseZBegin(), m_MainMatrix.reverseZRowEnd(1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseZRowBegin(2), m_MainMatrix.reverseZEnd(), 1);
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseZBegin(), m_MainMatrix.reverseZRowBegin(2), 1);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
}

void ReverseZIteratorTests::testStdFind()
{
    using namespace std;

    // test finding elements in specific ranges within unempty matrix
    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, -2, 2, 8, 9, -7, 7, 2, 9, 11}};

    QVERIFY2(find(m_MainMatrix.reverseZBegin(), m_MainMatrix.reverseZEnd(), 5) != m_MainMatrix.reverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZBegin(), m_MainMatrix.reverseZEnd(), 10) == m_MainMatrix.reverseZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZRowBegin(1), m_MainMatrix.reverseZRowEnd(1), 6) != m_MainMatrix.reverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZRowBegin(1), m_MainMatrix.reverseZRowEnd(1), 5) != m_MainMatrix.reverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZRowBegin(1), m_MainMatrix.reverseZRowEnd(1), 8) != m_MainMatrix.reverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZRowBegin(1), m_MainMatrix.reverseZRowEnd(1), -1) == m_MainMatrix.reverseZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZRowBegin(1), m_MainMatrix.reverseZRowEnd(1), 1) == m_MainMatrix.reverseZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZRowBegin(1), m_MainMatrix.reverseZRowEnd(1), 10) == m_MainMatrix.reverseZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZRowBegin(1), m_MainMatrix.reverseZEnd(), 6) != m_MainMatrix.reverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZRowBegin(1), m_MainMatrix.reverseZEnd(), -1) != m_MainMatrix.reverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZRowBegin(1), m_MainMatrix.reverseZEnd(), 3) != m_MainMatrix.reverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZRowBegin(1), m_MainMatrix.reverseZEnd(), -2) == m_MainMatrix.reverseZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZRowBegin(1), m_MainMatrix.reverseZEnd(), 10) == m_MainMatrix.reverseZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZBegin(), m_MainMatrix.reverseZRowEnd(1), 11) != m_MainMatrix.reverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZBegin(), m_MainMatrix.reverseZRowEnd(1), 5) != m_MainMatrix.reverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZBegin(), m_MainMatrix.reverseZRowEnd(1), 0) != m_MainMatrix.reverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZBegin(), m_MainMatrix.reverseZRowEnd(1), 1) == m_MainMatrix.reverseZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZBegin(), m_MainMatrix.reverseZRowEnd(1), 10) == m_MainMatrix.reverseZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseZIterator(3, 1), m_MainMatrix.getReverseZIterator(1, 3), 7) != m_MainMatrix.getReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseZIterator(3, 1), m_MainMatrix.getReverseZIterator(1, 3), -7) != m_MainMatrix.getReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseZIterator(3, 1), m_MainMatrix.getReverseZIterator(1, 3), -2) != m_MainMatrix.getReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseZIterator(3, 1), m_MainMatrix.getReverseZIterator(1, 3), -1) == m_MainMatrix.getReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseZIterator(3, 1), m_MainMatrix.getReverseZIterator(1, 3), 11) == m_MainMatrix.getReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseZIterator(3, 1), m_MainMatrix.getReverseZIterator(1, 3), 10) == m_MainMatrix.getReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseZIterator(1, 3), m_MainMatrix.reverseZEnd(), 0) != m_MainMatrix.reverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseZIterator(1, 3), m_MainMatrix.reverseZEnd(), -1) != m_MainMatrix.reverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseZIterator(1, 3), m_MainMatrix.reverseZEnd(), 4) != m_MainMatrix.reverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseZIterator(1, 3), m_MainMatrix.reverseZEnd(), 11) == m_MainMatrix.reverseZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseZIterator(1, 3), m_MainMatrix.reverseZEnd(), 10) == m_MainMatrix.reverseZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZBegin(), m_MainMatrix.getReverseZIterator(3, 1), 11) != m_MainMatrix.getReverseZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZBegin(), m_MainMatrix.getReverseZIterator(3, 1), 2) != m_MainMatrix.getReverseZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZBegin(), m_MainMatrix.getReverseZIterator(3, 1), 9) != m_MainMatrix.getReverseZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZBegin(), m_MainMatrix.getReverseZIterator(3, 1), 0) == m_MainMatrix.getReverseZIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseZBegin(), m_MainMatrix.getReverseZIterator(3, 1), 10) == m_MainMatrix.getReverseZIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

    // other tests
    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};
    IntMatrixReverseZIterator it{find(m_MainMatrix.reverseZBegin(), m_MainMatrix.reverseZEnd(), 4)};
    ++it;
    QVERIFY2(*it == 1, "The iterator doesn't work correctly with std::find, incorrect next element returned");

    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};
    QVERIFY2(find(m_MainMatrix.reverseZBegin(), m_MainMatrix.reverseZEnd(), 10) == m_MainMatrix.reverseZEnd(), "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix");

    it = m_MainMatrix.reverseZBegin();
    while(it != m_MainMatrix.reverseZEnd())
    {
        it = find(it, m_MainMatrix.reverseZEnd(), 9);

        if (it != m_MainMatrix.reverseZEnd())
        {
            *it = 10;
        }
    }
    int expectedNumber{std::count(m_MainMatrix.reverseZBegin(), m_MainMatrix.reverseZEnd(), 10)};
    QVERIFY2(expectedNumber == 3, "The iterator doesn't work properly with std::find, element values haven't been correctly replaced");
}

void ReverseZIteratorTests::testStdSort()
{
    m_MainMatrix = {4, 5, {
                      -1,  1, 3, 1, 4,
                       5,  9, 8, 0, 6,
                       2, -2, 2, 8, 9,
                      -7,  7, 2, 9, 11
                   }};

    for (int row{0}; row<m_MainMatrix.getNrOfRows(); ++row)
    {
        std::sort(m_MainMatrix.reverseZRowBegin(row), m_MainMatrix.reverseZRowEnd(row));
    }

    QVERIFY2(m_MainMatrix.at(0, 0) == 4 && m_MainMatrix.at(0, 1) == 3 && m_MainMatrix.at(0, 2) == 1 && m_MainMatrix.at(0, 3) == 1 && m_MainMatrix.at(0, 4) == -1 &&
             m_MainMatrix.at(1, 0) ==  9 && m_MainMatrix.at(1, 1) == 8 && m_MainMatrix.at(1, 2) == 6 && m_MainMatrix.at(1, 3) == 5 && m_MainMatrix.at(1, 4) == 0 &&
             m_MainMatrix.at(2, 0) == 9 && m_MainMatrix.at(2, 1) == 8 && m_MainMatrix.at(2, 2) == 2 && m_MainMatrix.at(2, 3) == 2 && m_MainMatrix.at(2, 4) == -2 &&
             m_MainMatrix.at(3, 0) == 11 && m_MainMatrix.at(3, 1) == 9 && m_MainMatrix.at(3, 2) == 7 && m_MainMatrix.at(3, 3) == 2 && m_MainMatrix.at(3, 4) == -7,

             "The iterator objects don't work correctly, the per row sorting has not been done properly");

    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, -2, 2, 8, 9, -7, 7, 2, 9, 11}};

    std::sort(m_MainMatrix.reverseZBegin(), m_MainMatrix.reverseZEnd());

    QVERIFY2(m_MainMatrix.at(0, 0) == 11 && m_MainMatrix.at(0, 1) == 9 && m_MainMatrix.at(0, 2) == 9 && m_MainMatrix.at(0, 3) == 9 && m_MainMatrix.at(0, 4) == 8 &&
             m_MainMatrix.at(1, 0) ==  8 && m_MainMatrix.at(1, 1) ==  7 && m_MainMatrix.at(1, 2) ==  6 && m_MainMatrix.at(1, 3) == 5 && m_MainMatrix.at(1, 4) == 4 &&
             m_MainMatrix.at(2, 0) ==  3 && m_MainMatrix.at(2, 1) ==  2 && m_MainMatrix.at(2, 2) ==  2 && m_MainMatrix.at(2, 3) == 2 && m_MainMatrix.at(2, 4) == 1 &&
             m_MainMatrix.at(3, 0) ==  1 && m_MainMatrix.at(3, 1) ==  0 && m_MainMatrix.at(3, 2) ==  -1 && m_MainMatrix.at(3, 3) == -2 && m_MainMatrix.at(3, 4) == -7,

             "The iterator objects don't work correctly, the matrix has not been sorted properly");

    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, (0), 6, 2, -2, 2, 8, 9, -7, (7), 2, 9, 11}};

    std::sort(m_MainMatrix.getReverseZIterator(3, 1), m_MainMatrix.getReverseZIterator(1, 3));

    QVERIFY2(m_MainMatrix.at(0, 0) == -1 && m_MainMatrix.at(0, 1) == 1   && m_MainMatrix.at(0, 2) == 3 && m_MainMatrix.at(0, 3) == 1    && m_MainMatrix.at(0, 4) ==  4 &&
             m_MainMatrix.at(1, 0) ==  5 && m_MainMatrix.at(1, 1) == 9   && m_MainMatrix.at(1, 2) == 8 && m_MainMatrix.at(1, 3) == (0) && m_MainMatrix.at(1, 4) == 9 &&
             m_MainMatrix.at(2, 0) ==  8 && m_MainMatrix.at(2, 1) == 7   && m_MainMatrix.at(2, 2) == 6 && m_MainMatrix.at(2, 3) == 2    && m_MainMatrix.at(2, 4) ==  2 &&
             m_MainMatrix.at(3, 0) ==  -2 && m_MainMatrix.at(3, 1) == (-7) && m_MainMatrix.at(3, 2) == 2 && m_MainMatrix.at(3, 3) == 9    && m_MainMatrix.at(3, 4) == 11,

             "The iterator objects don't work correctly, the matrix has not been sorted properly");

    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, (-2), 2, 8, 9, -7, 7, 2, 9, (11)}};

    std::sort(m_MainMatrix.reverseZBegin(), m_MainMatrix.getReverseZIterator(2, 1));

    QVERIFY2(m_MainMatrix.at(0, 0) == -1 && m_MainMatrix.at(0, 1) == 1    && m_MainMatrix.at(0, 2) == 3 && m_MainMatrix.at(0, 3) == 1 && m_MainMatrix.at(0, 4) == 4 &&
             m_MainMatrix.at(1, 0) ==  5 && m_MainMatrix.at(1, 1) == 9    && m_MainMatrix.at(1, 2) == 8 && m_MainMatrix.at(1, 3) == 0 && m_MainMatrix.at(1, 4) == 6 &&
             m_MainMatrix.at(2, 0) ==  2 && m_MainMatrix.at(2, 1) == (-2) && m_MainMatrix.at(2, 2) == 11 && m_MainMatrix.at(2, 3) == 9 && m_MainMatrix.at(2, 4) == 9 &&
             m_MainMatrix.at(3, 0) == 8 && m_MainMatrix.at(3, 1) == 7    && m_MainMatrix.at(3, 2) == 2 && m_MainMatrix.at(3, 3) == 2 && m_MainMatrix.at(3, 4) == (-7),

             "The iterator objects don't work correctly, the matrix has not been sorted properly");

    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, (-2), 2, 8, 9, -7, 7, 2, 9, 11}};

    std::sort(m_MainMatrix.getReverseZIterator(2, 1), m_MainMatrix.reverseZEnd());

    QVERIFY2(m_MainMatrix.at(0, 0) == 9 && m_MainMatrix.at(0, 1) == 8    && m_MainMatrix.at(0, 2) == 6  && m_MainMatrix.at(0, 3) == 5 && m_MainMatrix.at(0, 4) == 4 &&
             m_MainMatrix.at(1, 0) ==  3 && m_MainMatrix.at(1, 1) == 2    && m_MainMatrix.at(1, 2) == 1  && m_MainMatrix.at(1, 3) == 1 && m_MainMatrix.at(1, 4) == 0 &&
             m_MainMatrix.at(2, 0) ==  -1 && m_MainMatrix.at(2, 1) == (-2) && m_MainMatrix.at(2, 2) == 2 && m_MainMatrix.at(2, 3) == 8 && m_MainMatrix.at(2, 4) == 9 &&
             m_MainMatrix.at(3, 0) ==  -7 && m_MainMatrix.at(3, 1) == 7    && m_MainMatrix.at(3, 2) == 2  && m_MainMatrix.at(3, 3) == 9 && m_MainMatrix.at(3, 4) == 11,

             "The iterator objects don't work correctly, the matrix has not been sorted properly");
}

QTEST_APPLESS_MAIN(ReverseZIteratorTests)

#include "tst_reverseziteratortests.moc"
