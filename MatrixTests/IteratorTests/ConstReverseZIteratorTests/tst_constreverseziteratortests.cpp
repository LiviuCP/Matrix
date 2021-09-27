#include <QtTest>

#include "matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixConstReverseZIterator = Matrix<int>::ConstReverseZIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixConstReverseZIterator = Matrix<std::string>::ConstReverseZIterator;

class ConstReverseZIteratorTests : public QObject
{
    Q_OBJECT

public:
    ConstReverseZIteratorTests();
    ~ConstReverseZIteratorTests();

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

ConstReverseZIteratorTests::ConstReverseZIteratorTests()
{
}

ConstReverseZIteratorTests::~ConstReverseZIteratorTests()
{
}

void ConstReverseZIteratorTests::testIteratorCreation()
{
    m_MainMatrix = {9, 8, -5};

    IntMatrixConstReverseZIterator it{m_MainMatrix.constReverseZBegin()};
    QVERIFY2(it.getRowNr() == 8 && it.getColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseZEnd();
    QVERIFY2(it.getRowNr() == 0 && it.getColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseZRowBegin(0);
    QVERIFY2(it.getRowNr() == 0 && it.getColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseZRowBegin(1);
    QVERIFY2(it.getRowNr() == 1 && it.getColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseZRowBegin(4);
    QVERIFY2(it.getRowNr() == 4 && it.getColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseZRowBegin(7);
    QVERIFY2(it.getRowNr() == 7 && it.getColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseZRowBegin(8);
    QVERIFY2(it.getRowNr() == 8 && it.getColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseZRowEnd(0);
    QVERIFY2(it.getRowNr() == 0 && it.getColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseZRowEnd(1);
    QVERIFY2(it.getRowNr() == 0 && it.getColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseZRowEnd(4);
    QVERIFY2(it.getRowNr() == 3 && it.getColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseZRowEnd(7);
    QVERIFY2(it.getRowNr() == 6 && it.getColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseZRowEnd(8);
    QVERIFY2(it.getRowNr() == 7 && it.getColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseZIterator(0, 0);
    QVERIFY2(it.getRowNr() == 0 && it.getColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseZIterator(0, 1);
    QVERIFY2(it.getRowNr() == 0 && it.getColumnNr() == 1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseZIterator(5, 4);
    QVERIFY2(it.getRowNr() == 5 && it.getColumnNr() == 4 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseZIterator(8, 6);
    QVERIFY2(it.getRowNr() == 8 && it.getColumnNr() == 6 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseZIterator(8, 7);
    QVERIFY2(it.getRowNr() == 8 && it.getColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseZIterator(0);
    QVERIFY2(it.getRowNr() == 0 && it.getColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseZIterator(1);
    QVERIFY2(it.getRowNr() == 0 && it.getColumnNr() == 1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseZIterator(44);
    QVERIFY2(it.getRowNr() == 5 && it.getColumnNr() == 4 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseZIterator(70);
    QVERIFY2(it.getRowNr() == 8 && it.getColumnNr() == 6 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseZIterator(71);
    QVERIFY2(it.getRowNr() == 8 && it.getColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // test iterator creation for empty matrix
    m_MainMatrix.clear();
    it = m_MainMatrix.constReverseZBegin();
    QVERIFY2(it.getRowNr() == -1 && it.getColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseZEnd();
    QVERIFY2(it.getRowNr() == -1 && it.getColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // test empty iterator creation (not bound to any matrix) - an empty iterator should be valid for any empty matrix
    IntMatrixConstReverseZIterator emptyIt;
    QVERIFY2(emptyIt.getRowNr() == -1 && emptyIt.getColumnNr() == -1 && emptyIt.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // additional test
    m_MainMatrix = {9, 8, -5};
    m_AuxIntMatrix = {9, 8, -5};
    it = m_MainMatrix.getConstReverseZIterator(5, 4);
    QVERIFY(!it.isValidWithMatrix(m_AuxIntMatrix));
    m_AuxIntMatrix.clear();
    QVERIFY(!it.isValidWithMatrix(m_AuxIntMatrix));
    it = m_AuxIntMatrix.constReverseZBegin();
    QVERIFY(!it.isValidWithMatrix(m_MainMatrix));
    it = m_AuxIntMatrix.constReverseZEnd();
    QVERIFY(!it.isValidWithMatrix(m_MainMatrix));
    m_MainMatrix.clear();
    it = m_MainMatrix.constReverseZBegin();
    QVERIFY(it.isValidWithMatrix(m_AuxIntMatrix)); // an iterator of an empty matrix is valid with any other empty matrix
    it = m_MainMatrix.constReverseZEnd();
    QVERIFY(it.isValidWithMatrix(m_AuxIntMatrix));
}

void ConstReverseZIteratorTests::testIteratorsAreEqual()
{

    m_MainMatrix = {9, 8, -5};

    // test different iterators for equality
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0) == m_MainMatrix.getConstReverseZIterator(0, 0)) && !(m_MainMatrix.getConstReverseZIterator(0) != m_MainMatrix.getConstReverseZIterator(0, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(1) == m_MainMatrix.getConstReverseZIterator(0, 1)) && !(m_MainMatrix.getConstReverseZIterator(1) != m_MainMatrix.getConstReverseZIterator(0, 1)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(44) == m_MainMatrix.getConstReverseZIterator(5, 4)) && !(m_MainMatrix.getConstReverseZIterator(44) != m_MainMatrix.getConstReverseZIterator(5, 4)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(70) == m_MainMatrix.getConstReverseZIterator(8, 6)) && !(m_MainMatrix.getConstReverseZIterator(70) != m_MainMatrix.getConstReverseZIterator(8, 6)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(71) == m_MainMatrix.getConstReverseZIterator(8, 7)) && !(m_MainMatrix.getConstReverseZIterator(71) != m_MainMatrix.getConstReverseZIterator(8, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseZBegin() == m_MainMatrix.getConstReverseZIterator(8, 7) && !(m_MainMatrix.constReverseZBegin() != m_MainMatrix.getConstReverseZIterator(8, 7))), "The two iterators are not equal");
    QVERIFY2((m_MainMatrix.constReverseZRowBegin(0) == m_MainMatrix.getConstReverseZIterator(0, 7)) && !(m_MainMatrix.constReverseZRowBegin(0) != m_MainMatrix.getConstReverseZIterator(0, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseZRowBegin(1) == m_MainMatrix.getConstReverseZIterator(1, 7)) && !(m_MainMatrix.constReverseZRowBegin(1) != m_MainMatrix.getConstReverseZIterator(1, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseZRowBegin(5) == m_MainMatrix.getConstReverseZIterator(5, 7)) && !(m_MainMatrix.constReverseZRowBegin(5) != m_MainMatrix.getConstReverseZIterator(5, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseZRowBegin(7) == m_MainMatrix.getConstReverseZIterator(7, 7)) && !(m_MainMatrix.constReverseZRowBegin(7) != m_MainMatrix.getConstReverseZIterator(7, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseZRowBegin(8) == m_MainMatrix.getConstReverseZIterator(8, 7)) && !(m_MainMatrix.constReverseZRowBegin(8) != m_MainMatrix.getConstReverseZIterator(8, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseZRowEnd(0) == m_MainMatrix.constReverseZEnd()) && !(m_MainMatrix.constReverseZRowEnd(0) != m_MainMatrix.constReverseZEnd()), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseZRowEnd(1) == m_MainMatrix.getConstReverseZIterator(0, 7)) && !(m_MainMatrix.constReverseZRowEnd(1) != m_MainMatrix.getConstReverseZIterator(0, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseZRowEnd(5) == m_MainMatrix.getConstReverseZIterator(4, 7)) && !(m_MainMatrix.constReverseZRowEnd(5) != m_MainMatrix.getConstReverseZIterator(4, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseZRowEnd(7) == m_MainMatrix.getConstReverseZIterator(6, 7)) && !(m_MainMatrix.constReverseZRowEnd(7) != m_MainMatrix.getConstReverseZIterator(6, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseZRowEnd(8) == m_MainMatrix.getConstReverseZIterator(7, 7)) && !(m_MainMatrix.constReverseZRowEnd(8) != m_MainMatrix.getConstReverseZIterator(7, 7)), "The two iterators are NOT equal");

    // test iterator equality to itself
    IntMatrixConstReverseZIterator it{m_MainMatrix.constReverseZEnd()};
    QVERIFY2((it == it) && (it == m_MainMatrix.constReverseZEnd()) && !(it != it) && !(it != m_MainMatrix.constReverseZEnd()), "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getConstReverseZIterator(0, 0);
    QVERIFY2((it == it) && (it == m_MainMatrix.getConstReverseZIterator(0, 0)) && !(it != it) && !(it != m_MainMatrix.getConstReverseZIterator(0, 0)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getConstReverseZIterator(0, 1);
    QVERIFY2((it == it) && (it == m_MainMatrix.getConstReverseZIterator(0, 1)) && !(it != it) && !(it != m_MainMatrix.getConstReverseZIterator(0, 1)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getConstReverseZIterator(5, 4);
    QVERIFY2((it == it) && (it == m_MainMatrix.getConstReverseZIterator(5, 4)) && !(it != it) && !(it != m_MainMatrix.getConstReverseZIterator(5, 4)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getConstReverseZIterator(8, 6);
    QVERIFY2((it == it) && (it == m_MainMatrix.getConstReverseZIterator(8, 6)) && !(it != it) && !(it != m_MainMatrix.getConstReverseZIterator(8, 6)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.constReverseZBegin();
    QVERIFY2((it == it) && (it == m_MainMatrix.constReverseZBegin()) && !(it != it) && !(it != m_MainMatrix.constReverseZBegin()),  "The iterator is NOT equal to itself and/or to source iterator");

    // test empty matrix iterator equality
    m_MainMatrix.clear();
    QVERIFY2((m_MainMatrix.constReverseZBegin() == m_MainMatrix.constReverseZEnd()) && !(m_MainMatrix.constReverseZBegin() != m_MainMatrix.constReverseZEnd()), "The two iterators are NOT equal");
}

void ConstReverseZIteratorTests::testIteratorsAreNotEqual()
{
    m_MainMatrix = {9, 8, -5};

    QVERIFY2((m_MainMatrix.constReverseZEnd() != m_MainMatrix.getConstReverseZIterator(0, 0)) && !(m_MainMatrix.constReverseZEnd() == m_MainMatrix.getConstReverseZIterator(0, 0)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 0) != m_MainMatrix.getConstReverseZIterator(0, 1)) && !(m_MainMatrix.getConstReverseZIterator(0, 0) == m_MainMatrix.getConstReverseZIterator(0, 1)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 1) != m_MainMatrix.getConstReverseZIterator(0, 2)) && !(m_MainMatrix.getConstReverseZIterator(0, 1) == m_MainMatrix.getConstReverseZIterator(0, 2)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 2) != m_MainMatrix.getConstReverseZIterator(5, 4)) && !(m_MainMatrix.getConstReverseZIterator(0, 2) == m_MainMatrix.getConstReverseZIterator(5, 4)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(5, 4) != m_MainMatrix.getConstReverseZIterator(8, 6)) && !(m_MainMatrix.getConstReverseZIterator(5, 4) == m_MainMatrix.getConstReverseZIterator(8, 6)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(8, 6) != m_MainMatrix.constReverseZBegin()) && !(m_MainMatrix.getConstReverseZIterator(8, 6) == m_MainMatrix.constReverseZBegin()), "The two iterators are NOT different");
}

void ConstReverseZIteratorTests::testSmallerThanOperator()
{
    m_MainMatrix = {9, 8, -5};

    QVERIFY2((m_MainMatrix.constReverseZBegin() < m_MainMatrix.getConstReverseZIterator(8, 6)) && !(m_MainMatrix.constReverseZBegin() >= m_MainMatrix.getConstReverseZIterator(8, 6)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(8, 6) < m_MainMatrix.getConstReverseZIterator(5, 4)) && !(m_MainMatrix.getConstReverseZIterator(8, 6) >= m_MainMatrix.getConstReverseZIterator(5, 4)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(5, 4) < m_MainMatrix.getConstReverseZIterator(0, 2)) && !(m_MainMatrix.getConstReverseZIterator(5, 4) >= m_MainMatrix.getConstReverseZIterator(0, 2)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 2) < m_MainMatrix.getConstReverseZIterator(0, 1)) && !(m_MainMatrix.getConstReverseZIterator(0, 2) >= m_MainMatrix.getConstReverseZIterator(0, 1)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 1) < m_MainMatrix.getConstReverseZIterator(0, 0)) && !(m_MainMatrix.getConstReverseZIterator(0, 1) >= m_MainMatrix.getConstReverseZIterator(0, 0)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 0) < m_MainMatrix.constReverseZEnd()) && !(m_MainMatrix.getConstReverseZIterator(0, 0) >= m_MainMatrix.constReverseZEnd()), "The first iterator is NOT smaller than the second iterator");
}

void ConstReverseZIteratorTests::testSmallerThanOrEqualToOperator()
{
    m_MainMatrix = {9, 8, -5};

    // test operator with different iterators
    QVERIFY2((m_MainMatrix.constReverseZBegin() <= m_MainMatrix.constReverseZBegin()) && !(m_MainMatrix.constReverseZBegin() > m_MainMatrix.constReverseZBegin()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.constReverseZBegin() <= m_MainMatrix.getConstReverseZIterator(8, 6)) && !(m_MainMatrix.constReverseZBegin() > m_MainMatrix.getConstReverseZIterator(8, 6)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(8, 6) <= m_MainMatrix.getConstReverseZIterator(8, 6)) && !(m_MainMatrix.getConstReverseZIterator(8, 6) > m_MainMatrix.getConstReverseZIterator(8, 6)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(8, 6) <= m_MainMatrix.getConstReverseZIterator(5, 4)) && !(m_MainMatrix.getConstReverseZIterator(8, 6) > m_MainMatrix.getConstReverseZIterator(5, 4)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(5, 4) <= m_MainMatrix.getConstReverseZIterator(5, 4)) && !(m_MainMatrix.getConstReverseZIterator(5, 4) > m_MainMatrix.getConstReverseZIterator(5, 4)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(5, 4) <= m_MainMatrix.getConstReverseZIterator(0, 2)) && !(m_MainMatrix.getConstReverseZIterator(5, 4) > m_MainMatrix.getConstReverseZIterator(0, 2)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 2) <= m_MainMatrix.getConstReverseZIterator(0, 2)) && !(m_MainMatrix.getConstReverseZIterator(0, 2) > m_MainMatrix.getConstReverseZIterator(0, 2)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 2) <= m_MainMatrix.getConstReverseZIterator(0, 1)) && !(m_MainMatrix.getConstReverseZIterator(0, 2) > m_MainMatrix.getConstReverseZIterator(0, 1)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 1) <= m_MainMatrix.getConstReverseZIterator(0, 1)) && !(m_MainMatrix.getConstReverseZIterator(0, 1) > m_MainMatrix.getConstReverseZIterator(0, 1)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 1) <= m_MainMatrix.getConstReverseZIterator(0, 0)) && !(m_MainMatrix.getConstReverseZIterator(0, 1) > m_MainMatrix.getConstReverseZIterator(0, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 0) <= m_MainMatrix.getConstReverseZIterator(0, 0)) && !(m_MainMatrix.getConstReverseZIterator(0, 0) > m_MainMatrix.getConstReverseZIterator(0, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 0) <= m_MainMatrix.constReverseZEnd()) && !(m_MainMatrix.getConstReverseZIterator(0, 0) > m_MainMatrix.constReverseZEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.constReverseZEnd() <= m_MainMatrix.constReverseZEnd()) && !(m_MainMatrix.constReverseZEnd() > m_MainMatrix.constReverseZEnd()), "The first iterator is NOT smaller than or equal to the second iterator");

    // test if iterator is smaller than or equal to itself
    IntMatrixConstReverseZIterator it{m_MainMatrix.constReverseZBegin()};
    QVERIFY2((it <= it) && (it <= m_MainMatrix.constReverseZBegin()) && !(it > it) && !(it > m_MainMatrix.constReverseZBegin()),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstReverseZIterator(0, 1);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getConstReverseZIterator(0, 1)) && !(it > it) && !(it > m_MainMatrix.getConstReverseZIterator(0, 1)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstReverseZIterator(5, 4);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getConstReverseZIterator(5, 4)) && !(it > it) && !(it > m_MainMatrix.getConstReverseZIterator(5, 4)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstReverseZIterator(8, 6);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getConstReverseZIterator(8, 6)) && !(it > it) && !(it > m_MainMatrix.getConstReverseZIterator(8, 6)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstReverseZIterator(8, 7);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getConstReverseZIterator(8, 7) && !(it > it) && !(it > m_MainMatrix.getConstReverseZIterator(8, 7))),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.constReverseZEnd();
    QVERIFY2((it <= it) && (it <= m_MainMatrix.constReverseZEnd()) && !(it > it) && !(it > m_MainMatrix.constReverseZEnd()),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");

    // test with empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.constReverseZBegin() <= m_MainMatrix.constReverseZEnd(), "The first iterator is NOT smaller than or equal to the second iterator");
}

void ConstReverseZIteratorTests::testGreaterThanOperator()
{
    m_MainMatrix = {9, 8, -5};

    QVERIFY2((m_MainMatrix.constReverseZEnd() > m_MainMatrix.getConstReverseZIterator(0, 0)) && !(m_MainMatrix.constReverseZEnd() <= m_MainMatrix.getConstReverseZIterator(0, 0)), "TThe first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 0) > m_MainMatrix.getConstReverseZIterator(0, 1)) && !(m_MainMatrix.getConstReverseZIterator(0, 0) <= m_MainMatrix.getConstReverseZIterator(0, 1)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 1) > m_MainMatrix.getConstReverseZIterator(0, 2)) && !(m_MainMatrix.getConstReverseZIterator(0, 1) <= m_MainMatrix.getConstReverseZIterator(0, 2)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 2) > m_MainMatrix.getConstReverseZIterator(5, 4)) && !(m_MainMatrix.getConstReverseZIterator(0, 2) <= m_MainMatrix.getConstReverseZIterator(5, 4)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(5, 4) > m_MainMatrix.getConstReverseZIterator(8, 6)) && !(m_MainMatrix.getConstReverseZIterator(5, 4) <= m_MainMatrix.getConstReverseZIterator(8, 6)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(8, 6) > m_MainMatrix.constReverseZBegin()) && !(m_MainMatrix.getConstReverseZIterator(8, 6) <= m_MainMatrix.constReverseZBegin()), "The first iterator is NOT greater than the second iterator");
}

void ConstReverseZIteratorTests::testGreaterThanOrEqualToOperator()
{
    m_MainMatrix = {9, 8, -5};

    // test operator with different iterators
    QVERIFY2((m_MainMatrix.constReverseZEnd() >= m_MainMatrix.constReverseZEnd()) && !(m_MainMatrix.constReverseZEnd() < m_MainMatrix.constReverseZEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.constReverseZEnd() >= m_MainMatrix.getConstReverseZIterator(0, 0)) && !(m_MainMatrix.constReverseZEnd() < m_MainMatrix.getConstReverseZIterator(0, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 0) >= m_MainMatrix.getConstReverseZIterator(0, 0)) && !(m_MainMatrix.getConstReverseZIterator(0, 0) < m_MainMatrix.getConstReverseZIterator(0, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 0) >= m_MainMatrix.getConstReverseZIterator(0, 1)) && !(m_MainMatrix.getConstReverseZIterator(0, 0) < m_MainMatrix.getConstReverseZIterator(0, 1)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 1) >= m_MainMatrix.getConstReverseZIterator(0, 1)) && !(m_MainMatrix.getConstReverseZIterator(0, 1) < m_MainMatrix.getConstReverseZIterator(0, 1)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 1) >= m_MainMatrix.getConstReverseZIterator(0, 2)) && !(m_MainMatrix.getConstReverseZIterator(0, 1) < m_MainMatrix.getConstReverseZIterator(0, 2)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 2) >= m_MainMatrix.getConstReverseZIterator(0, 2)) && !(m_MainMatrix.getConstReverseZIterator(0, 2) < m_MainMatrix.getConstReverseZIterator(0, 2)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(0, 2) >= m_MainMatrix.getConstReverseZIterator(5, 4)) && !(m_MainMatrix.getConstReverseZIterator(0, 2) < m_MainMatrix.getConstReverseZIterator(5, 4)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(5, 4) >= m_MainMatrix.getConstReverseZIterator(5, 4)) && !(m_MainMatrix.getConstReverseZIterator(5, 4) < m_MainMatrix.getConstReverseZIterator(5, 4)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(5, 4) >= m_MainMatrix.getConstReverseZIterator(8, 6)) && !(m_MainMatrix.getConstReverseZIterator(5, 4) < m_MainMatrix.getConstReverseZIterator(8, 6)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(8, 6) >= m_MainMatrix.getConstReverseZIterator(8, 6)) && !(m_MainMatrix.getConstReverseZIterator(8, 6) < m_MainMatrix.getConstReverseZIterator(8, 6)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseZIterator(8, 6) >= m_MainMatrix.constReverseZBegin()) && !(m_MainMatrix.getConstReverseZIterator(8, 6) < m_MainMatrix.constReverseZBegin()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.constReverseZBegin() >= m_MainMatrix.constReverseZBegin()) && !(m_MainMatrix.constReverseZBegin() < m_MainMatrix.constReverseZBegin()), "The first iterator is NOT smaller than or equal to the second iterator");

    // test if iterator is greater than or equal to itself
    IntMatrixConstReverseZIterator it{m_MainMatrix.constReverseZEnd()};
    QVERIFY2((it >= it) && (it >= m_MainMatrix.constReverseZEnd()) && !(it < it) && !(it < m_MainMatrix.constReverseZEnd()),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstReverseZIterator(8, 7);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getConstReverseZIterator(8, 7)) && !(it < it) && !(it < m_MainMatrix.getConstReverseZIterator(8, 7)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstReverseZIterator(8, 6);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getConstReverseZIterator(8, 6)) && !(it < it) && !(it < m_MainMatrix.getConstReverseZIterator(8, 6)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstReverseZIterator(5, 4);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getConstReverseZIterator(5, 4)) && !(it < it) && !(it < m_MainMatrix.getConstReverseZIterator(5, 4)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstReverseZIterator(0, 1);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getConstReverseZIterator(0, 1)) && !(it < it) && !(it < m_MainMatrix.getConstReverseZIterator(0, 1)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.constReverseZBegin();
    QVERIFY2((it >= it) && (it >= m_MainMatrix.constReverseZBegin()) && !(it < it) && !(it < m_MainMatrix.constReverseZBegin()),  "The iterator is NOT greater than or equal to itself and/or the source iterator");

    // test with empty matrix
    m_MainMatrix.clear();
    QVERIFY2((m_MainMatrix.constReverseZBegin() >= m_MainMatrix.constReverseZEnd()) && !(m_MainMatrix.constReverseZBegin() < m_MainMatrix.constReverseZEnd()), "The first iterator is NOT greater than or equal to the second iterator");
}

void ConstReverseZIteratorTests::testIncrementOperators()
{
    m_MainMatrix = {9, 8, -5};

    // pre-increment
    IntMatrixConstReverseZIterator it{m_MainMatrix.constReverseZBegin()};
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 6), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 5), "Incorrect pre-incrementation");
    it = m_MainMatrix.getConstReverseZIterator(5, 5);
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 4), "Incorrect pre-incrementation");
    it = m_MainMatrix.getConstReverseZIterator(5, 2);
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 1), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 0), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(4, 7), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(4, 6), "Incorrect pre-incrementation");
    it = m_MainMatrix.getConstReverseZIterator(0, 1);
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 0), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Incorrect pre-incrementation");

    // post-increment
    it = m_MainMatrix.constReverseZBegin();
    it++;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 6), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 5), "Incorrect post-incrementation");
    it = m_MainMatrix.getConstReverseZIterator(5, 5);
    it++;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 4), "Incorrect post-incrementation");
    it = m_MainMatrix.getConstReverseZIterator(5, 2);
    it++;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 1), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 0), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(4, 7), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(4, 6), "Incorrect post-incrementation");
    it = m_MainMatrix.getConstReverseZIterator(0, 1);
    it++;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 0), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Incorrect post-incrementation");

    // test a combination of "pre" and "post" behaviors
    IntMatrixConstReverseZIterator srcIt{m_MainMatrix.getConstReverseZIterator(5, 6)};
    IntMatrixConstReverseZIterator destIt{++(++srcIt)};
    QVERIFY2(srcIt == m_MainMatrix.getConstReverseZIterator(5, 5) && destIt == m_MainMatrix.getConstReverseZIterator(5, 4), "Incorrect pre-pre-incrementation");
    srcIt = m_MainMatrix.getConstReverseZIterator(5, 6);
    destIt = (srcIt++)++;
    QVERIFY2(srcIt == m_MainMatrix.getConstReverseZIterator(5, 5) && destIt == m_MainMatrix.getConstReverseZIterator(5, 6), "Incorrect post-post-incrementation");
    srcIt = m_MainMatrix.getConstReverseZIterator(5, 6);
    destIt = (++srcIt)++;
    QVERIFY2(srcIt == m_MainMatrix.getConstReverseZIterator(5, 5) && destIt == m_MainMatrix.getConstReverseZIterator(5, 5), "Incorrect post-pre-incrementation");
    srcIt = m_MainMatrix.getConstReverseZIterator(5, 6);
    destIt = ++(srcIt++);
    QVERIFY2(srcIt == m_MainMatrix.getConstReverseZIterator(5, 5) && destIt == m_MainMatrix.getConstReverseZIterator(5, 5), "Incorrect pre-post-incrementation");
}

void ConstReverseZIteratorTests::testDecrementOperators()
{
    m_MainMatrix = {9, 8, -5};

    // pre-decrement
    IntMatrixConstReverseZIterator it{m_MainMatrix.constReverseZEnd()};
    --it;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 0), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 1), "Incorrect pre-decrementation");
    it = m_MainMatrix.getConstReverseZIterator(4, 6);
    --it;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(4, 7), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 0), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 1), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 2), "Incorrect pre-decrementation");
    it = m_MainMatrix.getConstReverseZIterator(5, 4);
    --it;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 5), "Incorrect pre-decrementation");
    it = m_MainMatrix.getConstReverseZIterator(8, 5);
    --it;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 6), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Incorrect pre-decrementation");


    // post-decrement
    it = m_MainMatrix.constReverseZEnd();
    it--;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 0), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 1), "Incorrect post-decrementation");
    it = m_MainMatrix.getConstReverseZIterator(5, 4);
    it--;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 5), "Incorrect post-decrementation");
    it = m_MainMatrix.getConstReverseZIterator(4, 6);
    it--;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(4, 7), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 0), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 1), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 2), "Incorrect post-decrementation");
    it = m_MainMatrix.getConstReverseZIterator(8, 6);
    it--;
    QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 7), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Incorrect post-decrementation");

    // test a combination of "pre" and "post" behaviors
    IntMatrixConstReverseZIterator srcIt{m_MainMatrix.getConstReverseZIterator(5, 4)};
    IntMatrixConstReverseZIterator destIt{--(--srcIt)};
    QVERIFY2(srcIt == m_MainMatrix.getConstReverseZIterator(5, 5) && destIt == m_MainMatrix.getConstReverseZIterator(5, 6), "Incorrect pre-pre-decrementation");
    srcIt = m_MainMatrix.getConstReverseZIterator(5, 4);
    destIt = (srcIt--)--;
    QVERIFY2(srcIt == m_MainMatrix.getConstReverseZIterator(5, 5) && destIt == m_MainMatrix.getConstReverseZIterator(5, 4), "Incorrect post-post-decrementation");
    srcIt = m_MainMatrix.getConstReverseZIterator(5, 4);
    destIt = (--srcIt)--;
    QVERIFY2(srcIt == m_MainMatrix.getConstReverseZIterator(5, 5) && destIt == m_MainMatrix.getConstReverseZIterator(5, 5), "Incorrect post-pre-decrementation");
    srcIt = m_MainMatrix.getConstReverseZIterator(5, 4);
    destIt = --(srcIt--);
    QVERIFY2(srcIt == m_MainMatrix.getConstReverseZIterator(5, 5) && destIt == m_MainMatrix.getConstReverseZIterator(5, 5), "Incorrect pre-post-decrementation");
}

void ConstReverseZIteratorTests::testOperatorPlus()
{
    m_MainMatrix = {9, 8, -5};

    // test for non-empty matrix
    IntMatrixConstReverseZIterator it{m_MainMatrix.constReverseZEnd()};
    QVERIFY2(it + 3 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-5) == m_MainMatrix.getConstReverseZIterator(0, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-11) == m_MainMatrix.getConstReverseZIterator(1, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-72) == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-73) == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-75) == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstReverseZIterator(0, 0);
    QVERIFY2(it + 4 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-4) == m_MainMatrix.getConstReverseZIterator(0, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-10) == m_MainMatrix.getConstReverseZIterator(1, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-70) == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-72) == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-74) == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstReverseZIterator(0, 1);
    QVERIFY2(it + 5 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-3) == m_MainMatrix.getConstReverseZIterator(0, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-9) == m_MainMatrix.getConstReverseZIterator(1, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-69) == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-70) == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-73) == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstReverseZIterator(5, 4);
    QVERIFY2(it + 48 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 46 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 45 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 44 == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 43 == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 6 == m_MainMatrix.getConstReverseZIterator(4, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.getConstReverseZIterator(5, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getConstReverseZIterator(5, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.getConstReverseZIterator(5, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-6) == m_MainMatrix.getConstReverseZIterator(6, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-26) == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-27) == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-28) == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-30) == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstReverseZIterator(8, 6);
    QVERIFY2(it + 74 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 72 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 71 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 70 == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 69 == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 24 == m_MainMatrix.getConstReverseZIterator(5, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.getConstReverseZIterator(8, 3), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-4) == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.constReverseZBegin();
    QVERIFY2(it + 75 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 73 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 72 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 71 == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 70 == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 25 == m_MainMatrix.getConstReverseZIterator(5, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 4 == m_MainMatrix.getConstReverseZIterator(8, 3), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-3) == m_MainMatrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.constReverseZBegin() + (-1) == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constReverseZBegin() + 1 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constReverseZEnd() + 0 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constReverseZEnd() + 1 == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constReverseZEnd() + (-1) == m_MainMatrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");

    // test for empty iterators
    IntMatrixConstReverseZIterator emptyIt1{};
    IntMatrixConstReverseZIterator emptyIt2{};
    IntMatrixConstReverseZIterator emptyIt3{};
    emptyIt1 = emptyIt3 + (-1);
    emptyIt2 = emptyIt3 + 1;
    QVERIFY2(emptyIt1 == emptyIt3, "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(emptyIt2 == emptyIt3, "Operator + does not work correctly, the resulting iterator is not the right one");
}

void ConstReverseZIteratorTests::testOperatorMinus()
{
    m_MainMatrix = {9, 8, -5};

    // test for non-empty matrix
    IntMatrixConstReverseZIterator it{m_MainMatrix.constReverseZEnd()};
    QVERIFY2(it - (-3) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 5 == m_MainMatrix.getConstReverseZIterator(0, 4), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 11 == m_MainMatrix.getConstReverseZIterator(1, 2), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 72 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 73 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 75 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstReverseZIterator(0, 0);
    QVERIFY2(it - (-4) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 4 == m_MainMatrix.getConstReverseZIterator(0, 4), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 10 == m_MainMatrix.getConstReverseZIterator(1, 2), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 70 == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 72 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 74 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstReverseZIterator(0, 1);
    QVERIFY2(it - (-5) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 3 == m_MainMatrix.getConstReverseZIterator(0, 4), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 9 == m_MainMatrix.getConstReverseZIterator(1, 2), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 69 == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 70 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 73 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstReverseZIterator(5, 4);
    QVERIFY2(it - (-48) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-46) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-45) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-44) == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-43) == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-6) == m_MainMatrix.getConstReverseZIterator(4, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.getConstReverseZIterator(5, 2), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getConstReverseZIterator(5, 4), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.getConstReverseZIterator(5, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 6 == m_MainMatrix.getConstReverseZIterator(6, 2), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 26 == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 27 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 28 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 30 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstReverseZIterator(8, 6);
    QVERIFY2(it - (-74) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-72) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-71) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-70) == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-69) == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-24) == m_MainMatrix.getConstReverseZIterator(5, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.getConstReverseZIterator(8, 3), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 4 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.constReverseZBegin();
    QVERIFY2(it - (-75) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-73) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-72) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-71) == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-70) == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-25) == m_MainMatrix.getConstReverseZIterator(5, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-4) == m_MainMatrix.getConstReverseZIterator(8, 3), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 3 == m_MainMatrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.constReverseZBegin() - 1 == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constReverseZBegin() - (-1) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constReverseZEnd() - 0 == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constReverseZEnd() - (-1) == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constReverseZEnd() - 1 == m_MainMatrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");

    // test for empty iterators
    IntMatrixConstReverseZIterator emptyIt1{};
    IntMatrixConstReverseZIterator emptyIt2{};
    IntMatrixConstReverseZIterator emptyIt3{};
    emptyIt1 = emptyIt3 - 1;
    emptyIt2 = emptyIt3 - (-1);
    QVERIFY2(emptyIt1 == emptyIt3, "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(emptyIt2 == emptyIt3, "Operator - does not work correctly, the resulting iterator is not the right one");
}

void ConstReverseZIteratorTests::testOperatorPlusEqual()
{
    IntMatrixConstReverseZIterator it;

    // test for non-empty matrix
    m_MainMatrix = {9, 8, -5};

    IntMatrixConstReverseZIterator referenceIt{m_MainMatrix.constReverseZEnd()};
    it = referenceIt; it += 3; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-2); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-5); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-11); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(1, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-71); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-72); QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-73); QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-75); QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstReverseZIterator(0, 0);
    it = referenceIt; it += 4; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 2; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-4); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-10); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(1, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-70); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-71); QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-72); QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-74); QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstReverseZIterator(0, 1);
    it = referenceIt; it += 5; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 3; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 2; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-3); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-9); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(1, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-69); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-70); QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-71); QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-73); QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstReverseZIterator(5, 4);
    it = referenceIt; it += 48; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 46; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 45; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 44; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 43; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 6; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(4, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 2; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-2); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-6); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(6, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-26); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-27); QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-28); QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-30); QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstReverseZIterator(8, 6);
    it = referenceIt; it += 74; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 72; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 71; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 70; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 69; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 24; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 3; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 3), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-2); QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-4); QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.constReverseZBegin();
    it = referenceIt; it += 75; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 73; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 72; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 71; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 70; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 25; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 4; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 3), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-3); QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    referenceIt = m_MainMatrix.constReverseZBegin();
    referenceIt = m_MainMatrix.constReverseZEnd();
    it = referenceIt; it += (-1); QVERIFY2(m_MainMatrix.constReverseZBegin() == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += 1; QVERIFY2(m_MainMatrix.constReverseZBegin() == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += 0; QVERIFY2(m_MainMatrix.constReverseZEnd() == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += 1; QVERIFY2(m_MainMatrix.constReverseZEnd() == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += (-1); QVERIFY2(m_MainMatrix.constReverseZEnd() == m_MainMatrix.constReverseZEnd(), "Operator += does not work correctly, the updated iterator is not the right one");

    // test for empty iterators
    IntMatrixConstReverseZIterator emptyIt1{};
    IntMatrixConstReverseZIterator emptyIt2{};
    IntMatrixConstReverseZIterator emptyIt3{};
    emptyIt2 += (-1); QVERIFY2(emptyIt2 == emptyIt1, "Operator += does not work correctly, the updated iterator is not the right one");
    emptyIt3 += 1; QVERIFY2(emptyIt3 == emptyIt1, "Operator += does not work correctly, the updated iterator is not the right one");
}

void ConstReverseZIteratorTests::testOperatorMinusEqual()
{
    IntMatrixConstReverseZIterator it;

    // test for non-empty matrix
    m_MainMatrix = {9, 8, -5};

    IntMatrixConstReverseZIterator referenceIt{m_MainMatrix.constReverseZEnd()};
    it = referenceIt; it -= (-3); QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 2; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 5; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 11; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(1, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 71; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 72; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 73; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 75; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstReverseZIterator(0, 0);
    it = referenceIt; it -= (-4); QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-2); QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 4; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 10; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(1, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 70; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 71; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 72; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 74; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstReverseZIterator(0, 1);
    it = referenceIt; it -= (-5); QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-3); QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-2); QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 3; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 9; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(1, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 69; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 70; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 71; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 73; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstReverseZIterator(5, 4);
    it = referenceIt; it -= (-48); QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-46); QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-45); QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-44); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-43); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-6); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(4, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-2); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 2; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 6; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(6, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 26; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 27; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 28; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 30; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstReverseZIterator(8, 6);
    it = referenceIt; it -= (-74); QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-72); QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-71); QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-70); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-69); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-24); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-3); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 3), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 2; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 4; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.constReverseZBegin();
    it = referenceIt; it -= (-75); QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-73); QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-72); QVERIFY2(it == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-71); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-70); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-25); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(5, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-4); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 3), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.getConstReverseZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 3; QVERIFY2(it == m_MainMatrix.constReverseZBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    referenceIt = m_MainMatrix.constReverseZBegin();
    referenceIt = m_MainMatrix.constReverseZEnd();
    it = referenceIt; it -= 1; QVERIFY2(m_MainMatrix.constReverseZBegin() == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= (-1); QVERIFY2(m_MainMatrix.constReverseZBegin() == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= 0; QVERIFY2(m_MainMatrix.constReverseZEnd() == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= (-1); QVERIFY2(m_MainMatrix.constReverseZEnd() == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= 1; QVERIFY2(m_MainMatrix.constReverseZEnd() == m_MainMatrix.constReverseZEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");

    // test for empty iterators
    IntMatrixConstReverseZIterator emptyIt1{};
    IntMatrixConstReverseZIterator emptyIt2{};
    IntMatrixConstReverseZIterator emptyIt3{};
    emptyIt2 -= 1; QVERIFY2(emptyIt2 == emptyIt1, "Operator -= does not work correctly, the updated iterator is not the right one");
    emptyIt3 -= (-1); QVERIFY2(emptyIt3 == emptyIt1, "Operator -= does not work correctly, the updated iterator is not the right one");
}

void ConstReverseZIteratorTests::testDifferenceOperator()
{
    // test for non-empty matrix
    m_MainMatrix = {9, 8, -5};

    QVERIFY2(m_MainMatrix.constReverseZBegin() - m_MainMatrix.constReverseZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseZBegin() - m_MainMatrix.getConstReverseZIterator(8, 6) == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseZBegin() - m_MainMatrix.getConstReverseZIterator(5, 4) == -27, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseZBegin() - m_MainMatrix.getConstReverseZIterator(0, 1) == -70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseZBegin() - m_MainMatrix.getConstReverseZIterator(0, 0) == -71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseZBegin() - m_MainMatrix.constReverseZEnd() == -72, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getConstReverseZIterator(8, 6) - m_MainMatrix.constReverseZBegin() == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(8, 6) - m_MainMatrix.getConstReverseZIterator(8, 6) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(8, 6) - m_MainMatrix.getConstReverseZIterator(5, 4) == -26, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(8, 6) - m_MainMatrix.getConstReverseZIterator(0, 1) == -69, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(8, 6) - m_MainMatrix.getConstReverseZIterator(0, 0) == -70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(8, 6) - m_MainMatrix.constReverseZEnd() == -71, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getConstReverseZIterator(5, 4) - m_MainMatrix.constReverseZBegin() == 27, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(5, 4) - m_MainMatrix.getConstReverseZIterator(8, 6) == 26, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(5, 4) - m_MainMatrix.getConstReverseZIterator(5, 4) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(5, 4) - m_MainMatrix.getConstReverseZIterator(0, 1) == -43, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(5, 4) - m_MainMatrix.getConstReverseZIterator(0, 0) == -44, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(5, 4) - m_MainMatrix.constReverseZEnd() == -45, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getConstReverseZIterator(0, 1) - m_MainMatrix.constReverseZBegin() == 70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(0, 1) - m_MainMatrix.getConstReverseZIterator(8, 6) == 69, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(0, 1) - m_MainMatrix.getConstReverseZIterator(5, 4) == 43, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(0, 1) - m_MainMatrix.getConstReverseZIterator(0, 1) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(0, 1) - m_MainMatrix.getConstReverseZIterator(0, 0) == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(0, 1) - m_MainMatrix.constReverseZEnd() == -2, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getConstReverseZIterator(0, 0) - m_MainMatrix.constReverseZBegin() == 71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(0, 0) - m_MainMatrix.getConstReverseZIterator(8, 6) == 70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(0, 0) - m_MainMatrix.getConstReverseZIterator(5, 4) == 44, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(0, 0) - m_MainMatrix.getConstReverseZIterator(0, 1) == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(0, 0) - m_MainMatrix.getConstReverseZIterator(0, 0) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(0, 0) - m_MainMatrix.constReverseZEnd() == -1, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.constReverseZEnd() - m_MainMatrix.constReverseZBegin() == 72, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseZEnd() - m_MainMatrix.getConstReverseZIterator(8, 6) == 71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseZEnd() - m_MainMatrix.getConstReverseZIterator(5, 4) == 45, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseZEnd() - m_MainMatrix.getConstReverseZIterator(0, 1) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseZEnd() - m_MainMatrix.getConstReverseZIterator(0, 0) == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseZEnd() - m_MainMatrix.constReverseZEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");

    // additional tests with "random" elements from same row/different rows
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(5, 4) - m_MainMatrix.getConstReverseZIterator(7, 2) == 14, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(7, 2) - m_MainMatrix.getConstReverseZIterator(5, 4) == -14, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(5, 4) - m_MainMatrix.getConstReverseZIterator(5, 2) == -2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseZIterator(5, 2) - m_MainMatrix.getConstReverseZIterator(5, 4) == 2, "The difference operator does not work correctly, difference between iterators is wrong");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.constReverseZEnd() - m_MainMatrix.constReverseZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseZBegin() - m_MainMatrix.constReverseZEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseZBegin() - m_MainMatrix.constReverseZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseZEnd() - m_MainMatrix.constReverseZEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");

    // test for empty iterator
    IntMatrixConstReverseZIterator emptyIt1{};
    IntMatrixConstReverseZIterator emptyIt2{};
    QVERIFY2(emptyIt1 - emptyIt2 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(emptyIt2 - emptyIt1 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(emptyIt1 - emptyIt1 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
}

void ConstReverseZIteratorTests::testDereferenceAsteriskOperator()
{
    // test reading element
    m_MainMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};
    QVERIFY2(*m_MainMatrix.getConstReverseZIterator(0, 0) == 1, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getConstReverseZIterator(0, 1) == -2, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getConstReverseZIterator(1, 2) == -6, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getConstReverseZIterator(3, 1) == 11, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.constReverseZBegin() == -12, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");

    // additional test
    m_MainMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    IntMatrixConstReverseZIterator readIter{m_MainMatrix.constReverseZBegin()};
    m_MainMatrix.at(1, 0) = 10;
    readIter += 2;
    QVERIFY2(*readIter == 10, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
}

void ConstReverseZIteratorTests::testDereferenceArrowOperator()
{
    // test reading element
    m_AuxStringMatrix = {4, 3, {"abc", "ba", "abcd", "jihgfedcba", "a", "gfedcba", "abcde", "ihgfedcba", "abcdefgh", "", "abcdefghijk", "fedcba"}};
    QVERIFY2(m_AuxStringMatrix.getConstReverseZIterator(0, 0)->size() == 3, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getConstReverseZIterator(0, 1)->size() == 2, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getConstReverseZIterator(1, 2)->size() == 7, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getConstReverseZIterator(3, 1)->size() == 11, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.constReverseZBegin()->size() == 6, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");

    // additional test
    m_AuxStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mnop", "qr"}};
    StringMatrixConstReverseZIterator it{m_AuxStringMatrix.constReverseZBegin()};
    m_AuxStringMatrix.at(1, 0) = "abcdefghi";
    it += 2;
    QVERIFY2(it->size() == 9, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
}

void ConstReverseZIteratorTests::testDereferenceSquareBracketsOperator()
{
    // test reading element
    m_MainMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};

    IntMatrixConstReverseZIterator it{m_MainMatrix.constReverseZBegin()};
    QVERIFY2(it[11] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[10] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[6] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[1] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getConstReverseZIterator(3, 1);
    QVERIFY2(it[10] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[9] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[5] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-1] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getConstReverseZIterator(1, 2);
    QVERIFY2(it[5] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[4] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-5] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-6] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getConstReverseZIterator(0, 1);
    QVERIFY2(it[1] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-4] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-9] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-10] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getConstReverseZIterator(0, 0);
    QVERIFY2(it[0] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-1] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-5] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-10] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-11] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");
}

void ConstReverseZIteratorTests::testStdCount()
{
    using namespace std;

    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};

    int matchCount{count(m_MainMatrix.constReverseZBegin(), m_MainMatrix.constReverseZEnd(), 2)};
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseZBegin(), m_MainMatrix.constReverseZEnd(), -5);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseZIterator(1, 4), m_MainMatrix.getConstReverseZIterator(0, 3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseZIterator(2, 0), m_MainMatrix.getConstReverseZIterator(0, 2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseZIterator(2, 0), m_MainMatrix.getConstReverseZIterator(0, 3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseZIterator(1, 4), m_MainMatrix.getConstReverseZIterator(0, 2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseZBegin(), m_MainMatrix.getConstReverseZIterator(2, 3), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseZIterator(2, 3), m_MainMatrix.constReverseZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseZBegin(), m_MainMatrix.getConstReverseZIterator(2, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseZIterator(2, 2), m_MainMatrix.constReverseZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseZIterator(9), m_MainMatrix.getConstReverseZIterator(2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseZIterator(10), m_MainMatrix.getConstReverseZIterator(2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseZIterator(9), m_MainMatrix.getConstReverseZIterator(3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseZIterator(10), m_MainMatrix.getConstReverseZIterator(3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseZBegin(), m_MainMatrix.getConstReverseZIterator(13), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseZIterator(13), m_MainMatrix.constReverseZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseZBegin(), m_MainMatrix.getConstReverseZIterator(12), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseZIterator(12), m_MainMatrix.constReverseZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseZRowBegin(1), m_MainMatrix.constReverseZRowEnd(1), 5);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseZRowEnd(3), m_MainMatrix.constReverseZRowEnd(0), 8);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseZRowBegin(3), m_MainMatrix.constReverseZRowEnd(3), 9);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseZRowBegin(3), m_MainMatrix.constReverseZRowEnd(2), 9);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseZRowEnd(1), m_MainMatrix.constReverseZEnd(), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseZBegin(), m_MainMatrix.constReverseZRowEnd(1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseZRowBegin(2), m_MainMatrix.constReverseZEnd(), 1);
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseZBegin(), m_MainMatrix.constReverseZRowBegin(2), 1);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
}

void ConstReverseZIteratorTests::testStdFind()
{
    using namespace std;

    // test finding elements in specific ranges within unempty matrix
    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, -2, 2, 8, 9, -7, 7, 2, 9, 11}};

    QVERIFY2(find(m_MainMatrix.constReverseZBegin(), m_MainMatrix.constReverseZEnd(), 5) != m_MainMatrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZBegin(), m_MainMatrix.constReverseZEnd(), 10) == m_MainMatrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZRowBegin(1), m_MainMatrix.constReverseZRowEnd(1), 6) != m_MainMatrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZRowBegin(1), m_MainMatrix.constReverseZRowEnd(1), 5) != m_MainMatrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZRowBegin(1), m_MainMatrix.constReverseZRowEnd(1), 8) != m_MainMatrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZRowBegin(1), m_MainMatrix.constReverseZRowEnd(1), -1) == m_MainMatrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZRowBegin(1), m_MainMatrix.constReverseZRowEnd(1), 1) == m_MainMatrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZRowBegin(1), m_MainMatrix.constReverseZRowEnd(1), 10) == m_MainMatrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZRowBegin(1), m_MainMatrix.constReverseZEnd(), 6) != m_MainMatrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZRowBegin(1), m_MainMatrix.constReverseZEnd(), -1) != m_MainMatrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZRowBegin(1), m_MainMatrix.constReverseZEnd(), 3) != m_MainMatrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZRowBegin(1), m_MainMatrix.constReverseZEnd(), -2) == m_MainMatrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZRowBegin(1), m_MainMatrix.constReverseZEnd(), 10) == m_MainMatrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZBegin(), m_MainMatrix.constReverseZRowEnd(1), 11) != m_MainMatrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZBegin(), m_MainMatrix.constReverseZRowEnd(1), 5) != m_MainMatrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZBegin(), m_MainMatrix.constReverseZRowEnd(1), 0) != m_MainMatrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZBegin(), m_MainMatrix.constReverseZRowEnd(1), 1) == m_MainMatrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZBegin(), m_MainMatrix.constReverseZRowEnd(1), 10) == m_MainMatrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseZIterator(3, 1), m_MainMatrix.getConstReverseZIterator(1, 3), 7) != m_MainMatrix.getConstReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseZIterator(3, 1), m_MainMatrix.getConstReverseZIterator(1, 3), -7) != m_MainMatrix.getConstReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseZIterator(3, 1), m_MainMatrix.getConstReverseZIterator(1, 3), -2) != m_MainMatrix.getConstReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseZIterator(3, 1), m_MainMatrix.getConstReverseZIterator(1, 3), -1) == m_MainMatrix.getConstReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseZIterator(3, 1), m_MainMatrix.getConstReverseZIterator(1, 3), 11) == m_MainMatrix.getConstReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseZIterator(3, 1), m_MainMatrix.getConstReverseZIterator(1, 3), 10) == m_MainMatrix.getConstReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseZIterator(1, 3), m_MainMatrix.constReverseZEnd(), 0) != m_MainMatrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseZIterator(1, 3), m_MainMatrix.constReverseZEnd(), -1) != m_MainMatrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseZIterator(1, 3), m_MainMatrix.constReverseZEnd(), 4) != m_MainMatrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseZIterator(1, 3), m_MainMatrix.constReverseZEnd(), 11) == m_MainMatrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseZIterator(1, 3), m_MainMatrix.constReverseZEnd(), 10) == m_MainMatrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZBegin(), m_MainMatrix.getConstReverseZIterator(3, 1), 11) != m_MainMatrix.getConstReverseZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZBegin(), m_MainMatrix.getConstReverseZIterator(3, 1), 2) != m_MainMatrix.getConstReverseZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZBegin(), m_MainMatrix.getConstReverseZIterator(3, 1), 9) != m_MainMatrix.getConstReverseZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZBegin(), m_MainMatrix.getConstReverseZIterator(3, 1), 0) == m_MainMatrix.getConstReverseZIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseZBegin(), m_MainMatrix.getConstReverseZIterator(3, 1), 10) == m_MainMatrix.getConstReverseZIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

    // other tests
    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};
    IntMatrixConstReverseZIterator it{find(m_MainMatrix.constReverseZBegin(), m_MainMatrix.constReverseZEnd(), 4)};
    ++it;
    QVERIFY2(*it == 1, "The iterator doesn't work correctly with std::find, incorrect next element returned");

    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};
    QVERIFY2(find(m_MainMatrix.constReverseZBegin(), m_MainMatrix.constReverseZEnd(), 10) == m_MainMatrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix");

    it = m_MainMatrix.constReverseZBegin();
    while(it != m_MainMatrix.constReverseZEnd())
    {
        it = find(it, m_MainMatrix.constReverseZEnd(), 9);

        if (it != m_MainMatrix.constReverseZEnd())
        {
            m_MainMatrix.at(it.getRowNr(), it.getColumnNr()) = 10;
        }
    }
    int expectedNumber{std::count(m_MainMatrix.constReverseZBegin(), m_MainMatrix.constReverseZEnd(), 10)};
    QVERIFY2(expectedNumber == 3, "The iterator doesn't work properly with std::find, element values haven't been correctly replaced");
}

QTEST_APPLESS_MAIN(ConstReverseZIteratorTests)

#include "tst_constreverseziteratortests.moc"
