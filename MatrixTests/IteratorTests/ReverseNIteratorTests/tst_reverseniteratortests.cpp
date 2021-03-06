#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixReverseNIterator = Matrix<int>::ReverseNIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixReverseNIterator = Matrix<std::string>::ReverseNIterator;

class ReverseNIteratorTests : public QObject
{
    Q_OBJECT

public:
    ReverseNIteratorTests();
    ~ReverseNIteratorTests();

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

ReverseNIteratorTests::ReverseNIteratorTests()
{
}

ReverseNIteratorTests::~ReverseNIteratorTests()
{
}

void ReverseNIteratorTests::testIteratorCreation()
{
    m_MainMatrix = {8, 9, -5};

    IntMatrixReverseNIterator it{m_MainMatrix.reverseNBegin()};
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseNEnd();
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseNColumnBegin(0);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseNColumnBegin(1);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseNColumnBegin(4);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 4 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseNColumnBegin(7);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseNColumnBegin(8);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseNColumnEnd(0);
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseNColumnEnd(1);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseNColumnEnd(4);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 3 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseNColumnEnd(7);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 6 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseNColumnEnd(8);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseNIterator(0, 0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseNIterator(1, 0);
    QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseNIterator(4, 5);
    QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 5 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseNIterator(6, 8);
    QVERIFY2(it.getCurrentRowNr() == 6 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseNIterator(7, 8);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseNIterator(0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseNIterator(1);
    QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseNIterator(44);
    QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 5 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseNIterator(70);
    QVERIFY2(it.getCurrentRowNr() == 6 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getReverseNIterator(71);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // test iterator creation for empty matrix
    m_MainMatrix.clear();
    it = m_MainMatrix.reverseNBegin();
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.reverseNEnd();
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // test empty iterator creation (not bound to any matrix) - an empty iterator should be valid for any empty matrix
    IntMatrixReverseNIterator emptyIt;
    QVERIFY2(emptyIt.getCurrentRowNr() == -1 && emptyIt.getCurrentColumnNr() == -1 && emptyIt.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // additional test
    m_MainMatrix = {8, 9, -5};
    m_AuxIntMatrix = {8, 9, -5};
    it = m_MainMatrix.getReverseNIterator(4, 5);
    QVERIFY(!it.isValidWithMatrix(m_AuxIntMatrix));
    m_AuxIntMatrix.clear();
    QVERIFY(!it.isValidWithMatrix(m_AuxIntMatrix));
    it = m_AuxIntMatrix.reverseNBegin();
    QVERIFY(!it.isValidWithMatrix(m_MainMatrix));
    it = m_AuxIntMatrix.reverseNEnd();
    QVERIFY(!it.isValidWithMatrix(m_MainMatrix));
    m_MainMatrix.clear();
    it = m_MainMatrix.reverseNBegin();
    QVERIFY(it.isValidWithMatrix(m_AuxIntMatrix)); // an iterator of an empty matrix is valid with any other empty matrix
    it = m_MainMatrix.reverseNEnd();
    QVERIFY(it.isValidWithMatrix(m_AuxIntMatrix));
}

void ReverseNIteratorTests::testIteratorsAreEqual()
{

    m_MainMatrix = {8, 9, -5};

    // test different iterators for equality
    QVERIFY2((m_MainMatrix.getReverseNIterator(0) == m_MainMatrix.getReverseNIterator(0, 0)) && !(m_MainMatrix.getReverseNIterator(0) != m_MainMatrix.getReverseNIterator(0, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getReverseNIterator(1) == m_MainMatrix.getReverseNIterator(1, 0)) && !(m_MainMatrix.getReverseNIterator(1) != m_MainMatrix.getReverseNIterator(1, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getReverseNIterator(44) == m_MainMatrix.getReverseNIterator(4, 5)) && !(m_MainMatrix.getReverseNIterator(44) != m_MainMatrix.getReverseNIterator(4, 5)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getReverseNIterator(70) == m_MainMatrix.getReverseNIterator(6, 8)) && !(m_MainMatrix.getReverseNIterator(70) != m_MainMatrix.getReverseNIterator(6, 8)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getReverseNIterator(71) == m_MainMatrix.getReverseNIterator(7, 8)) && !(m_MainMatrix.getReverseNIterator(71) != m_MainMatrix.getReverseNIterator(7, 8)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseNBegin() == m_MainMatrix.getReverseNIterator(7, 8) && !(m_MainMatrix.reverseNBegin() != m_MainMatrix.getReverseNIterator(7, 8))), "The two iterators are not equal");
    QVERIFY2((m_MainMatrix.reverseNColumnBegin(0) == m_MainMatrix.getReverseNIterator(7, 0)) && !(m_MainMatrix.reverseNColumnBegin(0) != m_MainMatrix.getReverseNIterator(7, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseNColumnBegin(1) == m_MainMatrix.getReverseNIterator(7, 1)) && !(m_MainMatrix.reverseNColumnBegin(1) != m_MainMatrix.getReverseNIterator(7, 1)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseNColumnBegin(5) == m_MainMatrix.getReverseNIterator(7, 5)) && !(m_MainMatrix.reverseNColumnBegin(5) != m_MainMatrix.getReverseNIterator(7, 5)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseNColumnBegin(7) == m_MainMatrix.getReverseNIterator(7, 7)) && !(m_MainMatrix.reverseNColumnBegin(7) != m_MainMatrix.getReverseNIterator(7, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseNColumnBegin(8) == m_MainMatrix.getReverseNIterator(7, 8)) && !(m_MainMatrix.reverseNColumnBegin(8) != m_MainMatrix.getReverseNIterator(7, 8)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseNColumnEnd(0) == m_MainMatrix.reverseNEnd()) && !(m_MainMatrix.reverseNColumnEnd(0) != m_MainMatrix.reverseNEnd()), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseNColumnEnd(1) == m_MainMatrix.getReverseNIterator(7, 0)) && !(m_MainMatrix.reverseNColumnEnd(1) != m_MainMatrix.getReverseNIterator(7, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseNColumnEnd(5) == m_MainMatrix.getReverseNIterator(7, 4)) && !(m_MainMatrix.reverseNColumnEnd(5) != m_MainMatrix.getReverseNIterator(7, 4)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseNColumnEnd(7) == m_MainMatrix.getReverseNIterator(7, 6)) && !(m_MainMatrix.reverseNColumnEnd(7) != m_MainMatrix.getReverseNIterator(7, 6)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.reverseNColumnEnd(8) == m_MainMatrix.getReverseNIterator(7, 7)) && !(m_MainMatrix.reverseNColumnEnd(8) != m_MainMatrix.getReverseNIterator(7, 7)), "The two iterators are NOT equal");

    // test iterator equality to itself
    IntMatrixReverseNIterator it{m_MainMatrix.reverseNEnd()};
    QVERIFY2((it == it) && (it == m_MainMatrix.reverseNEnd()) && !(it != it) && !(it != m_MainMatrix.reverseNEnd()), "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getReverseNIterator(0, 0);
    QVERIFY2((it == it) && (it == m_MainMatrix.getReverseNIterator(0, 0)) && !(it != it) && !(it != m_MainMatrix.getReverseNIterator(0, 0)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getReverseNIterator(1, 0);
    QVERIFY2((it == it) && (it == m_MainMatrix.getReverseNIterator(1, 0)) && !(it != it) && !(it != m_MainMatrix.getReverseNIterator(1, 0)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getReverseNIterator(4, 5);
    QVERIFY2((it == it) && (it == m_MainMatrix.getReverseNIterator(4, 5)) && !(it != it) && !(it != m_MainMatrix.getReverseNIterator(4, 5)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getReverseNIterator(6, 8);
    QVERIFY2((it == it) && (it == m_MainMatrix.getReverseNIterator(6, 8)) && !(it != it) && !(it != m_MainMatrix.getReverseNIterator(6, 8)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.reverseNBegin();
    QVERIFY2((it == it) && (it == m_MainMatrix.reverseNBegin()) && !(it != it) && !(it != m_MainMatrix.reverseNBegin()),  "The iterator is NOT equal to itself and/or to source iterator");

    // test empty matrix iterator equality
    m_MainMatrix.clear();
    QVERIFY2((m_MainMatrix.reverseNBegin() == m_MainMatrix.reverseNEnd()) && !(m_MainMatrix.reverseNBegin() != m_MainMatrix.reverseNEnd()), "The two iterators are NOT equal");
}

void ReverseNIteratorTests::testIteratorsAreNotEqual()
{
    m_MainMatrix = {8, 9, -5};

    QVERIFY2((m_MainMatrix.reverseNEnd() != m_MainMatrix.getReverseNIterator(0, 0)) && !(m_MainMatrix.reverseNEnd() == m_MainMatrix.getReverseNIterator(0, 0)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getReverseNIterator(0, 0) != m_MainMatrix.getReverseNIterator(1, 0)) && !(m_MainMatrix.getReverseNIterator(0, 0) == m_MainMatrix.getReverseNIterator(1, 0)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getReverseNIterator(1, 0) != m_MainMatrix.getReverseNIterator(2, 0)) && !(m_MainMatrix.getReverseNIterator(1, 0) == m_MainMatrix.getReverseNIterator(2, 0)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getReverseNIterator(2, 0) != m_MainMatrix.getReverseNIterator(4, 5)) && !(m_MainMatrix.getReverseNIterator(2, 0) == m_MainMatrix.getReverseNIterator(4, 5)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getReverseNIterator(4, 5) != m_MainMatrix.getReverseNIterator(6, 8)) && !(m_MainMatrix.getReverseNIterator(4, 5) == m_MainMatrix.getReverseNIterator(6, 8)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getReverseNIterator(6, 8) != m_MainMatrix.reverseNBegin()) && !(m_MainMatrix.getReverseNIterator(6, 8) == m_MainMatrix.reverseNBegin()), "The two iterators are NOT different");
}

void ReverseNIteratorTests::testSmallerThanOperator()
{
    m_MainMatrix = {8, 9, -5};

    QVERIFY2((m_MainMatrix.reverseNBegin() < m_MainMatrix.getReverseNIterator(6, 8)) && !(m_MainMatrix.reverseNBegin() >= m_MainMatrix.getReverseNIterator(6, 8)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(6, 8) < m_MainMatrix.getReverseNIterator(4, 5)) && !(m_MainMatrix.getReverseNIterator(6, 8) >= m_MainMatrix.getReverseNIterator(4, 5)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(4, 5) < m_MainMatrix.getReverseNIterator(2, 0)) && !(m_MainMatrix.getReverseNIterator(4, 5) >= m_MainMatrix.getReverseNIterator(2, 0)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(2, 0) < m_MainMatrix.getReverseNIterator(1, 0)) && !(m_MainMatrix.getReverseNIterator(2, 0) >= m_MainMatrix.getReverseNIterator(1, 0)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(1, 0) < m_MainMatrix.getReverseNIterator(0, 0)) && !(m_MainMatrix.getReverseNIterator(1, 0) >= m_MainMatrix.getReverseNIterator(0, 0)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(0, 0) < m_MainMatrix.reverseNEnd()) && !(m_MainMatrix.getReverseNIterator(0, 0) >= m_MainMatrix.reverseNEnd()), "The first iterator is NOT smaller than the second iterator");
}

void ReverseNIteratorTests::testSmallerThanOrEqualToOperator()
{
    m_MainMatrix = {8, 9, -5};

    // test operator with different iterators
    QVERIFY2((m_MainMatrix.reverseNBegin() <= m_MainMatrix.reverseNBegin()) && !(m_MainMatrix.reverseNBegin() > m_MainMatrix.reverseNBegin()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.reverseNBegin() <= m_MainMatrix.getReverseNIterator(6, 8)) && !(m_MainMatrix.reverseNBegin() > m_MainMatrix.getReverseNIterator(6, 8)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(6, 8) <= m_MainMatrix.getReverseNIterator(6, 8)) && !(m_MainMatrix.getReverseNIterator(6, 8) > m_MainMatrix.getReverseNIterator(6, 8)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(6, 8) <= m_MainMatrix.getReverseNIterator(4, 5)) && !(m_MainMatrix.getReverseNIterator(6, 8) > m_MainMatrix.getReverseNIterator(4, 5)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(4, 5) <= m_MainMatrix.getReverseNIterator(4, 5)) && !(m_MainMatrix.getReverseNIterator(4, 5) > m_MainMatrix.getReverseNIterator(4, 5)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(4, 5) <= m_MainMatrix.getReverseNIterator(2, 0)) && !(m_MainMatrix.getReverseNIterator(4, 5) > m_MainMatrix.getReverseNIterator(2, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(2, 0) <= m_MainMatrix.getReverseNIterator(2, 0)) && !(m_MainMatrix.getReverseNIterator(2, 0) > m_MainMatrix.getReverseNIterator(2, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(2, 0) <= m_MainMatrix.getReverseNIterator(1, 0)) && !(m_MainMatrix.getReverseNIterator(2, 0) > m_MainMatrix.getReverseNIterator(1, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(1, 0) <= m_MainMatrix.getReverseNIterator(1, 0)) && !(m_MainMatrix.getReverseNIterator(1, 0) > m_MainMatrix.getReverseNIterator(1, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(1, 0) <= m_MainMatrix.getReverseNIterator(0, 0)) && !(m_MainMatrix.getReverseNIterator(1, 0) > m_MainMatrix.getReverseNIterator(0, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(0, 0) <= m_MainMatrix.getReverseNIterator(0, 0)) && !(m_MainMatrix.getReverseNIterator(0, 0) > m_MainMatrix.getReverseNIterator(0, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(0, 0) <= m_MainMatrix.reverseNEnd()) && !(m_MainMatrix.getReverseNIterator(0, 0) > m_MainMatrix.reverseNEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.reverseNEnd() <= m_MainMatrix.reverseNEnd()) && !(m_MainMatrix.reverseNEnd() > m_MainMatrix.reverseNEnd()), "The first iterator is NOT smaller than or equal to the second iterator");

    // test if iterator is smaller than or equal to itself
    IntMatrixReverseNIterator it{m_MainMatrix.reverseNBegin()};
    QVERIFY2((it <= it) && (it <= m_MainMatrix.reverseNBegin()) && !(it > it) && !(it > m_MainMatrix.reverseNBegin()),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getReverseNIterator(1, 0);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getReverseNIterator(1, 0)) && !(it > it) && !(it > m_MainMatrix.getReverseNIterator(1, 0)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getReverseNIterator(4, 5);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getReverseNIterator(4, 5)) && !(it > it) && !(it > m_MainMatrix.getReverseNIterator(4, 5)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getReverseNIterator(6, 8);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getReverseNIterator(6, 8)) && !(it > it) && !(it > m_MainMatrix.getReverseNIterator(6, 8)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getReverseNIterator(7, 8);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getReverseNIterator(7, 8) && !(it > it) && !(it > m_MainMatrix.getReverseNIterator(7, 8))),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.reverseNEnd();
    QVERIFY2((it <= it) && (it <= m_MainMatrix.reverseNEnd()) && !(it > it) && !(it > m_MainMatrix.reverseNEnd()),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");

    // test with empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.reverseNBegin() <= m_MainMatrix.reverseNEnd(), "The first iterator is NOT smaller than or equal to the second iterator");
}

void ReverseNIteratorTests::testGreaterThanOperator()
{
    m_MainMatrix = {8, 9, -5};

    QVERIFY2((m_MainMatrix.reverseNEnd() > m_MainMatrix.getReverseNIterator(0, 0)) && !(m_MainMatrix.reverseNEnd() <= m_MainMatrix.getReverseNIterator(0, 0)), "TThe first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(0, 0) > m_MainMatrix.getReverseNIterator(1, 0)) && !(m_MainMatrix.getReverseNIterator(0, 0) <= m_MainMatrix.getReverseNIterator(1, 0)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(1, 0) > m_MainMatrix.getReverseNIterator(2, 0)) && !(m_MainMatrix.getReverseNIterator(1, 0) <= m_MainMatrix.getReverseNIterator(2, 0)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(2, 0) > m_MainMatrix.getReverseNIterator(4, 5)) && !(m_MainMatrix.getReverseNIterator(2, 0) <= m_MainMatrix.getReverseNIterator(4, 5)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(4, 5) > m_MainMatrix.getReverseNIterator(6, 8)) && !(m_MainMatrix.getReverseNIterator(4, 5) <= m_MainMatrix.getReverseNIterator(6, 8)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(6, 8) > m_MainMatrix.reverseNBegin()) && !(m_MainMatrix.getReverseNIterator(6, 8) <= m_MainMatrix.reverseNBegin()), "The first iterator is NOT greater than the second iterator");
}

void ReverseNIteratorTests::testGreaterThanOrEqualToOperator()
{
    m_MainMatrix = {8, 9, -5};

    // test operator with different iterators
    QVERIFY2((m_MainMatrix.reverseNEnd() >= m_MainMatrix.reverseNEnd()) && !(m_MainMatrix.reverseNEnd() < m_MainMatrix.reverseNEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.reverseNEnd() >= m_MainMatrix.getReverseNIterator(0, 0)) && !(m_MainMatrix.reverseNEnd() < m_MainMatrix.getReverseNIterator(0, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(0, 0) >= m_MainMatrix.getReverseNIterator(0, 0)) && !(m_MainMatrix.getReverseNIterator(0, 0) < m_MainMatrix.getReverseNIterator(0, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(0, 0) >= m_MainMatrix.getReverseNIterator(1, 0)) && !(m_MainMatrix.getReverseNIterator(0, 0) < m_MainMatrix.getReverseNIterator(1, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(1, 0) >= m_MainMatrix.getReverseNIterator(1, 0)) && !(m_MainMatrix.getReverseNIterator(1, 0) < m_MainMatrix.getReverseNIterator(1, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(1, 0) >= m_MainMatrix.getReverseNIterator(2, 0)) && !(m_MainMatrix.getReverseNIterator(1, 0) < m_MainMatrix.getReverseNIterator(2, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(2, 0) >= m_MainMatrix.getReverseNIterator(2, 0)) && !(m_MainMatrix.getReverseNIterator(2, 0) < m_MainMatrix.getReverseNIterator(2, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(2, 0) >= m_MainMatrix.getReverseNIterator(4, 5)) && !(m_MainMatrix.getReverseNIterator(2, 0) < m_MainMatrix.getReverseNIterator(4, 5)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(4, 5) >= m_MainMatrix.getReverseNIterator(4, 5)) && !(m_MainMatrix.getReverseNIterator(4, 5) < m_MainMatrix.getReverseNIterator(4, 5)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(4, 5) >= m_MainMatrix.getReverseNIterator(6, 8)) && !(m_MainMatrix.getReverseNIterator(4, 5) < m_MainMatrix.getReverseNIterator(6, 8)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(6, 8) >= m_MainMatrix.getReverseNIterator(6, 8)) && !(m_MainMatrix.getReverseNIterator(6, 8) < m_MainMatrix.getReverseNIterator(6, 8)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getReverseNIterator(6, 8) >= m_MainMatrix.reverseNBegin()) && !(m_MainMatrix.getReverseNIterator(6, 8) < m_MainMatrix.reverseNBegin()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.reverseNBegin() >= m_MainMatrix.reverseNBegin()) && !(m_MainMatrix.reverseNBegin() < m_MainMatrix.reverseNBegin()), "The first iterator is NOT smaller than or equal to the second iterator");

    // test if iterator is greater than or equal to itself
    IntMatrixReverseNIterator it{m_MainMatrix.reverseNEnd()};
    QVERIFY2((it >= it) && (it >= m_MainMatrix.reverseNEnd()) && !(it < it) && !(it < m_MainMatrix.reverseNEnd()),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getReverseNIterator(7, 8);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getReverseNIterator(7, 8)) && !(it < it) && !(it < m_MainMatrix.getReverseNIterator(7, 8)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getReverseNIterator(6, 8);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getReverseNIterator(6, 8)) && !(it < it) && !(it < m_MainMatrix.getReverseNIterator(6, 8)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getReverseNIterator(4, 5);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getReverseNIterator(4, 5)) && !(it < it) && !(it < m_MainMatrix.getReverseNIterator(4, 5)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getReverseNIterator(1, 0);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getReverseNIterator(1, 0)) && !(it < it) && !(it < m_MainMatrix.getReverseNIterator(1, 0)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.reverseNBegin();
    QVERIFY2((it >= it) && (it >= m_MainMatrix.reverseNBegin()) && !(it < it) && !(it < m_MainMatrix.reverseNBegin()),  "The iterator is NOT greater than or equal to itself and/or the source iterator");

    // test with empty matrix
    m_MainMatrix.clear();
    QVERIFY2((m_MainMatrix.reverseNBegin() >= m_MainMatrix.reverseNEnd()) && !(m_MainMatrix.reverseNBegin() < m_MainMatrix.reverseNEnd()), "The first iterator is NOT greater than or equal to the second iterator");
}

void ReverseNIteratorTests::testIncrementOperators()
{
    m_MainMatrix = {8, 9, -5};

    // pre-increment
    IntMatrixReverseNIterator it{m_MainMatrix.reverseNBegin()};
    ++it;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 8), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(5, 8), "Incorrect pre-incrementation");
    it = m_MainMatrix.getReverseNIterator(5, 5);
    ++it;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(4, 5), "Incorrect pre-incrementation");
    it = m_MainMatrix.getReverseNIterator(2, 5);
    ++it;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 5), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 5), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(7, 4), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 4), "Incorrect pre-incrementation");
    it = m_MainMatrix.getReverseNIterator(1, 0);
    ++it;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 0), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Incorrect pre-incrementation");

    // post-increment
    it = m_MainMatrix.reverseNBegin();
    it++;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 8), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(5, 8), "Incorrect post-incrementation");
    it = m_MainMatrix.getReverseNIterator(5, 5);
    it++;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(4, 5), "Incorrect post-incrementation");
    it = m_MainMatrix.getReverseNIterator(2, 5);
    it++;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 5), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 5), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(7, 4), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 4), "Incorrect post-incrementation");
    it = m_MainMatrix.getReverseNIterator(1, 0);
    it++;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 0), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Incorrect post-incrementation");

    // test a combination of "pre" and "post" behaviors
    IntMatrixReverseNIterator srcIt{m_MainMatrix.getReverseNIterator(6, 5)};
    IntMatrixReverseNIterator destIt{++(++srcIt)};
    QVERIFY2(srcIt == m_MainMatrix.getReverseNIterator(5, 5) && destIt == m_MainMatrix.getReverseNIterator(4, 5), "Incorrect pre-pre-incrementation");
    srcIt = m_MainMatrix.getReverseNIterator(6, 5);
    destIt = (srcIt++)++;
    QVERIFY2(srcIt == m_MainMatrix.getReverseNIterator(5, 5) && destIt == m_MainMatrix.getReverseNIterator(6, 5), "Incorrect post-post-incrementation");
    srcIt = m_MainMatrix.getReverseNIterator(6, 5);
    destIt = (++srcIt)++;
    QVERIFY2(srcIt == m_MainMatrix.getReverseNIterator(5, 5) && destIt == m_MainMatrix.getReverseNIterator(5, 5), "Incorrect post-pre-incrementation");
    srcIt = m_MainMatrix.getReverseNIterator(6, 5);
    destIt = ++(srcIt++);
    QVERIFY2(srcIt == m_MainMatrix.getReverseNIterator(5, 5) && destIt == m_MainMatrix.getReverseNIterator(5, 5), "Incorrect pre-post-incrementation");
}

void ReverseNIteratorTests::testDecrementOperators()
{
    m_MainMatrix = {8, 9, -5};

    // pre-decrement
    IntMatrixReverseNIterator it{m_MainMatrix.reverseNEnd()};
    --it;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 0), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 0), "Incorrect pre-decrementation");
    it = m_MainMatrix.getReverseNIterator(6, 4);
    --it;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(7, 4), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 5), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 5), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(2, 5), "Incorrect pre-decrementation");
    it = m_MainMatrix.getReverseNIterator(4, 5);
    --it;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(5, 5), "Incorrect pre-decrementation");
    it = m_MainMatrix.getReverseNIterator(5, 8);
    --it;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 8), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Incorrect pre-decrementation");


    // post-decrement
    it = m_MainMatrix.reverseNEnd();
    it--;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 0), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 0), "Incorrect post-decrementation");
    it = m_MainMatrix.getReverseNIterator(4, 5);
    it--;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(5, 5), "Incorrect post-decrementation");
    it = m_MainMatrix.getReverseNIterator(6, 4);
    it--;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(7, 4), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 5), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 5), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(2, 5), "Incorrect post-decrementation");
    it = m_MainMatrix.getReverseNIterator(6, 8);
    it--;
    QVERIFY2(it == m_MainMatrix.getReverseNIterator(7, 8), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Incorrect post-decrementation");

    // test a combination of "pre" and "post" behaviors
    IntMatrixReverseNIterator srcIt{m_MainMatrix.getReverseNIterator(4, 5)};
    IntMatrixReverseNIterator destIt{--(--srcIt)};
    QVERIFY2(srcIt == m_MainMatrix.getReverseNIterator(5, 5) && destIt == m_MainMatrix.getReverseNIterator(6, 5), "Incorrect pre-pre-decrementation");
    srcIt = m_MainMatrix.getReverseNIterator(4, 5);
    destIt = (srcIt--)--;
    QVERIFY2(srcIt == m_MainMatrix.getReverseNIterator(5, 5) && destIt == m_MainMatrix.getReverseNIterator(4, 5), "Incorrect post-post-decrementation");
    srcIt = m_MainMatrix.getReverseNIterator(4, 5);
    destIt = (--srcIt)--;
    QVERIFY2(srcIt == m_MainMatrix.getReverseNIterator(5, 5) && destIt == m_MainMatrix.getReverseNIterator(5, 5), "Incorrect post-pre-decrementation");
    srcIt = m_MainMatrix.getReverseNIterator(4, 5);
    destIt = --(srcIt--);
    QVERIFY2(srcIt == m_MainMatrix.getReverseNIterator(5, 5) && destIt == m_MainMatrix.getReverseNIterator(5, 5), "Incorrect pre-post-decrementation");
}

void ReverseNIteratorTests::testOperatorPlus()
{
    m_MainMatrix = {8, 9, -5};

    // test for non-empty matrix
    IntMatrixReverseNIterator it{m_MainMatrix.reverseNEnd()};
    QVERIFY2(it + 3 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.getReverseNIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.getReverseNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-5) == m_MainMatrix.getReverseNIterator(4, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-11) == m_MainMatrix.getReverseNIterator(2, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.getReverseNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-72) == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-73) == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-75) == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getReverseNIterator(0, 0);
    QVERIFY2(it + 4 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getReverseNIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.getReverseNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-4) == m_MainMatrix.getReverseNIterator(4, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-10) == m_MainMatrix.getReverseNIterator(2, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-70) == m_MainMatrix.getReverseNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-72) == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-74) == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getReverseNIterator(1, 0);
    QVERIFY2(it + 5 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.getReverseNIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getReverseNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-3) == m_MainMatrix.getReverseNIterator(4, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-9) == m_MainMatrix.getReverseNIterator(2, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-69) == m_MainMatrix.getReverseNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-70) == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-73) == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getReverseNIterator(4, 5);
    QVERIFY2(it + 48 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 46 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 45 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 44 == m_MainMatrix.getReverseNIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 43 == m_MainMatrix.getReverseNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 6 == m_MainMatrix.getReverseNIterator(6, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.getReverseNIterator(2, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getReverseNIterator(4, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.getReverseNIterator(6, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-6) == m_MainMatrix.getReverseNIterator(2, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-26) == m_MainMatrix.getReverseNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-27) == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-28) == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-30) == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getReverseNIterator(6, 8);
    QVERIFY2(it + 74 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 72 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 71 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 70 == m_MainMatrix.getReverseNIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 69 == m_MainMatrix.getReverseNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 24 == m_MainMatrix.getReverseNIterator(6, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.getReverseNIterator(3, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getReverseNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-4) == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.reverseNBegin();
    QVERIFY2(it + 75 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 73 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 72 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 71 == m_MainMatrix.getReverseNIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 70 == m_MainMatrix.getReverseNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 25 == m_MainMatrix.getReverseNIterator(6, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 4 == m_MainMatrix.getReverseNIterator(3, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.getReverseNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-3) == m_MainMatrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.reverseNBegin() + (-1) == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.reverseNBegin() + 1 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.reverseNEnd() + 0 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.reverseNEnd() + 1 == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.reverseNEnd() + (-1) == m_MainMatrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");

    // test for empty iterators
    IntMatrixReverseNIterator emptyIt1{};
    IntMatrixReverseNIterator emptyIt2{};
    IntMatrixReverseNIterator emptyIt3{};
    emptyIt1 = emptyIt3 + (-1);
    emptyIt2 = emptyIt3 + 1;
    QVERIFY2(emptyIt1 == emptyIt3, "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(emptyIt2 == emptyIt3, "Operator + does not work correctly, the resulting iterator is not the right one");
}

void ReverseNIteratorTests::testOperatorMinus()
{
    m_MainMatrix = {8, 9, -5};

    // test for non-empty matrix
    IntMatrixReverseNIterator it{m_MainMatrix.reverseNEnd()};
    QVERIFY2(it - (-3) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.getReverseNIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.getReverseNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 5 == m_MainMatrix.getReverseNIterator(4, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 11 == m_MainMatrix.getReverseNIterator(2, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.getReverseNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 72 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 73 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 75 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getReverseNIterator(0, 0);
    QVERIFY2(it - (-4) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getReverseNIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.getReverseNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 4 == m_MainMatrix.getReverseNIterator(4, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 10 == m_MainMatrix.getReverseNIterator(2, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 70 == m_MainMatrix.getReverseNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 72 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 74 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getReverseNIterator(1, 0);
    QVERIFY2(it - (-5) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.getReverseNIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getReverseNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 3 == m_MainMatrix.getReverseNIterator(4, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 9 == m_MainMatrix.getReverseNIterator(2, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 69 == m_MainMatrix.getReverseNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 70 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 73 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getReverseNIterator(4, 5);
    QVERIFY2(it - (-48) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-46) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-45) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-44) == m_MainMatrix.getReverseNIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-43) == m_MainMatrix.getReverseNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-6) == m_MainMatrix.getReverseNIterator(6, 4), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.getReverseNIterator(2, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getReverseNIterator(4, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.getReverseNIterator(6, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 6 == m_MainMatrix.getReverseNIterator(2, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 26 == m_MainMatrix.getReverseNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 27 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 28 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 30 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getReverseNIterator(6, 8);
    QVERIFY2(it - (-74) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-72) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-71) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-70) == m_MainMatrix.getReverseNIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-69) == m_MainMatrix.getReverseNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-24) == m_MainMatrix.getReverseNIterator(6, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.getReverseNIterator(3, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getReverseNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 4 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.reverseNBegin();
    QVERIFY2(it - (-75) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-73) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-72) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-71) == m_MainMatrix.getReverseNIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-70) == m_MainMatrix.getReverseNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-25) == m_MainMatrix.getReverseNIterator(6, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-4) == m_MainMatrix.getReverseNIterator(3, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.getReverseNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 3 == m_MainMatrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.reverseNBegin() - 1 == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.reverseNBegin() - (-1) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.reverseNEnd() - 0 == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.reverseNEnd() - (-1) == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.reverseNEnd() - 1 == m_MainMatrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");

    // test for empty iterators
    IntMatrixReverseNIterator emptyIt1{};
    IntMatrixReverseNIterator emptyIt2{};
    IntMatrixReverseNIterator emptyIt3{};
    emptyIt1 = emptyIt3 - 1;
    emptyIt2 = emptyIt3 - (-1);
    QVERIFY2(emptyIt1 == emptyIt3, "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(emptyIt2 == emptyIt3, "Operator - does not work correctly, the resulting iterator is not the right one");
}

void ReverseNIteratorTests::testOperatorPlusEqual()
{
    IntMatrixReverseNIterator it;

    // test for non-empty matrix
    m_MainMatrix = {8, 9, -5};

    IntMatrixReverseNIterator referenceIt{m_MainMatrix.reverseNEnd()};
    it = referenceIt; it += 3; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-2); QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-5); QVERIFY2(it == m_MainMatrix.getReverseNIterator(4, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-11); QVERIFY2(it == m_MainMatrix.getReverseNIterator(2, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-71); QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-72); QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-73); QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-75); QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getReverseNIterator(0, 0);
    it = referenceIt; it += 4; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 2; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-4); QVERIFY2(it == m_MainMatrix.getReverseNIterator(4, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-10); QVERIFY2(it == m_MainMatrix.getReverseNIterator(2, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-70); QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-71); QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-72); QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-74); QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getReverseNIterator(1, 0);
    it = referenceIt; it += 5; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 3; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 2; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-3); QVERIFY2(it == m_MainMatrix.getReverseNIterator(4, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-9); QVERIFY2(it == m_MainMatrix.getReverseNIterator(2, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-69); QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-70); QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-71); QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-73); QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getReverseNIterator(4, 5);
    it = referenceIt; it += 48; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 46; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 45; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 44; QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 43; QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 6; QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 2; QVERIFY2(it == m_MainMatrix.getReverseNIterator(2, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getReverseNIterator(4, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-2); QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-6); QVERIFY2(it == m_MainMatrix.getReverseNIterator(2, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-26); QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-27); QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-28); QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-30); QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getReverseNIterator(6, 8);
    it = referenceIt; it += 74; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 72; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 71; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 70; QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 69; QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 24; QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 3; QVERIFY2(it == m_MainMatrix.getReverseNIterator(3, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-2); QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-4); QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.reverseNBegin();
    it = referenceIt; it += 75; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 73; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 72; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 71; QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 70; QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 25; QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 4; QVERIFY2(it == m_MainMatrix.getReverseNIterator(3, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-3); QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    referenceIt = m_MainMatrix.reverseNBegin();
    referenceIt = m_MainMatrix.reverseNEnd();
    it = referenceIt; it += (-1); QVERIFY2(m_MainMatrix.reverseNBegin() == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += 1; QVERIFY2(m_MainMatrix.reverseNBegin() == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += 0; QVERIFY2(m_MainMatrix.reverseNEnd() == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += 1; QVERIFY2(m_MainMatrix.reverseNEnd() == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += (-1); QVERIFY2(m_MainMatrix.reverseNEnd() == m_MainMatrix.reverseNEnd(), "Operator += does not work correctly, the updated iterator is not the right one");

    // test for empty iterators
    IntMatrixReverseNIterator emptyIt1{};
    IntMatrixReverseNIterator emptyIt2{};
    IntMatrixReverseNIterator emptyIt3{};
    emptyIt2 += (-1); QVERIFY2(emptyIt2 == emptyIt1, "Operator += does not work correctly, the updated iterator is not the right one");
    emptyIt3 += 1; QVERIFY2(emptyIt3 == emptyIt1, "Operator += does not work correctly, the updated iterator is not the right one");
}

void ReverseNIteratorTests::testOperatorMinusEqual()
{
    IntMatrixReverseNIterator it;

    // test for non-empty matrix
    m_MainMatrix = {8, 9, -5};

    IntMatrixReverseNIterator referenceIt{m_MainMatrix.reverseNEnd()};
    it = referenceIt; it -= (-3); QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 2; QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 5; QVERIFY2(it == m_MainMatrix.getReverseNIterator(4, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 11; QVERIFY2(it == m_MainMatrix.getReverseNIterator(2, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 71; QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 72; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 73; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 75; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getReverseNIterator(0, 0);
    it = referenceIt; it -= (-4); QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-2); QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 4; QVERIFY2(it == m_MainMatrix.getReverseNIterator(4, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 10; QVERIFY2(it == m_MainMatrix.getReverseNIterator(2, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 70; QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 71; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 72; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 74; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getReverseNIterator(1, 0);
    it = referenceIt; it -= (-5); QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-3); QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-2); QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 3; QVERIFY2(it == m_MainMatrix.getReverseNIterator(4, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 9; QVERIFY2(it == m_MainMatrix.getReverseNIterator(2, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 69; QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 70; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 71; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 73; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getReverseNIterator(4, 5);
    it = referenceIt; it -= (-48); QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-46); QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-45); QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-44); QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-43); QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-6); QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-2); QVERIFY2(it == m_MainMatrix.getReverseNIterator(2, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getReverseNIterator(4, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 2; QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 6; QVERIFY2(it == m_MainMatrix.getReverseNIterator(2, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 26; QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 27; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 28; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 30; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getReverseNIterator(6, 8);
    it = referenceIt; it -= (-74); QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-72); QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-71); QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-70); QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-69); QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-24); QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-3); QVERIFY2(it == m_MainMatrix.getReverseNIterator(3, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 2; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 4; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.reverseNBegin();
    it = referenceIt; it -= (-75); QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-73); QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-72); QVERIFY2(it == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-71); QVERIFY2(it == m_MainMatrix.getReverseNIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-70); QVERIFY2(it == m_MainMatrix.getReverseNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-25); QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-4); QVERIFY2(it == m_MainMatrix.getReverseNIterator(3, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.getReverseNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 3; QVERIFY2(it == m_MainMatrix.reverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    referenceIt = m_MainMatrix.reverseNBegin();
    referenceIt = m_MainMatrix.reverseNEnd();
    it = referenceIt; it -= 1; QVERIFY2(m_MainMatrix.reverseNBegin() == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= (-1); QVERIFY2(m_MainMatrix.reverseNBegin() == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= 0; QVERIFY2(m_MainMatrix.reverseNEnd() == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= (-1); QVERIFY2(m_MainMatrix.reverseNEnd() == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= 1; QVERIFY2(m_MainMatrix.reverseNEnd() == m_MainMatrix.reverseNEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");

    // test for empty iterators
    IntMatrixReverseNIterator emptyIt1{};
    IntMatrixReverseNIterator emptyIt2{};
    IntMatrixReverseNIterator emptyIt3{};
    emptyIt2 -= 1; QVERIFY2(emptyIt2 == emptyIt1, "Operator -= does not work correctly, the updated iterator is not the right one");
    emptyIt3 -= (-1); QVERIFY2(emptyIt3 == emptyIt1, "Operator -= does not work correctly, the updated iterator is not the right one");
}

void ReverseNIteratorTests::testDifferenceOperator()
{
    // test for non-empty matrix
    m_MainMatrix = {8, 9, -5};

    QVERIFY2(m_MainMatrix.reverseNBegin() - m_MainMatrix.reverseNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseNBegin() - m_MainMatrix.getReverseNIterator(6, 8) == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseNBegin() - m_MainMatrix.getReverseNIterator(4, 5) == -27, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseNBegin() - m_MainMatrix.getReverseNIterator(1, 0) == -70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseNBegin() - m_MainMatrix.getReverseNIterator(0, 0) == -71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseNBegin() - m_MainMatrix.reverseNEnd() == -72, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getReverseNIterator(6, 8) - m_MainMatrix.reverseNBegin() == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(6, 8) - m_MainMatrix.getReverseNIterator(6, 8) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(6, 8) - m_MainMatrix.getReverseNIterator(4, 5) == -26, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(6, 8) - m_MainMatrix.getReverseNIterator(1, 0) == -69, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(6, 8) - m_MainMatrix.getReverseNIterator(0, 0) == -70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(6, 8) - m_MainMatrix.reverseNEnd() == -71, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getReverseNIterator(4, 5) - m_MainMatrix.reverseNBegin() == 27, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(4, 5) - m_MainMatrix.getReverseNIterator(6, 8) == 26, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(4, 5) - m_MainMatrix.getReverseNIterator(4, 5) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(4, 5) - m_MainMatrix.getReverseNIterator(1, 0) == -43, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(4, 5) - m_MainMatrix.getReverseNIterator(0, 0) == -44, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(4, 5) - m_MainMatrix.reverseNEnd() == -45, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getReverseNIterator(1, 0) - m_MainMatrix.reverseNBegin() == 70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(1, 0) - m_MainMatrix.getReverseNIterator(6, 8) == 69, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(1, 0) - m_MainMatrix.getReverseNIterator(4, 5) == 43, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(1, 0) - m_MainMatrix.getReverseNIterator(1, 0) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(1, 0) - m_MainMatrix.getReverseNIterator(0, 0) == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(1, 0) - m_MainMatrix.reverseNEnd() == -2, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getReverseNIterator(0, 0) - m_MainMatrix.reverseNBegin() == 71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(0, 0) - m_MainMatrix.getReverseNIterator(6, 8) == 70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(0, 0) - m_MainMatrix.getReverseNIterator(4, 5) == 44, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(0, 0) - m_MainMatrix.getReverseNIterator(1, 0) == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(0, 0) - m_MainMatrix.getReverseNIterator(0, 0) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(0, 0) - m_MainMatrix.reverseNEnd() == -1, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.reverseNEnd() - m_MainMatrix.reverseNBegin() == 72, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseNEnd() - m_MainMatrix.getReverseNIterator(6, 8) == 71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseNEnd() - m_MainMatrix.getReverseNIterator(4, 5) == 45, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseNEnd() - m_MainMatrix.getReverseNIterator(1, 0) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseNEnd() - m_MainMatrix.getReverseNIterator(0, 0) == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseNEnd() - m_MainMatrix.reverseNEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");

    // additional tests with "random" elements from same column/different columns
    QVERIFY2(m_MainMatrix.getReverseNIterator(4, 5) - m_MainMatrix.getReverseNIterator(2, 7) == 14, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(2, 7) - m_MainMatrix.getReverseNIterator(4, 5) == -14, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(4, 5) - m_MainMatrix.getReverseNIterator(2, 5) == -2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getReverseNIterator(2, 5) - m_MainMatrix.getReverseNIterator(4, 5) == 2, "The difference operator does not work correctly, difference between iterators is wrong");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.reverseNEnd() - m_MainMatrix.reverseNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseNBegin() - m_MainMatrix.reverseNEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseNBegin() - m_MainMatrix.reverseNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.reverseNEnd() - m_MainMatrix.reverseNEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");

    // test for empty iterator
    IntMatrixReverseNIterator emptyIt1{};
    IntMatrixReverseNIterator emptyIt2{};
    QVERIFY2(emptyIt1 - emptyIt2 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(emptyIt2 - emptyIt1 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(emptyIt1 - emptyIt1 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
}

void ReverseNIteratorTests::testDereferenceAsteriskOperator()
{
    // test reading element
    m_MainMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};
    QVERIFY2(*m_MainMatrix.getReverseNIterator(0, 0) == 1, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getReverseNIterator(1, 0) == -2, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getReverseNIterator(2, 1) == -6, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getReverseNIterator(1, 3) == 11, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.reverseNBegin() == -12, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");

    // test writing to element
    m_MainMatrix = {3, 4, -20};
    *m_MainMatrix.getReverseNIterator(0, 0) = 1;
    *m_MainMatrix.getReverseNIterator(1, 0) = -2;
    *m_MainMatrix.getReverseNIterator(2, 1) = -6;
    *m_MainMatrix.getReverseNIterator(1, 3) = 11;
    *m_MainMatrix.reverseNBegin() = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY2(m_MainMatrix.at(1, 0) == -2, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY2(m_MainMatrix.at(2, 1) == -6, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY2(m_MainMatrix.at(1, 3) == 11, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY2(m_MainMatrix.at(2, 3) == -12, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY(m_MainMatrix.at(1, 2) == -20);

    // additional tests
    m_MainMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    IntMatrixReverseNIterator readIter{m_MainMatrix.reverseNBegin()};
    m_MainMatrix.at(0, 1) = 10;
    readIter += 2;
    QVERIFY2(*readIter == 10, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");

    m_MainMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    IntMatrixReverseNIterator writeIter{m_MainMatrix.reverseNBegin()};
    writeIter += 2;
    *writeIter = 10;
    QVERIFY2(m_MainMatrix.at(0, 1) == 10, "The dereference (*) operator does not work correctly, the value is not correctly written to the pointed location");
}

void ReverseNIteratorTests::testDereferenceArrowOperator()
{
    // test reading element
    m_AuxStringMatrix = {3, 4, {"abc", "jihgfedcba", "abcde", "", "ba", "a", "ihgfedcba", "abcdefghijk", "abcd", "gfedcba", "abcdefgh", "fedcba"}};
    QVERIFY2(m_AuxStringMatrix.getReverseNIterator(0, 0)->size() == 3, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getReverseNIterator(1, 0)->size() == 2, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getReverseNIterator(2, 1)->size() == 7, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getReverseNIterator(1, 3)->size() == 11, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.reverseNBegin()->size() == 6, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");

    // test writing to element
    m_AuxStringMatrix = {3, 4, "zzz"};
    m_AuxStringMatrix.getReverseNIterator(0, 0)->assign("abc");
    m_AuxStringMatrix.getReverseNIterator(1, 0)->assign("ba");
    m_AuxStringMatrix.getReverseNIterator(2, 1)->assign("gfedcba");
    m_AuxStringMatrix.getReverseNIterator(1, 3)->assign("abcdefghijk");
    m_AuxStringMatrix.reverseNBegin()->assign("fedcba");
    QVERIFY2(m_AuxStringMatrix.at(0, 0) == "abc", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY2(m_AuxStringMatrix.at(1, 0) == "ba", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY2(m_AuxStringMatrix.at(2, 1) == "gfedcba", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY2(m_AuxStringMatrix.at(1, 3) == "abcdefghijk", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY2(m_AuxStringMatrix.at(2, 3) == "fedcba", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY(m_AuxStringMatrix.at(1, 2) == "zzz");

    // additional tests
    m_AuxStringMatrix = {3, 2, {"abc", "jkl", "defed", "mnop", "ghi", "qr"}};
    StringMatrixReverseNIterator it{m_AuxStringMatrix.reverseNBegin()};
    m_AuxStringMatrix.at(0, 1) = "abcdefghi";
    it += 2;
    QVERIFY2(it->size() == 9, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");

    m_AuxStringMatrix = {3, 2, {"abc", "jkl", "defed", "mnop", "ghi", "qr"}};
    it = m_AuxStringMatrix.reverseNBegin();
    it += 2;
    it->assign("abcdefghi");
    QVERIFY2(m_AuxStringMatrix.at(0, 1) == "abcdefghi", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
}

void ReverseNIteratorTests::testDereferenceSquareBracketsOperator()
{
    // test reading element
    m_MainMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};

    IntMatrixReverseNIterator it{m_MainMatrix.reverseNBegin()};
    QVERIFY2(it[11] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[10] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[6] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[1] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getReverseNIterator(1, 3);
    QVERIFY2(it[10] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[9] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[5] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-1] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getReverseNIterator(2, 1);
    QVERIFY2(it[5] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[4] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-5] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-6] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getReverseNIterator(1, 0);
    QVERIFY2(it[1] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-4] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-9] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-10] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getReverseNIterator(0, 0);
    QVERIFY2(it[0] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-1] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-5] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-10] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-11] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    // test writing to element (before running a new scenario the matrix should be reset to its initial value value)
    m_MainMatrix = {3, 4, -20}; // initial

    it = m_MainMatrix.getReverseNIterator(0, 0);
    it[0] = 1;
    it[-1] = -2;
    it[-5] = -6;
    it[-10] = 11;
    it[-11] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 0) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 1) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 3) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 3) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(1, 2) == -20);

    m_MainMatrix = {3, 4, -20}; // reset

    it = m_MainMatrix.getReverseNIterator(1, 0);
    it[1] = 1;
    it[0] = -2;
    it[-4] = -6;
    it[-9] = 11;
    it[-10] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 0) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 1) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 3) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 3) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(1, 2) == -20);

    m_MainMatrix = {3, 4, -20}; // reset

    it = m_MainMatrix.getReverseNIterator(2, 1);
    it[5] = 1;
    it[4] = -2;
    it[0] = -6;
    it[-5] = 11;
    it[-6] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 0) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 1) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 3) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 3) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(1, 2) == -20);

    m_MainMatrix = {3, 4, -20}; // reset

    it = m_MainMatrix.getReverseNIterator(1, 3);
    it[10] = 1;
    it[9] = -2;
    it[5] = -6;
    it[0] = 11;
    it[-1] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 0) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 1) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 3) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 3) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(1, 2) == -20);

    m_MainMatrix = {3, 4, -20}; // reset

    it = m_MainMatrix.reverseNBegin();
    it[11] = 1;
    it[10] = -2;
    it[6] = -6;
    it[1] = 11;
    it[0] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 0) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 1) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 3) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(2, 3) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(1, 2) == -20);
}

void ReverseNIteratorTests::testStdCount()
{
    using namespace std;

    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};

    int matchCount{count(m_MainMatrix.reverseNBegin(), m_MainMatrix.reverseNEnd(), 2)};
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseNBegin(), m_MainMatrix.reverseNEnd(), -5);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseNIterator(4, 1), m_MainMatrix.getReverseNIterator(3, 0), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseNIterator(0, 2), m_MainMatrix.getReverseNIterator(2, 0), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseNIterator(0, 2), m_MainMatrix.getReverseNIterator(3, 0), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseNIterator(4, 1), m_MainMatrix.getReverseNIterator(2, 0), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseNBegin(), m_MainMatrix.getReverseNIterator(3, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseNIterator(3, 2), m_MainMatrix.reverseNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseNBegin(), m_MainMatrix.getReverseNIterator(2, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseNIterator(2, 2), m_MainMatrix.reverseNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseNIterator(9), m_MainMatrix.getReverseNIterator(2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseNIterator(10), m_MainMatrix.getReverseNIterator(2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseNIterator(9), m_MainMatrix.getReverseNIterator(3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseNIterator(10), m_MainMatrix.getReverseNIterator(3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseNBegin(), m_MainMatrix.getReverseNIterator(13), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseNIterator(13), m_MainMatrix.reverseNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseNBegin(), m_MainMatrix.getReverseNIterator(12), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getReverseNIterator(12), m_MainMatrix.reverseNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseNColumnBegin(1), m_MainMatrix.reverseNColumnEnd(1), 5);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseNColumnEnd(3), m_MainMatrix.reverseNColumnEnd(0), 8);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseNColumnBegin(3), m_MainMatrix.reverseNColumnEnd(3), 9);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseNColumnBegin(3), m_MainMatrix.reverseNColumnEnd(2), 9);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseNColumnEnd(1), m_MainMatrix.reverseNEnd(), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseNBegin(), m_MainMatrix.reverseNColumnEnd(1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseNColumnBegin(2), m_MainMatrix.reverseNEnd(), 1);
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.reverseNBegin(), m_MainMatrix.reverseNColumnBegin(2), 1);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
}

void ReverseNIteratorTests::testStdFind()
{
    using namespace std;

    // test finding elements in specific ranges within unempty matrix
    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 6, 9, 11}};

    QVERIFY2(find(m_MainMatrix.reverseNBegin(), m_MainMatrix.reverseNEnd(), 5) != m_MainMatrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNBegin(), m_MainMatrix.reverseNEnd(), 10) == m_MainMatrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNColumnBegin(1), m_MainMatrix.reverseNColumnEnd(1), 6) != m_MainMatrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNColumnBegin(1), m_MainMatrix.reverseNColumnEnd(1), 5) != m_MainMatrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNColumnBegin(1), m_MainMatrix.reverseNColumnEnd(1), 8) != m_MainMatrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNColumnBegin(1), m_MainMatrix.reverseNColumnEnd(1), -1) == m_MainMatrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNColumnBegin(1), m_MainMatrix.reverseNColumnEnd(1), 1) == m_MainMatrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNColumnBegin(1), m_MainMatrix.reverseNColumnEnd(1), 10) == m_MainMatrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNColumnBegin(1), m_MainMatrix.reverseNEnd(), 6) != m_MainMatrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNColumnBegin(1), m_MainMatrix.reverseNEnd(), -1) != m_MainMatrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNColumnBegin(1), m_MainMatrix.reverseNEnd(), 3) != m_MainMatrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNColumnBegin(1), m_MainMatrix.reverseNEnd(), -2) == m_MainMatrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNColumnBegin(1), m_MainMatrix.reverseNEnd(), 10) == m_MainMatrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNBegin(), m_MainMatrix.reverseNColumnEnd(1), 11) != m_MainMatrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNBegin(), m_MainMatrix.reverseNColumnEnd(1), 5) != m_MainMatrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNBegin(), m_MainMatrix.reverseNColumnEnd(1), 0) != m_MainMatrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNBegin(), m_MainMatrix.reverseNColumnEnd(1), 1) == m_MainMatrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNBegin(), m_MainMatrix.reverseNColumnEnd(1), 10) == m_MainMatrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseNIterator(1, 3), m_MainMatrix.getReverseNIterator(3, 1), 7) != m_MainMatrix.getReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseNIterator(1, 3), m_MainMatrix.getReverseNIterator(3, 1), -7) != m_MainMatrix.getReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseNIterator(1, 3), m_MainMatrix.getReverseNIterator(3, 1), -2) != m_MainMatrix.getReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseNIterator(1, 3), m_MainMatrix.getReverseNIterator(3, 1), -1) == m_MainMatrix.getReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseNIterator(1, 3), m_MainMatrix.getReverseNIterator(3, 1), 11) == m_MainMatrix.getReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseNIterator(1, 3), m_MainMatrix.getReverseNIterator(3, 1), 10) == m_MainMatrix.getReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseNIterator(3, 1), m_MainMatrix.reverseNEnd(), 0) != m_MainMatrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseNIterator(3, 1), m_MainMatrix.reverseNEnd(), -1) != m_MainMatrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseNIterator(3, 1), m_MainMatrix.reverseNEnd(), 4) != m_MainMatrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseNIterator(3, 1), m_MainMatrix.reverseNEnd(), 11) == m_MainMatrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getReverseNIterator(3, 1), m_MainMatrix.reverseNEnd(), 10) == m_MainMatrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNBegin(), m_MainMatrix.getReverseNIterator(1, 3), 11) != m_MainMatrix.getReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNBegin(), m_MainMatrix.getReverseNIterator(1, 3), 2) != m_MainMatrix.getReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNBegin(), m_MainMatrix.getReverseNIterator(1, 3), 9) != m_MainMatrix.getReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNBegin(), m_MainMatrix.getReverseNIterator(1, 3), 0) == m_MainMatrix.getReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.reverseNBegin(), m_MainMatrix.getReverseNIterator(1, 3), 10) == m_MainMatrix.getReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

    // other tests
    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};
    IntMatrixReverseNIterator it{find(m_MainMatrix.reverseNBegin(), m_MainMatrix.reverseNEnd(), 4)};
    ++it;
    QVERIFY2(*it == 1, "The iterator doesn't work correctly with std::find, incorrect next element returned");

    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};
    QVERIFY2(find(m_MainMatrix.reverseNBegin(), m_MainMatrix.reverseNEnd(), 10) == m_MainMatrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix");

    it = m_MainMatrix.reverseNBegin();
    while(it != m_MainMatrix.reverseNEnd())
    {
        it = find(it, m_MainMatrix.reverseNEnd(), 9);

        if (it != m_MainMatrix.reverseNEnd())
        {
            *it = 10;
        }
    }
    int expectedNumber{std::count(m_MainMatrix.reverseNBegin(), m_MainMatrix.reverseNEnd(), 10)};
    QVERIFY2(expectedNumber == 3, "The iterator doesn't work properly with std::find, element values haven't been correctly replaced");
}

void ReverseNIteratorTests::testStdSort()
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
        std::sort(m_MainMatrix.reverseNColumnBegin(col), m_MainMatrix.reverseNColumnEnd(col));
    }

    QVERIFY2(m_MainMatrix.at(0, 0) ==  4 && m_MainMatrix.at(0, 1) == 9 && m_MainMatrix.at(0, 2) ==  9 && m_MainMatrix.at(0, 3) == 11 &&
             m_MainMatrix.at(1, 0) ==  3 && m_MainMatrix.at(1, 1) == 8 && m_MainMatrix.at(1, 2) ==  8 && m_MainMatrix.at(1, 3) ==  9 &&
             m_MainMatrix.at(2, 0) ==  1 && m_MainMatrix.at(2, 1) == 6 && m_MainMatrix.at(2, 2) ==  2 && m_MainMatrix.at(2, 3) ==  7 &&
             m_MainMatrix.at(3, 0) ==  1 && m_MainMatrix.at(3, 1) == 5 && m_MainMatrix.at(3, 2) ==  2 && m_MainMatrix.at(3, 3) ==  2 &&
             m_MainMatrix.at(4, 0) == -1 && m_MainMatrix.at(4, 1) == 0 && m_MainMatrix.at(4, 2) == -2 && m_MainMatrix.at(4, 3) == -7,

             "The iterator objects don't work correctly, the per column sorting has not been done properly");

    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 6, 9, 11}};

    std::sort(m_MainMatrix.reverseNBegin(), m_MainMatrix.reverseNEnd());

    QVERIFY2(m_MainMatrix.at(0, 0) == 11 && m_MainMatrix.at(0, 1) == 8 && m_MainMatrix.at(0, 2) == 3 && m_MainMatrix.at(0, 3) ==  1 &&
             m_MainMatrix.at(1, 0) ==  9 && m_MainMatrix.at(1, 1) == 7 && m_MainMatrix.at(1, 2) == 2 && m_MainMatrix.at(1, 3) ==  0 &&
             m_MainMatrix.at(2, 0) ==  9 && m_MainMatrix.at(2, 1) == 6 && m_MainMatrix.at(2, 2) == 2 && m_MainMatrix.at(2, 3) == -1 &&
             m_MainMatrix.at(3, 0) ==  9 && m_MainMatrix.at(3, 1) == 5 && m_MainMatrix.at(3, 2) == 2 && m_MainMatrix.at(3, 3) == -2 &&
             m_MainMatrix.at(4, 0) ==  8 && m_MainMatrix.at(4, 1) == 4 && m_MainMatrix.at(4, 2) == 1 && m_MainMatrix.at(4, 3) == -7,

             "The iterator objects don't work correctly, the matrix has not been sorted properly");

    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, (7), 3, 8, 2, 2, 1, (0), 8, 9, 4, 6, 9, 11}};

    std::sort(m_MainMatrix.getReverseNIterator(1, 3), m_MainMatrix.getReverseNIterator(3, 1));

    QVERIFY2(m_MainMatrix.at(0, 0) == -1 && m_MainMatrix.at(0, 1) ==  5  && m_MainMatrix.at(0, 2) == 8 && m_MainMatrix.at(0, 3) ==  -2  &&
             m_MainMatrix.at(1, 0) ==  1 && m_MainMatrix.at(1, 1) ==  9  && m_MainMatrix.at(1, 2) == 7 && m_MainMatrix.at(1, 3) == (-7) &&
             m_MainMatrix.at(2, 0) ==  3 && m_MainMatrix.at(2, 1) ==  8  && m_MainMatrix.at(2, 2) == 6 && m_MainMatrix.at(2, 3) ==   2  &&
             m_MainMatrix.at(3, 0) ==  1 && m_MainMatrix.at(3, 1) == (0) && m_MainMatrix.at(3, 2) == 2 && m_MainMatrix.at(3, 3) ==   9  &&
             m_MainMatrix.at(4, 0) ==  4 && m_MainMatrix.at(4, 1) ==  9  && m_MainMatrix.at(4, 2) == 2 && m_MainMatrix.at(4, 3) ==  11,

             "The iterator objects don't work correctly, the matrix has not been sorted properly");

    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, (-2), 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 6, 9, (11)}};

    std::sort(m_MainMatrix.reverseNBegin(), m_MainMatrix.getReverseNIterator(1, 2));

    QVERIFY2(m_MainMatrix.at(0, 0) == -1 && m_MainMatrix.at(0, 1) == 5 && m_MainMatrix.at(0, 2) ==   2  && m_MainMatrix.at(0, 3) ==   8 &&
             m_MainMatrix.at(1, 0) ==  1 && m_MainMatrix.at(1, 1) == 9 && m_MainMatrix.at(1, 2) == (-2) && m_MainMatrix.at(1, 3) ==   7 &&
             m_MainMatrix.at(2, 0) ==  3 && m_MainMatrix.at(2, 1) == 8 && m_MainMatrix.at(2, 2) ==  11  && m_MainMatrix.at(2, 3) ==   2 &&
             m_MainMatrix.at(3, 0) ==  1 && m_MainMatrix.at(3, 1) == 0 && m_MainMatrix.at(3, 2) ==   9  && m_MainMatrix.at(3, 3) ==   2 &&
             m_MainMatrix.at(4, 0) ==  4 && m_MainMatrix.at(4, 1) == 6 && m_MainMatrix.at(4, 2) ==   9  && m_MainMatrix.at(4, 3) == (-7),

             "The iterator objects don't work correctly, the matrix has not been sorted properly");

    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, (-2), 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 6, 9, 11}};

    std::sort(m_MainMatrix.getReverseNIterator(1, 2), m_MainMatrix.reverseNEnd());

    QVERIFY2(m_MainMatrix.at(0, 0) == 9 && m_MainMatrix.at(0, 1) == 3 && m_MainMatrix.at(0, 2) ==  -1  && m_MainMatrix.at(0, 3) == -7 &&
             m_MainMatrix.at(1, 0) == 8 && m_MainMatrix.at(1, 1) == 2 && m_MainMatrix.at(1, 2) == (-2) && m_MainMatrix.at(1, 3) ==  7 &&
             m_MainMatrix.at(2, 0) == 6 && m_MainMatrix.at(2, 1) == 1 && m_MainMatrix.at(2, 2) ==   2  && m_MainMatrix.at(2, 3) ==  2 &&
             m_MainMatrix.at(3, 0) == 5 && m_MainMatrix.at(3, 1) == 1 && m_MainMatrix.at(3, 2) ==   8  && m_MainMatrix.at(3, 3) ==  9 &&
             m_MainMatrix.at(4, 0) == 4 && m_MainMatrix.at(4, 1) == 0 && m_MainMatrix.at(4, 2) ==   9  && m_MainMatrix.at(4, 3) == 11,

             "The iterator objects don't work correctly, the matrix has not been sorted properly");
}

QTEST_APPLESS_MAIN(ReverseNIteratorTests)

#include "tst_reverseniteratortests.moc"
