#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixConstZIterator = Matrix<int>::ConstZIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixConstZIterator = Matrix<std::string>::ConstZIterator;

class ConstZIteratorTests : public QObject
{
    Q_OBJECT

public:
    ConstZIteratorTests();
    ~ConstZIteratorTests();

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

private:
    IntMatrix m_MainMatrix;
    IntMatrix m_AuxIntMatrix;
    StringMatrix m_AuxStringMatrix;
};

ConstZIteratorTests::ConstZIteratorTests()
{
}

ConstZIteratorTests::~ConstZIteratorTests()
{
}

void ConstZIteratorTests::testIteratorCreation()
{
    m_MainMatrix = {9, 8, -5};

    IntMatrixConstZIterator it{m_MainMatrix.constZBegin()};
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constZEnd();
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constZRowBegin(0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constZRowBegin(1);
    QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constZRowBegin(4);
    QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constZRowBegin(7);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constZRowBegin(8);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constZRowEnd(0);
    QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constZRowEnd(1);
    QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constZRowEnd(4);
    QVERIFY2(it.getCurrentRowNr() == 5 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constZRowEnd(7);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constZRowEnd(8);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstZIterator(0, 0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstZIterator(0, 1);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstZIterator(5, 4);
    QVERIFY2(it.getCurrentRowNr() == 5 && it.getCurrentColumnNr() == 4 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstZIterator(8, 6);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 6 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstZIterator(8, 7);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstZIterator(0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstZIterator(1);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstZIterator(44);
    QVERIFY2(it.getCurrentRowNr() == 5 && it.getCurrentColumnNr() == 4 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstZIterator(70);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 6 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstZIterator(71);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // test iterator creation for empty matrix
    m_MainMatrix.clear();
    it = m_MainMatrix.constZBegin();
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constZEnd();
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // test empty iterator creation (not bound to any matrix) - an empty iterator should be valid for any empty matrix
    IntMatrixConstZIterator emptyIt;
    QVERIFY2(emptyIt.getCurrentRowNr() == -1 && emptyIt.getCurrentColumnNr() == -1 && emptyIt.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // additional test
    m_MainMatrix = {9, 8, -5};
    m_AuxIntMatrix = {9, 8, -5};
    it = m_MainMatrix.getConstZIterator(5, 4);
    QVERIFY(!it.isValidWithMatrix(m_AuxIntMatrix));
    m_AuxIntMatrix.clear();
    QVERIFY(!it.isValidWithMatrix(m_AuxIntMatrix));
    it = m_AuxIntMatrix.constZBegin();
    QVERIFY(!it.isValidWithMatrix(m_MainMatrix));
    it = m_AuxIntMatrix.constZEnd();
    QVERIFY(!it.isValidWithMatrix(m_MainMatrix));
    m_MainMatrix.clear();
    it = m_MainMatrix.constZBegin();
    QVERIFY(it.isValidWithMatrix(m_AuxIntMatrix)); // an iterator of an empty matrix is valid with any other empty matrix
    it = m_MainMatrix.constZEnd();
    QVERIFY(it.isValidWithMatrix(m_AuxIntMatrix));
}

void ConstZIteratorTests::testIteratorsAreEqual()
{

    m_MainMatrix = {9, 8, -5};

    // test different iterators for equality
    QVERIFY2((m_MainMatrix.constZBegin() == m_MainMatrix.getConstZIterator(0, 0) && !(m_MainMatrix.constZBegin() != m_MainMatrix.getConstZIterator(0, 0))), "The two iterators are not equal");
    QVERIFY2((m_MainMatrix.getConstZIterator(0) == m_MainMatrix.getConstZIterator(0, 0)) && !(m_MainMatrix.getConstZIterator(0) != m_MainMatrix.getConstZIterator(0, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getConstZIterator(1) == m_MainMatrix.getConstZIterator(0, 1)) && !(m_MainMatrix.getConstZIterator(1) != m_MainMatrix.getConstZIterator(0, 1)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getConstZIterator(44) == m_MainMatrix.getConstZIterator(5, 4)) && !(m_MainMatrix.getConstZIterator(44) != m_MainMatrix.getConstZIterator(5, 4)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getConstZIterator(70) == m_MainMatrix.getConstZIterator(8, 6)) && !(m_MainMatrix.getConstZIterator(70) != m_MainMatrix.getConstZIterator(8, 6)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getConstZIterator(71) == m_MainMatrix.getConstZIterator(8, 7)) && !(m_MainMatrix.getConstZIterator(71) != m_MainMatrix.getConstZIterator(8, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constZRowBegin(0) == m_MainMatrix.getConstZIterator(0, 0)) && !(m_MainMatrix.constZRowBegin(0) != m_MainMatrix.getConstZIterator(0, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constZRowBegin(1) == m_MainMatrix.getConstZIterator(1, 0)) && !(m_MainMatrix.constZRowBegin(1) != m_MainMatrix.getConstZIterator(1, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constZRowBegin(5) == m_MainMatrix.getConstZIterator(5, 0)) && !(m_MainMatrix.constZRowBegin(5) != m_MainMatrix.getConstZIterator(5, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constZRowBegin(7) == m_MainMatrix.getConstZIterator(7, 0)) && !(m_MainMatrix.constZRowBegin(7) != m_MainMatrix.getConstZIterator(7, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constZRowBegin(8) == m_MainMatrix.getConstZIterator(8, 0)) && !(m_MainMatrix.constZRowBegin(8) != m_MainMatrix.getConstZIterator(8, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constZRowEnd(0) == m_MainMatrix.getConstZIterator(1, 0)) && !(m_MainMatrix.constZRowEnd(0) != m_MainMatrix.getConstZIterator(1, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constZRowEnd(1) == m_MainMatrix.getConstZIterator(2, 0)) && !(m_MainMatrix.constZRowEnd(1) != m_MainMatrix.getConstZIterator(2, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constZRowEnd(5) == m_MainMatrix.getConstZIterator(6, 0)) && !(m_MainMatrix.constZRowEnd(5) != m_MainMatrix.getConstZIterator(6, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constZRowEnd(7) == m_MainMatrix.getConstZIterator(8, 0)) && !(m_MainMatrix.constZRowEnd(7) != m_MainMatrix.getConstZIterator(8, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constZRowEnd(8) == m_MainMatrix.constZEnd()) && !(m_MainMatrix.constZRowEnd(8) != m_MainMatrix.constZEnd()), "The two iterators are NOT equal");

    // test iterator equality to itself
    IntMatrixConstZIterator it{m_MainMatrix.constZBegin()};
    QVERIFY2((it == it) && (it == m_MainMatrix.constZBegin()) && !(it != it) && !(it != m_MainMatrix.constZBegin()), "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getConstZIterator(0, 1);
    QVERIFY2((it == it) && (it == m_MainMatrix.getConstZIterator(0, 1)) && !(it != it) && !(it != m_MainMatrix.getConstZIterator(0, 1)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getConstZIterator(5, 4);
    QVERIFY2((it == it) && (it == m_MainMatrix.getConstZIterator(5, 4)) && !(it != it) && !(it != m_MainMatrix.getConstZIterator(5, 4)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getConstZIterator(8, 6);
    QVERIFY2((it == it) && (it == m_MainMatrix.getConstZIterator(8, 6)) && !(it != it) && !(it != m_MainMatrix.getConstZIterator(8, 6)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getConstZIterator(8, 7);
    QVERIFY2((it == it) && (it == m_MainMatrix.getConstZIterator(8, 7)) && !(it != it) && !(it != m_MainMatrix.getConstZIterator(8, 7)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.constZEnd();
    QVERIFY2((it == it) && (it == m_MainMatrix.constZEnd()) && !(it != it) && !(it != m_MainMatrix.constZEnd()),  "The iterator is NOT equal to itself and/or to source iterator");

    // test empty matrix iterator equality
    m_MainMatrix.clear();
    QVERIFY2((m_MainMatrix.constZBegin() == m_MainMatrix.constZEnd()) && !(m_MainMatrix.constZBegin() != m_MainMatrix.constZEnd()), "The two iterators are NOT equal");
}

void ConstZIteratorTests::testIteratorsAreNotEqual()
{
    m_MainMatrix = {9, 8, -5};

    QVERIFY2((m_MainMatrix.constZBegin() != m_MainMatrix.getConstZIterator(0, 1)) && !(m_MainMatrix.constZBegin() == m_MainMatrix.getConstZIterator(0, 1)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstZIterator(0, 1) != m_MainMatrix.getConstZIterator(0, 2)) && !(m_MainMatrix.getConstZIterator(0, 1) == m_MainMatrix.getConstZIterator(0, 2)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstZIterator(0, 2) != m_MainMatrix.getConstZIterator(5, 4)) && !(m_MainMatrix.getConstZIterator(0, 2) == m_MainMatrix.getConstZIterator(5, 4)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstZIterator(5, 4) != m_MainMatrix.getConstZIterator(8, 6)) && !(m_MainMatrix.getConstZIterator(5, 4) == m_MainMatrix.getConstZIterator(8, 6)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstZIterator(8, 6) != m_MainMatrix.getConstZIterator(8, 7)) && !(m_MainMatrix.getConstZIterator(8, 6) == m_MainMatrix.getConstZIterator(8, 7)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstZIterator(8, 7) != m_MainMatrix.constZEnd()) && !(m_MainMatrix.getConstZIterator(8, 7) == m_MainMatrix.constZEnd()), "The two iterators are NOT different");
}

void ConstZIteratorTests::testSmallerThanOperator()
{
    m_MainMatrix = {9, 8, -5};

    QVERIFY2((m_MainMatrix.constZBegin() < m_MainMatrix.getConstZIterator(0, 1)) && !(m_MainMatrix.constZBegin() >= m_MainMatrix.getConstZIterator(0, 1)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(0, 1) < m_MainMatrix.getConstZIterator(0, 2)) && !(m_MainMatrix.getConstZIterator(0, 1) >= m_MainMatrix.getConstZIterator(0, 2)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(0, 2) < m_MainMatrix.getConstZIterator(5, 4)) && !(m_MainMatrix.getConstZIterator(0, 2) >= m_MainMatrix.getConstZIterator(5, 4)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(5, 4) < m_MainMatrix.getConstZIterator(8, 6)) && !(m_MainMatrix.getConstZIterator(5, 4) >= m_MainMatrix.getConstZIterator(8, 6)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(8, 6) < m_MainMatrix.getConstZIterator(8, 7)) && !(m_MainMatrix.getConstZIterator(8, 6) >= m_MainMatrix.getConstZIterator(8, 7)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(8, 7) < m_MainMatrix.constZEnd()) && !(m_MainMatrix.getConstZIterator(8, 7) >= m_MainMatrix.constZEnd()), "The first iterator is NOT smaller than the second iterator");
}

void ConstZIteratorTests::testSmallerThanOrEqualToOperator()
{
    m_MainMatrix = {9, 8, -5};

    // test operator with different iterators
    QVERIFY2((m_MainMatrix.constZBegin() <= m_MainMatrix.constZBegin()) && !(m_MainMatrix.constZBegin() > m_MainMatrix.constZEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.constZBegin() <= m_MainMatrix.getConstZIterator(0, 1)) && !(m_MainMatrix.getConstZIterator(8, 7) > m_MainMatrix.constZEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(0, 1) <= m_MainMatrix.getConstZIterator(0, 1)) && !(m_MainMatrix.getConstZIterator(0, 1) > m_MainMatrix.getConstZIterator(0, 1)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(0, 1) <= m_MainMatrix.getConstZIterator(0, 2)) && !(m_MainMatrix.getConstZIterator(0, 1) > m_MainMatrix.getConstZIterator(0, 2)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(0, 2) <= m_MainMatrix.getConstZIterator(0, 2)) && !(m_MainMatrix.getConstZIterator(0, 2) > m_MainMatrix.getConstZIterator(0, 2)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(0, 2) <= m_MainMatrix.getConstZIterator(5, 4)) && !(m_MainMatrix.getConstZIterator(0, 2) > m_MainMatrix.getConstZIterator(5, 4)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(5, 4) <= m_MainMatrix.getConstZIterator(5, 4)) && !(m_MainMatrix.getConstZIterator(5, 4) > m_MainMatrix.getConstZIterator(5, 4)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(5, 4) <= m_MainMatrix.getConstZIterator(8, 6)) && !(m_MainMatrix.getConstZIterator(5, 4) > m_MainMatrix.getConstZIterator(8, 6)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(8, 6) <= m_MainMatrix.getConstZIterator(8, 6)) && !(m_MainMatrix.getConstZIterator(8, 6) > m_MainMatrix.getConstZIterator(8, 6)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(8, 6) <= m_MainMatrix.getConstZIterator(8, 7)) && !(m_MainMatrix.getConstZIterator(8, 6) > m_MainMatrix.getConstZIterator(8, 7)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(8, 7) <= m_MainMatrix.getConstZIterator(8, 7)) && !(m_MainMatrix.getConstZIterator(8, 7) > m_MainMatrix.getConstZIterator(8, 7)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(8, 7) <= m_MainMatrix.constZEnd()) && !(m_MainMatrix.getConstZIterator(8, 7) > m_MainMatrix.constZEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.constZEnd() <= m_MainMatrix.constZEnd()) && !(m_MainMatrix.constZEnd() > m_MainMatrix.constZEnd()), "The first iterator is NOT smaller than or equal to the second iterator");

    // test if iterator is smaller than or equal to itself
    IntMatrixConstZIterator it{m_MainMatrix.constZBegin()};
    QVERIFY2((it <= it) && (it <= m_MainMatrix.constZBegin()) && !(it > it) && !(it > m_MainMatrix.constZBegin()),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstZIterator(0, 1);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getConstZIterator(0, 1)) && !(it > it) && !(it > m_MainMatrix.getConstZIterator(0, 1)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstZIterator(5, 4);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getConstZIterator(5, 4)) && !(it > it) && !(it > m_MainMatrix.getConstZIterator(5, 4)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstZIterator(8, 6);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getConstZIterator(8, 6)) && !(it > it) && !(it > m_MainMatrix.getConstZIterator(8, 6)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstZIterator(8, 7);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getConstZIterator(8, 7) && !(it > it) && !(it > m_MainMatrix.getConstZIterator(8, 7))),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.constZEnd();
    QVERIFY2((it <= it) && (it <= m_MainMatrix.constZEnd()) && !(it > it) && !(it > m_MainMatrix.constZEnd()),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");

    // test with empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.constZBegin() <= m_MainMatrix.constZEnd(), "The first iterator is NOT smaller than or equal to the second iterator");
}

void ConstZIteratorTests::testGreaterThanOperator()
{
    m_MainMatrix = {9, 8, -5};

    QVERIFY2((m_MainMatrix.constZEnd() > m_MainMatrix.getConstZIterator(8, 7)) && !(m_MainMatrix.constZEnd() <= m_MainMatrix.getConstZIterator(8, 7)), "TThe first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(8, 7) > m_MainMatrix.getConstZIterator(8, 6)) && !(m_MainMatrix.getConstZIterator(8, 7) <= m_MainMatrix.getConstZIterator(8, 6)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(8, 6) > m_MainMatrix.getConstZIterator(5, 4)) && !(m_MainMatrix.getConstZIterator(8, 6) <= m_MainMatrix.getConstZIterator(5, 4)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(5, 4) > m_MainMatrix.getConstZIterator(0, 2)) && !(m_MainMatrix.getConstZIterator(5, 4) <= m_MainMatrix.getConstZIterator(0, 2)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(0, 2) > m_MainMatrix.getConstZIterator(0, 1)) && !(m_MainMatrix.getConstZIterator(0, 2) <= m_MainMatrix.getConstZIterator(0, 1)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(0, 1) > m_MainMatrix.constZBegin()) && !(m_MainMatrix.getConstZIterator(0, 1) <= m_MainMatrix.constZBegin()), "The first iterator is NOT greater than the second iterator");
}

void ConstZIteratorTests::testGreaterThanOrEqualToOperator()
{
    m_MainMatrix = {9, 8, -5};

    // test operator with different iterators
    QVERIFY2((m_MainMatrix.constZEnd() >= m_MainMatrix.constZEnd()) && !(m_MainMatrix.constZEnd() < m_MainMatrix.constZEnd()), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.constZEnd() >= m_MainMatrix.getConstZIterator(8, 7)) && !(m_MainMatrix.constZEnd() < m_MainMatrix.getConstZIterator(8, 7)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(8, 7) >= m_MainMatrix.getConstZIterator(8, 7)) && !(m_MainMatrix.getConstZIterator(8, 7) < m_MainMatrix.getConstZIterator(8, 7)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(8, 7) >= m_MainMatrix.getConstZIterator(8, 6)) && !(m_MainMatrix.getConstZIterator(8, 7) < m_MainMatrix.getConstZIterator(8, 6)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(8, 6) >= m_MainMatrix.getConstZIterator(8, 6)) && !(m_MainMatrix.getConstZIterator(8, 6) < m_MainMatrix.getConstZIterator(8, 6)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(8, 6) >= m_MainMatrix.getConstZIterator(5, 4)) && !(m_MainMatrix.getConstZIterator(8, 6) < m_MainMatrix.getConstZIterator(5, 4)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(5, 4) >= m_MainMatrix.getConstZIterator(5, 4)) && !(m_MainMatrix.getConstZIterator(5, 4) < m_MainMatrix.getConstZIterator(5, 4)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(5, 4) >= m_MainMatrix.getConstZIterator(0, 2)) && !(m_MainMatrix.getConstZIterator(5, 4) < m_MainMatrix.getConstZIterator(0, 2)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(0, 2) >= m_MainMatrix.getConstZIterator(0, 2)) && !(m_MainMatrix.getConstZIterator(0, 2) < m_MainMatrix.getConstZIterator(0, 2)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(0, 2) >= m_MainMatrix.getConstZIterator(0, 1)) && !(m_MainMatrix.getConstZIterator(0, 2) < m_MainMatrix.getConstZIterator(0, 1)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(0, 1) >= m_MainMatrix.getConstZIterator(0, 1)) && !(m_MainMatrix.getConstZIterator(0, 1) < m_MainMatrix.getConstZIterator(0, 1)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstZIterator(0, 1) >= m_MainMatrix.constZBegin()) && !(m_MainMatrix.getConstZIterator(0, 1) < m_MainMatrix.constZBegin()), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.constZBegin() >= m_MainMatrix.constZBegin()) && !(m_MainMatrix.constZBegin() < m_MainMatrix.constZBegin()), "The first iterator is NOT greater than or equal to the second iterator");

    // test if iterator is greater than or equal to itself
    IntMatrixConstZIterator it{m_MainMatrix.constZEnd()};
    QVERIFY2((it >= it) && (it >= m_MainMatrix.constZEnd()) && !(it < it) && !(it < m_MainMatrix.constZEnd()),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstZIterator(8, 7);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getConstZIterator(8, 7)) && !(it < it) && !(it < m_MainMatrix.getConstZIterator(8, 7)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstZIterator(8, 6);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getConstZIterator(8, 6)) && !(it < it) && !(it < m_MainMatrix.getConstZIterator(8, 6)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstZIterator(5, 4);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getConstZIterator(5, 4)) && !(it < it) && !(it < m_MainMatrix.getConstZIterator(5, 4)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstZIterator(0, 1);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getConstZIterator(0, 1)) && !(it < it) && !(it < m_MainMatrix.getConstZIterator(0, 1)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.constZBegin();
    QVERIFY2((it >= it) && (it >= m_MainMatrix.constZBegin()) && !(it < it) && !(it < m_MainMatrix.constZBegin()),  "The iterator is NOT greater than or equal to itself and/or the source iterator");

    // test with empty matrix
    m_MainMatrix.clear();
    QVERIFY2((m_MainMatrix.constZBegin() >= m_MainMatrix.constZEnd()) && !(m_MainMatrix.constZBegin() < m_MainMatrix.constZEnd()), "The first iterator is NOT greater than or equal to the second iterator");
}

void ConstZIteratorTests::testIncrementOperators()
{
    m_MainMatrix = {9, 8, -5};

    // pre-increment
    IntMatrixConstZIterator it{m_MainMatrix.constZBegin()};
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 1), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 2), "Incorrect pre-incrementation");
    it = m_MainMatrix.getConstZIterator(4, 6);
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(4, 7), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 0), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 1), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 2), "Incorrect pre-incrementation");
    it = m_MainMatrix.getConstZIterator(5, 4);
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 5), "Incorrect pre-incrementation");
    it = m_MainMatrix.getConstZIterator(8, 6);
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 7), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.constZEnd(), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.constZEnd(), "Incorrect pre-incrementation");

    // post-increment
    it = m_MainMatrix.constZBegin();
    it++;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 1), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 2), "Incorrect post-incrementation");
    it = m_MainMatrix.getConstZIterator(4, 6);
    it++;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(4, 7), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 0), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 1), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 2), "Incorrect post-incrementation");
    it = m_MainMatrix.getConstZIterator(5, 4);
    it++;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 5), "Incorrect post-incrementation");
    it = m_MainMatrix.getConstZIterator(8, 6);
    it++;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 7), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.constZEnd(), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.constZEnd(), "Incorrect post-incrementation");

    // test a combination of "pre" and "post" behaviors
    IntMatrixConstZIterator srcIt{m_MainMatrix.getConstZIterator(5, 4)};
    IntMatrixConstZIterator destIt{++(++srcIt)};
    QVERIFY2(srcIt == m_MainMatrix.getConstZIterator(5, 5) && destIt == m_MainMatrix.getConstZIterator(5, 6), "Incorrect pre-pre-incrementation");
    srcIt = m_MainMatrix.getConstZIterator(5, 4);
    destIt = (srcIt++)++;
    QVERIFY2(srcIt == m_MainMatrix.getConstZIterator(5, 5) && destIt == m_MainMatrix.getConstZIterator(5, 4), "Incorrect post-post-incrementation");
    srcIt = m_MainMatrix.getConstZIterator(5, 4);
    destIt = (++srcIt)++;
    QVERIFY2(srcIt == m_MainMatrix.getConstZIterator(5, 5) && destIt == m_MainMatrix.getConstZIterator(5, 5), "Incorrect post-pre-incrementation");
    srcIt = m_MainMatrix.getConstZIterator(5, 4);
    destIt = ++(srcIt++);
    QVERIFY2(srcIt == m_MainMatrix.getConstZIterator(5, 5) && destIt == m_MainMatrix.getConstZIterator(5, 5), "Incorrect pre-post-incrementation");
}

void ConstZIteratorTests::testDecrementOperators()
{
    m_MainMatrix = {9, 8, -5};

    // pre-decrement
    IntMatrixConstZIterator it{m_MainMatrix.constZEnd()};
    --it;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 7), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 6), "Incorrect pre-decrementation");
    it = m_MainMatrix.getConstZIterator(5, 5);
    --it;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 4), "Incorrect pre-decrementation");
    it = m_MainMatrix.getConstZIterator(5, 2);
    --it;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 1), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 0), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(4, 7), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(4, 6), "Incorrect pre-decrementation");
    it = m_MainMatrix.getConstZIterator(0, 2);
    --it;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 1), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.constZBegin(), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.constZBegin(), "Incorrect pre-decrementation");


    // post-decrement
    it = m_MainMatrix.constZEnd();
    it--;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 7), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 6), "Incorrect post-decrementation");
    it = m_MainMatrix.getConstZIterator(5, 5);
    it--;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 4), "Incorrect post-decrementation");
    it = m_MainMatrix.getConstZIterator(5, 2);
    it--;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 1), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 0), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(4, 7), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(4, 6), "Incorrect post-decrementation");
    it = m_MainMatrix.getConstZIterator(0, 2);
    it--;
    QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 1), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.constZBegin(), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.constZBegin(), "Incorrect post-decrementation");

    // test a combination of "pre" and "post" behaviors
    IntMatrixConstZIterator srcIt{m_MainMatrix.getConstZIterator(5, 6)};
    IntMatrixConstZIterator destIt{--(--srcIt)};
    QVERIFY2(srcIt == m_MainMatrix.getConstZIterator(5, 5) && destIt == m_MainMatrix.getConstZIterator(5, 4), "Incorrect pre-pre-decrementation");
    srcIt = m_MainMatrix.getConstZIterator(5, 6);
    destIt = (srcIt--)--;
    QVERIFY2(srcIt == m_MainMatrix.getConstZIterator(5, 5) && destIt == m_MainMatrix.getConstZIterator(5, 6), "Incorrect post-post-decrementation");
    srcIt = m_MainMatrix.getConstZIterator(5, 6);
    destIt = (--srcIt)--;
    QVERIFY2(srcIt == m_MainMatrix.getConstZIterator(5, 5) && destIt == m_MainMatrix.getConstZIterator(5, 5), "Incorrect post-pre-decrementation");
    srcIt = m_MainMatrix.getConstZIterator(5, 6);
    destIt = --(srcIt--);
    QVERIFY2(srcIt == m_MainMatrix.getConstZIterator(5, 5) && destIt == m_MainMatrix.getConstZIterator(5, 5), "Incorrect pre-post-decrementation");
}

void ConstZIteratorTests::testOperatorPlus()
{
    m_MainMatrix = {9, 8, -5};

    // test for non-empty matrix
    IntMatrixConstZIterator it{m_MainMatrix.constZBegin()};
    QVERIFY2(it + (-3) == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.getConstZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 4 == m_MainMatrix.getConstZIterator(0, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 10 == m_MainMatrix.getConstZIterator(1, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 70 == m_MainMatrix.getConstZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 71 == m_MainMatrix.getConstZIterator(8, 7), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 72 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 73 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 75 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstZIterator(0, 1);
    QVERIFY2(it + (-4) == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getConstZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.getConstZIterator(0, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 9 == m_MainMatrix.getConstZIterator(1, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 69 == m_MainMatrix.getConstZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 70 == m_MainMatrix.getConstZIterator(8, 7), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 71 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 72 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 74 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstZIterator(5, 4);
    QVERIFY2(it + (-47) == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-45) == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-44) == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-43) == m_MainMatrix.getConstZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-6) == m_MainMatrix.getConstZIterator(4, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.getConstZIterator(5, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getConstZIterator(5, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.getConstZIterator(5, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 6 == m_MainMatrix.getConstZIterator(6, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 26 == m_MainMatrix.getConstZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 27 == m_MainMatrix.getConstZIterator(8, 7), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 28 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 29 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 31 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstZIterator(8, 6);
    QVERIFY2(it + (-73) == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-70) == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-69) == m_MainMatrix.getConstZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-24) == m_MainMatrix.getConstZIterator(5, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-3) == m_MainMatrix.getConstZIterator(8, 3), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getConstZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.getConstZIterator(8, 7), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 5 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstZIterator(8, 7);
    QVERIFY2(it + (-74) == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-72) == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-70) == m_MainMatrix.getConstZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-25) == m_MainMatrix.getConstZIterator(5, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-4) == m_MainMatrix.getConstZIterator(8, 3), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.getConstZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getConstZIterator(8, 7), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 4 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.constZEnd();
    QVERIFY2(it + (-75) == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-73) == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-72) == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.getConstZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-26) == m_MainMatrix.getConstZIterator(5, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-5) == m_MainMatrix.getConstZIterator(8, 3), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.getConstZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.getConstZIterator(8, 7), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.constZBegin() + (-1) == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constZBegin() + 1 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constZEnd() + 0 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constZEnd() + 1 == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constZEnd() + (-1) == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");

    // test for empty iterators
    IntMatrixConstZIterator emptyIt1{};
    IntMatrixConstZIterator emptyIt2{};
    IntMatrixConstZIterator emptyIt3{};
    emptyIt1 = emptyIt3 + (-1);
    emptyIt2 = emptyIt3 + 1;
    QVERIFY2(emptyIt1 == emptyIt3, "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(emptyIt2 == emptyIt3, "Operator + does not work correctly, the resulting iterator is not the right one");
}

void ConstZIteratorTests::testOperatorMinus()
{
    m_MainMatrix = {9, 8, -5};

    // test for non-empty matrix
    IntMatrixConstZIterator it{m_MainMatrix.constZBegin()};
    QVERIFY2(it - 3 == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.constZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.getConstZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-4) == m_MainMatrix.getConstZIterator(0, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-10) == m_MainMatrix.getConstZIterator(1, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-70) == m_MainMatrix.getConstZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-71) == m_MainMatrix.getConstZIterator(8, 7), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-72) == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-73) == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-75) == m_MainMatrix.constZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstZIterator(0, 1);
    QVERIFY2(it - 4 == m_MainMatrix.constZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.constZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.constZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getConstZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.getConstZIterator(0, 4), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-9) == m_MainMatrix.getConstZIterator(1, 2), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-69) == m_MainMatrix.getConstZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-70) == m_MainMatrix.getConstZIterator(8, 7), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-71) == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-72) == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-74) == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstZIterator(5, 4);
    QVERIFY2(it - 47 == m_MainMatrix.constZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 45 == m_MainMatrix.constZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 44 == m_MainMatrix.constZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 43 == m_MainMatrix.getConstZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 6 == m_MainMatrix.getConstZIterator(4, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.getConstZIterator(5, 2), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getConstZIterator(5, 4), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.getConstZIterator(5, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-6) == m_MainMatrix.getConstZIterator(6, 2), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-26) == m_MainMatrix.getConstZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-27) == m_MainMatrix.getConstZIterator(8, 7), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-28) == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-29) == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-31) == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstZIterator(8, 6);
    QVERIFY2(it - 73 == m_MainMatrix.constZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.constZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 70 == m_MainMatrix.constZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 69 == m_MainMatrix.getConstZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 24 == m_MainMatrix.getConstZIterator(5, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 3 == m_MainMatrix.getConstZIterator(8, 3), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getConstZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.getConstZIterator(8, 7), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-5) == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstZIterator(8, 7);
    QVERIFY2(it - 74 == m_MainMatrix.constZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 72 == m_MainMatrix.constZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.constZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 70 == m_MainMatrix.getConstZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 25 == m_MainMatrix.getConstZIterator(5, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 4 == m_MainMatrix.getConstZIterator(8, 3), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.getConstZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getConstZIterator(8, 7), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-4) == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.constZEnd();
    QVERIFY2(it - 75 == m_MainMatrix.constZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 73 == m_MainMatrix.constZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 72 == m_MainMatrix.constZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.getConstZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 26 == m_MainMatrix.getConstZIterator(5, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 5 == m_MainMatrix.getConstZIterator(8, 3), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.getConstZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.getConstZIterator(8, 7), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.constZBegin() - 1 == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constZBegin() - (-1) == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constZEnd() - 0 == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constZEnd() - (-1) == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constZEnd() - 1 == m_MainMatrix.constZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");

    // test for empty iterator
    IntMatrixConstZIterator emptyIt1{};
    IntMatrixConstZIterator emptyIt2{};
    IntMatrixConstZIterator emptyIt3{};
    emptyIt1 = emptyIt3 - 1;
    emptyIt2 = emptyIt3 - (-1);
    QVERIFY2(emptyIt1 == emptyIt3, "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(emptyIt2 == emptyIt3, "Operator - does not work correctly, the resulting iterator is not the right one");
}

void ConstZIteratorTests::testOperatorPlusEqual()
{
    IntMatrixConstZIterator it;

    // test for non-empty matrix
    m_MainMatrix = {9, 8, -5};

    IntMatrixConstZIterator referenceIt{m_MainMatrix.constZBegin()};
    it = referenceIt; it += (-3); QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 4; QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 10; QVERIFY2(it == m_MainMatrix.getConstZIterator(1, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 70; QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 71; QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 7), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 72; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 73; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 75; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstZIterator(0, 1);
    it = referenceIt; it += (-4); QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-2); QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 3; QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 9; QVERIFY2(it == m_MainMatrix.getConstZIterator(1, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 69; QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 70; QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 7), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 71; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 72; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 74; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstZIterator(5, 4);
    it = referenceIt; it += (-47); QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-45); QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-44); QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-43); QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-6); QVERIFY2(it == m_MainMatrix.getConstZIterator(4, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-2); QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 2; QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 6; QVERIFY2(it == m_MainMatrix.getConstZIterator(6, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 26; QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 27; QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 7), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 28; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 29; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 31; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstZIterator(8, 6);
    it = referenceIt; it += (-73); QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-71); QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-70); QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-69); QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-24); QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-3); QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 3), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 7), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 2; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 3; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 5; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstZIterator(8, 7);
    it = referenceIt; it += (-74); QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-72); QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-71); QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-70); QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-25); QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-4); QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 3), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 7), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 2; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 4; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.constZEnd();
    it = referenceIt; it += (-75); QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-73); QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-72); QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-71); QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-26); QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-5); QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 3), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-2); QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 7), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 3; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    referenceIt = m_MainMatrix.constZBegin();
    referenceIt = m_MainMatrix.constZEnd();
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator += does not work correctly, the updated iterator is not the right one");

    // test for empty iterator
    IntMatrixConstZIterator emptyIt1{};
    IntMatrixConstZIterator emptyIt2{};
    IntMatrixConstZIterator emptyIt3{};
    emptyIt2 += (-1); QVERIFY2(emptyIt2 == emptyIt1, "Operator += does not work correctly, the resulting updated is not the right one");
    emptyIt3 += 1; QVERIFY2(emptyIt3 == emptyIt1, "Operator += does not work correctly, the resulting updated is not the right one");
}

void ConstZIteratorTests::testOperatorMinusEqual()
{
    IntMatrixConstZIterator it;

    // test for non-empty matrix
    m_MainMatrix = {9, 8, -5};

    IntMatrixConstZIterator referenceIt{m_MainMatrix.constZBegin()};
    it = referenceIt; it -= 3; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-4); QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-10); QVERIFY2(it == m_MainMatrix.getConstZIterator(1, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-70); QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-71); QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 7), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-72); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-73); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-75); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstZIterator(0, 1);
    it = referenceIt; it -= 4; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 2; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-3); QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-9); QVERIFY2(it == m_MainMatrix.getConstZIterator(1, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-69); QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-70); QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 7), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-71); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-72); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-74); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstZIterator(5, 4);
    it = referenceIt; it -= 47; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 45; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 44; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 43; QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 6; QVERIFY2(it == m_MainMatrix.getConstZIterator(4, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 2; QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-2); QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-6); QVERIFY2(it == m_MainMatrix.getConstZIterator(6, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-26); QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-27); QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 7), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-28); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-29); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-31); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstZIterator(8, 6);
    it = referenceIt; it -= 73; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 71; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 70; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 69; QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 24; QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 3; QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 3), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 7), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-2); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-3); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-5); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstZIterator(8, 7);
    it = referenceIt; it -= 74; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 72; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 71; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 70; QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 25; QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 4; QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 3), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 7), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-2); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-4); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.constZEnd();
    it = referenceIt; it -= 75; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 73; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 72; QVERIFY2(it == m_MainMatrix.constZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 71; QVERIFY2(it == m_MainMatrix.getConstZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 26; QVERIFY2(it == m_MainMatrix.getConstZIterator(5, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 5; QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 3), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 2; QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.getConstZIterator(8, 7), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-3); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    referenceIt = m_MainMatrix.constZBegin();
    referenceIt = m_MainMatrix.constZEnd();
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.constZEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");

    // test for empty iterator
    IntMatrixConstZIterator emptyIt1{};
    IntMatrixConstZIterator emptyIt2{};
    IntMatrixConstZIterator emptyIt3{};
    emptyIt2 -= 1; QVERIFY2(emptyIt2 == emptyIt1, "Operator -= does not work correctly, the updated iterator is not the right one");
    emptyIt3 -= (-1); QVERIFY2(emptyIt3 == emptyIt1, "Operator -= does not work correctly, the updated iterator is not the right one");
}

void ConstZIteratorTests::testDifferenceOperator()
{
    // test for non-empty matrix
    m_MainMatrix = {9, 8, -5};

    QVERIFY2(m_MainMatrix.constZEnd() - m_MainMatrix.constZEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constZEnd() - m_MainMatrix.getConstZIterator(8, 7) == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constZEnd() - m_MainMatrix.getConstZIterator(8, 6) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constZEnd() - m_MainMatrix.getConstZIterator(5, 4) == 28, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constZEnd() - m_MainMatrix.getConstZIterator(0, 1) == 71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constZEnd() - m_MainMatrix.constZBegin() == 72, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getConstZIterator(8, 7) - m_MainMatrix.constZEnd() == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(8, 7) - m_MainMatrix.getConstZIterator(8, 7) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(8, 7) - m_MainMatrix.getConstZIterator(8, 6) == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(8, 7) - m_MainMatrix.getConstZIterator(5, 4) == 27, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(8, 7) - m_MainMatrix.getConstZIterator(0, 1) == 70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(8, 7) - m_MainMatrix.constZBegin() == 71, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getConstZIterator(8, 6) - m_MainMatrix.constZEnd() == -2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(8, 6) - m_MainMatrix.getConstZIterator(8, 7) == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(8, 6) - m_MainMatrix.getConstZIterator(8, 6) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(8, 6) - m_MainMatrix.getConstZIterator(5, 4) == 26, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(8, 6) - m_MainMatrix.getConstZIterator(0, 1) == 69, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(8, 6) - m_MainMatrix.constZBegin() == 70, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getConstZIterator(5, 4) - m_MainMatrix.constZEnd() == -28, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(5, 4) - m_MainMatrix.getConstZIterator(8, 7) == -27, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(5, 4) - m_MainMatrix.getConstZIterator(8, 6) == -26, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(5, 4) - m_MainMatrix.getConstZIterator(5, 4) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(5, 4) - m_MainMatrix.getConstZIterator(0, 1) == 43, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(5, 4) - m_MainMatrix.constZBegin() == 44, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getConstZIterator(0, 1) - m_MainMatrix.constZEnd() == -71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(0, 1) - m_MainMatrix.getConstZIterator(8, 7) == -70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(0, 1) - m_MainMatrix.getConstZIterator(8, 6) == -69, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(0, 1) - m_MainMatrix.getConstZIterator(5, 4) == -43, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(0, 1) - m_MainMatrix.getConstZIterator(0, 1) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(0, 1) - m_MainMatrix.constZBegin() == 1, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.constZBegin() - m_MainMatrix.constZEnd() == -72, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constZBegin() - m_MainMatrix.getConstZIterator(8, 7) == -71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constZBegin() - m_MainMatrix.getConstZIterator(8, 6) == -70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constZBegin() - m_MainMatrix.getConstZIterator(5, 4) == -44, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constZBegin() - m_MainMatrix.getConstZIterator(0, 1) == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constZBegin() - m_MainMatrix.constZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");

    // additional tests with "random" elements from same row/different rows
    QVERIFY2(m_MainMatrix.getConstZIterator(5, 4) - m_MainMatrix.getConstZIterator(7, 2) == -14, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(7, 2) - m_MainMatrix.getConstZIterator(5, 4) == 14, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(5, 4) - m_MainMatrix.getConstZIterator(5, 2) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstZIterator(5, 2) - m_MainMatrix.getConstZIterator(5, 4) == -2, "The difference operator does not work correctly, difference between iterators is wrong");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.constZEnd() - m_MainMatrix.constZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constZBegin() - m_MainMatrix.constZEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constZBegin() - m_MainMatrix.constZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constZEnd() - m_MainMatrix.constZEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");

    // test for empty iterator
    IntMatrixConstZIterator emptyIt1{};
    IntMatrixConstZIterator emptyIt2{};
    QVERIFY2(emptyIt1 - emptyIt2 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(emptyIt2 - emptyIt1 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(emptyIt1 - emptyIt1 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
}

void ConstZIteratorTests::testDereferenceAsteriskOperator()
{
    // test reading element
    m_MainMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};
    QVERIFY2(*m_MainMatrix.constZBegin() == 1, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getConstZIterator(0, 1) == -2, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getConstZIterator(1, 2) == -6, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getConstZIterator(3, 1) == 11, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getConstZIterator(3, 2) == -12, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");

    // additional test
    m_MainMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    IntMatrixConstZIterator readIter{m_MainMatrix.constZBegin()};
    m_MainMatrix.at(0, 2) = 10;
    readIter += 2;
    QVERIFY2(*readIter == 10, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
}

void ConstZIteratorTests::testDereferenceArrowOperator()
{
    // test reading element
    m_AuxStringMatrix = {4, 3, {"abc", "ba", "abcd", "jihgfedcba", "a", "gfedcba", "abcde", "ihgfedcba", "abcdefgh", "", "abcdefghijk", "fedcba"}};
    QVERIFY2(m_AuxStringMatrix.constZBegin()->size() == 3, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getConstZIterator(0, 1)->size() == 2, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getConstZIterator(1, 2)->size() == 7, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getConstZIterator(3, 1)->size() == 11, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getConstZIterator(3, 2)->size() == 6, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");

    // additional test
    m_AuxStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    StringMatrixConstZIterator it{m_AuxStringMatrix.constZBegin()};
    m_AuxStringMatrix.at(0, 2) = "abcdefghi";
    it += 2;;
    QVERIFY2(it->size() == 9, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
}

void ConstZIteratorTests::testDereferenceSquareBracketsOperator()
{
    // test reading element
    m_MainMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};

    IntMatrixConstZIterator it{m_MainMatrix.constZBegin()};
    QVERIFY2(it[0] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[1] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[5] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[10] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[11] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getConstZIterator(0, 1);
    QVERIFY2(it[-1] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[4] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[9] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[10] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getConstZIterator(1, 2);
    QVERIFY2(it[-5] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-4] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[5] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[6] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getConstZIterator(3, 1);
    QVERIFY2(it[-10] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-9] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-5] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[1] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getConstZIterator(3, 2);
    QVERIFY2(it[-11] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-10] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-6] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-1] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");
}

void ConstZIteratorTests::testStdCount()
{
    using namespace std;

    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};

    int matchCount{count(m_MainMatrix.constZBegin(), m_MainMatrix.constZEnd(), 2)};
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constZBegin(), m_MainMatrix.constZEnd(), -5);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstZIterator(0, 2), m_MainMatrix.getConstZIterator(1, 4), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstZIterator(0, 2), m_MainMatrix.getConstZIterator(2, 0), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstZIterator(0, 3), m_MainMatrix.getConstZIterator(1, 4), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstZIterator(0, 3), m_MainMatrix.getConstZIterator(2, 0), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constZBegin(), m_MainMatrix.getConstZIterator(2, 3), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstZIterator(2, 3), m_MainMatrix.constZEnd(), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constZBegin(), m_MainMatrix.getConstZIterator(2, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstZIterator(2, 2), m_MainMatrix.constZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstZIterator(2), m_MainMatrix.getConstZIterator(9), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstZIterator(2), m_MainMatrix.getConstZIterator(10), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstZIterator(3), m_MainMatrix.getConstZIterator(9), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstZIterator(3), m_MainMatrix.getConstZIterator(10), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constZBegin(), m_MainMatrix.getConstZIterator(13), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstZIterator(13), m_MainMatrix.constZEnd(), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constZBegin(), m_MainMatrix.getConstZIterator(12), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstZIterator(12), m_MainMatrix.constZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constZRowBegin(1), m_MainMatrix.constZRowEnd(1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constZRowBegin(1), m_MainMatrix.constZRowEnd(2), 8);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constZRowBegin(2), m_MainMatrix.constZRowEnd(2), 9);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constZRowBegin(2), m_MainMatrix.constZRowEnd(3), 9);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constZBegin(), m_MainMatrix.constZRowBegin(1), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constZRowBegin(1), m_MainMatrix.constZEnd(), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constZBegin(), m_MainMatrix.constZRowEnd(1), 1);
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constZRowEnd(1), m_MainMatrix.constZEnd(), 1);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
}

void ConstZIteratorTests::testStdFind()
{
    using namespace std;

    // test finding elements in specific ranges within unempty matrix
    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, -2, 2, 8, 9, -7, 7, 2, 9, 11}};

    QVERIFY2(find(m_MainMatrix.constZBegin(), m_MainMatrix.constZEnd(), 5) != m_MainMatrix.constZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZBegin(), m_MainMatrix.constZEnd(), 10) == m_MainMatrix.constZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZRowBegin(1), m_MainMatrix.constZRowEnd(1), 5) != m_MainMatrix.constZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZRowBegin(1), m_MainMatrix.constZRowEnd(1), 6) != m_MainMatrix.constZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZRowBegin(1), m_MainMatrix.constZRowEnd(1), 8) != m_MainMatrix.constZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZRowBegin(1), m_MainMatrix.constZRowEnd(1), -1) == m_MainMatrix.constZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZRowBegin(1), m_MainMatrix.constZRowEnd(1), -2) == m_MainMatrix.constZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZRowBegin(1), m_MainMatrix.constZRowEnd(1), 10) == m_MainMatrix.constZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZRowBegin(1), m_MainMatrix.constZEnd(), 5) != m_MainMatrix.constZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZRowBegin(1), m_MainMatrix.constZEnd(), 11) != m_MainMatrix.constZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZRowBegin(1), m_MainMatrix.constZEnd(), -2) != m_MainMatrix.constZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZRowBegin(1), m_MainMatrix.constZEnd(), -1) == m_MainMatrix.constZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZRowBegin(1), m_MainMatrix.constZEnd(), 10) == m_MainMatrix.constZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZBegin(), m_MainMatrix.constZRowEnd(1), -1) != m_MainMatrix.constZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZBegin(), m_MainMatrix.constZRowEnd(1), 6) != m_MainMatrix.constZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZBegin(), m_MainMatrix.constZRowEnd(1), 8) != m_MainMatrix.constZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZBegin(), m_MainMatrix.constZRowEnd(1), -2) == m_MainMatrix.constZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZBegin(), m_MainMatrix.constZRowEnd(1), 10) == m_MainMatrix.constZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstZIterator(1, 3), m_MainMatrix.getConstZIterator(3, 1), 0) != m_MainMatrix.getConstZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstZIterator(1, 3), m_MainMatrix.getConstZIterator(3, 1), -7) != m_MainMatrix.getConstZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstZIterator(1, 3), m_MainMatrix.getConstZIterator(3, 1), -2) != m_MainMatrix.getConstZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstZIterator(1, 3), m_MainMatrix.getConstZIterator(3, 1), -1) == m_MainMatrix.getConstZIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstZIterator(1, 3), m_MainMatrix.getConstZIterator(3, 1), 11) == m_MainMatrix.getConstZIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstZIterator(1, 3), m_MainMatrix.getConstZIterator(3, 1), 10) == m_MainMatrix.getConstZIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstZIterator(1, 3), m_MainMatrix.constZEnd(), 0) != m_MainMatrix.constZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstZIterator(1, 3), m_MainMatrix.constZEnd(), 11) != m_MainMatrix.constZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstZIterator(1, 3), m_MainMatrix.constZEnd(), -2) != m_MainMatrix.constZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstZIterator(1, 3), m_MainMatrix.constZEnd(), -1) == m_MainMatrix.constZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstZIterator(1, 3), m_MainMatrix.constZEnd(), 10) == m_MainMatrix.constZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZBegin(), m_MainMatrix.getConstZIterator(3, 1), -1) != m_MainMatrix.getConstZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZBegin(), m_MainMatrix.getConstZIterator(3, 1), -7) != m_MainMatrix.getConstZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZBegin(), m_MainMatrix.getConstZIterator(3, 1), -2) != m_MainMatrix.getConstZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZBegin(), m_MainMatrix.getConstZIterator(3, 1), 11) == m_MainMatrix.getConstZIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constZBegin(), m_MainMatrix.getConstZIterator(3, 1), 10) == m_MainMatrix.getConstZIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

    // other tests
    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};
    IntMatrixConstZIterator it{find(m_MainMatrix.constZBegin(), m_MainMatrix.constZEnd(), 4)};
    ++it;
    QVERIFY2(*it == 5, "The iterator doesn't work correctly with std::find, incorrect next element returned");

    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};
    QVERIFY2(find(m_MainMatrix.constZBegin(), m_MainMatrix.constZEnd(), 10) == m_MainMatrix.constZEnd(), "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix");

    it = m_MainMatrix.constZBegin();
    while(it != m_MainMatrix.constZEnd())
    {
        it = find(it, m_MainMatrix.constZEnd(), 9);

        if (it != m_MainMatrix.constZEnd())
        {
            m_MainMatrix.at(it.getCurrentRowNr(), it.getCurrentColumnNr()) = 10;
        }
    }
    int expectedNumber{std::count(m_MainMatrix.constZBegin(), m_MainMatrix.constZEnd(), 10)};
    QVERIFY2(expectedNumber == 3, "The iterator doesn't work properly with std::find, element values haven't been correctly replaced");
}

QTEST_APPLESS_MAIN(ConstZIteratorTests)

#include "tst_constziteratortests.moc"
