#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixNIterator = Matrix<int>::NIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixNIterator = Matrix<std::string>::NIterator;

class NIteratorTests : public QObject
{
    Q_OBJECT

public:
    NIteratorTests();
    ~NIteratorTests();

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

NIteratorTests::NIteratorTests()
{
}

NIteratorTests::~NIteratorTests()
{
}

void NIteratorTests::testIteratorCreation()
{
    m_MainMatrix = {8, 9, -5};

    IntMatrixNIterator it{m_MainMatrix.nBegin()};
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.nEnd();
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.nColumnBegin(0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.nColumnBegin(1);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.nColumnBegin(4);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 4 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.nColumnBegin(7);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.nColumnBegin(8);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.nColumnEnd(0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.nColumnEnd(1);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 2 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.nColumnEnd(4);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 5 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.nColumnEnd(7);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.nColumnEnd(8);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getNIterator(0, 0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getNIterator(1, 0);
    QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getNIterator(4, 5);
    QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 5 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getNIterator(6, 8);
    QVERIFY2(it.getCurrentRowNr() == 6 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getNIterator(7, 8);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getNIterator(0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getNIterator(1);
    QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getNIterator(44);
    QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 5 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getNIterator(70);
    QVERIFY2(it.getCurrentRowNr() == 6 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getNIterator(71);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // test iterator creation for empty matrix
    m_MainMatrix.clear();
    it = m_MainMatrix.nBegin();
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.nEnd();
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // test empty iterator creation (not bound to any matrix) - an empty iterator should be valid for any empty matrix
    IntMatrixNIterator emptyIt;
    QVERIFY2(emptyIt.getCurrentRowNr() == -1 && emptyIt.getCurrentColumnNr() == -1 && emptyIt.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // additional test
    m_MainMatrix = {8, 9, -5};
    m_AuxIntMatrix = {8, 9, -5};
    it = m_MainMatrix.getNIterator(4, 5);
    QVERIFY(!it.isValidWithMatrix(m_AuxIntMatrix));
    m_AuxIntMatrix.clear();
    QVERIFY(!it.isValidWithMatrix(m_AuxIntMatrix));
    it = m_AuxIntMatrix.nBegin();
    QVERIFY(!it.isValidWithMatrix(m_MainMatrix));
    it = m_AuxIntMatrix.nEnd();
    QVERIFY(!it.isValidWithMatrix(m_MainMatrix));
    m_MainMatrix.clear();
    it = m_MainMatrix.nBegin();
    QVERIFY(it.isValidWithMatrix(m_AuxIntMatrix)); // an iterator of an empty matrix is valid with any other empty matrix
    it = m_MainMatrix.nEnd();
    QVERIFY(it.isValidWithMatrix(m_AuxIntMatrix));
}

void NIteratorTests::testIteratorsAreEqual()
{

    m_MainMatrix = {8, 9, -5};

    // test different iterators for equality
    QVERIFY2((m_MainMatrix.nBegin() == m_MainMatrix.getNIterator(0, 0) && !(m_MainMatrix.nBegin() != m_MainMatrix.getNIterator(0, 0))), "The two iterators are not equal");
    QVERIFY2((m_MainMatrix.getNIterator(0) == m_MainMatrix.getNIterator(0, 0)) && !(m_MainMatrix.getNIterator(0) != m_MainMatrix.getNIterator(0, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getNIterator(1) == m_MainMatrix.getNIterator(1, 0)) && !(m_MainMatrix.getNIterator(1) != m_MainMatrix.getNIterator(1, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getNIterator(44) == m_MainMatrix.getNIterator(4, 5)) && !(m_MainMatrix.getNIterator(44) != m_MainMatrix.getNIterator(4, 5)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getNIterator(70) == m_MainMatrix.getNIterator(6, 8)) && !(m_MainMatrix.getNIterator(70) != m_MainMatrix.getNIterator(6, 8)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getNIterator(71) == m_MainMatrix.getNIterator(7, 8)) && !(m_MainMatrix.getNIterator(71) != m_MainMatrix.getNIterator(7, 8)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.nColumnBegin(0) == m_MainMatrix.getNIterator(0, 0)) && !(m_MainMatrix.nColumnBegin(0) != m_MainMatrix.getNIterator(0, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.nColumnBegin(1) == m_MainMatrix.getNIterator(0, 1)) && !(m_MainMatrix.nColumnBegin(1) != m_MainMatrix.getNIterator(0, 1)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.nColumnBegin(5) == m_MainMatrix.getNIterator(0, 5)) && !(m_MainMatrix.nColumnBegin(5) != m_MainMatrix.getNIterator(0, 5)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.nColumnBegin(7) == m_MainMatrix.getNIterator(0, 7)) && !(m_MainMatrix.nColumnBegin(7) != m_MainMatrix.getNIterator(0, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.nColumnBegin(8) == m_MainMatrix.getNIterator(0, 8)) && !(m_MainMatrix.nColumnBegin(8) != m_MainMatrix.getNIterator(0, 8)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.nColumnEnd(0) == m_MainMatrix.getNIterator(0, 1)) && !(m_MainMatrix.nColumnEnd(0) != m_MainMatrix.getNIterator(0, 1)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.nColumnEnd(1) == m_MainMatrix.getNIterator(0, 2)) && !(m_MainMatrix.nColumnEnd(1) != m_MainMatrix.getNIterator(0, 2)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.nColumnEnd(5) == m_MainMatrix.getNIterator(0, 6)) && !(m_MainMatrix.nColumnEnd(5) != m_MainMatrix.getNIterator(0, 6)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.nColumnEnd(7) == m_MainMatrix.getNIterator(0, 8)) && !(m_MainMatrix.nColumnEnd(7) != m_MainMatrix.getNIterator(0, 8)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.nColumnEnd(8) == m_MainMatrix.nEnd()) && !(m_MainMatrix.nColumnEnd(8) != m_MainMatrix.nEnd()), "The two iterators are NOT equal");

    // test iterator equality to itself
    IntMatrixNIterator it{m_MainMatrix.nBegin()};
    QVERIFY2((it == it) && (it == m_MainMatrix.nBegin()) && !(it != it) && !(it != m_MainMatrix.nBegin()), "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getNIterator(1, 0);
    QVERIFY2((it == it) && (it == m_MainMatrix.getNIterator(1, 0)) && !(it != it) && !(it != m_MainMatrix.getNIterator(1, 0)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getNIterator(4, 5);
    QVERIFY2((it == it) && (it == m_MainMatrix.getNIterator(4, 5)) && !(it != it) && !(it != m_MainMatrix.getNIterator(4, 5)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getNIterator(6, 8);
    QVERIFY2((it == it) && (it == m_MainMatrix.getNIterator(6, 8)) && !(it != it) && !(it != m_MainMatrix.getNIterator(6, 8)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getNIterator(7, 8);
    QVERIFY2((it == it) && (it == m_MainMatrix.getNIterator(7, 8)) && !(it != it) && !(it != m_MainMatrix.getNIterator(7, 8)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.nEnd();
    QVERIFY2((it == it) && (it == m_MainMatrix.nEnd()) && !(it != it) && !(it != m_MainMatrix.nEnd()),  "The iterator is NOT equal to itself and/or to source iterator");

    // test empty matrix iterator equality
    m_MainMatrix.clear();
    QVERIFY2((m_MainMatrix.nBegin() == m_MainMatrix.nEnd()) && !(m_MainMatrix.nBegin() != m_MainMatrix.nEnd()), "The two iterators are NOT equal");
}

void NIteratorTests::testIteratorsAreNotEqual()
{
    m_MainMatrix = {8, 9, -5};

    QVERIFY2((m_MainMatrix.nBegin() != m_MainMatrix.getNIterator(1, 0)) && !(m_MainMatrix.nBegin() == m_MainMatrix.getNIterator(1, 0)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getNIterator(1, 0) != m_MainMatrix.getNIterator(2, 0)) && !(m_MainMatrix.getNIterator(1, 0) == m_MainMatrix.getNIterator(2, 0)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getNIterator(2, 0) != m_MainMatrix.getNIterator(4, 5)) && !(m_MainMatrix.getNIterator(2, 0) == m_MainMatrix.getNIterator(4, 5)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getNIterator(4, 5) != m_MainMatrix.getNIterator(6, 8)) && !(m_MainMatrix.getNIterator(4, 5) == m_MainMatrix.getNIterator(6, 8)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getNIterator(6, 8) != m_MainMatrix.getNIterator(7, 8)) && !(m_MainMatrix.getNIterator(6, 8) == m_MainMatrix.getNIterator(7, 8)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getNIterator(7, 8) != m_MainMatrix.nEnd()) && !(m_MainMatrix.getNIterator(7, 8) == m_MainMatrix.nEnd()), "The two iterators are NOT different");
}

void NIteratorTests::testSmallerThanOperator()
{
    m_MainMatrix = {8, 9, -5};

    QVERIFY2((m_MainMatrix.nBegin() < m_MainMatrix.getNIterator(1, 0)) && !(m_MainMatrix.nBegin() >= m_MainMatrix.getNIterator(1, 0)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(1, 0) < m_MainMatrix.getNIterator(2, 0)) && !(m_MainMatrix.getNIterator(1, 0) >= m_MainMatrix.getNIterator(2, 0)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(2, 0) < m_MainMatrix.getNIterator(4, 5)) && !(m_MainMatrix.getNIterator(2, 0) >= m_MainMatrix.getNIterator(4, 5)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(4, 5) < m_MainMatrix.getNIterator(6, 8)) && !(m_MainMatrix.getNIterator(4, 5) >= m_MainMatrix.getNIterator(6, 8)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(6, 8) < m_MainMatrix.getNIterator(7, 8)) && !(m_MainMatrix.getNIterator(6, 8) >= m_MainMatrix.getNIterator(7, 8)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(7, 8) < m_MainMatrix.nEnd()) && !(m_MainMatrix.getNIterator(7, 8) >= m_MainMatrix.nEnd()), "The first iterator is NOT smaller than the second iterator");
}

void NIteratorTests::testSmallerThanOrEqualToOperator()
{
    m_MainMatrix = {8, 9, -5};

    // test operator with different iterators
    QVERIFY2((m_MainMatrix.nBegin() <= m_MainMatrix.nBegin()) && !(m_MainMatrix.nBegin() > m_MainMatrix.nEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.nBegin() <= m_MainMatrix.getNIterator(1, 0)) && !(m_MainMatrix.getNIterator(7, 8) > m_MainMatrix.nEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(1, 0) <= m_MainMatrix.getNIterator(1, 0)) && !(m_MainMatrix.getNIterator(1, 0) > m_MainMatrix.getNIterator(1, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(1, 0) <= m_MainMatrix.getNIterator(2, 0)) && !(m_MainMatrix.getNIterator(1, 0) > m_MainMatrix.getNIterator(2, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(2, 0) <= m_MainMatrix.getNIterator(2, 0)) && !(m_MainMatrix.getNIterator(2, 0) > m_MainMatrix.getNIterator(2, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(2, 0) <= m_MainMatrix.getNIterator(4, 5)) && !(m_MainMatrix.getNIterator(2, 0) > m_MainMatrix.getNIterator(4, 5)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(4, 5) <= m_MainMatrix.getNIterator(4, 5)) && !(m_MainMatrix.getNIterator(4, 5) > m_MainMatrix.getNIterator(4, 5)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(4, 5) <= m_MainMatrix.getNIterator(6, 8)) && !(m_MainMatrix.getNIterator(4, 5) > m_MainMatrix.getNIterator(6, 8)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(6, 8) <= m_MainMatrix.getNIterator(6, 8)) && !(m_MainMatrix.getNIterator(6, 8) > m_MainMatrix.getNIterator(6, 8)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(6, 8) <= m_MainMatrix.getNIterator(7, 8)) && !(m_MainMatrix.getNIterator(6, 8) > m_MainMatrix.getNIterator(7, 8)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(7, 8) <= m_MainMatrix.getNIterator(7, 8)) && !(m_MainMatrix.getNIterator(7, 8) > m_MainMatrix.getNIterator(7, 8)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(7, 8) <= m_MainMatrix.nEnd()) && !(m_MainMatrix.getNIterator(7, 8) > m_MainMatrix.nEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.nEnd() <= m_MainMatrix.nEnd()) && !(m_MainMatrix.nEnd() > m_MainMatrix.nEnd()), "The first iterator is NOT smaller than or equal to the second iterator");

    // test if iterator is smaller than or equal to itself
    IntMatrixNIterator it{m_MainMatrix.nBegin()};
    QVERIFY2((it <= it) && (it <= m_MainMatrix.nBegin()) && !(it > it) && !(it > m_MainMatrix.nBegin()),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getNIterator(1, 0);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getNIterator(1, 0)) && !(it > it) && !(it > m_MainMatrix.getNIterator(1, 0)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getNIterator(4, 5);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getNIterator(4, 5)) && !(it > it) && !(it > m_MainMatrix.getNIterator(4, 5)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getNIterator(6, 8);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getNIterator(6, 8)) && !(it > it) && !(it > m_MainMatrix.getNIterator(6, 8)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getNIterator(7, 8);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getNIterator(7, 8) && !(it > it) && !(it > m_MainMatrix.getNIterator(7, 8))),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.nEnd();
    QVERIFY2((it <= it) && (it <= m_MainMatrix.nEnd()) && !(it > it) && !(it > m_MainMatrix.nEnd()),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");

    // test with empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.nBegin() <= m_MainMatrix.nEnd(), "The first iterator is NOT smaller than or equal to the second iterator");
}

void NIteratorTests::testGreaterThanOperator()
{
    m_MainMatrix = {8, 9, -5};

    QVERIFY2((m_MainMatrix.nEnd() > m_MainMatrix.getNIterator(7, 8)) && !(m_MainMatrix.nEnd() <= m_MainMatrix.getNIterator(7, 8)), "TThe first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(7, 8) > m_MainMatrix.getNIterator(6, 8)) && !(m_MainMatrix.getNIterator(7, 8) <= m_MainMatrix.getNIterator(6, 8)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(6, 8) > m_MainMatrix.getNIterator(4, 5)) && !(m_MainMatrix.getNIterator(6, 8) <= m_MainMatrix.getNIterator(4, 5)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(4, 5) > m_MainMatrix.getNIterator(2, 0)) && !(m_MainMatrix.getNIterator(4, 5) <= m_MainMatrix.getNIterator(2, 0)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(2, 0) > m_MainMatrix.getNIterator(1, 0)) && !(m_MainMatrix.getNIterator(2, 0) <= m_MainMatrix.getNIterator(1, 0)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(1, 0) > m_MainMatrix.nBegin()) && !(m_MainMatrix.getNIterator(1, 0) <= m_MainMatrix.nBegin()), "The first iterator is NOT greater than the second iterator");
}

void NIteratorTests::testGreaterThanOrEqualToOperator()
{
    m_MainMatrix = {8, 9, -5};

    // test operator with different iterators
    QVERIFY2((m_MainMatrix.nEnd() >= m_MainMatrix.nEnd()) && !(m_MainMatrix.nEnd() < m_MainMatrix.nEnd()), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.nEnd() >= m_MainMatrix.getNIterator(7, 8)) && !(m_MainMatrix.nEnd() < m_MainMatrix.getNIterator(7, 8)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(7, 8) >= m_MainMatrix.getNIterator(7, 8)) && !(m_MainMatrix.getNIterator(7, 8) < m_MainMatrix.getNIterator(7, 8)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(7, 8) >= m_MainMatrix.getNIterator(6, 8)) && !(m_MainMatrix.getNIterator(7, 8) < m_MainMatrix.getNIterator(6, 8)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(6, 8) >= m_MainMatrix.getNIterator(6, 8)) && !(m_MainMatrix.getNIterator(6, 8) < m_MainMatrix.getNIterator(6, 8)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(6, 8) >= m_MainMatrix.getNIterator(4, 5)) && !(m_MainMatrix.getNIterator(6, 8) < m_MainMatrix.getNIterator(4, 5)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(4, 5) >= m_MainMatrix.getNIterator(4, 5)) && !(m_MainMatrix.getNIterator(4, 5) < m_MainMatrix.getNIterator(4, 5)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(4, 5) >= m_MainMatrix.getNIterator(2, 0)) && !(m_MainMatrix.getNIterator(4, 5) < m_MainMatrix.getNIterator(2, 0)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(2, 0) >= m_MainMatrix.getNIterator(2, 0)) && !(m_MainMatrix.getNIterator(2, 0) < m_MainMatrix.getNIterator(2, 0)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(2, 0) >= m_MainMatrix.getNIterator(1, 0)) && !(m_MainMatrix.getNIterator(2, 0) < m_MainMatrix.getNIterator(1, 0)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(1, 0) >= m_MainMatrix.getNIterator(1, 0)) && !(m_MainMatrix.getNIterator(1, 0) < m_MainMatrix.getNIterator(1, 0)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getNIterator(1, 0) >= m_MainMatrix.nBegin()) && !(m_MainMatrix.getNIterator(1, 0) < m_MainMatrix.nBegin()), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.nBegin() >= m_MainMatrix.nBegin()) && !(m_MainMatrix.nBegin() < m_MainMatrix.nBegin()), "The first iterator is NOT greater than or equal to the second iterator");

    // test if iterator is greater than or equal to itself
    IntMatrixNIterator it{m_MainMatrix.nEnd()};
    QVERIFY2((it >= it) && (it >= m_MainMatrix.nEnd()) && !(it < it) && !(it < m_MainMatrix.nEnd()),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getNIterator(7, 8);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getNIterator(7, 8)) && !(it < it) && !(it < m_MainMatrix.getNIterator(7, 8)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getNIterator(6, 8);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getNIterator(6, 8)) && !(it < it) && !(it < m_MainMatrix.getNIterator(6, 8)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getNIterator(4, 5);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getNIterator(4, 5)) && !(it < it) && !(it < m_MainMatrix.getNIterator(4, 5)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getNIterator(1, 0);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getNIterator(1, 0)) && !(it < it) && !(it < m_MainMatrix.getNIterator(1, 0)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.nBegin();
    QVERIFY2((it >= it) && (it >= m_MainMatrix.nBegin()) && !(it < it) && !(it < m_MainMatrix.nBegin()),  "The iterator is NOT greater than or equal to itself and/or the source iterator");

    // test with empty matrix
    m_MainMatrix.clear();
    QVERIFY2((m_MainMatrix.nBegin() >= m_MainMatrix.nEnd()) && !(m_MainMatrix.nBegin() < m_MainMatrix.nEnd()), "The first iterator is NOT greater than or equal to the second iterator");
}

void NIteratorTests::testIncrementOperators()
{
    m_MainMatrix = {8, 9, -5};

    // pre-increment
    IntMatrixNIterator it{m_MainMatrix.nBegin()};
    ++it;
    QVERIFY2(it == m_MainMatrix.getNIterator(1, 0), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getNIterator(2, 0), "Incorrect pre-incrementation");
    it = m_MainMatrix.getNIterator(6, 4);
    ++it;
    QVERIFY2(it == m_MainMatrix.getNIterator(7, 4), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getNIterator(0, 5), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getNIterator(1, 5), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getNIterator(2, 5), "Incorrect pre-incrementation");
    it = m_MainMatrix.getNIterator(4, 5);
    ++it;
    QVERIFY2(it == m_MainMatrix.getNIterator(5, 5), "Incorrect pre-incrementation");
    it = m_MainMatrix.getNIterator(6, 8);
    ++it;
    QVERIFY2(it == m_MainMatrix.getNIterator(7, 8), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.nEnd(), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.nEnd(), "Incorrect pre-incrementation");

    // post-increment
    it = m_MainMatrix.nBegin();
    it++;
    QVERIFY2(it == m_MainMatrix.getNIterator(1, 0), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getNIterator(2, 0), "Incorrect post-incrementation");
    it = m_MainMatrix.getNIterator(6, 4);
    it++;
    QVERIFY2(it == m_MainMatrix.getNIterator(7, 4), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getNIterator(0, 5), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getNIterator(1, 5), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getNIterator(2, 5), "Incorrect post-incrementation");
    it = m_MainMatrix.getNIterator(4, 5);
    it++;
    QVERIFY2(it == m_MainMatrix.getNIterator(5, 5), "Incorrect post-incrementation");
    it = m_MainMatrix.getNIterator(6, 8);
    it++;
    QVERIFY2(it == m_MainMatrix.getNIterator(7, 8), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.nEnd(), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.nEnd(), "Incorrect post-incrementation");

    // test a combination of "pre" and "post" behaviors
    IntMatrixNIterator srcIt{m_MainMatrix.getNIterator(4, 5)};
    IntMatrixNIterator destIt{++(++srcIt)};
    QVERIFY2(srcIt == m_MainMatrix.getNIterator(5, 5) && destIt == m_MainMatrix.getNIterator(6, 5), "Incorrect pre-pre-incrementation");
    srcIt = m_MainMatrix.getNIterator(4, 5);
    destIt = (srcIt++)++;
    QVERIFY2(srcIt == m_MainMatrix.getNIterator(5, 5) && destIt == m_MainMatrix.getNIterator(4, 5), "Incorrect post-post-incrementation");
    srcIt = m_MainMatrix.getNIterator(4, 5);
    destIt = (++srcIt)++;
    QVERIFY2(srcIt == m_MainMatrix.getNIterator(5, 5) && destIt == m_MainMatrix.getNIterator(5, 5), "Incorrect post-pre-incrementation");
    srcIt = m_MainMatrix.getNIterator(4, 5);
    destIt = ++(srcIt++);
    QVERIFY2(srcIt == m_MainMatrix.getNIterator(5, 5) && destIt == m_MainMatrix.getNIterator(5, 5), "Incorrect pre-post-incrementation");
}

void NIteratorTests::testDecrementOperators()
{
    m_MainMatrix = {8, 9, -5};

    // pre-decrement
    IntMatrixNIterator it{m_MainMatrix.nEnd()};
    --it;
    QVERIFY2(it == m_MainMatrix.getNIterator(7, 8), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getNIterator(6, 8), "Incorrect pre-decrementation");
    it = m_MainMatrix.getNIterator(5, 5);
    --it;
    QVERIFY2(it == m_MainMatrix.getNIterator(4, 5), "Incorrect pre-decrementation");
    it = m_MainMatrix.getNIterator(2, 5);
    --it;
    QVERIFY2(it == m_MainMatrix.getNIterator(1, 5), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getNIterator(0, 5), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getNIterator(7, 4), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getNIterator(6, 4), "Incorrect pre-decrementation");
    it = m_MainMatrix.getNIterator(2, 0);
    --it;
    QVERIFY2(it == m_MainMatrix.getNIterator(1, 0), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.nBegin(), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.nBegin(), "Incorrect pre-decrementation");


    // post-decrement
    it = m_MainMatrix.nEnd();
    it--;
    QVERIFY2(it == m_MainMatrix.getNIterator(7, 8), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getNIterator(6, 8), "Incorrect post-decrementation");
    it = m_MainMatrix.getNIterator(5, 5);
    it--;
    QVERIFY2(it == m_MainMatrix.getNIterator(4, 5), "Incorrect post-decrementation");
    it = m_MainMatrix.getNIterator(2, 5);
    it--;
    QVERIFY2(it == m_MainMatrix.getNIterator(1, 5), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getNIterator(0, 5), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getNIterator(7, 4), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getNIterator(6, 4), "Incorrect post-decrementation");
    it = m_MainMatrix.getNIterator(2, 0);
    it--;
    QVERIFY2(it == m_MainMatrix.getNIterator(1, 0), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.nBegin(), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.nBegin(), "Incorrect post-decrementation");

    // test a combination of "pre" and "post" behaviors
    IntMatrixNIterator srcIt{m_MainMatrix.getNIterator(6, 5)};
    IntMatrixNIterator destIt{--(--srcIt)};
    QVERIFY2(srcIt == m_MainMatrix.getNIterator(5, 5) && destIt == m_MainMatrix.getNIterator(4, 5), "Incorrect pre-pre-decrementation");
    srcIt = m_MainMatrix.getNIterator(6, 5);
    destIt = (srcIt--)--;
    QVERIFY2(srcIt == m_MainMatrix.getNIterator(5, 5) && destIt == m_MainMatrix.getNIterator(6, 5), "Incorrect post-post-decrementation");
    srcIt = m_MainMatrix.getNIterator(6, 5);
    destIt = (--srcIt)--;
    QVERIFY2(srcIt == m_MainMatrix.getNIterator(5, 5) && destIt == m_MainMatrix.getNIterator(5, 5), "Incorrect post-pre-decrementation");
    srcIt = m_MainMatrix.getNIterator(6, 5);
    destIt = --(srcIt--);
    QVERIFY2(srcIt == m_MainMatrix.getNIterator(5, 5) && destIt == m_MainMatrix.getNIterator(5, 5), "Incorrect pre-post-decrementation");
}

void NIteratorTests::testOperatorPlus()
{
    m_MainMatrix = {8, 9, -5};

    // test for non-empty matrix
    IntMatrixNIterator it{m_MainMatrix.nBegin()};
    QVERIFY2(it + (-3) == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.getNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 4 == m_MainMatrix.getNIterator(4, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 10 == m_MainMatrix.getNIterator(2, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 70 == m_MainMatrix.getNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 71 == m_MainMatrix.getNIterator(7, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 72 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 73 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 75 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getNIterator(1, 0);
    QVERIFY2(it + (-4) == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.getNIterator(4, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 9 == m_MainMatrix.getNIterator(2, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 69 == m_MainMatrix.getNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 70 == m_MainMatrix.getNIterator(7, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 71 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 72 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 74 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getNIterator(4, 5);
    QVERIFY2(it + (-47) == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-45) == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-44) == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-43) == m_MainMatrix.getNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-6) == m_MainMatrix.getNIterator(6, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.getNIterator(2, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getNIterator(4, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.getNIterator(6, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 6 == m_MainMatrix.getNIterator(2, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 26 == m_MainMatrix.getNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 27 == m_MainMatrix.getNIterator(7, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 28 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 29 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 31 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getNIterator(6, 8);
    QVERIFY2(it + (-73) == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-70) == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-69) == m_MainMatrix.getNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-24) == m_MainMatrix.getNIterator(6, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-3) == m_MainMatrix.getNIterator(3, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.getNIterator(7, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 5 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getNIterator(7, 8);
    QVERIFY2(it + (-74) == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-72) == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-70) == m_MainMatrix.getNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-25) == m_MainMatrix.getNIterator(6, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-4) == m_MainMatrix.getNIterator(3, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.getNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getNIterator(7, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 4 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.nEnd();
    QVERIFY2(it + (-75) == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-73) == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-72) == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.getNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-26) == m_MainMatrix.getNIterator(6, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-5) == m_MainMatrix.getNIterator(3, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.getNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.getNIterator(7, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.nBegin() + (-1) == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.nBegin() + 1 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.nEnd() + 0 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.nEnd() + 1 == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.nEnd() + (-1) == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");

    // test for empty iterators
    IntMatrixNIterator emptyIt1{};
    IntMatrixNIterator emptyIt2{};
    IntMatrixNIterator emptyIt3{};
    emptyIt1 = emptyIt3 + (-1);
    emptyIt2 = emptyIt3 + 1;
    QVERIFY2(emptyIt1 == emptyIt3, "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(emptyIt2 == emptyIt3, "Operator + does not work correctly, the resulting iterator is not the right one");
}

void NIteratorTests::testOperatorMinus()
{
    m_MainMatrix = {8, 9, -5};

    // test for non-empty matrix
    IntMatrixNIterator it{m_MainMatrix.nBegin()};
    QVERIFY2(it - 3 == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.nBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.getNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-4) == m_MainMatrix.getNIterator(4, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-10) == m_MainMatrix.getNIterator(2, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-70) == m_MainMatrix.getNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-71) == m_MainMatrix.getNIterator(7, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-72) == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-73) == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-75) == m_MainMatrix.nEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getNIterator(1, 0);
    QVERIFY2(it - 4 == m_MainMatrix.nBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.nBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.nBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.getNIterator(4, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-9) == m_MainMatrix.getNIterator(2, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-69) == m_MainMatrix.getNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-70) == m_MainMatrix.getNIterator(7, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-71) == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-72) == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-74) == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getNIterator(4, 5);
    QVERIFY2(it - 47 == m_MainMatrix.nBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 45 == m_MainMatrix.nBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 44 == m_MainMatrix.nBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 43 == m_MainMatrix.getNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 6 == m_MainMatrix.getNIterator(6, 4), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.getNIterator(2, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getNIterator(4, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.getNIterator(6, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-6) == m_MainMatrix.getNIterator(2, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-26) == m_MainMatrix.getNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-27) == m_MainMatrix.getNIterator(7, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-28) == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-29) == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-31) == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getNIterator(6, 8);
    QVERIFY2(it - 73 == m_MainMatrix.nBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.nBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 70 == m_MainMatrix.nBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 69 == m_MainMatrix.getNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 24 == m_MainMatrix.getNIterator(6, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 3 == m_MainMatrix.getNIterator(3, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.getNIterator(7, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-5) == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getNIterator(7, 8);
    QVERIFY2(it - 74 == m_MainMatrix.nBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 72 == m_MainMatrix.nBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.nBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 70 == m_MainMatrix.getNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 25 == m_MainMatrix.getNIterator(6, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 4 == m_MainMatrix.getNIterator(3, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.getNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getNIterator(7, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-4) == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.nEnd();
    QVERIFY2(it - 75 == m_MainMatrix.nBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 73 == m_MainMatrix.nBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 72 == m_MainMatrix.nBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.getNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 26 == m_MainMatrix.getNIterator(6, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 5 == m_MainMatrix.getNIterator(3, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.getNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.getNIterator(7, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.nBegin() - 1 == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.nBegin() - (-1) == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.nEnd() - 0 == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.nEnd() - (-1) == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.nEnd() - 1 == m_MainMatrix.nEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");

    // test for empty iterator
    IntMatrixNIterator emptyIt1{};
    IntMatrixNIterator emptyIt2{};
    IntMatrixNIterator emptyIt3{};
    emptyIt1 = emptyIt3 - 1;
    emptyIt2 = emptyIt3 - (-1);
    QVERIFY2(emptyIt1 == emptyIt3, "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(emptyIt2 == emptyIt3, "Operator - does not work correctly, the resulting iterator is not the right one");
}

void NIteratorTests::testOperatorPlusEqual()
{
    IntMatrixNIterator it;

    // test for non-empty matrix
    m_MainMatrix = {8, 9, -5};

    IntMatrixNIterator it1{m_MainMatrix.nBegin()};
    it = it1; it += (-3); QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.getNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 4; QVERIFY2(it == m_MainMatrix.getNIterator(4, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 10; QVERIFY2(it == m_MainMatrix.getNIterator(2, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 70; QVERIFY2(it == m_MainMatrix.getNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 71; QVERIFY2(it == m_MainMatrix.getNIterator(7, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 72; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 73; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 75; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getNIterator(1, 0);
    it = it1; it += (-4); QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-2); QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.getNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 3; QVERIFY2(it == m_MainMatrix.getNIterator(4, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 9; QVERIFY2(it == m_MainMatrix.getNIterator(2, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 69; QVERIFY2(it == m_MainMatrix.getNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 70; QVERIFY2(it == m_MainMatrix.getNIterator(7, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 71; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 72; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 74; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getNIterator(4, 5);
    it = it1; it += (-47); QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-45); QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-44); QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-43); QVERIFY2(it == m_MainMatrix.getNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-6); QVERIFY2(it == m_MainMatrix.getNIterator(6, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-2); QVERIFY2(it == m_MainMatrix.getNIterator(2, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.getNIterator(4, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 2; QVERIFY2(it == m_MainMatrix.getNIterator(6, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 6; QVERIFY2(it == m_MainMatrix.getNIterator(2, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 26; QVERIFY2(it == m_MainMatrix.getNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 27; QVERIFY2(it == m_MainMatrix.getNIterator(7, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 28; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 29; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 31; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getNIterator(6, 8);
    it = it1; it += (-73); QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-71); QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-70); QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-69); QVERIFY2(it == m_MainMatrix.getNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-24); QVERIFY2(it == m_MainMatrix.getNIterator(6, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-3); QVERIFY2(it == m_MainMatrix.getNIterator(3, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.getNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.getNIterator(7, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 2; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 3; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 5; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getNIterator(7, 8);
    it = it1; it += (-74); QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-72); QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-71); QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-70); QVERIFY2(it == m_MainMatrix.getNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-25); QVERIFY2(it == m_MainMatrix.getNIterator(6, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-4); QVERIFY2(it == m_MainMatrix.getNIterator(3, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.getNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.getNIterator(7, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 2; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 4; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.nEnd();
    it = it1; it += (-75); QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-73); QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-72); QVERIFY2(it == m_MainMatrix.nBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-71); QVERIFY2(it == m_MainMatrix.getNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-26); QVERIFY2(it == m_MainMatrix.getNIterator(6, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-5); QVERIFY2(it == m_MainMatrix.getNIterator(3, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-2); QVERIFY2(it == m_MainMatrix.getNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.getNIterator(7, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 3; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    it1 = m_MainMatrix.nBegin();
    it1 = m_MainMatrix.nEnd();
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator += does not work correctly, the updated iterator is not the right one");

    // test for empty iterator
    IntMatrixNIterator it2{};
    IntMatrixNIterator it3{};
    IntMatrixNIterator it4{};
    it3 += (-1); QVERIFY2(it3 == it2, "Operator += does not work correctly, the resulting updated is not the right one");
    it4 += 1; QVERIFY2(it4 == it2, "Operator += does not work correctly, the resulting updated is not the right one");
}

void NIteratorTests::testOperatorMinusEqual()
{
    IntMatrixNIterator it;

    // test for non-empty matrix
    m_MainMatrix = {8, 9, -5};

    IntMatrixNIterator it1{m_MainMatrix.nBegin()};
    it = it1; it -= 3; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.getNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-4); QVERIFY2(it == m_MainMatrix.getNIterator(4, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-10); QVERIFY2(it == m_MainMatrix.getNIterator(2, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-70); QVERIFY2(it == m_MainMatrix.getNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-71); QVERIFY2(it == m_MainMatrix.getNIterator(7, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-72); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-73); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-75); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getNIterator(1, 0);
    it = it1; it -= 4; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 2; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.getNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-3); QVERIFY2(it == m_MainMatrix.getNIterator(4, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-9); QVERIFY2(it == m_MainMatrix.getNIterator(2, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-69); QVERIFY2(it == m_MainMatrix.getNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-70); QVERIFY2(it == m_MainMatrix.getNIterator(7, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-71); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-72); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-74); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getNIterator(4, 5);
    it = it1; it -= 47; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 45; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 44; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 43; QVERIFY2(it == m_MainMatrix.getNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 6; QVERIFY2(it == m_MainMatrix.getNIterator(6, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 2; QVERIFY2(it == m_MainMatrix.getNIterator(2, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.getNIterator(4, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-2); QVERIFY2(it == m_MainMatrix.getNIterator(6, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-6); QVERIFY2(it == m_MainMatrix.getNIterator(2, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-26); QVERIFY2(it == m_MainMatrix.getNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-27); QVERIFY2(it == m_MainMatrix.getNIterator(7, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-28); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-29); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-31); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getNIterator(6, 8);
    it = it1; it -= 73; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 71; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 70; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 69; QVERIFY2(it == m_MainMatrix.getNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 24; QVERIFY2(it == m_MainMatrix.getNIterator(6, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 3; QVERIFY2(it == m_MainMatrix.getNIterator(3, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.getNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.getNIterator(7, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-2); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-3); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-5); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getNIterator(7, 8);
    it = it1; it -= 74; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 72; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 71; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 70; QVERIFY2(it == m_MainMatrix.getNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 25; QVERIFY2(it == m_MainMatrix.getNIterator(6, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 4; QVERIFY2(it == m_MainMatrix.getNIterator(3, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.getNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.getNIterator(7, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-2); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-4); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.nEnd();
    it = it1; it -= 75; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 73; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 72; QVERIFY2(it == m_MainMatrix.nBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 71; QVERIFY2(it == m_MainMatrix.getNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 26; QVERIFY2(it == m_MainMatrix.getNIterator(6, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 5; QVERIFY2(it == m_MainMatrix.getNIterator(3, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 2; QVERIFY2(it == m_MainMatrix.getNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.getNIterator(7, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-3); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    it1 = m_MainMatrix.nBegin();
    it1 = m_MainMatrix.nEnd();
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.nEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");

    // test for empty iterator
    IntMatrixNIterator it2{};
    IntMatrixNIterator it3{};
    IntMatrixNIterator it4{};
    it3 -= 1; QVERIFY2(it3 == it2, "Operator -= does not work correctly, the updated iterator is not the right one");
    it4 -= (-1); QVERIFY2(it4 == it2, "Operator -= does not work correctly, the updated iterator is not the right one");
}

void NIteratorTests::testDifferenceOperator()
{
    // test for non-empty matrix
    m_MainMatrix = {8, 9, -5};

    QVERIFY2(m_MainMatrix.nEnd() - m_MainMatrix.nEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.nEnd() - m_MainMatrix.getNIterator(7, 8) == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.nEnd() - m_MainMatrix.getNIterator(6, 8) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.nEnd() - m_MainMatrix.getNIterator(4, 5) == 28, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.nEnd() - m_MainMatrix.getNIterator(1, 0) == 71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.nEnd() - m_MainMatrix.nBegin() == 72, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getNIterator(7, 8) - m_MainMatrix.nEnd() == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(7, 8) - m_MainMatrix.getNIterator(7, 8) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(7, 8) - m_MainMatrix.getNIterator(6, 8) == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(7, 8) - m_MainMatrix.getNIterator(4, 5) == 27, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(7, 8) - m_MainMatrix.getNIterator(1, 0) == 70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(7, 8) - m_MainMatrix.nBegin() == 71, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getNIterator(6, 8) - m_MainMatrix.nEnd() == -2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(6, 8) - m_MainMatrix.getNIterator(7, 8) == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(6, 8) - m_MainMatrix.getNIterator(6, 8) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(6, 8) - m_MainMatrix.getNIterator(4, 5) == 26, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(6, 8) - m_MainMatrix.getNIterator(1, 0) == 69, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(6, 8) - m_MainMatrix.nBegin() == 70, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getNIterator(4, 5) - m_MainMatrix.nEnd() == -28, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(4, 5) - m_MainMatrix.getNIterator(7, 8) == -27, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(4, 5) - m_MainMatrix.getNIterator(6, 8) == -26, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(4, 5) - m_MainMatrix.getNIterator(4, 5) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(4, 5) - m_MainMatrix.getNIterator(1, 0) == 43, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(4, 5) - m_MainMatrix.nBegin() == 44, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getNIterator(1, 0) - m_MainMatrix.nEnd() == -71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(1, 0) - m_MainMatrix.getNIterator(7, 8) == -70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(1, 0) - m_MainMatrix.getNIterator(6, 8) == -69, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(1, 0) - m_MainMatrix.getNIterator(4, 5) == -43, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(1, 0) - m_MainMatrix.getNIterator(1, 0) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(1, 0) - m_MainMatrix.nBegin() == 1, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.nBegin() - m_MainMatrix.nEnd() == -72, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.nBegin() - m_MainMatrix.getNIterator(7, 8) == -71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.nBegin() - m_MainMatrix.getNIterator(6, 8) == -70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.nBegin() - m_MainMatrix.getNIterator(4, 5) == -44, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.nBegin() - m_MainMatrix.getNIterator(1, 0) == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.nBegin() - m_MainMatrix.nBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");

    // additional tests with "random" elements from same column/different columns
    QVERIFY2(m_MainMatrix.getNIterator(4, 5) - m_MainMatrix.getNIterator(2, 7) == -14, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(2, 7) - m_MainMatrix.getNIterator(4, 5) == 14, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(4, 5) - m_MainMatrix.getNIterator(2, 5) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getNIterator(2, 5) - m_MainMatrix.getNIterator(4, 5) == -2, "The difference operator does not work correctly, difference between iterators is wrong");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.nEnd() - m_MainMatrix.nBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.nBegin() - m_MainMatrix.nEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.nBegin() - m_MainMatrix.nBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.nEnd() - m_MainMatrix.nEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");

    // test for empty iterator
    IntMatrixNIterator it1{};
    IntMatrixNIterator it2{};
    QVERIFY2(it1 - it2 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(it2 - it1 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(it1 - it1 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
}

void NIteratorTests::testDereferenceAsteriskOperator()
{
    // test reading element
    m_MainMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};
    QVERIFY2(*m_MainMatrix.nBegin() == 1, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getNIterator(1, 0) == -2, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getNIterator(2, 1) == -6, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getNIterator(1, 3) == 11, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getNIterator(2, 3) == -12, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");

    // test writing to element
    m_MainMatrix = {3, 4, -20};
    *m_MainMatrix.nBegin() = 1;
    *m_MainMatrix.getNIterator(1, 0) = -2;
    *m_MainMatrix.getNIterator(2, 1) = -6;
    *m_MainMatrix.getNIterator(1, 3) = 11;
    *m_MainMatrix.getNIterator(2, 3) = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY2(m_MainMatrix.at(1, 0) == -2, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY2(m_MainMatrix.at(2, 1) == -6, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY2(m_MainMatrix.at(1, 3) == 11, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY2(m_MainMatrix.at(2, 3) == -12, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY(m_MainMatrix.at(1, 2) == -20);

    // additional tests
    m_MainMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    IntMatrixNIterator readIter{m_MainMatrix.nBegin()};
    m_MainMatrix.at(2, 0) = 10;
    readIter += 2;
    QVERIFY2(*readIter == 10, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");

    m_MainMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    IntMatrixNIterator writeIter{m_MainMatrix.nBegin()};
    writeIter += 2;
    *writeIter = 10;
    QVERIFY2(m_MainMatrix.at(2, 0) == 10, "The dereference (*) operator does not work correctly, the value is not correctly written to the pointed location");
}

void NIteratorTests::testDereferenceArrowOperator()
{
    // test reading element
    m_AuxStringMatrix = {3, 4, {"abc", "jihgfedcba", "abcde", "", "ba", "a", "ihgfedcba", "abcdefghijk", "abcd", "gfedcba", "abcdefgh", "fedcba"}};
    QVERIFY2(m_AuxStringMatrix.nBegin()->size() == 3, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getNIterator(1, 0)->size() == 2, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getNIterator(2, 1)->size() == 7, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getNIterator(1, 3)->size() == 11, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getNIterator(2, 3)->size() == 6, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");

    // test writing to element
    m_AuxStringMatrix = {3, 4, "zzz"};
    m_AuxStringMatrix.nBegin()->assign("abc");
    m_AuxStringMatrix.getNIterator(1, 0)->assign("ba");
    m_AuxStringMatrix.getNIterator(2, 1)->assign("gfedcba");
    m_AuxStringMatrix.getNIterator(1, 3)->assign("abcdefghijk");
    m_AuxStringMatrix.getNIterator(2, 3)->assign("fedcba");
    QVERIFY2(m_AuxStringMatrix.at(0, 0) == "abc", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY2(m_AuxStringMatrix.at(1, 0) == "ba", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY2(m_AuxStringMatrix.at(2, 1) == "gfedcba", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY2(m_AuxStringMatrix.at(1, 3) == "abcdefghijk", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY2(m_AuxStringMatrix.at(2, 3) == "fedcba", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY(m_AuxStringMatrix.at(1, 2) == "zzz");

    // additional tests
    m_AuxStringMatrix = {3, 2, {"abc", "jkl", "defed", "mno", "ghi", "pqr"}};
    StringMatrixNIterator it{m_AuxStringMatrix.nBegin()};
    m_AuxStringMatrix.at(2, 0) = "abcdefghi";
    it += 2;
    QVERIFY2(it->size() == 9, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");

    m_AuxStringMatrix = {3, 2, {"abc", "jkl", "defed", "mno", "ghi", "pqr"}};
    it = m_AuxStringMatrix.nBegin();
    it += 2;
    it->assign("abcdefghi");
    QVERIFY2(m_AuxStringMatrix.at(2, 0) == "abcdefghi", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
}

void NIteratorTests::testDereferenceSquareBracketsOperator()
{
    // test reading element
    m_MainMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};

    IntMatrixNIterator it{m_MainMatrix.nBegin()};
    QVERIFY2(it[0] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[1] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[5] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[10] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[11] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getNIterator(1, 0);
    QVERIFY2(it[-1] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[4] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[9] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[10] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getNIterator(2, 1);
    QVERIFY2(it[-5] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-4] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[5] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[6] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getNIterator(1, 3);
    QVERIFY2(it[-10] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-9] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-5] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[1] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getNIterator(2, 3);
    QVERIFY2(it[-11] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-10] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-6] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-1] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    // test writing to element (before running a new scenario the matrix should be reset to its initial value value)
    m_MainMatrix = {3, 4, -20}; // initial

    it = m_MainMatrix.nBegin();
    it[0] = 1;
    it[1] = -2;
    it[5] = -6;
    it[10] = 11;
    it[11] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 0) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 1) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 3) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 3) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(1, 2) == -20);

    m_MainMatrix = {3, 4, -20}; // reset

    it = m_MainMatrix.getNIterator(1, 0);
    it[-1] = 1;
    it[0] = -2;
    it[4] = -6;
    it[9] = 11;
    it[10] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 0) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 1) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 3) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 3) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(1, 2) == -20);

    m_MainMatrix = {3, 4, -20}; // reset

    it = m_MainMatrix.getNIterator(2, 1);
    it[-5] = 1;
    it[-4] = -2;
    it[0] = -6;
    it[5] = 11;
    it[6] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 0) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 1) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 3) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 3) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(1, 2) == -20);

    m_MainMatrix = {3, 4, -20}; // reset

    it = m_MainMatrix.getNIterator(1, 3);
    it[-10] = 1;
    it[-9] = -2;
    it[-5] = -6;
    it[0] = 11;
    it[1] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 0) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 1) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 3) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 3) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(1, 2) == -20);

    m_MainMatrix = {3, 4, -20}; // reset

    it = m_MainMatrix.getNIterator(2, 3);
    it[-11] = 1;
    it[-10] = -2;
    it[-6] = -6;
    it[-1] = 11;
    it[0] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 0) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 1) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 3) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 3) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(1, 2) == -20);
}

void NIteratorTests::testStdCount()
{
    using namespace std;

    m_MainMatrix = {5, 4, {-1, 5, 2, 7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8 }};

    int matchCount{count(m_MainMatrix.nBegin(), m_MainMatrix.nEnd(), 2)};
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.nBegin(), m_MainMatrix.nEnd(), -5);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getNIterator(2, 0), m_MainMatrix.getNIterator(4, 1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getNIterator(2, 0), m_MainMatrix.getNIterator(0, 2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getNIterator(3, 0), m_MainMatrix.getNIterator(4, 1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getNIterator(3, 0), m_MainMatrix.getNIterator(0, 2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.nBegin(), m_MainMatrix.getNIterator(3, 2), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getNIterator(3, 2), m_MainMatrix.nEnd(), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.nBegin(), m_MainMatrix.getNIterator(2, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getNIterator(2, 2), m_MainMatrix.nEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getNIterator(2), m_MainMatrix.getNIterator(9), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getNIterator(2), m_MainMatrix.getNIterator(10), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getNIterator(3), m_MainMatrix.getNIterator(9), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getNIterator(3), m_MainMatrix.getNIterator(10), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.nBegin(), m_MainMatrix.getNIterator(13), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getNIterator(13), m_MainMatrix.nEnd(), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.nBegin(), m_MainMatrix.getNIterator(12), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getNIterator(12), m_MainMatrix.nEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.nColumnBegin(1), m_MainMatrix.nColumnEnd(1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.nColumnBegin(1), m_MainMatrix.nColumnEnd(2), 8);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.nColumnBegin(2), m_MainMatrix.nColumnEnd(2), 9);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.nColumnBegin(2), m_MainMatrix.nColumnEnd(3), 9);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.nBegin(), m_MainMatrix.nColumnBegin(1), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.nColumnBegin(1), m_MainMatrix.nEnd(), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.nBegin(), m_MainMatrix.nColumnEnd(1), 1);
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.nColumnEnd(1), m_MainMatrix.nEnd(), 1);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
}

void NIteratorTests::testStdFind()
{
    using namespace std;

    // test finding elements in specific ranges within unempty matrix
    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 6, 9, 11}};

    QVERIFY2(find(m_MainMatrix.nBegin(), m_MainMatrix.nEnd(), 5) != m_MainMatrix.nEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.nBegin(), m_MainMatrix.nEnd(), 10) == m_MainMatrix.nEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.nColumnBegin(1), m_MainMatrix.nColumnEnd(1), 5) != m_MainMatrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.nColumnBegin(1), m_MainMatrix.nColumnEnd(1), 6) != m_MainMatrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.nColumnBegin(1), m_MainMatrix.nColumnEnd(1), 8) != m_MainMatrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.nColumnBegin(1), m_MainMatrix.nColumnEnd(1), -1) == m_MainMatrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.nColumnBegin(1), m_MainMatrix.nColumnEnd(1), -2) == m_MainMatrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.nColumnBegin(1), m_MainMatrix.nColumnEnd(1), 10) == m_MainMatrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.nColumnBegin(1), m_MainMatrix.nEnd(), 5) != m_MainMatrix.nEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.nColumnBegin(1), m_MainMatrix.nEnd(), 11) != m_MainMatrix.nEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.nColumnBegin(1), m_MainMatrix.nEnd(), -2) != m_MainMatrix.nEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.nColumnBegin(1), m_MainMatrix.nEnd(), -1) == m_MainMatrix.nEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.nColumnBegin(1), m_MainMatrix.nEnd(), 10) == m_MainMatrix.nEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.nBegin(), m_MainMatrix.nColumnEnd(1), -1) != m_MainMatrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.nBegin(), m_MainMatrix.nColumnEnd(1), 6) != m_MainMatrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.nBegin(), m_MainMatrix.nColumnEnd(1), 8) != m_MainMatrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.nBegin(), m_MainMatrix.nColumnEnd(1), -2) == m_MainMatrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.nBegin(), m_MainMatrix.nColumnEnd(1), 10) == m_MainMatrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getNIterator(3, 1), m_MainMatrix.getNIterator(1, 3), 0) != m_MainMatrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getNIterator(3, 1), m_MainMatrix.getNIterator(1, 3), -7) != m_MainMatrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getNIterator(3, 1), m_MainMatrix.getNIterator(1, 3), -2) != m_MainMatrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getNIterator(3, 1), m_MainMatrix.getNIterator(1, 3), -1) == m_MainMatrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getNIterator(3, 1), m_MainMatrix.getNIterator(1, 3), 11) == m_MainMatrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getNIterator(3, 1), m_MainMatrix.getNIterator(1, 3), 10) == m_MainMatrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getNIterator(3, 1), m_MainMatrix.nEnd(), 0) != m_MainMatrix.nEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getNIterator(3, 1), m_MainMatrix.nEnd(), 11) != m_MainMatrix.nEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getNIterator(3, 1), m_MainMatrix.nEnd(), -2) != m_MainMatrix.nEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getNIterator(3, 1), m_MainMatrix.nEnd(), -1) == m_MainMatrix.nEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getNIterator(3, 1), m_MainMatrix.nEnd(), 10) == m_MainMatrix.nEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.nBegin(), m_MainMatrix.getNIterator(1, 3), -1) != m_MainMatrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.nBegin(), m_MainMatrix.getNIterator(1, 3), -7) != m_MainMatrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.nBegin(), m_MainMatrix.getNIterator(1, 3), -2) != m_MainMatrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.nBegin(), m_MainMatrix.getNIterator(1, 3), 11) == m_MainMatrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.nBegin(), m_MainMatrix.getNIterator(1, 3), 10) == m_MainMatrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

    // other tests
    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};
    IntMatrixNIterator it{find(m_MainMatrix.nBegin(), m_MainMatrix.nEnd(), 4)};
    ++it;
    QVERIFY2(*it == 5, "The iterator doesn't work correctly with std::find, incorrect next element returned");

    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};
    QVERIFY2(find(m_MainMatrix.nBegin(), m_MainMatrix.nEnd(), 10) == m_MainMatrix.nEnd(), "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix");

    it = m_MainMatrix.nBegin();
    while(it != m_MainMatrix.nEnd())
    {
        it = find(it, m_MainMatrix.nEnd(), 9);

        if (it != m_MainMatrix.nEnd())
        {
            *it = 10;
        }
    }
    int expectedNumber{std::count(m_MainMatrix.nBegin(), m_MainMatrix.nEnd(), 10)};
    QVERIFY2(expectedNumber == 3, "The iterator doesn't work properly with std::find, element values haven't been correctly replaced");
}

void NIteratorTests::testStdSort()
{
    m_MainMatrix = {5, 4, {
                      -1, 5,  2, -7,
                       1, 9, -2,  7,
                       3, 8,  2,  2,
                       1, 0,  8,  9,
                       4, 6,  9,  11
                   }};

    for (int col{0}; col<m_MainMatrix.getNrOfColumns(); ++col)
    {
        std::sort(m_MainMatrix.nColumnBegin(col), m_MainMatrix.nColumnEnd(col));
    }

    QVERIFY2(m_MainMatrix.at(0, 0) == -1 && m_MainMatrix.at(0, 1) == 0 && m_MainMatrix.at(0, 2) == -2 && m_MainMatrix.at(0, 3) == -7 &&
             m_MainMatrix.at(1, 0) ==  1 && m_MainMatrix.at(1, 1) == 5 && m_MainMatrix.at(1, 2) ==  2 && m_MainMatrix.at(1, 3) ==  2 &&
             m_MainMatrix.at(2, 0) ==  1 && m_MainMatrix.at(2, 1) == 6 && m_MainMatrix.at(2, 2) ==  2 && m_MainMatrix.at(2, 3) ==  7 &&
             m_MainMatrix.at(3, 0) ==  3 && m_MainMatrix.at(3, 1) == 8 && m_MainMatrix.at(3, 2) ==  8 && m_MainMatrix.at(3, 3) ==  9 &&
             m_MainMatrix.at(4, 0) ==  4 && m_MainMatrix.at(4, 1) == 9 && m_MainMatrix.at(4, 2) ==  9 && m_MainMatrix.at(4, 3) ==  11,

             "The iterator objects don't work correctly, the per column sorting has not been done properly");

    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 6, 9, 11}};

    std::sort(m_MainMatrix.nBegin(), m_MainMatrix.nEnd());

    QVERIFY2(m_MainMatrix.at(0, 0) == -7 && m_MainMatrix.at(0, 1) == 1 && m_MainMatrix.at(0, 2) == 4 && m_MainMatrix.at(0, 3) == 8 &&
             m_MainMatrix.at(1, 0) == -2 && m_MainMatrix.at(1, 1) == 2 && m_MainMatrix.at(1, 2) == 5 && m_MainMatrix.at(1, 3) == 9 &&
             m_MainMatrix.at(2, 0) == -1 && m_MainMatrix.at(2, 1) == 2 && m_MainMatrix.at(2, 2) == 6 && m_MainMatrix.at(2, 3) == 9 &&
             m_MainMatrix.at(3, 0) ==  0 && m_MainMatrix.at(3, 1) == 2 && m_MainMatrix.at(3, 2) == 7 && m_MainMatrix.at(3, 3) == 9 &&
             m_MainMatrix.at(4, 0) ==  1 && m_MainMatrix.at(4, 1) == 3 && m_MainMatrix.at(4, 2) == 8 && m_MainMatrix.at(4, 3) == 11,

             "The iterator objects don't work correctly, the matrix has not been sorted properly");

    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, (7), 3, 8, 2, 2, 1, (0), 8, 9, 4, 6, 9, 11}};

    std::sort(m_MainMatrix.getNIterator(3, 1), m_MainMatrix.getNIterator(1, 3));

    QVERIFY2(m_MainMatrix.at(0, 0) == -1 && m_MainMatrix.at(0, 1) ==   5  && m_MainMatrix.at(0, 2) == 0 && m_MainMatrix.at(0, 3) ==  9  &&
             m_MainMatrix.at(1, 0) ==  1 && m_MainMatrix.at(1, 1) ==   9  && m_MainMatrix.at(1, 2) == 2 && m_MainMatrix.at(1, 3) == (7) &&
             m_MainMatrix.at(2, 0) ==  3 && m_MainMatrix.at(2, 1) ==   8  && m_MainMatrix.at(2, 2) == 2 && m_MainMatrix.at(2, 3) ==  2  &&
             m_MainMatrix.at(3, 0) ==  1 && m_MainMatrix.at(3, 1) == (-7) && m_MainMatrix.at(3, 2) == 6 && m_MainMatrix.at(3, 3) ==  9  &&
             m_MainMatrix.at(4, 0) ==  4 && m_MainMatrix.at(4, 1) ==  -2  && m_MainMatrix.at(4, 2) == 8 && m_MainMatrix.at(4, 3) ==  11 ,

             "The iterator objects don't work correctly, the matrix has not been sorted properly");

    m_MainMatrix = {5, 4, {(-1), 5, 2, -7, 1, 9, (-2), 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 6, 9, 11}};

    std::sort(m_MainMatrix.nBegin(), m_MainMatrix.getNIterator(1, 2));

    QVERIFY2(m_MainMatrix.at(0, 0) == (-1) && m_MainMatrix.at(0, 1) == 3 && m_MainMatrix.at(0, 2) ==   9  && m_MainMatrix.at(0, 3) == -7 &&
             m_MainMatrix.at(1, 0) ==   0  && m_MainMatrix.at(1, 1) == 4 && m_MainMatrix.at(1, 2) == (-2) && m_MainMatrix.at(1, 3) ==  7 &&
             m_MainMatrix.at(2, 0) ==   1  && m_MainMatrix.at(2, 1) == 5 && m_MainMatrix.at(2, 2) ==   2  && m_MainMatrix.at(2, 3) ==  2 &&
             m_MainMatrix.at(3, 0) ==   1  && m_MainMatrix.at(3, 1) == 6 && m_MainMatrix.at(3, 2) ==   8  && m_MainMatrix.at(3, 3) ==  9 &&
             m_MainMatrix.at(4, 0) ==   2  && m_MainMatrix.at(4, 1) == 8 && m_MainMatrix.at(4, 2) ==   9  && m_MainMatrix.at(4, 3) ==  11,

             "The iterator objects don't work correctly, the matrix has not been sorted properly");

    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, (-2), 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 6, 9, 11}};

    std::sort(m_MainMatrix.getNIterator(1, 2), m_MainMatrix.nEnd());

    QVERIFY2(m_MainMatrix.at(0, 0) == -1 && m_MainMatrix.at(0, 1) == 5 && m_MainMatrix.at(0, 2) ==   2  && m_MainMatrix.at(0, 3) == 7 &&
             m_MainMatrix.at(1, 0) ==  1 && m_MainMatrix.at(1, 1) == 9 && m_MainMatrix.at(1, 2) == (-7) && m_MainMatrix.at(1, 3) == 8 &&
             m_MainMatrix.at(2, 0) ==  3 && m_MainMatrix.at(2, 1) == 8 && m_MainMatrix.at(2, 2) ==  -2  && m_MainMatrix.at(2, 3) == 9 &&
             m_MainMatrix.at(3, 0) ==  1 && m_MainMatrix.at(3, 1) == 0 && m_MainMatrix.at(3, 2) ==   2  && m_MainMatrix.at(3, 3) == 9 &&
             m_MainMatrix.at(4, 0) ==  4 && m_MainMatrix.at(4, 1) == 6 && m_MainMatrix.at(4, 2) ==   2  && m_MainMatrix.at(4, 3) == 11,

             "The iterator objects don't work correctly, the matrix has not been sorted properly");

}

QTEST_APPLESS_MAIN(NIteratorTests)

#include "tst_niteratortests.moc"
