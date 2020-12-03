#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixConstReverseNIterator = Matrix<int>::ConstReverseNIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixConstReverseNIterator = Matrix<std::string>::ConstReverseNIterator;

class ConstReverseNIteratorTests : public QObject
{
    Q_OBJECT

public:
    ConstReverseNIteratorTests();
    ~ConstReverseNIteratorTests();

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

ConstReverseNIteratorTests::ConstReverseNIteratorTests()
{
}

ConstReverseNIteratorTests::~ConstReverseNIteratorTests()
{
}

void ConstReverseNIteratorTests::testIteratorCreation()
{
    m_MainMatrix = {8, 9, -5};

    IntMatrixConstReverseNIterator it{m_MainMatrix.constReverseNBegin()};
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseNEnd();
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseNColumnBegin(0);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseNColumnBegin(1);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseNColumnBegin(4);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 4 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseNColumnBegin(7);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseNColumnBegin(8);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseNColumnEnd(0);
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseNColumnEnd(1);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseNColumnEnd(4);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 3 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseNColumnEnd(7);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 6 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseNColumnEnd(8);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseNIterator(0, 0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseNIterator(1, 0);
    QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseNIterator(4, 5);
    QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 5 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseNIterator(6, 8);
    QVERIFY2(it.getCurrentRowNr() == 6 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseNIterator(7, 8);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseNIterator(0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseNIterator(1);
    QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseNIterator(44);
    QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 5 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseNIterator(70);
    QVERIFY2(it.getCurrentRowNr() == 6 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getConstReverseNIterator(71);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // test iterator creation for empty matrix
    m_MainMatrix.clear();
    it = m_MainMatrix.constReverseNBegin();
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.constReverseNEnd();
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // test empty iterator creation (not bound to any matrix) - an empty iterator should be valid for any empty matrix
    IntMatrixConstReverseNIterator emptyIt;
    QVERIFY2(emptyIt.getCurrentRowNr() == -1 && emptyIt.getCurrentColumnNr() == -1 && emptyIt.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // additional test
    m_MainMatrix = {8, 9, -5};
    m_AuxIntMatrix = {8, 9, -5};
    it = m_MainMatrix.getConstReverseNIterator(4, 5);
    QVERIFY(!it.isValidWithMatrix(m_AuxIntMatrix));
    m_AuxIntMatrix.clear();
    QVERIFY(!it.isValidWithMatrix(m_AuxIntMatrix));
    it = m_AuxIntMatrix.constReverseNBegin();
    QVERIFY(!it.isValidWithMatrix(m_MainMatrix));
    it = m_AuxIntMatrix.constReverseNEnd();
    QVERIFY(!it.isValidWithMatrix(m_MainMatrix));
    m_MainMatrix.clear();
    it = m_MainMatrix.constReverseNBegin();
    QVERIFY(it.isValidWithMatrix(m_AuxIntMatrix)); // an iterator of an empty matrix is valid with any other empty matrix
    it = m_MainMatrix.constReverseNEnd();
    QVERIFY(it.isValidWithMatrix(m_AuxIntMatrix));
}

void ConstReverseNIteratorTests::testIteratorsAreEqual()
{

    m_MainMatrix = {8, 9, -5};

    // test different iterators for equality
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(0) == m_MainMatrix.getConstReverseNIterator(0, 0)) && !(m_MainMatrix.getConstReverseNIterator(0) != m_MainMatrix.getConstReverseNIterator(0, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(1) == m_MainMatrix.getConstReverseNIterator(1, 0)) && !(m_MainMatrix.getConstReverseNIterator(1) != m_MainMatrix.getConstReverseNIterator(1, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(44) == m_MainMatrix.getConstReverseNIterator(4, 5)) && !(m_MainMatrix.getConstReverseNIterator(44) != m_MainMatrix.getConstReverseNIterator(4, 5)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(70) == m_MainMatrix.getConstReverseNIterator(6, 8)) && !(m_MainMatrix.getConstReverseNIterator(70) != m_MainMatrix.getConstReverseNIterator(6, 8)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(71) == m_MainMatrix.getConstReverseNIterator(7, 8)) && !(m_MainMatrix.getConstReverseNIterator(71) != m_MainMatrix.getConstReverseNIterator(7, 8)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseNBegin() == m_MainMatrix.getConstReverseNIterator(7, 8) && !(m_MainMatrix.constReverseNBegin() != m_MainMatrix.getConstReverseNIterator(7, 8))), "The two iterators are not equal");
    QVERIFY2((m_MainMatrix.constReverseNColumnBegin(0) == m_MainMatrix.getConstReverseNIterator(7, 0)) && !(m_MainMatrix.constReverseNColumnBegin(0) != m_MainMatrix.getConstReverseNIterator(7, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseNColumnBegin(1) == m_MainMatrix.getConstReverseNIterator(7, 1)) && !(m_MainMatrix.constReverseNColumnBegin(1) != m_MainMatrix.getConstReverseNIterator(7, 1)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseNColumnBegin(5) == m_MainMatrix.getConstReverseNIterator(7, 5)) && !(m_MainMatrix.constReverseNColumnBegin(5) != m_MainMatrix.getConstReverseNIterator(7, 5)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseNColumnBegin(7) == m_MainMatrix.getConstReverseNIterator(7, 7)) && !(m_MainMatrix.constReverseNColumnBegin(7) != m_MainMatrix.getConstReverseNIterator(7, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseNColumnBegin(8) == m_MainMatrix.getConstReverseNIterator(7, 8)) && !(m_MainMatrix.constReverseNColumnBegin(8) != m_MainMatrix.getConstReverseNIterator(7, 8)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseNColumnEnd(0) == m_MainMatrix.constReverseNEnd()) && !(m_MainMatrix.constReverseNColumnEnd(0) != m_MainMatrix.constReverseNEnd()), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseNColumnEnd(1) == m_MainMatrix.getConstReverseNIterator(7, 0)) && !(m_MainMatrix.constReverseNColumnEnd(1) != m_MainMatrix.getConstReverseNIterator(7, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseNColumnEnd(5) == m_MainMatrix.getConstReverseNIterator(7, 4)) && !(m_MainMatrix.constReverseNColumnEnd(5) != m_MainMatrix.getConstReverseNIterator(7, 4)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseNColumnEnd(7) == m_MainMatrix.getConstReverseNIterator(7, 6)) && !(m_MainMatrix.constReverseNColumnEnd(7) != m_MainMatrix.getConstReverseNIterator(7, 6)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.constReverseNColumnEnd(8) == m_MainMatrix.getConstReverseNIterator(7, 7)) && !(m_MainMatrix.constReverseNColumnEnd(8) != m_MainMatrix.getConstReverseNIterator(7, 7)), "The two iterators are NOT equal");

    // test iterator equality to itself
    IntMatrixConstReverseNIterator it{m_MainMatrix.constReverseNEnd()};
    QVERIFY2((it == it) && (it == m_MainMatrix.constReverseNEnd()) && !(it != it) && !(it != m_MainMatrix.constReverseNEnd()), "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getConstReverseNIterator(0, 0);
    QVERIFY2((it == it) && (it == m_MainMatrix.getConstReverseNIterator(0, 0)) && !(it != it) && !(it != m_MainMatrix.getConstReverseNIterator(0, 0)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getConstReverseNIterator(1, 0);
    QVERIFY2((it == it) && (it == m_MainMatrix.getConstReverseNIterator(1, 0)) && !(it != it) && !(it != m_MainMatrix.getConstReverseNIterator(1, 0)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getConstReverseNIterator(4, 5);
    QVERIFY2((it == it) && (it == m_MainMatrix.getConstReverseNIterator(4, 5)) && !(it != it) && !(it != m_MainMatrix.getConstReverseNIterator(4, 5)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getConstReverseNIterator(6, 8);
    QVERIFY2((it == it) && (it == m_MainMatrix.getConstReverseNIterator(6, 8)) && !(it != it) && !(it != m_MainMatrix.getConstReverseNIterator(6, 8)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.constReverseNBegin();
    QVERIFY2((it == it) && (it == m_MainMatrix.constReverseNBegin()) && !(it != it) && !(it != m_MainMatrix.constReverseNBegin()),  "The iterator is NOT equal to itself and/or to source iterator");

    // test empty matrix iterator equality
    m_MainMatrix.clear();
    QVERIFY2((m_MainMatrix.constReverseNBegin() == m_MainMatrix.constReverseNEnd()) && !(m_MainMatrix.constReverseNBegin() != m_MainMatrix.constReverseNEnd()), "The two iterators are NOT equal");
}

void ConstReverseNIteratorTests::testIteratorsAreNotEqual()
{
    m_MainMatrix = {8, 9, -5};

    QVERIFY2((m_MainMatrix.constReverseNEnd() != m_MainMatrix.getConstReverseNIterator(0, 0)) && !(m_MainMatrix.constReverseNEnd() == m_MainMatrix.getConstReverseNIterator(0, 0)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(0, 0) != m_MainMatrix.getConstReverseNIterator(1, 0)) && !(m_MainMatrix.getConstReverseNIterator(0, 0) == m_MainMatrix.getConstReverseNIterator(1, 0)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(1, 0) != m_MainMatrix.getConstReverseNIterator(2, 0)) && !(m_MainMatrix.getConstReverseNIterator(1, 0) == m_MainMatrix.getConstReverseNIterator(2, 0)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(2, 0) != m_MainMatrix.getConstReverseNIterator(4, 5)) && !(m_MainMatrix.getConstReverseNIterator(2, 0) == m_MainMatrix.getConstReverseNIterator(4, 5)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(4, 5) != m_MainMatrix.getConstReverseNIterator(6, 8)) && !(m_MainMatrix.getConstReverseNIterator(4, 5) == m_MainMatrix.getConstReverseNIterator(6, 8)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(6, 8) != m_MainMatrix.constReverseNBegin()) && !(m_MainMatrix.getConstReverseNIterator(6, 8) == m_MainMatrix.constReverseNBegin()), "The two iterators are NOT different");
}

void ConstReverseNIteratorTests::testSmallerThanOperator()
{
    m_MainMatrix = {8, 9, -5};

    QVERIFY2((m_MainMatrix.constReverseNBegin() < m_MainMatrix.getConstReverseNIterator(6, 8)) && !(m_MainMatrix.constReverseNBegin() >= m_MainMatrix.getConstReverseNIterator(6, 8)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(6, 8) < m_MainMatrix.getConstReverseNIterator(4, 5)) && !(m_MainMatrix.getConstReverseNIterator(6, 8) >= m_MainMatrix.getConstReverseNIterator(4, 5)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(4, 5) < m_MainMatrix.getConstReverseNIterator(2, 0)) && !(m_MainMatrix.getConstReverseNIterator(4, 5) >= m_MainMatrix.getConstReverseNIterator(2, 0)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(2, 0) < m_MainMatrix.getConstReverseNIterator(1, 0)) && !(m_MainMatrix.getConstReverseNIterator(2, 0) >= m_MainMatrix.getConstReverseNIterator(1, 0)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(1, 0) < m_MainMatrix.getConstReverseNIterator(0, 0)) && !(m_MainMatrix.getConstReverseNIterator(1, 0) >= m_MainMatrix.getConstReverseNIterator(0, 0)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(0, 0) < m_MainMatrix.constReverseNEnd()) && !(m_MainMatrix.getConstReverseNIterator(0, 0) >= m_MainMatrix.constReverseNEnd()), "The first iterator is NOT smaller than the second iterator");
}

void ConstReverseNIteratorTests::testSmallerThanOrEqualToOperator()
{
    m_MainMatrix = {8, 9, -5};

    // test operator with different iterators
    QVERIFY2((m_MainMatrix.constReverseNBegin() <= m_MainMatrix.constReverseNBegin()) && !(m_MainMatrix.constReverseNBegin() > m_MainMatrix.constReverseNBegin()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.constReverseNBegin() <= m_MainMatrix.getConstReverseNIterator(6, 8)) && !(m_MainMatrix.constReverseNBegin() > m_MainMatrix.getConstReverseNIterator(6, 8)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(6, 8) <= m_MainMatrix.getConstReverseNIterator(6, 8)) && !(m_MainMatrix.getConstReverseNIterator(6, 8) > m_MainMatrix.getConstReverseNIterator(6, 8)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(6, 8) <= m_MainMatrix.getConstReverseNIterator(4, 5)) && !(m_MainMatrix.getConstReverseNIterator(6, 8) > m_MainMatrix.getConstReverseNIterator(4, 5)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(4, 5) <= m_MainMatrix.getConstReverseNIterator(4, 5)) && !(m_MainMatrix.getConstReverseNIterator(4, 5) > m_MainMatrix.getConstReverseNIterator(4, 5)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(4, 5) <= m_MainMatrix.getConstReverseNIterator(2, 0)) && !(m_MainMatrix.getConstReverseNIterator(4, 5) > m_MainMatrix.getConstReverseNIterator(2, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(2, 0) <= m_MainMatrix.getConstReverseNIterator(2, 0)) && !(m_MainMatrix.getConstReverseNIterator(2, 0) > m_MainMatrix.getConstReverseNIterator(2, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(2, 0) <= m_MainMatrix.getConstReverseNIterator(1, 0)) && !(m_MainMatrix.getConstReverseNIterator(2, 0) > m_MainMatrix.getConstReverseNIterator(1, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(1, 0) <= m_MainMatrix.getConstReverseNIterator(1, 0)) && !(m_MainMatrix.getConstReverseNIterator(1, 0) > m_MainMatrix.getConstReverseNIterator(1, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(1, 0) <= m_MainMatrix.getConstReverseNIterator(0, 0)) && !(m_MainMatrix.getConstReverseNIterator(1, 0) > m_MainMatrix.getConstReverseNIterator(0, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(0, 0) <= m_MainMatrix.getConstReverseNIterator(0, 0)) && !(m_MainMatrix.getConstReverseNIterator(0, 0) > m_MainMatrix.getConstReverseNIterator(0, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(0, 0) <= m_MainMatrix.constReverseNEnd()) && !(m_MainMatrix.getConstReverseNIterator(0, 0) > m_MainMatrix.constReverseNEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.constReverseNEnd() <= m_MainMatrix.constReverseNEnd()) && !(m_MainMatrix.constReverseNEnd() > m_MainMatrix.constReverseNEnd()), "The first iterator is NOT smaller than or equal to the second iterator");

    // test if iterator is smaller than or equal to itself
    IntMatrixConstReverseNIterator it{m_MainMatrix.constReverseNBegin()};
    QVERIFY2((it <= it) && (it <= m_MainMatrix.constReverseNBegin()) && !(it > it) && !(it > m_MainMatrix.constReverseNBegin()),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstReverseNIterator(1, 0);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getConstReverseNIterator(1, 0)) && !(it > it) && !(it > m_MainMatrix.getConstReverseNIterator(1, 0)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstReverseNIterator(4, 5);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getConstReverseNIterator(4, 5)) && !(it > it) && !(it > m_MainMatrix.getConstReverseNIterator(4, 5)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstReverseNIterator(6, 8);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getConstReverseNIterator(6, 8)) && !(it > it) && !(it > m_MainMatrix.getConstReverseNIterator(6, 8)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstReverseNIterator(7, 8);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getConstReverseNIterator(7, 8) && !(it > it) && !(it > m_MainMatrix.getConstReverseNIterator(7, 8))),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.constReverseNEnd();
    QVERIFY2((it <= it) && (it <= m_MainMatrix.constReverseNEnd()) && !(it > it) && !(it > m_MainMatrix.constReverseNEnd()),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");

    // test with empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.constReverseNBegin() <= m_MainMatrix.constReverseNEnd(), "The first iterator is NOT smaller than or equal to the second iterator");
}

void ConstReverseNIteratorTests::testGreaterThanOperator()
{
    m_MainMatrix = {8, 9, -5};

    QVERIFY2((m_MainMatrix.constReverseNEnd() > m_MainMatrix.getConstReverseNIterator(0, 0)) && !(m_MainMatrix.constReverseNEnd() <= m_MainMatrix.getConstReverseNIterator(0, 0)), "TThe first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(0, 0) > m_MainMatrix.getConstReverseNIterator(1, 0)) && !(m_MainMatrix.getConstReverseNIterator(0, 0) <= m_MainMatrix.getConstReverseNIterator(1, 0)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(1, 0) > m_MainMatrix.getConstReverseNIterator(2, 0)) && !(m_MainMatrix.getConstReverseNIterator(1, 0) <= m_MainMatrix.getConstReverseNIterator(2, 0)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(2, 0) > m_MainMatrix.getConstReverseNIterator(4, 5)) && !(m_MainMatrix.getConstReverseNIterator(2, 0) <= m_MainMatrix.getConstReverseNIterator(4, 5)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(4, 5) > m_MainMatrix.getConstReverseNIterator(6, 8)) && !(m_MainMatrix.getConstReverseNIterator(4, 5) <= m_MainMatrix.getConstReverseNIterator(6, 8)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(6, 8) > m_MainMatrix.constReverseNBegin()) && !(m_MainMatrix.getConstReverseNIterator(6, 8) <= m_MainMatrix.constReverseNBegin()), "The first iterator is NOT greater than the second iterator");
}

void ConstReverseNIteratorTests::testGreaterThanOrEqualToOperator()
{
    m_MainMatrix = {8, 9, -5};

    // test operator with different iterators
    QVERIFY2((m_MainMatrix.constReverseNEnd() >= m_MainMatrix.constReverseNEnd()) && !(m_MainMatrix.constReverseNEnd() < m_MainMatrix.constReverseNEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.constReverseNEnd() >= m_MainMatrix.getConstReverseNIterator(0, 0)) && !(m_MainMatrix.constReverseNEnd() < m_MainMatrix.getConstReverseNIterator(0, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(0, 0) >= m_MainMatrix.getConstReverseNIterator(0, 0)) && !(m_MainMatrix.getConstReverseNIterator(0, 0) < m_MainMatrix.getConstReverseNIterator(0, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(0, 0) >= m_MainMatrix.getConstReverseNIterator(1, 0)) && !(m_MainMatrix.getConstReverseNIterator(0, 0) < m_MainMatrix.getConstReverseNIterator(1, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(1, 0) >= m_MainMatrix.getConstReverseNIterator(1, 0)) && !(m_MainMatrix.getConstReverseNIterator(1, 0) < m_MainMatrix.getConstReverseNIterator(1, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(1, 0) >= m_MainMatrix.getConstReverseNIterator(2, 0)) && !(m_MainMatrix.getConstReverseNIterator(1, 0) < m_MainMatrix.getConstReverseNIterator(2, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(2, 0) >= m_MainMatrix.getConstReverseNIterator(2, 0)) && !(m_MainMatrix.getConstReverseNIterator(2, 0) < m_MainMatrix.getConstReverseNIterator(2, 0)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(2, 0) >= m_MainMatrix.getConstReverseNIterator(4, 5)) && !(m_MainMatrix.getConstReverseNIterator(2, 0) < m_MainMatrix.getConstReverseNIterator(4, 5)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(4, 5) >= m_MainMatrix.getConstReverseNIterator(4, 5)) && !(m_MainMatrix.getConstReverseNIterator(4, 5) < m_MainMatrix.getConstReverseNIterator(4, 5)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(4, 5) >= m_MainMatrix.getConstReverseNIterator(6, 8)) && !(m_MainMatrix.getConstReverseNIterator(4, 5) < m_MainMatrix.getConstReverseNIterator(6, 8)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(6, 8) >= m_MainMatrix.getConstReverseNIterator(6, 8)) && !(m_MainMatrix.getConstReverseNIterator(6, 8) < m_MainMatrix.getConstReverseNIterator(6, 8)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getConstReverseNIterator(6, 8) >= m_MainMatrix.constReverseNBegin()) && !(m_MainMatrix.getConstReverseNIterator(6, 8) < m_MainMatrix.constReverseNBegin()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.constReverseNBegin() >= m_MainMatrix.constReverseNBegin()) && !(m_MainMatrix.constReverseNBegin() < m_MainMatrix.constReverseNBegin()), "The first iterator is NOT smaller than or equal to the second iterator");

    // test if iterator is greater than or equal to itself
    IntMatrixConstReverseNIterator it{m_MainMatrix.constReverseNEnd()};
    QVERIFY2((it >= it) && (it >= m_MainMatrix.constReverseNEnd()) && !(it < it) && !(it < m_MainMatrix.constReverseNEnd()),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstReverseNIterator(7, 8);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getConstReverseNIterator(7, 8)) && !(it < it) && !(it < m_MainMatrix.getConstReverseNIterator(7, 8)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstReverseNIterator(6, 8);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getConstReverseNIterator(6, 8)) && !(it < it) && !(it < m_MainMatrix.getConstReverseNIterator(6, 8)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstReverseNIterator(4, 5);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getConstReverseNIterator(4, 5)) && !(it < it) && !(it < m_MainMatrix.getConstReverseNIterator(4, 5)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getConstReverseNIterator(1, 0);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getConstReverseNIterator(1, 0)) && !(it < it) && !(it < m_MainMatrix.getConstReverseNIterator(1, 0)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.constReverseNBegin();
    QVERIFY2((it >= it) && (it >= m_MainMatrix.constReverseNBegin()) && !(it < it) && !(it < m_MainMatrix.constReverseNBegin()),  "The iterator is NOT greater than or equal to itself and/or the source iterator");

    // test with empty matrix
    m_MainMatrix.clear();
    QVERIFY2((m_MainMatrix.constReverseNBegin() >= m_MainMatrix.constReverseNEnd()) && !(m_MainMatrix.constReverseNBegin() < m_MainMatrix.constReverseNEnd()), "The first iterator is NOT greater than or equal to the second iterator");
}

void ConstReverseNIteratorTests::testIncrementOperators()
{
    m_MainMatrix = {8, 9, -5};

    // pre-increment
    IntMatrixConstReverseNIterator it{m_MainMatrix.constReverseNBegin()};
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 8), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(5, 8), "Incorrect pre-incrementation");
    it = m_MainMatrix.getConstReverseNIterator(5, 5);
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(4, 5), "Incorrect pre-incrementation");
    it = m_MainMatrix.getConstReverseNIterator(2, 5);
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 5), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 5), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(7, 4), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 4), "Incorrect pre-incrementation");
    it = m_MainMatrix.getConstReverseNIterator(1, 0);
    ++it;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 0), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Incorrect pre-incrementation");

    // post-increment
    it = m_MainMatrix.constReverseNBegin();
    it++;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 8), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(5, 8), "Incorrect post-incrementation");
    it = m_MainMatrix.getConstReverseNIterator(5, 5);
    it++;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(4, 5), "Incorrect post-incrementation");
    it = m_MainMatrix.getConstReverseNIterator(2, 5);
    it++;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 5), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 5), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(7, 4), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 4), "Incorrect post-incrementation");
    it = m_MainMatrix.getConstReverseNIterator(1, 0);
    it++;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 0), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Incorrect post-incrementation");

    // test a combination of "pre" and "post" behaviors
    IntMatrixConstReverseNIterator srcIt{m_MainMatrix.getConstReverseNIterator(6, 5)};
    IntMatrixConstReverseNIterator destIt{++(++srcIt)};
    QVERIFY2(srcIt == m_MainMatrix.getConstReverseNIterator(5, 5) && destIt == m_MainMatrix.getConstReverseNIterator(4, 5), "Incorrect pre-pre-incrementation");
    srcIt = m_MainMatrix.getConstReverseNIterator(6, 5);
    destIt = (srcIt++)++;
    QVERIFY2(srcIt == m_MainMatrix.getConstReverseNIterator(5, 5) && destIt == m_MainMatrix.getConstReverseNIterator(6, 5), "Incorrect post-post-incrementation");
    srcIt = m_MainMatrix.getConstReverseNIterator(6, 5);
    destIt = (++srcIt)++;
    QVERIFY2(srcIt == m_MainMatrix.getConstReverseNIterator(5, 5) && destIt == m_MainMatrix.getConstReverseNIterator(5, 5), "Incorrect post-pre-incrementation");
    srcIt = m_MainMatrix.getConstReverseNIterator(6, 5);
    destIt = ++(srcIt++);
    QVERIFY2(srcIt == m_MainMatrix.getConstReverseNIterator(5, 5) && destIt == m_MainMatrix.getConstReverseNIterator(5, 5), "Incorrect pre-post-incrementation");
}

void ConstReverseNIteratorTests::testDecrementOperators()
{
    m_MainMatrix = {8, 9, -5};

    // pre-decrement
    IntMatrixConstReverseNIterator it{m_MainMatrix.constReverseNEnd()};
    --it;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 0), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 0), "Incorrect pre-decrementation");
    it = m_MainMatrix.getConstReverseNIterator(6, 4);
    --it;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(7, 4), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 5), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 5), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(2, 5), "Incorrect pre-decrementation");
    it = m_MainMatrix.getConstReverseNIterator(4, 5);
    --it;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(5, 5), "Incorrect pre-decrementation");
    it = m_MainMatrix.getConstReverseNIterator(5, 8);
    --it;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 8), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Incorrect pre-decrementation");


    // post-decrement
    it = m_MainMatrix.constReverseNEnd();
    it--;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 0), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 0), "Incorrect post-decrementation");
    it = m_MainMatrix.getConstReverseNIterator(4, 5);
    it--;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(5, 5), "Incorrect post-decrementation");
    it = m_MainMatrix.getConstReverseNIterator(6, 4);
    it--;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(7, 4), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 5), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 5), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(2, 5), "Incorrect post-decrementation");
    it = m_MainMatrix.getConstReverseNIterator(6, 8);
    it--;
    QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(7, 8), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Incorrect post-decrementation");

    // test a combination of "pre" and "post" behaviors
    IntMatrixConstReverseNIterator srcIt{m_MainMatrix.getConstReverseNIterator(4, 5)};
    IntMatrixConstReverseNIterator destIt{--(--srcIt)};
    QVERIFY2(srcIt == m_MainMatrix.getConstReverseNIterator(5, 5) && destIt == m_MainMatrix.getConstReverseNIterator(6, 5), "Incorrect pre-pre-decrementation");
    srcIt = m_MainMatrix.getConstReverseNIterator(4, 5);
    destIt = (srcIt--)--;
    QVERIFY2(srcIt == m_MainMatrix.getConstReverseNIterator(5, 5) && destIt == m_MainMatrix.getConstReverseNIterator(4, 5), "Incorrect post-post-decrementation");
    srcIt = m_MainMatrix.getConstReverseNIterator(4, 5);
    destIt = (--srcIt)--;
    QVERIFY2(srcIt == m_MainMatrix.getConstReverseNIterator(5, 5) && destIt == m_MainMatrix.getConstReverseNIterator(5, 5), "Incorrect post-pre-decrementation");
    srcIt = m_MainMatrix.getConstReverseNIterator(4, 5);
    destIt = --(srcIt--);
    QVERIFY2(srcIt == m_MainMatrix.getConstReverseNIterator(5, 5) && destIt == m_MainMatrix.getConstReverseNIterator(5, 5), "Incorrect pre-post-decrementation");
}

void ConstReverseNIteratorTests::testOperatorPlus()
{
    m_MainMatrix = {8, 9, -5};

    // test for non-empty matrix
    IntMatrixConstReverseNIterator it{m_MainMatrix.constReverseNEnd()};
    QVERIFY2(it + 3 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-5) == m_MainMatrix.getConstReverseNIterator(4, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-11) == m_MainMatrix.getConstReverseNIterator(2, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-72) == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-73) == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-75) == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstReverseNIterator(0, 0);
    QVERIFY2(it + 4 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-4) == m_MainMatrix.getConstReverseNIterator(4, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-10) == m_MainMatrix.getConstReverseNIterator(2, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-70) == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-72) == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-74) == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstReverseNIterator(1, 0);
    QVERIFY2(it + 5 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-3) == m_MainMatrix.getConstReverseNIterator(4, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-9) == m_MainMatrix.getConstReverseNIterator(2, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-69) == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-70) == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-73) == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstReverseNIterator(4, 5);
    QVERIFY2(it + 48 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 46 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 45 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 44 == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 43 == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 6 == m_MainMatrix.getConstReverseNIterator(6, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.getConstReverseNIterator(2, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getConstReverseNIterator(4, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.getConstReverseNIterator(6, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-6) == m_MainMatrix.getConstReverseNIterator(2, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-26) == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-27) == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-28) == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-30) == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstReverseNIterator(6, 8);
    QVERIFY2(it + 74 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 72 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 71 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 70 == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 69 == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 24 == m_MainMatrix.getConstReverseNIterator(6, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.getConstReverseNIterator(3, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-4) == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.constReverseNBegin();
    QVERIFY2(it + 75 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 73 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 72 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 71 == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 70 == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 25 == m_MainMatrix.getConstReverseNIterator(6, 5), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 4 == m_MainMatrix.getConstReverseNIterator(3, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-3) == m_MainMatrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.constReverseNBegin() + (-1) == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constReverseNBegin() + 1 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constReverseNEnd() + 0 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constReverseNEnd() + 1 == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constReverseNEnd() + (-1) == m_MainMatrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");

    // test for empty iterators
    IntMatrixConstReverseNIterator emptyIt1{};
    IntMatrixConstReverseNIterator emptyIt2{};
    IntMatrixConstReverseNIterator emptyIt3{};
    emptyIt1 = emptyIt3 + (-1);
    emptyIt2 = emptyIt3 + 1;
    QVERIFY2(emptyIt1 == emptyIt3, "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(emptyIt2 == emptyIt3, "Operator + does not work correctly, the resulting iterator is not the right one");
}

void ConstReverseNIteratorTests::testOperatorMinus()
{
    m_MainMatrix = {8, 9, -5};

    // test for non-empty matrix
    IntMatrixConstReverseNIterator it{m_MainMatrix.constReverseNEnd()};
    QVERIFY2(it - (-3) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 5 == m_MainMatrix.getConstReverseNIterator(4, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 11 == m_MainMatrix.getConstReverseNIterator(2, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 72 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 73 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 75 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstReverseNIterator(0, 0);
    QVERIFY2(it - (-4) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 4 == m_MainMatrix.getConstReverseNIterator(4, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 10 == m_MainMatrix.getConstReverseNIterator(2, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 70 == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 72 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 74 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstReverseNIterator(1, 0);
    QVERIFY2(it - (-5) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 3 == m_MainMatrix.getConstReverseNIterator(4, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 9 == m_MainMatrix.getConstReverseNIterator(2, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 69 == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 70 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 73 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstReverseNIterator(4, 5);
    QVERIFY2(it - (-48) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-46) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-45) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-44) == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-43) == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-6) == m_MainMatrix.getConstReverseNIterator(6, 4), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.getConstReverseNIterator(2, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getConstReverseNIterator(4, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.getConstReverseNIterator(6, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 6 == m_MainMatrix.getConstReverseNIterator(2, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 26 == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 27 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 28 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 30 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getConstReverseNIterator(6, 8);
    QVERIFY2(it - (-74) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-72) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-71) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-70) == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-69) == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-24) == m_MainMatrix.getConstReverseNIterator(6, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.getConstReverseNIterator(3, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 4 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.constReverseNBegin();
    QVERIFY2(it - (-75) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-73) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-72) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-71) == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-70) == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-25) == m_MainMatrix.getConstReverseNIterator(6, 5), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-4) == m_MainMatrix.getConstReverseNIterator(3, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 3 == m_MainMatrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.constReverseNBegin() - 1 == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constReverseNBegin() - (-1) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constReverseNEnd() - 0 == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constReverseNEnd() - (-1) == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.constReverseNEnd() - 1 == m_MainMatrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");

    // test for empty iterators
    IntMatrixConstReverseNIterator emptyIt1{};
    IntMatrixConstReverseNIterator emptyIt2{};
    IntMatrixConstReverseNIterator emptyIt3{};
    emptyIt1 = emptyIt3 - 1;
    emptyIt2 = emptyIt3 - (-1);
    QVERIFY2(emptyIt1 == emptyIt3, "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(emptyIt2 == emptyIt3, "Operator - does not work correctly, the resulting iterator is not the right one");
}

void ConstReverseNIteratorTests::testOperatorPlusEqual()
{
    IntMatrixConstReverseNIterator it;

    // test for non-empty matrix
    m_MainMatrix = {8, 9, -5};

    IntMatrixConstReverseNIterator referenceIt{m_MainMatrix.constReverseNEnd()};
    it = referenceIt; it += 3; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-2); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-5); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(4, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-11); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(2, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-71); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-72); QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-73); QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-75); QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstReverseNIterator(0, 0);
    it = referenceIt; it += 4; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 2; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-4); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(4, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-10); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(2, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-70); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-71); QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-72); QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-74); QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstReverseNIterator(1, 0);
    it = referenceIt; it += 5; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 3; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 2; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-3); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(4, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-9); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(2, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-69); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-70); QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-71); QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-73); QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstReverseNIterator(4, 5);
    it = referenceIt; it += 48; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 46; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 45; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 44; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 43; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 6; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 2; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(2, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(4, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-2); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-6); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(2, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-26); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-27); QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-28); QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-30); QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstReverseNIterator(6, 8);
    it = referenceIt; it += 74; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 72; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 71; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 70; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 69; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 24; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 3; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(3, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-2); QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-4); QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.constReverseNBegin();
    it = referenceIt; it += 75; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 73; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 72; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 71; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 70; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 25; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 5), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 4; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(3, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 1; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += 0; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-1); QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it += (-3); QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    referenceIt = m_MainMatrix.constReverseNBegin();
    referenceIt = m_MainMatrix.constReverseNEnd();
    it = referenceIt; it += (-1); QVERIFY2(m_MainMatrix.constReverseNBegin() == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += 1; QVERIFY2(m_MainMatrix.constReverseNBegin() == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += 0; QVERIFY2(m_MainMatrix.constReverseNEnd() == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += 1; QVERIFY2(m_MainMatrix.constReverseNEnd() == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it += (-1); QVERIFY2(m_MainMatrix.constReverseNEnd() == m_MainMatrix.constReverseNEnd(), "Operator += does not work correctly, the updated iterator is not the right one");

    // test for empty iterators
    IntMatrixConstReverseNIterator emptyIt1{};
    IntMatrixConstReverseNIterator emptyIt2{};
    IntMatrixConstReverseNIterator emptyIt3{};
    emptyIt2 += (-1); QVERIFY2(emptyIt2 == emptyIt1, "Operator += does not work correctly, the updated iterator is not the right one");
    emptyIt3 += 1; QVERIFY2(emptyIt3 == emptyIt1, "Operator += does not work correctly, the updated iterator is not the right one");
}

void ConstReverseNIteratorTests::testOperatorMinusEqual()
{
    IntMatrixConstReverseNIterator it;

    // test for non-empty matrix
    m_MainMatrix = {8, 9, -5};

    IntMatrixConstReverseNIterator referenceIt{m_MainMatrix.constReverseNEnd()};
    it = referenceIt; it -= (-3); QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 2; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 5; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(4, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 11; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(2, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 71; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 72; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 73; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 75; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstReverseNIterator(0, 0);
    it = referenceIt; it -= (-4); QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-2); QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 4; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(4, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 10; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(2, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 70; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 71; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 72; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 74; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstReverseNIterator(1, 0);
    it = referenceIt; it -= (-5); QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-3); QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-2); QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 3; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(4, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 9; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(2, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 69; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 70; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 71; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 73; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstReverseNIterator(4, 5);
    it = referenceIt; it -= (-48); QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-46); QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-45); QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-44); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-43); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-6); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-2); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(2, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(4, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 2; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 6; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(2, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 26; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 27; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 28; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 30; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.getConstReverseNIterator(6, 8);
    it = referenceIt; it -= (-74); QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-72); QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-71); QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-70); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-69); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-24); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-3); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(3, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 2; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 4; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    referenceIt = m_MainMatrix.constReverseNBegin();
    it = referenceIt; it -= (-75); QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-73); QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-72); QVERIFY2(it == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-71); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(0, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-70); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(1, 0), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-25); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 5), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-4); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(3, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= (-1); QVERIFY2(it == m_MainMatrix.getConstReverseNIterator(6, 8), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 0; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 1; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = referenceIt; it -= 3; QVERIFY2(it == m_MainMatrix.constReverseNBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    referenceIt = m_MainMatrix.constReverseNBegin();
    referenceIt = m_MainMatrix.constReverseNEnd();
    it = referenceIt; it -= 1; QVERIFY2(m_MainMatrix.constReverseNBegin() == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= (-1); QVERIFY2(m_MainMatrix.constReverseNBegin() == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= 0; QVERIFY2(m_MainMatrix.constReverseNEnd() == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= (-1); QVERIFY2(m_MainMatrix.constReverseNEnd() == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = referenceIt; it -= 1; QVERIFY2(m_MainMatrix.constReverseNEnd() == m_MainMatrix.constReverseNEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");

    // test for empty iterators
    IntMatrixConstReverseNIterator emptyIt1{};
    IntMatrixConstReverseNIterator emptyIt2{};
    IntMatrixConstReverseNIterator emptyIt3{};
    emptyIt2 -= 1; QVERIFY2(emptyIt2 == emptyIt1, "Operator -= does not work correctly, the updated iterator is not the right one");
    emptyIt3 -= (-1); QVERIFY2(emptyIt3 == emptyIt1, "Operator -= does not work correctly, the updated iterator is not the right one");
}

void ConstReverseNIteratorTests::testDifferenceOperator()
{
    // test for non-empty matrix
    m_MainMatrix = {8, 9, -5};

    QVERIFY2(m_MainMatrix.constReverseNBegin() - m_MainMatrix.constReverseNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseNBegin() - m_MainMatrix.getConstReverseNIterator(6, 8) == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseNBegin() - m_MainMatrix.getConstReverseNIterator(4, 5) == -27, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseNBegin() - m_MainMatrix.getConstReverseNIterator(1, 0) == -70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseNBegin() - m_MainMatrix.getConstReverseNIterator(0, 0) == -71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseNBegin() - m_MainMatrix.constReverseNEnd() == -72, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getConstReverseNIterator(6, 8) - m_MainMatrix.constReverseNBegin() == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(6, 8) - m_MainMatrix.getConstReverseNIterator(6, 8) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(6, 8) - m_MainMatrix.getConstReverseNIterator(4, 5) == -26, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(6, 8) - m_MainMatrix.getConstReverseNIterator(1, 0) == -69, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(6, 8) - m_MainMatrix.getConstReverseNIterator(0, 0) == -70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(6, 8) - m_MainMatrix.constReverseNEnd() == -71, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getConstReverseNIterator(4, 5) - m_MainMatrix.constReverseNBegin() == 27, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(4, 5) - m_MainMatrix.getConstReverseNIterator(6, 8) == 26, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(4, 5) - m_MainMatrix.getConstReverseNIterator(4, 5) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(4, 5) - m_MainMatrix.getConstReverseNIterator(1, 0) == -43, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(4, 5) - m_MainMatrix.getConstReverseNIterator(0, 0) == -44, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(4, 5) - m_MainMatrix.constReverseNEnd() == -45, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getConstReverseNIterator(1, 0) - m_MainMatrix.constReverseNBegin() == 70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(1, 0) - m_MainMatrix.getConstReverseNIterator(6, 8) == 69, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(1, 0) - m_MainMatrix.getConstReverseNIterator(4, 5) == 43, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(1, 0) - m_MainMatrix.getConstReverseNIterator(1, 0) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(1, 0) - m_MainMatrix.getConstReverseNIterator(0, 0) == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(1, 0) - m_MainMatrix.constReverseNEnd() == -2, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getConstReverseNIterator(0, 0) - m_MainMatrix.constReverseNBegin() == 71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(0, 0) - m_MainMatrix.getConstReverseNIterator(6, 8) == 70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(0, 0) - m_MainMatrix.getConstReverseNIterator(4, 5) == 44, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(0, 0) - m_MainMatrix.getConstReverseNIterator(1, 0) == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(0, 0) - m_MainMatrix.getConstReverseNIterator(0, 0) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(0, 0) - m_MainMatrix.constReverseNEnd() == -1, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.constReverseNEnd() - m_MainMatrix.constReverseNBegin() == 72, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseNEnd() - m_MainMatrix.getConstReverseNIterator(6, 8) == 71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseNEnd() - m_MainMatrix.getConstReverseNIterator(4, 5) == 45, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseNEnd() - m_MainMatrix.getConstReverseNIterator(1, 0) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseNEnd() - m_MainMatrix.getConstReverseNIterator(0, 0) == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseNEnd() - m_MainMatrix.constReverseNEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");

    // additional tests with "random" elements from same column/different columns
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(4, 5) - m_MainMatrix.getConstReverseNIterator(2, 7) == 14, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(2, 7) - m_MainMatrix.getConstReverseNIterator(4, 5) == -14, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(4, 5) - m_MainMatrix.getConstReverseNIterator(2, 5) == -2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getConstReverseNIterator(2, 5) - m_MainMatrix.getConstReverseNIterator(4, 5) == 2, "The difference operator does not work correctly, difference between iterators is wrong");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.constReverseNEnd() - m_MainMatrix.constReverseNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseNBegin() - m_MainMatrix.constReverseNEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseNBegin() - m_MainMatrix.constReverseNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.constReverseNEnd() - m_MainMatrix.constReverseNEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");

    // test for empty iterator
    IntMatrixConstReverseNIterator it1{};
    IntMatrixConstReverseNIterator it2{};
    QVERIFY2(it1 - it2 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(it2 - it1 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(it1 - it1 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
}

void ConstReverseNIteratorTests::testDereferenceAsteriskOperator()
{
    // test reading element
    m_MainMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};
    QVERIFY2(*m_MainMatrix.getConstReverseNIterator(0, 0) == 1, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getConstReverseNIterator(1, 0) == -2, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getConstReverseNIterator(2, 1) == -6, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getConstReverseNIterator(1, 3) == 11, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.constReverseNBegin() == -12, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");

    // additional tests
    m_MainMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    IntMatrixConstReverseNIterator readIter{m_MainMatrix.constReverseNBegin()};
    m_MainMatrix.at(0, 1) = 10;
    readIter += 2;
    QVERIFY2(*readIter == 10, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
}

void ConstReverseNIteratorTests::testDereferenceArrowOperator()
{
    // test reading element
    m_AuxStringMatrix = {3, 4, {"abc", "jihgfedcba", "abcde", "", "ba", "a", "ihgfedcba", "abcdefghijk", "abcd", "gfedcba", "abcdefgh", "fedcba"}};
    QVERIFY2(m_AuxStringMatrix.getConstReverseNIterator(0, 0)->size() == 3, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getConstReverseNIterator(1, 0)->size() == 2, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getConstReverseNIterator(2, 1)->size() == 7, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getConstReverseNIterator(1, 3)->size() == 11, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.constReverseNBegin()->size() == 6, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");

    // additional tests
    m_AuxStringMatrix = {3, 2, {"abc", "jkl", "defed", "mnop", "ghi", "qr"}};
    StringMatrixConstReverseNIterator it{m_AuxStringMatrix.constReverseNBegin()};
    m_AuxStringMatrix.at(0, 1) = "abcdefghi";
    it += 2;
    QVERIFY2(it->size() == 9, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
}

void ConstReverseNIteratorTests::testDereferenceSquareBracketsOperator()
{
    // test reading element
    m_MainMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};

    IntMatrixConstReverseNIterator it{m_MainMatrix.constReverseNBegin()};
    QVERIFY2(it[11] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[10] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[6] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[1] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getConstReverseNIterator(1, 3);
    QVERIFY2(it[10] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[9] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[5] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-1] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getConstReverseNIterator(2, 1);
    QVERIFY2(it[5] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[4] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-5] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-6] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getConstReverseNIterator(1, 0);
    QVERIFY2(it[1] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-4] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-9] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-10] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getConstReverseNIterator(0, 0);
    QVERIFY2(it[0] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-1] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-5] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-10] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-11] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");
}

void ConstReverseNIteratorTests::testStdCount()
{
    using namespace std;

    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};

    int matchCount{count(m_MainMatrix.constReverseNBegin(), m_MainMatrix.constReverseNEnd(), 2)};
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseNBegin(), m_MainMatrix.constReverseNEnd(), -5);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseNIterator(4, 1), m_MainMatrix.getConstReverseNIterator(3, 0), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseNIterator(0, 2), m_MainMatrix.getConstReverseNIterator(2, 0), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseNIterator(0, 2), m_MainMatrix.getConstReverseNIterator(3, 0), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseNIterator(4, 1), m_MainMatrix.getConstReverseNIterator(2, 0), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseNBegin(), m_MainMatrix.getConstReverseNIterator(3, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseNIterator(3, 2), m_MainMatrix.constReverseNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseNBegin(), m_MainMatrix.getConstReverseNIterator(2, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseNIterator(2, 2), m_MainMatrix.constReverseNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseNIterator(9), m_MainMatrix.getConstReverseNIterator(2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseNIterator(10), m_MainMatrix.getConstReverseNIterator(2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseNIterator(9), m_MainMatrix.getConstReverseNIterator(3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseNIterator(10), m_MainMatrix.getConstReverseNIterator(3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseNBegin(), m_MainMatrix.getConstReverseNIterator(13), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseNIterator(13), m_MainMatrix.constReverseNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseNBegin(), m_MainMatrix.getConstReverseNIterator(12), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getConstReverseNIterator(12), m_MainMatrix.constReverseNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseNColumnBegin(1), m_MainMatrix.constReverseNColumnEnd(1), 5);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseNColumnEnd(3), m_MainMatrix.constReverseNColumnEnd(0), 8);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseNColumnBegin(3), m_MainMatrix.constReverseNColumnEnd(3), 9);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseNColumnBegin(3), m_MainMatrix.constReverseNColumnEnd(2), 9);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseNColumnEnd(1), m_MainMatrix.constReverseNEnd(), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseNBegin(), m_MainMatrix.constReverseNColumnEnd(1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseNColumnBegin(2), m_MainMatrix.constReverseNEnd(), 1);
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.constReverseNBegin(), m_MainMatrix.constReverseNColumnBegin(2), 1);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
}

void ConstReverseNIteratorTests::testStdFind()
{
    using namespace std;

    // test finding elements in specific ranges within unempty matrix
    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 6, 9, 11}};

    QVERIFY2(find(m_MainMatrix.constReverseNBegin(), m_MainMatrix.constReverseNEnd(), 5) != m_MainMatrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNBegin(), m_MainMatrix.constReverseNEnd(), 10) == m_MainMatrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNColumnBegin(1), m_MainMatrix.constReverseNColumnEnd(1), 6) != m_MainMatrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNColumnBegin(1), m_MainMatrix.constReverseNColumnEnd(1), 5) != m_MainMatrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNColumnBegin(1), m_MainMatrix.constReverseNColumnEnd(1), 8) != m_MainMatrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNColumnBegin(1), m_MainMatrix.constReverseNColumnEnd(1), -1) == m_MainMatrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNColumnBegin(1), m_MainMatrix.constReverseNColumnEnd(1), 1) == m_MainMatrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNColumnBegin(1), m_MainMatrix.constReverseNColumnEnd(1), 10) == m_MainMatrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNColumnBegin(1), m_MainMatrix.constReverseNEnd(), 6) != m_MainMatrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNColumnBegin(1), m_MainMatrix.constReverseNEnd(), -1) != m_MainMatrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNColumnBegin(1), m_MainMatrix.constReverseNEnd(), 3) != m_MainMatrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNColumnBegin(1), m_MainMatrix.constReverseNEnd(), -2) == m_MainMatrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNColumnBegin(1), m_MainMatrix.constReverseNEnd(), 10) == m_MainMatrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNBegin(), m_MainMatrix.constReverseNColumnEnd(1), 11) != m_MainMatrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNBegin(), m_MainMatrix.constReverseNColumnEnd(1), 5) != m_MainMatrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNBegin(), m_MainMatrix.constReverseNColumnEnd(1), 0) != m_MainMatrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNBegin(), m_MainMatrix.constReverseNColumnEnd(1), 1) == m_MainMatrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNBegin(), m_MainMatrix.constReverseNColumnEnd(1), 10) == m_MainMatrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseNIterator(1, 3), m_MainMatrix.getConstReverseNIterator(3, 1), 7) != m_MainMatrix.getConstReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseNIterator(1, 3), m_MainMatrix.getConstReverseNIterator(3, 1), -7) != m_MainMatrix.getConstReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseNIterator(1, 3), m_MainMatrix.getConstReverseNIterator(3, 1), -2) != m_MainMatrix.getConstReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseNIterator(1, 3), m_MainMatrix.getConstReverseNIterator(3, 1), -1) == m_MainMatrix.getConstReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseNIterator(1, 3), m_MainMatrix.getConstReverseNIterator(3, 1), 11) == m_MainMatrix.getConstReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseNIterator(1, 3), m_MainMatrix.getConstReverseNIterator(3, 1), 10) == m_MainMatrix.getConstReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseNIterator(3, 1), m_MainMatrix.constReverseNEnd(), 0) != m_MainMatrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseNIterator(3, 1), m_MainMatrix.constReverseNEnd(), -1) != m_MainMatrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseNIterator(3, 1), m_MainMatrix.constReverseNEnd(), 4) != m_MainMatrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseNIterator(3, 1), m_MainMatrix.constReverseNEnd(), 11) == m_MainMatrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getConstReverseNIterator(3, 1), m_MainMatrix.constReverseNEnd(), 10) == m_MainMatrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNBegin(), m_MainMatrix.getConstReverseNIterator(1, 3), 11) != m_MainMatrix.getConstReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNBegin(), m_MainMatrix.getConstReverseNIterator(1, 3), 2) != m_MainMatrix.getConstReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNBegin(), m_MainMatrix.getConstReverseNIterator(1, 3), 9) != m_MainMatrix.getConstReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNBegin(), m_MainMatrix.getConstReverseNIterator(1, 3), 0) == m_MainMatrix.getConstReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.constReverseNBegin(), m_MainMatrix.getConstReverseNIterator(1, 3), 10) == m_MainMatrix.getConstReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

    // other tests
    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};
    IntMatrixConstReverseNIterator it{find(m_MainMatrix.constReverseNBegin(), m_MainMatrix.constReverseNEnd(), 4)};
    ++it;
    QVERIFY2(*it == 1, "The iterator doesn't work correctly with std::find, incorrect next element returned");

    m_MainMatrix = {5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};
    QVERIFY2(find(m_MainMatrix.constReverseNBegin(), m_MainMatrix.constReverseNEnd(), 10) == m_MainMatrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix");

    it = m_MainMatrix.constReverseNBegin();
    while(it != m_MainMatrix.constReverseNEnd())
    {
        it = find(it, m_MainMatrix.constReverseNEnd(), 9);

        if (it != m_MainMatrix.constReverseNEnd())
        {
            m_MainMatrix.at(it.getCurrentRowNr(), it.getCurrentColumnNr()) = 10;
        }
    }
    int expectedNumber{std::count(m_MainMatrix.constReverseNBegin(), m_MainMatrix.constReverseNEnd(), 10)};
    QVERIFY2(expectedNumber == 3, "The iterator doesn't work properly with std::find, element values haven't been correctly replaced");
}

QTEST_APPLESS_MAIN(ConstReverseNIteratorTests)

#include "tst_constreverseniteratortests.moc"
