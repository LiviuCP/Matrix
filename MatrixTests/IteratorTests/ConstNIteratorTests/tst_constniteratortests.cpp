#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixConstNIterator = Matrix<int>::ConstNIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixConstNIterator = Matrix<std::string>::ConstNIterator;

class ConstNIteratorTests : public QObject
{
    Q_OBJECT

public:
    ConstNIteratorTests();
    ~ConstNIteratorTests();

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

ConstNIteratorTests::ConstNIteratorTests()
{
}

ConstNIteratorTests::~ConstNIteratorTests()
{
}

void ConstNIteratorTests::testIteratorCreation()
{
    m_MainMatrix = {8, 9, -5};

    IntMatrixConstNIterator it{m_MainMatrix.constNBegin()};
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constNEnd();
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constNColumnBegin(0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constNColumnBegin(1);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constNColumnBegin(4);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 4 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constNColumnBegin(7);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constNColumnBegin(8);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constNColumnEnd(0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constNColumnEnd(1);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 2 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constNColumnEnd(4);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 5 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constNColumnEnd(7);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constNColumnEnd(8);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstNIterator(0, 0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstNIterator(1, 0);
    QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstNIterator(4, 5);
    QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 5 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstNIterator(6, 8);
    QVERIFY2(it.getCurrentRowNr() == 6 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstNIterator(7, 8);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstNIterator(0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstNIterator(1);
    QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstNIterator(44);
    QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 5 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstNIterator(70);
    QVERIFY2(it.getCurrentRowNr() == 6 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstNIterator(71);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // test iterator creation for empty matrix
    m_MainMatrix.clear();
    it = m_MainMatrix.constNBegin();
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constNEnd();
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // test empty iterator creation (not bound to any matrix) - an empty iterator should be valid for any empty matrix
    IntMatrixConstNIterator emptyIt;
    QVERIFY2(emptyIt.getCurrentRowNr() == -1 && emptyIt.getCurrentColumnNr() == -1 && emptyIt.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // additional test
    m_MainMatrix = {8, 9, -5};
    m_AuxIntMatrix = {8, 9, -5};
    it = m_MainMatrix.getConstNIterator(4, 5);
    QVERIFY(!it.isValidWithMatrix(m_AuxIntMatrix));
    m_AuxIntMatrix.clear();
    QVERIFY(!it.isValidWithMatrix(m_AuxIntMatrix));
    it = m_AuxIntMatrix.constNBegin();
    QVERIFY(!it.isValidWithMatrix(m_MainMatrix));
    it = m_AuxIntMatrix.constNEnd();
    QVERIFY(!it.isValidWithMatrix(m_MainMatrix));
    m_MainMatrix.clear();
    it = m_MainMatrix.constNBegin();
    QVERIFY(it.isValidWithMatrix(m_AuxIntMatrix)); // an iterator of an empty matrix is valid with any other empty matrix
    it = m_MainMatrix.constNEnd();
    QVERIFY(it.isValidWithMatrix(m_AuxIntMatrix));
}

void ConstNIteratorTests::testIteratorsAreEqual()
{

    m_MainMatrix = {8, 9, -5};

    // test different iterators for equality
    QVERIFY2((m_MainMatrix.constNBegin() == m_MainMatrix.getConstNIterator(0, 0) && !(m_MainMatrix.constNBegin() != m_MainMatrix.getConstNIterator(0, 0))), "The two iterators are not equal");
    QVERIFY2((m_MainMatrix.getConstNIterator(0) == m_MainMatrix.getConstNIterator(0, 0)) && !(m_MainMatrix.getConstNIterator(0) != m_MainMatrix.getConstNIterator(0, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getConstNIterator(1) == m_MainMatrix.getConstNIterator(1, 0)) && !(m_MainMatrix.getConstNIterator(1) != m_MainMatrix.getConstNIterator(1, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getConstNIterator(44) == m_MainMatrix.getConstNIterator(4, 5)) && !(m_MainMatrix.getConstNIterator(44) != m_MainMatrix.getConstNIterator(4, 5)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getConstNIterator(70) == m_MainMatrix.getConstNIterator(6, 8)) && !(m_MainMatrix.getConstNIterator(70) != m_MainMatrix.getConstNIterator(6, 8)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getConstNIterator(71) == m_MainMatrix.getConstNIterator(7, 8)) && !(m_MainMatrix.getConstNIterator(71) != m_MainMatrix.getConstNIterator(7, 8)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constNColumnBegin(0) == m_MainMatrix.getConstNIterator(0, 0)) && !(m_MainMatrix.constNColumnBegin(0) != m_MainMatrix.getConstNIterator(0, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constNColumnBegin(1) == m_MainMatrix.getConstNIterator(0, 1)) && !(m_MainMatrix.constNColumnBegin(1) != m_MainMatrix.getConstNIterator(0, 1)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constNColumnBegin(5) == m_MainMatrix.getConstNIterator(0, 5)) && !(m_MainMatrix.constNColumnBegin(5) != m_MainMatrix.getConstNIterator(0, 5)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constNColumnBegin(7) == m_MainMatrix.getConstNIterator(0, 7)) && !(m_MainMatrix.constNColumnBegin(7) != m_MainMatrix.getConstNIterator(0, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constNColumnBegin(8) == m_MainMatrix.getConstNIterator(0, 8)) && !(m_MainMatrix.constNColumnBegin(8) != m_MainMatrix.getConstNIterator(0, 8)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constNColumnEnd(0) == m_MainMatrix.getConstNIterator(0, 1)) && !(m_MainMatrix.constNColumnEnd(0) != m_MainMatrix.getConstNIterator(0, 1)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constNColumnEnd(1) == m_MainMatrix.getConstNIterator(0, 2)) && !(m_MainMatrix.constNColumnEnd(1) != m_MainMatrix.getConstNIterator(0, 2)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constNColumnEnd(5) == m_MainMatrix.getConstNIterator(0, 6)) && !(m_MainMatrix.constNColumnEnd(5) != m_MainMatrix.getConstNIterator(0, 6)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constNColumnEnd(7) == m_MainMatrix.getConstNIterator(0, 8)) && !(m_MainMatrix.constNColumnEnd(7) != m_MainMatrix.getConstNIterator(0, 8)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constNColumnEnd(8) == m_MainMatrix.constNEnd()) && !(m_MainMatrix.constNColumnEnd(8) != m_MainMatrix.constNEnd()), "The two iterators are NOT equal");

    // test iterator equality to itself
    IntMatrixConstNIterator it{m_MainMatrix.constNBegin()};
    QVERIFY2((it == it) && (it == m_MainMatrix.constNBegin()) && !(it != it) && !(it != m_MainMatrix.constNBegin()), "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getConstNIterator(1, 0);
    QVERIFY2((it == it) && (it == m_MainMatrix.getConstNIterator(1, 0)) && !(it != it) && !(it != m_MainMatrix.getConstNIterator(1, 0)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getConstNIterator(4, 5);
    QVERIFY2((it == it) && (it == m_MainMatrix.getConstNIterator(4, 5)) && !(it != it) && !(it != m_MainMatrix.getConstNIterator(4, 5)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getConstNIterator(6, 8);
    QVERIFY2((it == it) && (it == m_MainMatrix.getConstNIterator(6, 8)) && !(it != it) && !(it != m_MainMatrix.getConstNIterator(6, 8)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getConstNIterator(7, 8);
    QVERIFY2((it == it) && (it == m_MainMatrix.getConstNIterator(7, 8)) && !(it != it) && !(it != m_MainMatrix.getConstNIterator(7, 8)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.constNEnd();
    QVERIFY2((it == it) && (it == m_MainMatrix.constNEnd()) && !(it != it) && !(it != m_MainMatrix.constNEnd()),  "The iterator is NOT equal to itself and/or to source iterator");

    // test empty matrix iterator equality
    m_MainMatrix.clear();
    QVERIFY2((m_MainMatrix.constNBegin() == m_MainMatrix.constNEnd()) && !(m_MainMatrix.constNBegin() != m_MainMatrix.constNEnd()), "The two iterators are NOT equal");
}

void ConstNIteratorTests::testIteratorsAreNotEqual()
{
    m_MainMatrix = {8, 9, -5};

    QVERIFY2((m_MainMatrix.constNBegin() != m_MainMatrix.getConstNIterator(1, 0)) && !(m_MainMatrix.constNBegin() == m_MainMatrix.getConstNIterator(1, 0)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstNIterator(1, 0) != m_MainMatrix.getConstNIterator(2, 0)) && !(m_MainMatrix.getConstNIterator(1, 0) == m_MainMatrix.getConstNIterator(2, 0)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstNIterator(2, 0) != m_MainMatrix.getConstNIterator(4, 5)) && !(m_MainMatrix.getConstNIterator(2, 0) == m_MainMatrix.getConstNIterator(4, 5)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstNIterator(4, 5) != m_MainMatrix.getConstNIterator(6, 8)) && !(m_MainMatrix.getConstNIterator(4, 5) == m_MainMatrix.getConstNIterator(6, 8)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstNIterator(6, 8) != m_MainMatrix.getConstNIterator(7, 8)) && !(m_MainMatrix.getConstNIterator(6, 8) == m_MainMatrix.getConstNIterator(7, 8)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstNIterator(7, 8) != m_MainMatrix.constNEnd()) && !(m_MainMatrix.getConstNIterator(7, 8) == m_MainMatrix.constNEnd()), "The two iterators are NOT different");
}

void ConstNIteratorTests::testSmallerThanOperator()
{
    m_MainMatrix = {8, 9, -5};

    QVERIFY2((m_MainMatrix.constNBegin() < m_MainMatrix.getConstNIterator(1, 0)) && !(m_MainMatrix.constNBegin() >= m_MainMatrix.getConstNIterator(1, 0)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(1, 0) < m_MainMatrix.getConstNIterator(2, 0)) && !(m_MainMatrix.getConstNIterator(1, 0) >= m_MainMatrix.getConstNIterator(2, 0)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(2, 0) < m_MainMatrix.getConstNIterator(4, 5)) && !(m_MainMatrix.getConstNIterator(2, 0) >= m_MainMatrix.getConstNIterator(4, 5)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(4, 5) < m_MainMatrix.getConstNIterator(6, 8)) && !(m_MainMatrix.getConstNIterator(4, 5) >= m_MainMatrix.getConstNIterator(6, 8)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(6, 8) < m_MainMatrix.getConstNIterator(7, 8)) && !(m_MainMatrix.getConstNIterator(6, 8) >= m_MainMatrix.getConstNIterator(7, 8)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(7, 8) < m_MainMatrix.constNEnd()) && !(m_MainMatrix.getConstNIterator(7, 8) >= m_MainMatrix.constNEnd()), "The first iterator is NOT smaller than the second iterator");
}

void ConstNIteratorTests::testSmallerThanOrEqualToOperator()
{
    m_MainMatrix = {8, 9, -5};

    // test operator with different iterators
    QVERIFY2((m_MainMatrix.constNBegin() <= m_MainMatrix.constNBegin()) && !(m_MainMatrix.constNBegin() > m_MainMatrix.constNEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.constNBegin() <= m_MainMatrix.getConstNIterator(1, 0)) && !(m_MainMatrix.getConstNIterator(7, 8) > m_MainMatrix.constNEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(1, 0) <= m_MainMatrix.getConstNIterator(1, 0)) && !(m_MainMatrix.getConstNIterator(1, 0) > m_MainMatrix.getConstNIterator(1, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(1, 0) <= m_MainMatrix.getConstNIterator(2, 0)) && !(m_MainMatrix.getConstNIterator(1, 0) > m_MainMatrix.getConstNIterator(2, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(2, 0) <= m_MainMatrix.getConstNIterator(2, 0)) && !(m_MainMatrix.getConstNIterator(2, 0) > m_MainMatrix.getConstNIterator(2, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(2, 0) <= m_MainMatrix.getConstNIterator(4, 5)) && !(m_MainMatrix.getConstNIterator(2, 0) > m_MainMatrix.getConstNIterator(4, 5)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(4, 5) <= m_MainMatrix.getConstNIterator(4, 5)) && !(m_MainMatrix.getConstNIterator(4, 5) > m_MainMatrix.getConstNIterator(4, 5)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(4, 5) <= m_MainMatrix.getConstNIterator(6, 8)) && !(m_MainMatrix.getConstNIterator(4, 5) > m_MainMatrix.getConstNIterator(6, 8)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(6, 8) <= m_MainMatrix.getConstNIterator(6, 8)) && !(m_MainMatrix.getConstNIterator(6, 8) > m_MainMatrix.getConstNIterator(6, 8)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(6, 8) <= m_MainMatrix.getConstNIterator(7, 8)) && !(m_MainMatrix.getConstNIterator(6, 8) > m_MainMatrix.getConstNIterator(7, 8)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(7, 8) <= m_MainMatrix.getConstNIterator(7, 8)) && !(m_MainMatrix.getConstNIterator(7, 8) > m_MainMatrix.getConstNIterator(7, 8)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(7, 8) <= m_MainMatrix.constNEnd()) && !(m_MainMatrix.getConstNIterator(7, 8) > m_MainMatrix.constNEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.constNEnd() <= m_MainMatrix.constNEnd()) && !(m_MainMatrix.constNEnd() > m_MainMatrix.constNEnd()), "The first iterator is NOT smaller than or equal to the second iterator");

    // test if iterator is smaller than or equal to itself
    IntMatrixConstNIterator it{m_MainMatrix.constNBegin()};
    QVERIFY2((it <= it) && (it <= m_MainMatrix.constNBegin()) && !(it > it) && !(it > m_MainMatrix.constNBegin()),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstNIterator(1, 0);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getConstNIterator(1, 0)) && !(it > it) && !(it > m_MainMatrix.getConstNIterator(1, 0)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstNIterator(4, 5);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getConstNIterator(4, 5)) && !(it > it) && !(it > m_MainMatrix.getConstNIterator(4, 5)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstNIterator(6, 8);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getConstNIterator(6, 8)) && !(it > it) && !(it > m_MainMatrix.getConstNIterator(6, 8)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstNIterator(7, 8);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getConstNIterator(7, 8) && !(it > it) && !(it > m_MainMatrix.getConstNIterator(7, 8))),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.constNEnd();
    QVERIFY2((it <= it) && (it <= m_MainMatrix.constNEnd()) && !(it > it) && !(it > m_MainMatrix.constNEnd()),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");

    // test with empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.constNBegin() <= m_MainMatrix.constNEnd(), "The first iterator is NOT smaller than or equal to the second iterator");
}

void ConstNIteratorTests::testGreaterThanOperator()
{
    m_MainMatrix = {8, 9, -5};

    QVERIFY2((m_MainMatrix.constNEnd() > m_MainMatrix.getConstNIterator(7, 8)) && !(m_MainMatrix.constNEnd() <= m_MainMatrix.getConstNIterator(7, 8)), "TThe first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(7, 8) > m_MainMatrix.getConstNIterator(6, 8)) && !(m_MainMatrix.getConstNIterator(7, 8) <= m_MainMatrix.getConstNIterator(6, 8)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(6, 8) > m_MainMatrix.getConstNIterator(4, 5)) && !(m_MainMatrix.getConstNIterator(6, 8) <= m_MainMatrix.getConstNIterator(4, 5)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(4, 5) > m_MainMatrix.getConstNIterator(2, 0)) && !(m_MainMatrix.getConstNIterator(4, 5) <= m_MainMatrix.getConstNIterator(2, 0)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(2, 0) > m_MainMatrix.getConstNIterator(1, 0)) && !(m_MainMatrix.getConstNIterator(2, 0) <= m_MainMatrix.getConstNIterator(1, 0)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(1, 0) > m_MainMatrix.constNBegin()) && !(m_MainMatrix.getConstNIterator(1, 0) <= m_MainMatrix.constNBegin()), "The first iterator is NOT greater than the second iterator");
}

void ConstNIteratorTests::testGreaterThanOrEqualToOperator()
{
    m_MainMatrix = {8, 9, -5};

    // test operator with different iterators
    QVERIFY2((m_MainMatrix.constNEnd() >= m_MainMatrix.constNEnd()) && !(m_MainMatrix.constNEnd() < m_MainMatrix.constNEnd()), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.constNEnd() >= m_MainMatrix.getConstNIterator(7, 8)) && !(m_MainMatrix.constNEnd() < m_MainMatrix.getConstNIterator(7, 8)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(7, 8) >= m_MainMatrix.getConstNIterator(7, 8)) && !(m_MainMatrix.getConstNIterator(7, 8) < m_MainMatrix.getConstNIterator(7, 8)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(7, 8) >= m_MainMatrix.getConstNIterator(6, 8)) && !(m_MainMatrix.getConstNIterator(7, 8) < m_MainMatrix.getConstNIterator(6, 8)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(6, 8) >= m_MainMatrix.getConstNIterator(6, 8)) && !(m_MainMatrix.getConstNIterator(6, 8) < m_MainMatrix.getConstNIterator(6, 8)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(6, 8) >= m_MainMatrix.getConstNIterator(4, 5)) && !(m_MainMatrix.getConstNIterator(6, 8) < m_MainMatrix.getConstNIterator(4, 5)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(4, 5) >= m_MainMatrix.getConstNIterator(4, 5)) && !(m_MainMatrix.getConstNIterator(4, 5) < m_MainMatrix.getConstNIterator(4, 5)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(4, 5) >= m_MainMatrix.getConstNIterator(2, 0)) && !(m_MainMatrix.getConstNIterator(4, 5) < m_MainMatrix.getConstNIterator(2, 0)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(2, 0) >= m_MainMatrix.getConstNIterator(2, 0)) && !(m_MainMatrix.getConstNIterator(2, 0) < m_MainMatrix.getConstNIterator(2, 0)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(2, 0) >= m_MainMatrix.getConstNIterator(1, 0)) && !(m_MainMatrix.getConstNIterator(2, 0) < m_MainMatrix.getConstNIterator(1, 0)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(1, 0) >= m_MainMatrix.getConstNIterator(1, 0)) && !(m_MainMatrix.getConstNIterator(1, 0) < m_MainMatrix.getConstNIterator(1, 0)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstNIterator(1, 0) >= m_MainMatrix.constNBegin()) && !(m_MainMatrix.getConstNIterator(1, 0) < m_MainMatrix.constNBegin()), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.constNBegin() >= m_MainMatrix.constNBegin()) && !(m_MainMatrix.constNBegin() < m_MainMatrix.constNBegin()), "The first iterator is NOT greater than or equal to the second iterator");

    // test if iterator is greater than or equal to itself
    IntMatrixConstNIterator it{m_MainMatrix.constNEnd()};
    QVERIFY2((it >= it) && (it >= m_MainMatrix.constNEnd()) && !(it < it) && !(it < m_MainMatrix.constNEnd()),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstNIterator(7, 8);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getConstNIterator(7, 8)) && !(it < it) && !(it < m_MainMatrix.getConstNIterator(7, 8)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstNIterator(6, 8);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getConstNIterator(6, 8)) && !(it < it) && !(it < m_MainMatrix.getConstNIterator(6, 8)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstNIterator(4, 5);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getConstNIterator(4, 5)) && !(it < it) && !(it < m_MainMatrix.getConstNIterator(4, 5)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstNIterator(1, 0);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getConstNIterator(1, 0)) && !(it < it) && !(it < m_MainMatrix.getConstNIterator(1, 0)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.constNBegin();
    QVERIFY2((it >= it) && (it >= m_MainMatrix.constNBegin()) && !(it < it) && !(it < m_MainMatrix.constNBegin()),  "The iterator is NOT greater than or equal to itself and/or the source iterator");

    // test with empty matrix
    m_MainMatrix.clear();
    QVERIFY2((m_MainMatrix.constNBegin() >= m_MainMatrix.constNEnd()) && !(m_MainMatrix.constNBegin() < m_MainMatrix.constNEnd()), "The first iterator is NOT greater than or equal to the second iterator");
}

void ConstNIteratorTests::testIncrementOperators()
{
    m_MainMatrix = {8, 9, -5};

    // pre-increment
    IntMatrixConstNIterator it{m_MainMatrix.constNBegin()};
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 0), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(2, 0), "Incorrect pre-incrementation");
    it = m_MainMatrix.getConstNIterator(6, 4);
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 4), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(0, 5), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 5), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(2, 5), "Incorrect pre-incrementation");
    it = m_MainMatrix.getConstNIterator(4, 5);
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(5, 5), "Incorrect pre-incrementation");
    it = m_MainMatrix.getConstNIterator(6, 8);
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 8), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.constNEnd(), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.constNEnd(), "Incorrect pre-incrementation");

    // post-increment
    it = m_MainMatrix.constNBegin();
    it++;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 0), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(2, 0), "Incorrect post-incrementation");
    it = m_MainMatrix.getConstNIterator(6, 4);
    it++;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 4), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(0, 5), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 5), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(2, 5), "Incorrect post-incrementation");
    it = m_MainMatrix.getConstNIterator(4, 5);
    it++;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(5, 5), "Incorrect post-incrementation");
    it = m_MainMatrix.getConstNIterator(6, 8);
    it++;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 8), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.constNEnd(), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.constNEnd(), "Incorrect post-incrementation");

    // test a combination of "pre" and "post" behaviors
    IntMatrixConstNIterator srcIt{m_MainMatrix.getConstNIterator(4, 5)};
    IntMatrixConstNIterator destIt{++(++srcIt)};
    QVERIFY2(srcIt == m_MainMatrix.getConstNIterator(5, 5) && destIt == m_MainMatrix.getConstNIterator(6, 5), "Incorrect pre-pre-incrementation");
    srcIt = m_MainMatrix.getConstNIterator(4, 5);
    destIt = (srcIt++)++;
    QVERIFY2(srcIt == m_MainMatrix.getConstNIterator(5, 5) && destIt == m_MainMatrix.getConstNIterator(4, 5), "Incorrect post-post-incrementation");
    srcIt = m_MainMatrix.getConstNIterator(4, 5);
    destIt = (++srcIt)++;
    QVERIFY2(srcIt == m_MainMatrix.getConstNIterator(5, 5) && destIt == m_MainMatrix.getConstNIterator(5, 5), "Incorrect post-pre-incrementation");
    srcIt = m_MainMatrix.getConstNIterator(4, 5);
    destIt = ++(srcIt++);
    QVERIFY2(srcIt == m_MainMatrix.getConstNIterator(5, 5) && destIt == m_MainMatrix.getConstNIterator(5, 5), "Incorrect pre-post-incrementation");
}

void ConstNIteratorTests::testDecrementOperators()
{
    m_MainMatrix = {8, 9, -5};

    // pre-decrement
    IntMatrixConstNIterator it{m_MainMatrix.constNEnd()};
    --it;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 8), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 8), "Incorrect pre-decrementation");
    it = m_MainMatrix.getConstNIterator(5, 5);
    --it;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(4, 5), "Incorrect pre-decrementation");
    it = m_MainMatrix.getConstNIterator(2, 5);
    --it;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 5), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(0, 5), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 4), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 4), "Incorrect pre-decrementation");
    it = m_MainMatrix.getConstNIterator(2, 0);
    --it;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 0), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.constNBegin(), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.constNBegin(), "Incorrect pre-decrementation");


    // post-decrement
    it = m_MainMatrix.constNEnd();
    it--;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 8), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 8), "Incorrect post-decrementation");
    it = m_MainMatrix.getConstNIterator(5, 5);
    it--;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(4, 5), "Incorrect post-decrementation");
    it = m_MainMatrix.getConstNIterator(2, 5);
    it--;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 5), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(0, 5), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 4), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 4), "Incorrect post-decrementation");
    it = m_MainMatrix.getConstNIterator(2, 0);
    it--;
    QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 0), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.constNBegin(), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.constNBegin(), "Incorrect post-decrementation");

    // test a combination of "pre" and "post" behaviors
    IntMatrixConstNIterator srcIt{m_MainMatrix.getConstNIterator(6, 5)};
    IntMatrixConstNIterator destIt{--(--srcIt)};
    QVERIFY2(srcIt == m_MainMatrix.getConstNIterator(5, 5) && destIt == m_MainMatrix.getConstNIterator(4, 5), "Incorrect pre-pre-decrementation");
    srcIt = m_MainMatrix.getConstNIterator(6, 5);
    destIt = (srcIt--)--;
    QVERIFY2(srcIt == m_MainMatrix.getConstNIterator(5, 5) && destIt == m_MainMatrix.getConstNIterator(6, 5), "Incorrect post-post-decrementation");
    srcIt = m_MainMatrix.getConstNIterator(6, 5);
    destIt = (--srcIt)--;
    QVERIFY2(srcIt == m_MainMatrix.getConstNIterator(5, 5) && destIt == m_MainMatrix.getConstNIterator(5, 5), "Incorrect post-pre-decrementation");
    srcIt = m_MainMatrix.getConstNIterator(6, 5);
    destIt = --(srcIt--);
    QVERIFY2(srcIt == m_MainMatrix.getConstNIterator(5, 5) && destIt == m_MainMatrix.getConstNIterator(5, 5), "Incorrect pre-post-decrementation");
}

void ConstNIteratorTests::testOperatorPlus()
{
    m_MainMatrix = {8, 9, -5};

    // test for non-empty matrix
    IntMatrixConstNIterator it{m_MainMatrix.constNBegin()};
    QVERIFY2(it + (-3) == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.getConstNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 4 == m_MainMatrix.getConstNIterator(4, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 10 == m_MainMatrix.getConstNIterator(2, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 70 == m_MainMatrix.getConstNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 71 == m_MainMatrix.getConstNIterator(7, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 72 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 73 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 75 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstNIterator(1, 0);
    QVERIFY2(it + (-4) == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getConstNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.getConstNIterator(4, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 9 == m_MainMatrix.getConstNIterator(2, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 69 == m_MainMatrix.getConstNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 70 == m_MainMatrix.getConstNIterator(7, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 71 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 72 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 74 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstNIterator(4, 5);
    QVERIFY2(it + (-47) == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-45) == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-44) == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-43) == m_MainMatrix.getConstNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-6) == m_MainMatrix.getConstNIterator(6, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.getConstNIterator(2, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getConstNIterator(4, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.getConstNIterator(6, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 6 == m_MainMatrix.getConstNIterator(2, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 26 == m_MainMatrix.getConstNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 27 == m_MainMatrix.getConstNIterator(7, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 28 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 29 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 31 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstNIterator(6, 8);
    QVERIFY2(it + (-73) == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-70) == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-69) == m_MainMatrix.getConstNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-24) == m_MainMatrix.getConstNIterator(6, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-3) == m_MainMatrix.getConstNIterator(3, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getConstNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.getConstNIterator(7, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 5 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstNIterator(7, 8);
    QVERIFY2(it + (-74) == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-72) == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-70) == m_MainMatrix.getConstNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-25) == m_MainMatrix.getConstNIterator(6, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-4) == m_MainMatrix.getConstNIterator(3, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.getConstNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getConstNIterator(7, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 4 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.constNEnd();
    QVERIFY2(it + (-75) == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-73) == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-72) == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.getConstNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-26) == m_MainMatrix.getConstNIterator(6, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-5) == m_MainMatrix.getConstNIterator(3, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.getConstNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.getConstNIterator(7, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.constNBegin() + (-1) == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constNBegin() + 1 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constNEnd() + 0 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constNEnd() + 1 == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constNEnd() + (-1) == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");

    // test for empty iterators
    IntMatrixConstNIterator it1{};
    IntMatrixConstNIterator it2{};
    IntMatrixConstNIterator it3{};
    it1 = it3 + (-1);
    it2 = it3 + 1;
    QVERIFY2(it1 == it3, "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(it2 == it3, "Operator + does not work correctly, the resulting iterator is not the right one");
}

void ConstNIteratorTests::testOperatorMinus()
{
    m_MainMatrix = {8, 9, -5};

    // test for non-empty matrix
    IntMatrixConstNIterator it{m_MainMatrix.constNBegin()};
    QVERIFY2(it - 3 == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.constNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.getConstNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-4) == m_MainMatrix.getConstNIterator(4, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-10) == m_MainMatrix.getConstNIterator(2, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-70) == m_MainMatrix.getConstNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-71) == m_MainMatrix.getConstNIterator(7, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-72) == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-73) == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-75) == m_MainMatrix.constNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstNIterator(1, 0);
    QVERIFY2(it - 4 == m_MainMatrix.constNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.constNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.constNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getConstNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.getConstNIterator(4, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-9) == m_MainMatrix.getConstNIterator(2, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-69) == m_MainMatrix.getConstNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-70) == m_MainMatrix.getConstNIterator(7, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-71) == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-72) == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-74) == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstNIterator(4, 5);
    QVERIFY2(it - 47 == m_MainMatrix.constNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 45 == m_MainMatrix.constNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 44 == m_MainMatrix.constNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 43 == m_MainMatrix.getConstNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 6 == m_MainMatrix.getConstNIterator(6, 4), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.getConstNIterator(2, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getConstNIterator(4, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.getConstNIterator(6, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-6) == m_MainMatrix.getConstNIterator(2, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-26) == m_MainMatrix.getConstNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-27) == m_MainMatrix.getConstNIterator(7, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-28) == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-29) == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-31) == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstNIterator(6, 8);
    QVERIFY2(it - 73 == m_MainMatrix.constNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.constNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 70 == m_MainMatrix.constNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 69 == m_MainMatrix.getConstNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 24 == m_MainMatrix.getConstNIterator(6, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 3 == m_MainMatrix.getConstNIterator(3, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getConstNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.getConstNIterator(7, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-5) == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstNIterator(7, 8);
    QVERIFY2(it - 74 == m_MainMatrix.constNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 72 == m_MainMatrix.constNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.constNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 70 == m_MainMatrix.getConstNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 25 == m_MainMatrix.getConstNIterator(6, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 4 == m_MainMatrix.getConstNIterator(3, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.getConstNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getConstNIterator(7, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-4) == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.constNEnd();
    QVERIFY2(it - 75 == m_MainMatrix.constNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 73 == m_MainMatrix.constNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 72 == m_MainMatrix.constNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.getConstNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 26 == m_MainMatrix.getConstNIterator(6, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 5 == m_MainMatrix.getConstNIterator(3, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.getConstNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.getConstNIterator(7, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.constNBegin() - 1 == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constNBegin() - (-1) == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constNEnd() - 0 == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constNEnd() - (-1) == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constNEnd() - 1 == m_MainMatrix.constNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");

    // test for empty iterator
    IntMatrixConstNIterator it1{};
    IntMatrixConstNIterator it2{};
    IntMatrixConstNIterator it3{};
    it1 = it3 - 1;
    it2 = it3 - (-1);
    QVERIFY2(it1 == it3, "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(it2 == it3, "Operator - does not work correctly, the resulting iterator is not the right one");
}

void ConstNIteratorTests::testOperatorPlusEqual()
{
    IntMatrixConstNIterator it;

    // test for non-empty matrix
    m_MainMatrix = {8, 9, -5};

    IntMatrixConstNIterator it1{m_MainMatrix.constNBegin()};
    it = it1; it += (-3); QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 4; QVERIFY2(it == m_MainMatrix.getConstNIterator(4, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 10; QVERIFY2(it == m_MainMatrix.getConstNIterator(2, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 70; QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 71; QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 72; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 73; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 75; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getConstNIterator(1, 0);
    it = it1; it += (-4); QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-2); QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 3; QVERIFY2(it == m_MainMatrix.getConstNIterator(4, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 9; QVERIFY2(it == m_MainMatrix.getConstNIterator(2, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 69; QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 70; QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 71; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 72; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 74; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getConstNIterator(4, 5);
    it = it1; it += (-47); QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-45); QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-44); QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-43); QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-6); QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-2); QVERIFY2(it == m_MainMatrix.getConstNIterator(2, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.getConstNIterator(4, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 2; QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 6; QVERIFY2(it == m_MainMatrix.getConstNIterator(2, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 26; QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 27; QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 28; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 29; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 31; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getConstNIterator(6, 8);
    it = it1; it += (-73); QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-71); QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-70); QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-69); QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-24); QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-3); QVERIFY2(it == m_MainMatrix.getConstNIterator(3, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 2; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 3; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 5; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getConstNIterator(7, 8);
    it = it1; it += (-74); QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-72); QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-71); QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-70); QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-25); QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-4); QVERIFY2(it == m_MainMatrix.getConstNIterator(3, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 2; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 4; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.constNEnd();
    it = it1; it += (-75); QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-73); QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-72); QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-71); QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-26); QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-5); QVERIFY2(it == m_MainMatrix.getConstNIterator(3, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-2); QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 3; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    it1 = m_MainMatrix.constNBegin();
    it1 = m_MainMatrix.constNEnd();
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator += does not work correctly, the updated iterator is not the right one");

    // test for empty iterator
    IntMatrixConstNIterator it2{};
    IntMatrixConstNIterator it3{};
    IntMatrixConstNIterator it4{};
    it3 += (-1); QVERIFY2(it3 == it2, "Operator += does not work correctly, the resulting updated is not the right one");
    it4 += 1; QVERIFY2(it4 == it2, "Operator += does not work correctly, the resulting updated is not the right one");
}

void ConstNIteratorTests::testOperatorMinusEqual()
{
    IntMatrixConstNIterator it;

    // test for non-empty matrix
    m_MainMatrix = {8, 9, -5};

    IntMatrixConstNIterator it1{m_MainMatrix.constNBegin()};
    it = it1; it -= 3; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-4); QVERIFY2(it == m_MainMatrix.getConstNIterator(4, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-10); QVERIFY2(it == m_MainMatrix.getConstNIterator(2, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-70); QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-71); QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-72); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-73); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-75); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getConstNIterator(1, 0);
    it = it1; it -= 4; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 2; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-3); QVERIFY2(it == m_MainMatrix.getConstNIterator(4, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-9); QVERIFY2(it == m_MainMatrix.getConstNIterator(2, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-69); QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-70); QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-71); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-72); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-74); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getConstNIterator(4, 5);
    it = it1; it -= 47; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 45; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 44; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 43; QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 6; QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 2; QVERIFY2(it == m_MainMatrix.getConstNIterator(2, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.getConstNIterator(4, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-2); QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-6); QVERIFY2(it == m_MainMatrix.getConstNIterator(2, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-26); QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-27); QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-28); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-29); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-31); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getConstNIterator(6, 8);
    it = it1; it -= 73; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 71; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 70; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 69; QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 24; QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 3; QVERIFY2(it == m_MainMatrix.getConstNIterator(3, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-2); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-3); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-5); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getConstNIterator(7, 8);
    it = it1; it -= 74; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 72; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 71; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 70; QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 25; QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 4; QVERIFY2(it == m_MainMatrix.getConstNIterator(3, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-2); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-4); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.constNEnd();
    it = it1; it -= 75; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 73; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 72; QVERIFY2(it == m_MainMatrix.constNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 71; QVERIFY2(it == m_MainMatrix.getConstNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 26; QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 5; QVERIFY2(it == m_MainMatrix.getConstNIterator(3, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 2; QVERIFY2(it == m_MainMatrix.getConstNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.getConstNIterator(7, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-3); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    it1 = m_MainMatrix.constNBegin();
    it1 = m_MainMatrix.constNEnd();
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.constNEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");

    // test for empty iterator
    IntMatrixConstNIterator it2{};
    IntMatrixConstNIterator it3{};
    IntMatrixConstNIterator it4{};
    it3 -= 1; QVERIFY2(it3 == it2, "Operator -= does not work correctly, the updated iterator is not the right one");
    it4 -= (-1); QVERIFY2(it4 == it2, "Operator -= does not work correctly, the updated iterator is not the right one");
}

void ConstNIteratorTests::testDifferenceOperator()
{
    // test for non-empty matrix
    m_MainMatrix = {8, 9, -5};

    QVERIFY2(m_MainMatrix.constNEnd() - m_MainMatrix.constNEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constNEnd() - m_MainMatrix.getConstNIterator(7, 8) == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constNEnd() - m_MainMatrix.getConstNIterator(6, 8) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constNEnd() - m_MainMatrix.getConstNIterator(4, 5) == 28, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constNEnd() - m_MainMatrix.getConstNIterator(1, 0) == 71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constNEnd() - m_MainMatrix.constNBegin() == 72, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getConstNIterator(7, 8) - m_MainMatrix.constNEnd() == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(7, 8) - m_MainMatrix.getConstNIterator(7, 8) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(7, 8) - m_MainMatrix.getConstNIterator(6, 8) == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(7, 8) - m_MainMatrix.getConstNIterator(4, 5) == 27, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(7, 8) - m_MainMatrix.getConstNIterator(1, 0) == 70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(7, 8) - m_MainMatrix.constNBegin() == 71, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getConstNIterator(6, 8) - m_MainMatrix.constNEnd() == -2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(6, 8) - m_MainMatrix.getConstNIterator(7, 8) == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(6, 8) - m_MainMatrix.getConstNIterator(6, 8) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(6, 8) - m_MainMatrix.getConstNIterator(4, 5) == 26, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(6, 8) - m_MainMatrix.getConstNIterator(1, 0) == 69, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(6, 8) - m_MainMatrix.constNBegin() == 70, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getConstNIterator(4, 5) - m_MainMatrix.constNEnd() == -28, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(4, 5) - m_MainMatrix.getConstNIterator(7, 8) == -27, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(4, 5) - m_MainMatrix.getConstNIterator(6, 8) == -26, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(4, 5) - m_MainMatrix.getConstNIterator(4, 5) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(4, 5) - m_MainMatrix.getConstNIterator(1, 0) == 43, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(4, 5) - m_MainMatrix.constNBegin() == 44, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getConstNIterator(1, 0) - m_MainMatrix.constNEnd() == -71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(1, 0) - m_MainMatrix.getConstNIterator(7, 8) == -70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(1, 0) - m_MainMatrix.getConstNIterator(6, 8) == -69, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(1, 0) - m_MainMatrix.getConstNIterator(4, 5) == -43, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(1, 0) - m_MainMatrix.getConstNIterator(1, 0) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(1, 0) - m_MainMatrix.constNBegin() == 1, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.constNBegin() - m_MainMatrix.constNEnd() == -72, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constNBegin() - m_MainMatrix.getConstNIterator(7, 8) == -71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constNBegin() - m_MainMatrix.getConstNIterator(6, 8) == -70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constNBegin() - m_MainMatrix.getConstNIterator(4, 5) == -44, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constNBegin() - m_MainMatrix.getConstNIterator(1, 0) == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constNBegin() - m_MainMatrix.constNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");

    // additional tests with "random" elements from same column/different columns
    QVERIFY2(m_MainMatrix.getConstNIterator(4, 5) - m_MainMatrix.getConstNIterator(2, 7) == -14, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(2, 7) - m_MainMatrix.getConstNIterator(4, 5) == 14, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(4, 5) - m_MainMatrix.getConstNIterator(2, 5) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstNIterator(2, 5) - m_MainMatrix.getConstNIterator(4, 5) == -2, "The difference operator does not work correctly, difference between iterators is wrong");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.constNEnd() - m_MainMatrix.constNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constNBegin() - m_MainMatrix.constNEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constNBegin() - m_MainMatrix.constNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constNEnd() - m_MainMatrix.constNEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");

    // test for empty iterator
    IntMatrixConstNIterator it1{};
    IntMatrixConstNIterator it2{};
    QVERIFY2(it1 - it2 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(it2 - it1 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(it1 - it1 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
}

void ConstNIteratorTests::testDereferenceAsteriskOperator()
{
    // test reading element
    m_MainMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};
    QVERIFY2(*m_MainMatrix.constNBegin() == 1, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getConstNIterator(1, 0) == -2, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getConstNIterator(2, 1) == -6, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getConstNIterator(1, 3) == 11, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getConstNIterator(2, 3) == -12, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");

    // additional tests
    m_MainMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    IntMatrixConstNIterator readIter{m_MainMatrix.constNBegin()};
    m_MainMatrix.at(2, 0) = 10;
    readIter += 2;
    QVERIFY2(*readIter == 10, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
}

void ConstNIteratorTests::testDereferenceArrowOperator()
{
    // test reading element
    m_AuxStringMatrix = {3, 4, {"abc", "jihgfedcba", "abcde", "", "ba", "a", "ihgfedcba", "abcdefghijk", "abcd", "gfedcba", "abcdefgh", "fedcba"}};
    QVERIFY2(m_AuxStringMatrix.constNBegin()->size() == 3, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getConstNIterator(1, 0)->size() == 2, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getConstNIterator(2, 1)->size() == 7, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getConstNIterator(1, 3)->size() == 11, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getConstNIterator(2, 3)->size() == 6, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");

    // additional tests
    m_AuxStringMatrix = {3, 2, {"abc", "jkl", "defed", "mno", "ghi", "pqr"}};
    StringMatrixConstNIterator it{m_AuxStringMatrix.constNBegin()};
    m_AuxStringMatrix.at(2, 0) = "abcdefghi";
    it += 2;
    QVERIFY2(it->size() == 9, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
}

void ConstNIteratorTests::testDereferenceSquareBracketsOperator()
{
    // test reading element
    m_MainMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};

    IntMatrixConstNIterator it{m_MainMatrix.constNBegin()};
    QVERIFY2(it[0] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[1] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[5] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[10] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[11] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getConstNIterator(1, 0);
    QVERIFY2(it[-1] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[4] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[9] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[10] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getConstNIterator(2, 1);
    QVERIFY2(it[-5] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-4] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[5] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[6] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getConstNIterator(1, 3);
    QVERIFY2(it[-10] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-9] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-5] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[1] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getConstNIterator(2, 3);
    QVERIFY2(it[-11] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-10] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-6] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-1] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");
}

void ConstNIteratorTests::testStdCount()
{
    using namespace std;

    m_MainMatrix = {5, 4, {-1, 5, 2, 7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8 }};

    int matchCount{count(m_MainMatrix.constNBegin(), m_MainMatrix.constNEnd(), 2)};
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constNBegin(), m_MainMatrix.constNEnd(), -5);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstNIterator(2, 0), m_MainMatrix.getConstNIterator(4, 1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstNIterator(2, 0), m_MainMatrix.getConstNIterator(0, 2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstNIterator(3, 0), m_MainMatrix.getConstNIterator(4, 1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstNIterator(3, 0), m_MainMatrix.getConstNIterator(0, 2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constNBegin(), m_MainMatrix.getConstNIterator(3, 2), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstNIterator(3, 2), m_MainMatrix.constNEnd(), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constNBegin(), m_MainMatrix.getConstNIterator(2, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstNIterator(2, 2), m_MainMatrix.constNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstNIterator(2), m_MainMatrix.getConstNIterator(9), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstNIterator(2), m_MainMatrix.getConstNIterator(10), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstNIterator(3), m_MainMatrix.getConstNIterator(9), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstNIterator(3), m_MainMatrix.getConstNIterator(10), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constNBegin(), m_MainMatrix.getConstNIterator(13), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstNIterator(13), m_MainMatrix.constNEnd(), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constNBegin(), m_MainMatrix.getConstNIterator(12), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstNIterator(12), m_MainMatrix.constNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constNColumnBegin(1), m_MainMatrix.constNColumnEnd(1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constNColumnBegin(1), m_MainMatrix.constNColumnEnd(2), 8);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constNColumnBegin(2), m_MainMatrix.constNColumnEnd(2), 9);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constNColumnBegin(2), m_MainMatrix.constNColumnEnd(3), 9);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constNBegin(), m_MainMatrix.constNColumnBegin(1), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constNColumnBegin(1), m_MainMatrix.constNEnd(), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constNBegin(), m_MainMatrix.constNColumnEnd(1), 1);
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constNColumnEnd(1), m_MainMatrix.constNEnd(), 1);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
}

void ConstNIteratorTests::testStdFind()
{
    using namespace std;

    // test finding elements in specific ranges within unempty matrix
    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 6, 9, 11}};

    QVERIFY2(find(m_MainMatrix.constNBegin(), m_MainMatrix.constNEnd(), 5) != m_MainMatrix.constNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNBegin(), m_MainMatrix.constNEnd(), 10) == m_MainMatrix.constNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNColumnBegin(1), m_MainMatrix.constNColumnEnd(1), 5) != m_MainMatrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNColumnBegin(1), m_MainMatrix.constNColumnEnd(1), 6) != m_MainMatrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNColumnBegin(1), m_MainMatrix.constNColumnEnd(1), 8) != m_MainMatrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNColumnBegin(1), m_MainMatrix.constNColumnEnd(1), -1) == m_MainMatrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNColumnBegin(1), m_MainMatrix.constNColumnEnd(1), -2) == m_MainMatrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNColumnBegin(1), m_MainMatrix.constNColumnEnd(1), 10) == m_MainMatrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNColumnBegin(1), m_MainMatrix.constNEnd(), 5) != m_MainMatrix.constNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNColumnBegin(1), m_MainMatrix.constNEnd(), 11) != m_MainMatrix.constNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNColumnBegin(1), m_MainMatrix.constNEnd(), -2) != m_MainMatrix.constNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNColumnBegin(1), m_MainMatrix.constNEnd(), -1) == m_MainMatrix.constNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNColumnBegin(1), m_MainMatrix.constNEnd(), 10) == m_MainMatrix.constNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNBegin(), m_MainMatrix.constNColumnEnd(1), -1) != m_MainMatrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNBegin(), m_MainMatrix.constNColumnEnd(1), 6) != m_MainMatrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNBegin(), m_MainMatrix.constNColumnEnd(1), 8) != m_MainMatrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNBegin(), m_MainMatrix.constNColumnEnd(1), -2) == m_MainMatrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNBegin(), m_MainMatrix.constNColumnEnd(1), 10) == m_MainMatrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstNIterator(3, 1), m_MainMatrix.getConstNIterator(1, 3), 0) != m_MainMatrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstNIterator(3, 1), m_MainMatrix.getConstNIterator(1, 3), -7) != m_MainMatrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstNIterator(3, 1), m_MainMatrix.getConstNIterator(1, 3), -2) != m_MainMatrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstNIterator(3, 1), m_MainMatrix.getConstNIterator(1, 3), -1) == m_MainMatrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstNIterator(3, 1), m_MainMatrix.getConstNIterator(1, 3), 11) == m_MainMatrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstNIterator(3, 1), m_MainMatrix.getConstNIterator(1, 3), 10) == m_MainMatrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstNIterator(3, 1), m_MainMatrix.constNEnd(), 0) != m_MainMatrix.constNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstNIterator(3, 1), m_MainMatrix.constNEnd(), 11) != m_MainMatrix.constNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstNIterator(3, 1), m_MainMatrix.constNEnd(), -2) != m_MainMatrix.constNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstNIterator(3, 1), m_MainMatrix.constNEnd(), -1) == m_MainMatrix.constNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstNIterator(3, 1), m_MainMatrix.constNEnd(), 10) == m_MainMatrix.constNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNBegin(), m_MainMatrix.getConstNIterator(1, 3), -1) != m_MainMatrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNBegin(), m_MainMatrix.getConstNIterator(1, 3), -7) != m_MainMatrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNBegin(), m_MainMatrix.getConstNIterator(1, 3), -2) != m_MainMatrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNBegin(), m_MainMatrix.getConstNIterator(1, 3), 11) == m_MainMatrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constNBegin(), m_MainMatrix.getConstNIterator(1, 3), 10) == m_MainMatrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

    // other tests
    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};
    IntMatrixConstNIterator it{find(m_MainMatrix.constNBegin(), m_MainMatrix.constNEnd(), 4)};
    ++it;
    QVERIFY2(*it == 5, "The iterator doesn't work correctly with std::find, incorrect next element returned");

    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};
    QVERIFY2(find(m_MainMatrix.constNBegin(), m_MainMatrix.constNEnd(), 10) == m_MainMatrix.constNEnd(), "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix");

    it = m_MainMatrix.constNBegin();
    while(it != m_MainMatrix.constNEnd())
    {
        it = find(it, m_MainMatrix.constNEnd(), 9);

        if (it != m_MainMatrix.constNEnd())
        {
            m_MainMatrix.at(it.getCurrentRowNr(), it.getCurrentColumnNr()) = 10;
        }
    }
    int expectedNumber{std::count(m_MainMatrix.constNBegin(), m_MainMatrix.constNEnd(), 10)};
    QVERIFY2(expectedNumber == 3, "The iterator doesn't work properly with std::find, element values haven't been correctly replaced");
}

QTEST_APPLESS_MAIN(ConstNIteratorTests)

#include "tst_constniteratortests.moc"
