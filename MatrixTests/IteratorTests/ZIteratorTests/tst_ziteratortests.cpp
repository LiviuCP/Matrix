#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixZIterator = Matrix<int>::ZIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixZIterator = Matrix<std::string>::ZIterator;

class ZIteratorTests : public QObject
{
    Q_OBJECT

public:
    ZIteratorTests();
    ~ZIteratorTests();

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

    void testIteratingWithAuto(); // tests the begin() and end() functions

    // "bonus" tests, demonstrate the integration of the Matrix iterators with algorithms of the standard library
    void testStdCount();
    void testStdFind();
    void testStdSort();

private:
    IntMatrix m_MainMatrix;
    IntMatrix m_AuxIntMatrix;
    StringMatrix m_AuxStringMatrix;
};

ZIteratorTests::ZIteratorTests()
{
}

ZIteratorTests::~ZIteratorTests()
{
}

void ZIteratorTests::testIteratorCreation()
{
    m_MainMatrix = {9, 8, -5};

    IntMatrixZIterator it{m_MainMatrix.zBegin()};
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.zEnd();
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.zRowBegin(0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.zRowBegin(1);
    QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.zRowBegin(4);
    QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.zRowBegin(7);
    QVERIFY2(it.getCurrentRowNr() == 7 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.zRowBegin(8);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.zRowEnd(0);
    QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.zRowEnd(1);
    QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.zRowEnd(4);
    QVERIFY2(it.getCurrentRowNr() == 5 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.zRowEnd(7);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.zRowEnd(8);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 8 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getZIterator(0, 0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getZIterator(0, 1);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getZIterator(5, 4);
    QVERIFY2(it.getCurrentRowNr() == 5 && it.getCurrentColumnNr() == 4 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getZIterator(8, 6);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 6 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getZIterator(8, 7);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getZIterator(0);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getZIterator(1);
    QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getZIterator(44);
    QVERIFY2(it.getCurrentRowNr() == 5 && it.getCurrentColumnNr() == 4 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getZIterator(70);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 6 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.getZIterator(71);
    QVERIFY2(it.getCurrentRowNr() == 8 && it.getCurrentColumnNr() == 7 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // test iterator creation for empty matrix
    m_MainMatrix.clear();
    it = m_MainMatrix.zBegin();
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");
    it = m_MainMatrix.zEnd();
    QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // test empty iterator creation (not bound to any matrix) - an empty iterator should be valid for any empty matrix
    IntMatrixZIterator emptyIt;
    QVERIFY2(emptyIt.getCurrentRowNr() == -1 && emptyIt.getCurrentColumnNr() == -1 && emptyIt.isValidWithMatrix(m_MainMatrix), "The iterator has not been correctly created");

    // additional test
    m_MainMatrix = {9, 8, -5};
    m_AuxIntMatrix = {9, 8, -5};
    it = m_MainMatrix.getZIterator(5, 4);
    QVERIFY(!it.isValidWithMatrix(m_AuxIntMatrix));
    m_AuxIntMatrix.clear();
    QVERIFY(!it.isValidWithMatrix(m_AuxIntMatrix));
    it = m_AuxIntMatrix.zBegin();
    QVERIFY(!it.isValidWithMatrix(m_MainMatrix));
    it = m_AuxIntMatrix.zEnd();
    QVERIFY(!it.isValidWithMatrix(m_MainMatrix));
    m_MainMatrix.clear();
    it = m_MainMatrix.zBegin();
    QVERIFY(it.isValidWithMatrix(m_AuxIntMatrix)); // an iterator of an empty matrix is valid with any other empty matrix
    it = m_MainMatrix.zEnd();
    QVERIFY(it.isValidWithMatrix(m_AuxIntMatrix));
}

void ZIteratorTests::testIteratorsAreEqual()
{

    m_MainMatrix = {9, 8, -5};

    // test different iterators for equality
    QVERIFY2((m_MainMatrix.zBegin() == m_MainMatrix.getZIterator(0, 0) && !(m_MainMatrix.zBegin() != m_MainMatrix.getZIterator(0, 0))), "The two iterators are not equal");
    QVERIFY2((m_MainMatrix.getZIterator(0) == m_MainMatrix.getZIterator(0, 0)) && !(m_MainMatrix.getZIterator(0) != m_MainMatrix.getZIterator(0, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getZIterator(1) == m_MainMatrix.getZIterator(0, 1)) && !(m_MainMatrix.getZIterator(1) != m_MainMatrix.getZIterator(0, 1)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getZIterator(44) == m_MainMatrix.getZIterator(5, 4)) && !(m_MainMatrix.getZIterator(44) != m_MainMatrix.getZIterator(5, 4)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getZIterator(70) == m_MainMatrix.getZIterator(8, 6)) && !(m_MainMatrix.getZIterator(70) != m_MainMatrix.getZIterator(8, 6)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.getZIterator(71) == m_MainMatrix.getZIterator(8, 7)) && !(m_MainMatrix.getZIterator(71) != m_MainMatrix.getZIterator(8, 7)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.zRowBegin(0) == m_MainMatrix.getZIterator(0, 0)) && !(m_MainMatrix.zRowBegin(0) != m_MainMatrix.getZIterator(0, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.zRowBegin(1) == m_MainMatrix.getZIterator(1, 0)) && !(m_MainMatrix.zRowBegin(1) != m_MainMatrix.getZIterator(1, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.zRowBegin(5) == m_MainMatrix.getZIterator(5, 0)) && !(m_MainMatrix.zRowBegin(5) != m_MainMatrix.getZIterator(5, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.zRowBegin(7) == m_MainMatrix.getZIterator(7, 0)) && !(m_MainMatrix.zRowBegin(7) != m_MainMatrix.getZIterator(7, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.zRowBegin(8) == m_MainMatrix.getZIterator(8, 0)) && !(m_MainMatrix.zRowBegin(8) != m_MainMatrix.getZIterator(8, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.zRowEnd(0) == m_MainMatrix.getZIterator(1, 0)) && !(m_MainMatrix.zRowEnd(0) != m_MainMatrix.getZIterator(1, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.zRowEnd(1) == m_MainMatrix.getZIterator(2, 0)) && !(m_MainMatrix.zRowEnd(1) != m_MainMatrix.getZIterator(2, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.zRowEnd(5) == m_MainMatrix.getZIterator(6, 0)) && !(m_MainMatrix.zRowEnd(5) != m_MainMatrix.getZIterator(6, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.zRowEnd(7) == m_MainMatrix.getZIterator(8, 0)) && !(m_MainMatrix.zRowEnd(7) != m_MainMatrix.getZIterator(8, 0)), "The two iterators are NOT equal");
    QVERIFY2((m_MainMatrix.zRowEnd(8) == m_MainMatrix.zEnd()) && !(m_MainMatrix.zRowEnd(8) != m_MainMatrix.zEnd()), "The two iterators are NOT equal");

    // test iterator equality to itself
    IntMatrixZIterator it{m_MainMatrix.zBegin()};
    QVERIFY2((it == it) && (it == m_MainMatrix.zBegin()) && !(it != it) && !(it != m_MainMatrix.zBegin()), "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getZIterator(0, 1);
    QVERIFY2((it == it) && (it == m_MainMatrix.getZIterator(0, 1)) && !(it != it) && !(it != m_MainMatrix.getZIterator(0, 1)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getZIterator(5, 4);
    QVERIFY2((it == it) && (it == m_MainMatrix.getZIterator(5, 4)) && !(it != it) && !(it != m_MainMatrix.getZIterator(5, 4)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getZIterator(8, 6);
    QVERIFY2((it == it) && (it == m_MainMatrix.getZIterator(8, 6)) && !(it != it) && !(it != m_MainMatrix.getZIterator(8, 6)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.getZIterator(8, 7);
    QVERIFY2((it == it) && (it == m_MainMatrix.getZIterator(8, 7)) && !(it != it) && !(it != m_MainMatrix.getZIterator(8, 7)),  "The iterator is NOT equal to itself and/or to source iterator");
    it = m_MainMatrix.zEnd();
    QVERIFY2((it == it) && (it == m_MainMatrix.zEnd()) && !(it != it) && !(it != m_MainMatrix.zEnd()),  "The iterator is NOT equal to itself and/or to source iterator");

    // test empty matrix iterator equality
    m_MainMatrix.clear();
    QVERIFY2((m_MainMatrix.zBegin() == m_MainMatrix.zEnd()) && !(m_MainMatrix.zBegin() != m_MainMatrix.zEnd()), "The two iterators are NOT equal");
}

void ZIteratorTests::testIteratorsAreNotEqual()
{
    m_MainMatrix = {9, 8, -5};

    QVERIFY2((m_MainMatrix.zBegin() != m_MainMatrix.getZIterator(0, 1)) && !(m_MainMatrix.zBegin() == m_MainMatrix.getZIterator(0, 1)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getZIterator(0, 1) != m_MainMatrix.getZIterator(0, 2)) && !(m_MainMatrix.getZIterator(0, 1) == m_MainMatrix.getZIterator(0, 2)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getZIterator(0, 2) != m_MainMatrix.getZIterator(5, 4)) && !(m_MainMatrix.getZIterator(0, 2) == m_MainMatrix.getZIterator(5, 4)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getZIterator(5, 4) != m_MainMatrix.getZIterator(8, 6)) && !(m_MainMatrix.getZIterator(5, 4) == m_MainMatrix.getZIterator(8, 6)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getZIterator(8, 6) != m_MainMatrix.getZIterator(8, 7)) && !(m_MainMatrix.getZIterator(8, 6) == m_MainMatrix.getZIterator(8, 7)), "The two iterators are NOT different");
    QVERIFY2((m_MainMatrix.getZIterator(8, 7) != m_MainMatrix.zEnd()) && !(m_MainMatrix.getZIterator(8, 7) == m_MainMatrix.zEnd()), "The two iterators are NOT different");
}

void ZIteratorTests::testSmallerThanOperator()
{
    m_MainMatrix = {9, 8, -5};

    QVERIFY2((m_MainMatrix.zBegin() < m_MainMatrix.getZIterator(0, 1)) && !(m_MainMatrix.zBegin() >= m_MainMatrix.getZIterator(0, 1)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(0, 1) < m_MainMatrix.getZIterator(0, 2)) && !(m_MainMatrix.getZIterator(0, 1) >= m_MainMatrix.getZIterator(0, 2)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(0, 2) < m_MainMatrix.getZIterator(5, 4)) && !(m_MainMatrix.getZIterator(0, 2) >= m_MainMatrix.getZIterator(5, 4)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(5, 4) < m_MainMatrix.getZIterator(8, 6)) && !(m_MainMatrix.getZIterator(5, 4) >= m_MainMatrix.getZIterator(8, 6)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(8, 6) < m_MainMatrix.getZIterator(8, 7)) && !(m_MainMatrix.getZIterator(8, 6) >= m_MainMatrix.getZIterator(8, 7)), "The first iterator is NOT smaller than the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(8, 7) < m_MainMatrix.zEnd()) && !(m_MainMatrix.getZIterator(8, 7) >= m_MainMatrix.zEnd()), "The first iterator is NOT smaller than the second iterator");
}

void ZIteratorTests::testSmallerThanOrEqualToOperator()
{
    m_MainMatrix = {9, 8, -5};

    // test operator with different iterators
    QVERIFY2((m_MainMatrix.zBegin() <= m_MainMatrix.zBegin()) && !(m_MainMatrix.zBegin() > m_MainMatrix.zEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.zBegin() <= m_MainMatrix.getZIterator(0, 1)) && !(m_MainMatrix.getZIterator(8, 7) > m_MainMatrix.zEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(0, 1) <= m_MainMatrix.getZIterator(0, 1)) && !(m_MainMatrix.getZIterator(0, 1) > m_MainMatrix.getZIterator(0, 1)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(0, 1) <= m_MainMatrix.getZIterator(0, 2)) && !(m_MainMatrix.getZIterator(0, 1) > m_MainMatrix.getZIterator(0, 2)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(0, 2) <= m_MainMatrix.getZIterator(0, 2)) && !(m_MainMatrix.getZIterator(0, 2) > m_MainMatrix.getZIterator(0, 2)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(0, 2) <= m_MainMatrix.getZIterator(5, 4)) && !(m_MainMatrix.getZIterator(0, 2) > m_MainMatrix.getZIterator(5, 4)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(5, 4) <= m_MainMatrix.getZIterator(5, 4)) && !(m_MainMatrix.getZIterator(5, 4) > m_MainMatrix.getZIterator(5, 4)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(5, 4) <= m_MainMatrix.getZIterator(8, 6)) && !(m_MainMatrix.getZIterator(5, 4) > m_MainMatrix.getZIterator(8, 6)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(8, 6) <= m_MainMatrix.getZIterator(8, 6)) && !(m_MainMatrix.getZIterator(8, 6) > m_MainMatrix.getZIterator(8, 6)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(8, 6) <= m_MainMatrix.getZIterator(8, 7)) && !(m_MainMatrix.getZIterator(8, 6) > m_MainMatrix.getZIterator(8, 7)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(8, 7) <= m_MainMatrix.getZIterator(8, 7)) && !(m_MainMatrix.getZIterator(8, 7) > m_MainMatrix.getZIterator(8, 7)), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(8, 7) <= m_MainMatrix.zEnd()) && !(m_MainMatrix.getZIterator(8, 7) > m_MainMatrix.zEnd()), "The first iterator is NOT smaller than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.zEnd() <= m_MainMatrix.zEnd()) && !(m_MainMatrix.zEnd() > m_MainMatrix.zEnd()), "The first iterator is NOT smaller than or equal to the second iterator");

    // test if iterator is smaller than or equal to itself
    IntMatrixZIterator it{m_MainMatrix.zBegin()};
    QVERIFY2((it <= it) && (it <= m_MainMatrix.zBegin()) && !(it > it) && !(it > m_MainMatrix.zBegin()),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getZIterator(0, 1);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getZIterator(0, 1)) && !(it > it) && !(it > m_MainMatrix.getZIterator(0, 1)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getZIterator(5, 4);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getZIterator(5, 4)) && !(it > it) && !(it > m_MainMatrix.getZIterator(5, 4)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getZIterator(8, 6);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getZIterator(8, 6)) && !(it > it) && !(it > m_MainMatrix.getZIterator(8, 6)),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getZIterator(8, 7);
    QVERIFY2((it <= it) && (it <= m_MainMatrix.getZIterator(8, 7) && !(it > it) && !(it > m_MainMatrix.getZIterator(8, 7))),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");
    it = m_MainMatrix.zEnd();
    QVERIFY2((it <= it) && (it <= m_MainMatrix.zEnd()) && !(it > it) && !(it > m_MainMatrix.zEnd()),  "The iterator is NOT smaller than or equal to itself and/or the source iterator");

    // test with empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.zBegin() <= m_MainMatrix.zEnd(), "The first iterator is NOT smaller than or equal to the second iterator");
}

void ZIteratorTests::testGreaterThanOperator()
{
    m_MainMatrix = {9, 8, -5};

    QVERIFY2((m_MainMatrix.zEnd() > m_MainMatrix.getZIterator(8, 7)) && !(m_MainMatrix.zEnd() <= m_MainMatrix.getZIterator(8, 7)), "TThe first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(8, 7) > m_MainMatrix.getZIterator(8, 6)) && !(m_MainMatrix.getZIterator(8, 7) <= m_MainMatrix.getZIterator(8, 6)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(8, 6) > m_MainMatrix.getZIterator(5, 4)) && !(m_MainMatrix.getZIterator(8, 6) <= m_MainMatrix.getZIterator(5, 4)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(5, 4) > m_MainMatrix.getZIterator(0, 2)) && !(m_MainMatrix.getZIterator(5, 4) <= m_MainMatrix.getZIterator(0, 2)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(0, 2) > m_MainMatrix.getZIterator(0, 1)) && !(m_MainMatrix.getZIterator(0, 2) <= m_MainMatrix.getZIterator(0, 1)), "The first iterator is NOT greater than the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(0, 1) > m_MainMatrix.zBegin()) && !(m_MainMatrix.getZIterator(0, 1) <= m_MainMatrix.zBegin()), "The first iterator is NOT greater than the second iterator");
}

void ZIteratorTests::testGreaterThanOrEqualToOperator()
{
    m_MainMatrix = {9, 8, -5};

    // test operator with different iterators
    QVERIFY2((m_MainMatrix.zEnd() >= m_MainMatrix.zEnd()) && !(m_MainMatrix.zEnd() < m_MainMatrix.zEnd()), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.zEnd() >= m_MainMatrix.getZIterator(8, 7)) && !(m_MainMatrix.zEnd() < m_MainMatrix.getZIterator(8, 7)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(8, 7) >= m_MainMatrix.getZIterator(8, 7)) && !(m_MainMatrix.getZIterator(8, 7) < m_MainMatrix.getZIterator(8, 7)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(8, 7) >= m_MainMatrix.getZIterator(8, 6)) && !(m_MainMatrix.getZIterator(8, 7) < m_MainMatrix.getZIterator(8, 6)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(8, 6) >= m_MainMatrix.getZIterator(8, 6)) && !(m_MainMatrix.getZIterator(8, 6) < m_MainMatrix.getZIterator(8, 6)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(8, 6) >= m_MainMatrix.getZIterator(5, 4)) && !(m_MainMatrix.getZIterator(8, 6) < m_MainMatrix.getZIterator(5, 4)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(5, 4) >= m_MainMatrix.getZIterator(5, 4)) && !(m_MainMatrix.getZIterator(5, 4) < m_MainMatrix.getZIterator(5, 4)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(5, 4) >= m_MainMatrix.getZIterator(0, 2)) && !(m_MainMatrix.getZIterator(5, 4) < m_MainMatrix.getZIterator(0, 2)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(0, 2) >= m_MainMatrix.getZIterator(0, 2)) && !(m_MainMatrix.getZIterator(0, 2) < m_MainMatrix.getZIterator(0, 2)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(0, 2) >= m_MainMatrix.getZIterator(0, 1)) && !(m_MainMatrix.getZIterator(0, 2) < m_MainMatrix.getZIterator(0, 1)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(0, 1) >= m_MainMatrix.getZIterator(0, 1)) && !(m_MainMatrix.getZIterator(0, 1) < m_MainMatrix.getZIterator(0, 1)), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.getZIterator(0, 1) >= m_MainMatrix.zBegin()) && !(m_MainMatrix.getZIterator(0, 1) < m_MainMatrix.zBegin()), "The first iterator is NOT greater than or equal to the second iterator");
    QVERIFY2((m_MainMatrix.zBegin() >= m_MainMatrix.zBegin()) && !(m_MainMatrix.zBegin() < m_MainMatrix.zBegin()), "The first iterator is NOT greater than or equal to the second iterator");

    // test if iterator is greater than or equal to itself
    IntMatrixZIterator it{m_MainMatrix.zEnd()};
    QVERIFY2((it >= it) && (it >= m_MainMatrix.zEnd()) && !(it < it) && !(it < m_MainMatrix.zEnd()),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getZIterator(8, 7);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getZIterator(8, 7)) && !(it < it) && !(it < m_MainMatrix.getZIterator(8, 7)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getZIterator(8, 6);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getZIterator(8, 6)) && !(it < it) && !(it < m_MainMatrix.getZIterator(8, 6)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getZIterator(5, 4);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getZIterator(5, 4)) && !(it < it) && !(it < m_MainMatrix.getZIterator(5, 4)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.getZIterator(0, 1);
    QVERIFY2((it >= it) && (it >= m_MainMatrix.getZIterator(0, 1)) && !(it < it) && !(it < m_MainMatrix.getZIterator(0, 1)),  "The iterator is NOT greater than or equal to itself and/or the source iterator");
    it = m_MainMatrix.zBegin();
    QVERIFY2((it >= it) && (it >= m_MainMatrix.zBegin()) && !(it < it) && !(it < m_MainMatrix.zBegin()),  "The iterator is NOT greater than or equal to itself and/or the source iterator");

    // test with empty matrix
    m_MainMatrix.clear();
    QVERIFY2((m_MainMatrix.zBegin() >= m_MainMatrix.zEnd()) && !(m_MainMatrix.zBegin() < m_MainMatrix.zEnd()), "The first iterator is NOT greater than or equal to the second iterator");
}

void ZIteratorTests::testIncrementOperators()
{
    m_MainMatrix = {9, 8, -5};

    // pre-increment
    IntMatrixZIterator it{m_MainMatrix.zBegin()};
    ++it;
    QVERIFY2(it == m_MainMatrix.getZIterator(0, 1), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getZIterator(0, 2), "Incorrect pre-incrementation");
    it = m_MainMatrix.getZIterator(4, 6);
    ++it;
    QVERIFY2(it == m_MainMatrix.getZIterator(4, 7), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getZIterator(5, 0), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getZIterator(5, 1), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.getZIterator(5, 2), "Incorrect pre-incrementation");
    it = m_MainMatrix.getZIterator(5, 4);
    ++it;
    QVERIFY2(it == m_MainMatrix.getZIterator(5, 5), "Incorrect pre-incrementation");
    it = m_MainMatrix.getZIterator(8, 6);
    ++it;
    QVERIFY2(it == m_MainMatrix.getZIterator(8, 7), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.zEnd(), "Incorrect pre-incrementation");
    ++it;
    QVERIFY2(it == m_MainMatrix.zEnd(), "Incorrect pre-incrementation");

    // post-increment
    it = m_MainMatrix.zBegin();
    it++;
    QVERIFY2(it == m_MainMatrix.getZIterator(0, 1), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getZIterator(0, 2), "Incorrect post-incrementation");
    it = m_MainMatrix.getZIterator(4, 6);
    it++;
    QVERIFY2(it == m_MainMatrix.getZIterator(4, 7), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getZIterator(5, 0), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getZIterator(5, 1), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.getZIterator(5, 2), "Incorrect post-incrementation");
    it = m_MainMatrix.getZIterator(5, 4);
    it++;
    QVERIFY2(it == m_MainMatrix.getZIterator(5, 5), "Incorrect post-incrementation");
    it = m_MainMatrix.getZIterator(8, 6);
    it++;
    QVERIFY2(it == m_MainMatrix.getZIterator(8, 7), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.zEnd(), "Incorrect post-incrementation");
    it++;
    QVERIFY2(it == m_MainMatrix.zEnd(), "Incorrect post-incrementation");

    // test a combination of "pre" and "post" behaviors
    IntMatrixZIterator srcIt{m_MainMatrix.getZIterator(5, 4)};
    IntMatrixZIterator destIt{++(++srcIt)};
    QVERIFY2(srcIt == m_MainMatrix.getZIterator(5, 5) && destIt == m_MainMatrix.getZIterator(5, 6), "Incorrect pre-pre-incrementation");
    srcIt = m_MainMatrix.getZIterator(5, 4);
    destIt = (srcIt++)++;
    QVERIFY2(srcIt == m_MainMatrix.getZIterator(5, 5) && destIt == m_MainMatrix.getZIterator(5, 4), "Incorrect post-post-incrementation");
    srcIt = m_MainMatrix.getZIterator(5, 4);
    destIt = (++srcIt)++;
    QVERIFY2(srcIt == m_MainMatrix.getZIterator(5, 5) && destIt == m_MainMatrix.getZIterator(5, 5), "Incorrect post-pre-incrementation");
    srcIt = m_MainMatrix.getZIterator(5, 4);
    destIt = ++(srcIt++);
    QVERIFY2(srcIt == m_MainMatrix.getZIterator(5, 5) && destIt == m_MainMatrix.getZIterator(5, 5), "Incorrect pre-post-incrementation");
}

void ZIteratorTests::testDecrementOperators()
{
    m_MainMatrix = {9, 8, -5};

    // pre-decrement
    IntMatrixZIterator it{m_MainMatrix.zEnd()};
    --it;
    QVERIFY2(it == m_MainMatrix.getZIterator(8, 7), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getZIterator(8, 6), "Incorrect pre-decrementation");
    it = m_MainMatrix.getZIterator(5, 5);
    --it;
    QVERIFY2(it == m_MainMatrix.getZIterator(5, 4), "Incorrect pre-decrementation");
    it = m_MainMatrix.getZIterator(5, 2);
    --it;
    QVERIFY2(it == m_MainMatrix.getZIterator(5, 1), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getZIterator(5, 0), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getZIterator(4, 7), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.getZIterator(4, 6), "Incorrect pre-decrementation");
    it = m_MainMatrix.getZIterator(0, 2);
    --it;
    QVERIFY2(it == m_MainMatrix.getZIterator(0, 1), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.zBegin(), "Incorrect pre-decrementation");
    --it;
    QVERIFY2(it == m_MainMatrix.zBegin(), "Incorrect pre-decrementation");


    // post-decrement
    it = m_MainMatrix.zEnd();
    it--;
    QVERIFY2(it == m_MainMatrix.getZIterator(8, 7), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getZIterator(8, 6), "Incorrect post-decrementation");
    it = m_MainMatrix.getZIterator(5, 5);
    it--;
    QVERIFY2(it == m_MainMatrix.getZIterator(5, 4), "Incorrect post-decrementation");
    it = m_MainMatrix.getZIterator(5, 2);
    it--;
    QVERIFY2(it == m_MainMatrix.getZIterator(5, 1), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getZIterator(5, 0), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getZIterator(4, 7), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.getZIterator(4, 6), "Incorrect post-decrementation");
    it = m_MainMatrix.getZIterator(0, 2);
    it--;
    QVERIFY2(it == m_MainMatrix.getZIterator(0, 1), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.zBegin(), "Incorrect post-decrementation");
    it--;
    QVERIFY2(it == m_MainMatrix.zBegin(), "Incorrect post-decrementation");

    // test a combination of "pre" and "post" behaviors
    IntMatrixZIterator srcIt{m_MainMatrix.getZIterator(5, 6)};
    IntMatrixZIterator destIt{--(--srcIt)};
    QVERIFY2(srcIt == m_MainMatrix.getZIterator(5, 5) && destIt == m_MainMatrix.getZIterator(5, 4), "Incorrect pre-pre-decrementation");
    srcIt = m_MainMatrix.getZIterator(5, 6);
    destIt = (srcIt--)--;
    QVERIFY2(srcIt == m_MainMatrix.getZIterator(5, 5) && destIt == m_MainMatrix.getZIterator(5, 6), "Incorrect post-post-decrementation");
    srcIt = m_MainMatrix.getZIterator(5, 6);
    destIt = (--srcIt)--;
    QVERIFY2(srcIt == m_MainMatrix.getZIterator(5, 5) && destIt == m_MainMatrix.getZIterator(5, 5), "Incorrect post-pre-decrementation");
    srcIt = m_MainMatrix.getZIterator(5, 6);
    destIt = --(srcIt--);
    QVERIFY2(srcIt == m_MainMatrix.getZIterator(5, 5) && destIt == m_MainMatrix.getZIterator(5, 5), "Incorrect pre-post-decrementation");
}

void ZIteratorTests::testOperatorPlus()
{
    m_MainMatrix = {9, 8, -5};

    // test for non-empty matrix
    IntMatrixZIterator it{m_MainMatrix.zBegin()};
    QVERIFY2(it + (-3) == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.getZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 4 == m_MainMatrix.getZIterator(0, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 10 == m_MainMatrix.getZIterator(1, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 70 == m_MainMatrix.getZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 71 == m_MainMatrix.getZIterator(8, 7), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 72 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 73 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 75 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getZIterator(0, 1);
    QVERIFY2(it + (-4) == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.getZIterator(0, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 9 == m_MainMatrix.getZIterator(1, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 69 == m_MainMatrix.getZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 70 == m_MainMatrix.getZIterator(8, 7), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 71 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 72 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 74 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getZIterator(5, 4);
    QVERIFY2(it + (-47) == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-45) == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-44) == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-43) == m_MainMatrix.getZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-6) == m_MainMatrix.getZIterator(4, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.getZIterator(5, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getZIterator(5, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.getZIterator(5, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 6 == m_MainMatrix.getZIterator(6, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 26 == m_MainMatrix.getZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 27 == m_MainMatrix.getZIterator(8, 7), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 28 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 29 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 31 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getZIterator(8, 6);
    QVERIFY2(it + (-73) == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-70) == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-69) == m_MainMatrix.getZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-24) == m_MainMatrix.getZIterator(5, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-3) == m_MainMatrix.getZIterator(8, 3), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.getZIterator(8, 7), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 5 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getZIterator(8, 7);
    QVERIFY2(it + (-74) == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-72) == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-70) == m_MainMatrix.getZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-25) == m_MainMatrix.getZIterator(5, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-4) == m_MainMatrix.getZIterator(8, 3), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.getZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.getZIterator(8, 7), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 2 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 4 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.zEnd();
    QVERIFY2(it + (-75) == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-73) == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-72) == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-71) == m_MainMatrix.getZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-26) == m_MainMatrix.getZIterator(5, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-5) == m_MainMatrix.getZIterator(8, 3), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-2) == m_MainMatrix.getZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + (-1) == m_MainMatrix.getZIterator(8, 7), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 0 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 1 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it + 3 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.zBegin() + (-1) == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.zBegin() + 1 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.zEnd() + 0 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.zEnd() + 1 == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.zEnd() + (-1) == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");

    // test for empty iterators
    IntMatrixZIterator emptyIt1{};
    IntMatrixZIterator emptyIt2{};
    IntMatrixZIterator emptyIt3{};
    emptyIt1 = emptyIt3 + (-1);
    emptyIt2 = emptyIt3 + 1;
    QVERIFY2(emptyIt1 == emptyIt3, "Operator + does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(emptyIt2 == emptyIt3, "Operator + does not work correctly, the resulting iterator is not the right one");
}

void ZIteratorTests::testOperatorMinus()
{
    m_MainMatrix = {9, 8, -5};

    // test for non-empty matrix
    IntMatrixZIterator it{m_MainMatrix.zBegin()};
    QVERIFY2(it - 3 == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.zBegin(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.getZIterator(0, 1), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-4) == m_MainMatrix.getZIterator(0, 4), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-10) == m_MainMatrix.getZIterator(1, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-70) == m_MainMatrix.getZIterator(8, 6), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-71) == m_MainMatrix.getZIterator(8, 7), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-72) == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-73) == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-75) == m_MainMatrix.zEnd(), "Operator + does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getZIterator(0, 1);
    QVERIFY2(it - 4 == m_MainMatrix.zBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.zBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.zBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.getZIterator(0, 4), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-9) == m_MainMatrix.getZIterator(1, 2), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-69) == m_MainMatrix.getZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-70) == m_MainMatrix.getZIterator(8, 7), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-71) == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-72) == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-74) == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getZIterator(5, 4);
    QVERIFY2(it - 47 == m_MainMatrix.zBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 45 == m_MainMatrix.zBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 44 == m_MainMatrix.zBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 43 == m_MainMatrix.getZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 6 == m_MainMatrix.getZIterator(4, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.getZIterator(5, 2), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getZIterator(5, 4), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.getZIterator(5, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-6) == m_MainMatrix.getZIterator(6, 2), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-26) == m_MainMatrix.getZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-27) == m_MainMatrix.getZIterator(8, 7), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-28) == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-29) == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-31) == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getZIterator(8, 6);
    QVERIFY2(it - 73 == m_MainMatrix.zBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.zBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 70 == m_MainMatrix.zBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 69 == m_MainMatrix.getZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 24 == m_MainMatrix.getZIterator(5, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 3 == m_MainMatrix.getZIterator(8, 3), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.getZIterator(8, 7), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-5) == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.getZIterator(8, 7);
    QVERIFY2(it - 74 == m_MainMatrix.zBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 72 == m_MainMatrix.zBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.zBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 70 == m_MainMatrix.getZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 25 == m_MainMatrix.getZIterator(5, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 4 == m_MainMatrix.getZIterator(8, 3), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.getZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.getZIterator(8, 7), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-2) == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-4) == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    it = m_MainMatrix.zEnd();
    QVERIFY2(it - 75 == m_MainMatrix.zBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 73 == m_MainMatrix.zBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 72 == m_MainMatrix.zBegin(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 71 == m_MainMatrix.getZIterator(0, 1), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 26 == m_MainMatrix.getZIterator(5, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 5 == m_MainMatrix.getZIterator(8, 3), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 2 == m_MainMatrix.getZIterator(8, 6), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 1 == m_MainMatrix.getZIterator(8, 7), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - 0 == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-1) == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");
    QVERIFY2(it - (-3) == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.zBegin() - 1 == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.zBegin() - (-1) == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.zEnd() - 0 == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.zEnd() - (-1) == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(m_MainMatrix.zEnd() - 1 == m_MainMatrix.zEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");

    // test for empty iterator
    IntMatrixZIterator emptyIt1{};
    IntMatrixZIterator emptyIt2{};
    IntMatrixZIterator emptyIt3{};
    emptyIt1 = emptyIt3 - 1;
    emptyIt2 = emptyIt3 - (-1);
    QVERIFY2(emptyIt1 == emptyIt3, "Operator - does not work correctly, the resulting iterator is not the right one");
    QVERIFY2(emptyIt2 == emptyIt3, "Operator - does not work correctly, the resulting iterator is not the right one");
}

void ZIteratorTests::testOperatorPlusEqual()
{
    IntMatrixZIterator it;

    // test for non-empty matrix
    m_MainMatrix = {9, 8, -5};

    IntMatrixZIterator it1{m_MainMatrix.zBegin()};
    it = it1; it += (-3); QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.getZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 4; QVERIFY2(it == m_MainMatrix.getZIterator(0, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 10; QVERIFY2(it == m_MainMatrix.getZIterator(1, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 70; QVERIFY2(it == m_MainMatrix.getZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 71; QVERIFY2(it == m_MainMatrix.getZIterator(8, 7), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 72; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 73; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 75; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getZIterator(0, 1);
    it = it1; it += (-4); QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-2); QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.getZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 3; QVERIFY2(it == m_MainMatrix.getZIterator(0, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 9; QVERIFY2(it == m_MainMatrix.getZIterator(1, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 69; QVERIFY2(it == m_MainMatrix.getZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 70; QVERIFY2(it == m_MainMatrix.getZIterator(8, 7), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 71; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 72; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 74; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getZIterator(5, 4);
    it = it1; it += (-47); QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-45); QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-44); QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-43); QVERIFY2(it == m_MainMatrix.getZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-6); QVERIFY2(it == m_MainMatrix.getZIterator(4, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-2); QVERIFY2(it == m_MainMatrix.getZIterator(5, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.getZIterator(5, 4), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 2; QVERIFY2(it == m_MainMatrix.getZIterator(5, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 6; QVERIFY2(it == m_MainMatrix.getZIterator(6, 2), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 26; QVERIFY2(it == m_MainMatrix.getZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 27; QVERIFY2(it == m_MainMatrix.getZIterator(8, 7), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 28; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 29; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 31; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getZIterator(8, 6);
    it = it1; it += (-73); QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-71); QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-70); QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-69); QVERIFY2(it == m_MainMatrix.getZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-24); QVERIFY2(it == m_MainMatrix.getZIterator(5, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-3); QVERIFY2(it == m_MainMatrix.getZIterator(8, 3), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.getZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.getZIterator(8, 7), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 2; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 3; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 5; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getZIterator(8, 7);
    it = it1; it += (-74); QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-72); QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-71); QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-70); QVERIFY2(it == m_MainMatrix.getZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-25); QVERIFY2(it == m_MainMatrix.getZIterator(5, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-4); QVERIFY2(it == m_MainMatrix.getZIterator(8, 3), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.getZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.getZIterator(8, 7), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 2; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 4; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.zEnd();
    it = it1; it += (-75); QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-73); QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-72); QVERIFY2(it == m_MainMatrix.zBegin(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-71); QVERIFY2(it == m_MainMatrix.getZIterator(0, 1), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-26); QVERIFY2(it == m_MainMatrix.getZIterator(5, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-5); QVERIFY2(it == m_MainMatrix.getZIterator(8, 3), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-2); QVERIFY2(it == m_MainMatrix.getZIterator(8, 6), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.getZIterator(8, 7), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");
    it = it1; it += 3; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    it1 = m_MainMatrix.zBegin();
    it1 = m_MainMatrix.zEnd();
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = it1; it += 0; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = it1; it += 1; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator is not the right one");
    it = it1; it += (-1); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator += does not work correctly, the updated iterator is not the right one");

    // test for empty iterator
    IntMatrixZIterator it2{};
    IntMatrixZIterator it3{};
    IntMatrixZIterator it4{};
    it3 += (-1); QVERIFY2(it3 == it2, "Operator += does not work correctly, the resulting updated is not the right one");
    it4 += 1; QVERIFY2(it4 == it2, "Operator += does not work correctly, the resulting updated is not the right one");
}

void ZIteratorTests::testOperatorMinusEqual()
{
    IntMatrixZIterator it;

    // test for non-empty matrix
    m_MainMatrix = {9, 8, -5};

    IntMatrixZIterator it1{m_MainMatrix.zBegin()};
    it = it1; it -= 3; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.getZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-4); QVERIFY2(it == m_MainMatrix.getZIterator(0, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-10); QVERIFY2(it == m_MainMatrix.getZIterator(1, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-70); QVERIFY2(it == m_MainMatrix.getZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-71); QVERIFY2(it == m_MainMatrix.getZIterator(8, 7), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-72); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-73); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-75); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getZIterator(0, 1);
    it = it1; it -= 4; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 2; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.getZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-3); QVERIFY2(it == m_MainMatrix.getZIterator(0, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-9); QVERIFY2(it == m_MainMatrix.getZIterator(1, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-69); QVERIFY2(it == m_MainMatrix.getZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-70); QVERIFY2(it == m_MainMatrix.getZIterator(8, 7), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-71); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-72); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-74); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getZIterator(5, 4);
    it = it1; it -= 47; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 45; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 44; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 43; QVERIFY2(it == m_MainMatrix.getZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 6; QVERIFY2(it == m_MainMatrix.getZIterator(4, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 2; QVERIFY2(it == m_MainMatrix.getZIterator(5, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.getZIterator(5, 4), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-2); QVERIFY2(it == m_MainMatrix.getZIterator(5, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-6); QVERIFY2(it == m_MainMatrix.getZIterator(6, 2), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-26); QVERIFY2(it == m_MainMatrix.getZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-27); QVERIFY2(it == m_MainMatrix.getZIterator(8, 7), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-28); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-29); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-31); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getZIterator(8, 6);
    it = it1; it -= 73; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 71; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 70; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 69; QVERIFY2(it == m_MainMatrix.getZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 24; QVERIFY2(it == m_MainMatrix.getZIterator(5, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 3; QVERIFY2(it == m_MainMatrix.getZIterator(8, 3), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.getZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.getZIterator(8, 7), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-2); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-3); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-5); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.getZIterator(8, 7);
    it = it1; it -= 74; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 72; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 71; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 70; QVERIFY2(it == m_MainMatrix.getZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 25; QVERIFY2(it == m_MainMatrix.getZIterator(5, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 4; QVERIFY2(it == m_MainMatrix.getZIterator(8, 3), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.getZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.getZIterator(8, 7), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-2); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-4); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    it1 = m_MainMatrix.zEnd();
    it = it1; it -= 75; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 73; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 72; QVERIFY2(it == m_MainMatrix.zBegin(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 71; QVERIFY2(it == m_MainMatrix.getZIterator(0, 1), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 26; QVERIFY2(it == m_MainMatrix.getZIterator(5, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 5; QVERIFY2(it == m_MainMatrix.getZIterator(8, 3), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 2; QVERIFY2(it == m_MainMatrix.getZIterator(8, 6), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.getZIterator(8, 7), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");
    it = it1; it -= (-3); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator does not point to the right element");

    // test for empty matrix
    m_MainMatrix.clear();
    it1 = m_MainMatrix.zBegin();
    it1 = m_MainMatrix.zEnd();
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = it1; it -= 0; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = it1; it -= (-1); QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");
    it = it1; it -= 1; QVERIFY2(it == m_MainMatrix.zEnd(), "Operator -= does not work correctly, the updated iterator is not the right one");

    // test for empty iterator
    IntMatrixZIterator it2{};
    IntMatrixZIterator it3{};
    IntMatrixZIterator it4{};
    it3 -= 1; QVERIFY2(it3 == it2, "Operator -= does not work correctly, the updated iterator is not the right one");
    it4 -= (-1); QVERIFY2(it4 == it2, "Operator -= does not work correctly, the updated iterator is not the right one");
}

void ZIteratorTests::testDifferenceOperator()
{
    // test for non-empty matrix
    m_MainMatrix = {9, 8, -5};

    QVERIFY2(m_MainMatrix.zEnd() - m_MainMatrix.zEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.zEnd() - m_MainMatrix.getZIterator(8, 7) == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.zEnd() - m_MainMatrix.getZIterator(8, 6) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.zEnd() - m_MainMatrix.getZIterator(5, 4) == 28, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.zEnd() - m_MainMatrix.getZIterator(0, 1) == 71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.zEnd() - m_MainMatrix.zBegin() == 72, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getZIterator(8, 7) - m_MainMatrix.zEnd() == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(8, 7) - m_MainMatrix.getZIterator(8, 7) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(8, 7) - m_MainMatrix.getZIterator(8, 6) == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(8, 7) - m_MainMatrix.getZIterator(5, 4) == 27, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(8, 7) - m_MainMatrix.getZIterator(0, 1) == 70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(8, 7) - m_MainMatrix.zBegin() == 71, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getZIterator(8, 6) - m_MainMatrix.zEnd() == -2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(8, 6) - m_MainMatrix.getZIterator(8, 7) == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(8, 6) - m_MainMatrix.getZIterator(8, 6) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(8, 6) - m_MainMatrix.getZIterator(5, 4) == 26, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(8, 6) - m_MainMatrix.getZIterator(0, 1) == 69, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(8, 6) - m_MainMatrix.zBegin() == 70, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getZIterator(5, 4) - m_MainMatrix.zEnd() == -28, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(5, 4) - m_MainMatrix.getZIterator(8, 7) == -27, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(5, 4) - m_MainMatrix.getZIterator(8, 6) == -26, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(5, 4) - m_MainMatrix.getZIterator(5, 4) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(5, 4) - m_MainMatrix.getZIterator(0, 1) == 43, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(5, 4) - m_MainMatrix.zBegin() == 44, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.getZIterator(0, 1) - m_MainMatrix.zEnd() == -71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(0, 1) - m_MainMatrix.getZIterator(8, 7) == -70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(0, 1) - m_MainMatrix.getZIterator(8, 6) == -69, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(0, 1) - m_MainMatrix.getZIterator(5, 4) == -43, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(0, 1) - m_MainMatrix.getZIterator(0, 1) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(0, 1) - m_MainMatrix.zBegin() == 1, "The difference operator does not work correctly, difference between iterators is wrong");

    QVERIFY2(m_MainMatrix.zBegin() - m_MainMatrix.zEnd() == -72, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.zBegin() - m_MainMatrix.getZIterator(8, 7) == -71, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.zBegin() - m_MainMatrix.getZIterator(8, 6) == -70, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.zBegin() - m_MainMatrix.getZIterator(5, 4) == -44, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.zBegin() - m_MainMatrix.getZIterator(0, 1) == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.zBegin() - m_MainMatrix.zBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");

    // additional tests with "random" elements from same row/different rows
    QVERIFY2(m_MainMatrix.getZIterator(5, 4) - m_MainMatrix.getZIterator(7, 2) == -14, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(7, 2) - m_MainMatrix.getZIterator(5, 4) == 14, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(5, 4) - m_MainMatrix.getZIterator(5, 2) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.getZIterator(5, 2) - m_MainMatrix.getZIterator(5, 4) == -2, "The difference operator does not work correctly, difference between iterators is wrong");

    // test for empty matrix
    m_MainMatrix.clear();
    QVERIFY2(m_MainMatrix.zEnd() - m_MainMatrix.zBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.zBegin() - m_MainMatrix.zEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.zBegin() - m_MainMatrix.zBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(m_MainMatrix.zEnd() - m_MainMatrix.zEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");

    // test for empty iterator
    IntMatrixZIterator it1{};
    IntMatrixZIterator it2{};
    QVERIFY2(it1 - it2 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(it2 - it1 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    QVERIFY2(it1 - it1 == 0, "The difference operator does not work correctly, difference between iterators is wrong");
}

void ZIteratorTests::testDereferenceAsteriskOperator()
{
    // test reading element
    m_MainMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};
    QVERIFY2(*m_MainMatrix.zBegin() == 1, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getZIterator(0, 1) == -2, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getZIterator(1, 2) == -6, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getZIterator(3, 1) == 11, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    QVERIFY2(*m_MainMatrix.getZIterator(3, 2) == -12, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");

    // test writing to element
    m_MainMatrix = {4, 3, -20};
    *m_MainMatrix.zBegin() = 1;
    *m_MainMatrix.getZIterator(0, 1) = -2;
    *m_MainMatrix.getZIterator(1, 2) = -6;
    *m_MainMatrix.getZIterator(3, 1) = 11;
    *m_MainMatrix.getZIterator(3, 2) = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY2(m_MainMatrix.at(0, 1) == -2, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY2(m_MainMatrix.at(1, 2) == -6, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY2(m_MainMatrix.at(3, 1) == 11, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY2(m_MainMatrix.at(3, 2) == -12, "The dereference (*) operator does not work correctly, the pointed value hasn't been correctly modified");
    QVERIFY(m_MainMatrix.at(2, 1) == -20);

    // additional tests
    m_MainMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    IntMatrixZIterator readIter{m_MainMatrix.zBegin()};
    m_MainMatrix.at(0, 2) = 10;
    readIter += 2;
    QVERIFY2(*readIter == 10, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");

    m_MainMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    IntMatrixZIterator writeIter{m_MainMatrix.zBegin()};
    writeIter += 2;
    *writeIter = 10;
    QVERIFY2(m_MainMatrix.at(0, 2) == 10, "The dereference (*) operator does not work correctly, the value is not correctly written to the pointed location");
}

void ZIteratorTests::testDereferenceArrowOperator()
{
    // test reading element
    m_AuxStringMatrix = {4, 3, {"abc", "ba", "abcd", "jihgfedcba", "a", "gfedcba", "abcde", "ihgfedcba", "abcdefgh", "", "abcdefghijk", "fedcba"}};
    QVERIFY2(m_AuxStringMatrix.zBegin()->size() == 3, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getZIterator(0, 1)->size() == 2, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getZIterator(1, 2)->size() == 7, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getZIterator(3, 1)->size() == 11, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    QVERIFY2(m_AuxStringMatrix.getZIterator(3, 2)->size() == 6, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");

    // test writing to element
    m_AuxStringMatrix = {4, 3, "zzz"};
    m_AuxStringMatrix.zBegin()->assign("abc");
    m_AuxStringMatrix.getZIterator(0, 1)->assign("ba");
    m_AuxStringMatrix.getZIterator(1, 2)->assign("gfedcba");
    m_AuxStringMatrix.getZIterator(3, 1)->assign("abcdefghijk");
    m_AuxStringMatrix.getZIterator(3, 2)->assign("fedcba");
    QVERIFY2(m_AuxStringMatrix.at(0, 0) == "abc", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY2(m_AuxStringMatrix.at(0, 1) == "ba", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY2(m_AuxStringMatrix.at(1, 2) == "gfedcba", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY2(m_AuxStringMatrix.at(3, 1) == "abcdefghijk", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY2(m_AuxStringMatrix.at(3, 2) == "fedcba", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    QVERIFY(m_AuxStringMatrix.at(2, 1) == "zzz");

    // additional tests
    m_AuxStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    StringMatrixZIterator it{m_AuxStringMatrix.zBegin()};
    m_AuxStringMatrix.at(0, 2) = "abcdefghi";
    it += 2;
    QVERIFY2(it->size() == 9, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");

    m_AuxStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    it = m_AuxStringMatrix.zBegin();
    it += 2;
    it->assign("abcdefghi");
    QVERIFY2(m_AuxStringMatrix.at(0, 2) == "abcdefghi", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
}

void ZIteratorTests::testDereferenceSquareBracketsOperator()
{
    // test reading element
    m_MainMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};

    IntMatrixZIterator it{m_MainMatrix.zBegin()};
    QVERIFY2(it[0] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[1] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[5] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[10] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[11] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getZIterator(0, 1);
    QVERIFY2(it[-1] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[4] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[9] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[10] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getZIterator(1, 2);
    QVERIFY2(it[-5] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-4] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[5] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[6] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getZIterator(3, 1);
    QVERIFY2(it[-10] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-9] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-5] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[1] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    it = m_MainMatrix.getZIterator(3, 2);
    QVERIFY2(it[-11] == 1, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-10] == -2, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-6] == -6, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[-1] == 11, "The dereference square brackets operator doesn't work correctly when reading the element");
    QVERIFY2(it[0] == -12, "The dereference square brackets operator doesn't work correctly when reading the element");

    // test writing to element (before running a new scenario the matrix should be reset to its initial value value)
    m_MainMatrix = {4, 3, -20}; // initial

    it = m_MainMatrix.zBegin();
    it[0] = 1;
    it[1] = -2;
    it[5] = -6;
    it[10] = 11;
    it[11] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(0, 1) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 2) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 1) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 2) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(2, 1) == -20);

    m_MainMatrix = {4, 3, -20}; // reset

    it = m_MainMatrix.getZIterator(0, 1);
    it[-1] = 1;
    it[0] = -2;
    it[4] = -6;
    it[9] = 11;
    it[10] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(0, 1) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 2) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 1) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 2) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(2, 1) == -20);

    m_MainMatrix = {4, 3, -20}; // reset

    it = m_MainMatrix.getZIterator(1, 2);
    it[-5] = 1;
    it[-4] = -2;
    it[0] = -6;
    it[5] = 11;
    it[6] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(0, 1) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 2) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 1) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 2) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(2, 1) == -20);

    m_MainMatrix = {4, 3, -20}; // reset

    it = m_MainMatrix.getZIterator(3, 1);
    it[-10] = 1;
    it[-9] = -2;
    it[-5] = -6;
    it[0] = 11;
    it[1] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(0, 1) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 2) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 1) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 2) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(2, 1) == -20);

    m_MainMatrix = {4, 3, -20}; // reset

    it = m_MainMatrix.getZIterator(3, 2);
    it[-11] = 1;
    it[-10] = -2;
    it[-6] = -6;
    it[-1] = 11;
    it[0] = -12;
    QVERIFY2(m_MainMatrix.at(0, 0) == 1, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(0, 1) == -2, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(1, 2) == -6, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 1) == 11, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY2(m_MainMatrix.at(3, 2) == -12, "The dereference square brackets operator doesn't work correctly when writing the element");
    QVERIFY(m_MainMatrix.at(2, 1) == -20);
}

void ZIteratorTests::testIteratingWithAuto()
{
    // test auto (local copy) - read element
    {
        m_MainMatrix = {2, 3, {-1, 2, -3, 4, -5, 6}};

        int sum{0};
        int prod{1};
        int count{0};

        for (auto element : m_MainMatrix)
        {
            sum += element;
            prod *= element;
            ++count;
        }

        QVERIFY2(sum == 3 && prod == -720 && count == 6, "Iterating through the matrix elements by using the auto keyword does not work correctly");

        m_MainMatrix.clear();

        for (auto element : m_MainMatrix)
        {
            Q_UNUSED(element);
            ++count;
        }

        QVERIFY(count == 6);
    }

    // test auto (local copy) - write to local element copy
    {
        m_MainMatrix = {2, 3, {-1, 2, 3, 4, -5, 6}};

        int sum{0};
        int count{0};

        for (auto element : m_MainMatrix)
        {
            if (element < 0)
            {
                element = element * (-1);
            }

            sum += element;
            ++count;
        }

        QVERIFY2(m_MainMatrix.at(0, 0) == -1 && m_MainMatrix.at(0, 1) == 2 && m_MainMatrix.at(0, 2) == 3 && m_MainMatrix.at(1, 0) == 4 && m_MainMatrix.at(1, 1) == -5 && m_MainMatrix.at(1, 2) == 6 && sum == 21,
                 "Iterating through the matrix elements by using the auto keyword does not work correctly");

        m_MainMatrix.clear();

        for (auto element : m_MainMatrix)
        {
            Q_UNUSED(element);
            ++count;
        }

        QVERIFY(count == 6);
    }

    // test auto&
    {

        m_MainMatrix = {2, 3, {-1, 2, -3, 4, -5, 6}};

        int count{0};

        for (auto& element : m_MainMatrix)
        {
            if (element < 0)
            {
                element = element * (-1);
            }

            ++count;
        }

        QVERIFY2(m_MainMatrix.at(0, 0) == 1 && m_MainMatrix.at(0, 1) == 2 && m_MainMatrix.at(0, 2) == 3 && m_MainMatrix.at(1, 0) == 4 && m_MainMatrix.at(1, 1) == 5 && m_MainMatrix.at(1, 2) == 6,
                 "Iterating through the matrix elements by using the auto keyword with reference does not work correctly");

        m_MainMatrix.clear();

        for (auto& element : m_MainMatrix)
        {
            Q_UNUSED(element);
            ++count;
        }

        QVERIFY(count == 6);
    }

    // test const auto
    {
        m_MainMatrix = {2, 3, {-1, 2, -3, 4, -5, 6}};

        int sum{0};
        int prod{1};
        int count{0};

        for (const auto element : m_MainMatrix)
        {
            sum += element;
            prod *= element;
            ++count;
        }

        QVERIFY2(sum == 3 && prod == -720 && count == 6, "Iterating through the matrix elements by using the auto keyword does not work correctly");

        m_MainMatrix.clear();

        for (const auto element : m_MainMatrix)
        {
            Q_UNUSED(element);
            ++count;
        }

        QVERIFY(count == 6);
    }

    // test const auto&
    {
        m_MainMatrix = {2, 3, {-1, 2, -3, 4, -5, 6}};

        int sum{0};
        int prod{1};
        int count{0};

        for (const auto& element : m_MainMatrix)
        {
            sum += element;
            prod *= element;
            ++count;
        }

        QVERIFY2(sum == 3 && prod == -720 && count == 6, "Iterating through the matrix elements by using the auto keyword with const reference does not work correctly");

        m_MainMatrix.clear();

        for (const auto& element : m_MainMatrix)
        {
            Q_UNUSED(element);
            ++count;
        }

        QVERIFY(count == 6);
    }
}

void ZIteratorTests::testStdCount()
{
    using namespace std;

    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};

    int matchCount{count(m_MainMatrix.zBegin(), m_MainMatrix.zEnd(), 2)};
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.zBegin(), m_MainMatrix.zEnd(), -5);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getZIterator(0, 2), m_MainMatrix.getZIterator(1, 4), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getZIterator(0, 2), m_MainMatrix.getZIterator(2, 0), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getZIterator(0, 3), m_MainMatrix.getZIterator(1, 4), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getZIterator(0, 3), m_MainMatrix.getZIterator(2, 0), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.zBegin(), m_MainMatrix.getZIterator(2, 3), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getZIterator(2, 3), m_MainMatrix.zEnd(), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.zBegin(), m_MainMatrix.getZIterator(2, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getZIterator(2, 2), m_MainMatrix.zEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getZIterator(2), m_MainMatrix.getZIterator(9), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getZIterator(2), m_MainMatrix.getZIterator(10), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getZIterator(3), m_MainMatrix.getZIterator(9), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getZIterator(3), m_MainMatrix.getZIterator(10), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.zBegin(), m_MainMatrix.getZIterator(13), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getZIterator(13), m_MainMatrix.zEnd(), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.zBegin(), m_MainMatrix.getZIterator(12), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.getZIterator(12), m_MainMatrix.zEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.zRowBegin(1), m_MainMatrix.zRowEnd(1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.zRowBegin(1), m_MainMatrix.zRowEnd(2), 8);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.zRowBegin(2), m_MainMatrix.zRowEnd(2), 9);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.zRowBegin(2), m_MainMatrix.zRowEnd(3), 9);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.zBegin(), m_MainMatrix.zRowBegin(1), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.zRowBegin(1), m_MainMatrix.zEnd(), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.zBegin(), m_MainMatrix.zRowEnd(1), 1);
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    matchCount = count(m_MainMatrix.zRowEnd(1), m_MainMatrix.zEnd(), 1);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
}

void ZIteratorTests::testStdFind()
{
    using namespace std;

    // test finding elements in specific ranges within unempty matrix
    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, -2, 2, 8, 9, -7, 7, 2, 9, 11}};

    QVERIFY2(find(m_MainMatrix.zBegin(), m_MainMatrix.zEnd(), 5) != m_MainMatrix.zEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.zBegin(), m_MainMatrix.zEnd(), 10) == m_MainMatrix.zEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.zRowBegin(1), m_MainMatrix.zRowEnd(1), 5) != m_MainMatrix.zRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.zRowBegin(1), m_MainMatrix.zRowEnd(1), 6) != m_MainMatrix.zRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.zRowBegin(1), m_MainMatrix.zRowEnd(1), 8) != m_MainMatrix.zRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.zRowBegin(1), m_MainMatrix.zRowEnd(1), -1) == m_MainMatrix.zRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.zRowBegin(1), m_MainMatrix.zRowEnd(1), -2) == m_MainMatrix.zRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.zRowBegin(1), m_MainMatrix.zRowEnd(1), 10) == m_MainMatrix.zRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.zRowBegin(1), m_MainMatrix.zEnd(), 5) != m_MainMatrix.zEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.zRowBegin(1), m_MainMatrix.zEnd(), 11) != m_MainMatrix.zEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.zRowBegin(1), m_MainMatrix.zEnd(), -2) != m_MainMatrix.zEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.zRowBegin(1), m_MainMatrix.zEnd(), -1) == m_MainMatrix.zEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.zRowBegin(1), m_MainMatrix.zEnd(), 10) == m_MainMatrix.zEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.zBegin(), m_MainMatrix.zRowEnd(1), -1) != m_MainMatrix.zRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.zBegin(), m_MainMatrix.zRowEnd(1), 6) != m_MainMatrix.zRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.zBegin(), m_MainMatrix.zRowEnd(1), 8) != m_MainMatrix.zRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.zBegin(), m_MainMatrix.zRowEnd(1), -2) == m_MainMatrix.zRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.zBegin(), m_MainMatrix.zRowEnd(1), 10) == m_MainMatrix.zRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getZIterator(1, 3), m_MainMatrix.getZIterator(3, 1), 0) != m_MainMatrix.getZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getZIterator(1, 3), m_MainMatrix.getZIterator(3, 1), -7) != m_MainMatrix.getZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getZIterator(1, 3), m_MainMatrix.getZIterator(3, 1), -2) != m_MainMatrix.getZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getZIterator(1, 3), m_MainMatrix.getZIterator(3, 1), -1) == m_MainMatrix.getZIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getZIterator(1, 3), m_MainMatrix.getZIterator(3, 1), 11) == m_MainMatrix.getZIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getZIterator(1, 3), m_MainMatrix.getZIterator(3, 1), 10) == m_MainMatrix.getZIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getZIterator(1, 3), m_MainMatrix.zEnd(), 0) != m_MainMatrix.zEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getZIterator(1, 3), m_MainMatrix.zEnd(), 11) != m_MainMatrix.zEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getZIterator(1, 3), m_MainMatrix.zEnd(), -2) != m_MainMatrix.zEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.getZIterator(1, 3), m_MainMatrix.zEnd(), -1) == m_MainMatrix.zEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.getZIterator(1, 3), m_MainMatrix.zEnd(), 10) == m_MainMatrix.zEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.zBegin(), m_MainMatrix.getZIterator(3, 1), -1) != m_MainMatrix.getZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.zBegin(), m_MainMatrix.getZIterator(3, 1), -7) != m_MainMatrix.getZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.zBegin(), m_MainMatrix.getZIterator(3, 1), -2) != m_MainMatrix.getZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
    QVERIFY2(find(m_MainMatrix.zBegin(), m_MainMatrix.getZIterator(3, 1), 11) == m_MainMatrix.getZIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    QVERIFY2(find(m_MainMatrix.zBegin(), m_MainMatrix.getZIterator(3, 1), 10) == m_MainMatrix.getZIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

    // other tests
    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};
    IntMatrixZIterator it{find(m_MainMatrix.zBegin(), m_MainMatrix.zEnd(), 4)};
    ++it;
    QVERIFY2(*it == 5, "The iterator doesn't work correctly with std::find, incorrect next element returned");

    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};
    QVERIFY2(find(m_MainMatrix.zBegin(), m_MainMatrix.zEnd(), 10) == m_MainMatrix.zEnd(), "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix");

    it = m_MainMatrix.zBegin();
    while(it != m_MainMatrix.zEnd())
    {
        it = find(it, m_MainMatrix.zEnd(), 9);

        if (it != m_MainMatrix.zEnd())
        {
            *it = 10;
        }
    }
    int expectedNumber{std::count(m_MainMatrix.zBegin(), m_MainMatrix.zEnd(), 10)};
    QVERIFY2(expectedNumber == 3, "The iterator doesn't work properly with std::find, element values haven't been correctly replaced");  
}

void ZIteratorTests::testStdSort()
{
    m_MainMatrix = {4, 5, {
                      -1,  1, 3, 1, 4,
                       5,  9, 8, 0, 6,
                       2, -2, 2, 8, 9,
                      -7,  7, 2, 9, 11
                   }};

    for (int row{0}; row<m_MainMatrix.getNrOfRows(); ++row)
    {
        std::sort(m_MainMatrix.zRowBegin(row), m_MainMatrix.zRowEnd(row));
    }

    QVERIFY2(m_MainMatrix.at(0, 0) == -1 && m_MainMatrix.at(0, 1) == 1 && m_MainMatrix.at(0, 2) == 1 && m_MainMatrix.at(0, 3) == 3 && m_MainMatrix.at(0, 4) == 4 &&
             m_MainMatrix.at(1, 0) ==  0 && m_MainMatrix.at(1, 1) == 5 && m_MainMatrix.at(1, 2) == 6 && m_MainMatrix.at(1, 3) == 8 && m_MainMatrix.at(1, 4) == 9 &&
             m_MainMatrix.at(2, 0) == -2 && m_MainMatrix.at(2, 1) == 2 && m_MainMatrix.at(2, 2) == 2 && m_MainMatrix.at(2, 3) == 8 && m_MainMatrix.at(2, 4) == 9 &&
             m_MainMatrix.at(3, 0) == -7 && m_MainMatrix.at(3, 1) == 2 && m_MainMatrix.at(3, 2) == 7 && m_MainMatrix.at(3, 3) == 9 && m_MainMatrix.at(3, 4) == 11,

             "The iterator objects don't work correctly, the per row sorting has not been done properly");

    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, -2, 2, 8, 9, -7, 7, 2, 9, 11}};

    std::sort(m_MainMatrix.zBegin(), m_MainMatrix.zEnd());

    QVERIFY2(m_MainMatrix.at(0, 0) == -7 && m_MainMatrix.at(0, 1) == -2 && m_MainMatrix.at(0, 2) == -1 && m_MainMatrix.at(0, 3) == 0 && m_MainMatrix.at(0, 4) == 1 &&
             m_MainMatrix.at(1, 0) ==  1 && m_MainMatrix.at(1, 1) ==  2 && m_MainMatrix.at(1, 2) ==  2 && m_MainMatrix.at(1, 3) == 2 && m_MainMatrix.at(1, 4) == 3 &&
             m_MainMatrix.at(2, 0) ==  4 && m_MainMatrix.at(2, 1) ==  5 && m_MainMatrix.at(2, 2) ==  6 && m_MainMatrix.at(2, 3) == 7 && m_MainMatrix.at(2, 4) == 8 &&
             m_MainMatrix.at(3, 0) ==  8 && m_MainMatrix.at(3, 1) ==  9 && m_MainMatrix.at(3, 2) ==  9 && m_MainMatrix.at(3, 3) == 9 && m_MainMatrix.at(3, 4) == 11,

             "The iterator objects don't work correctly, the matrix has not been sorted properly");

    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, (0), 6, 2, -2, 2, 8, 9, -7, (7), 2, 9, 11}};

    std::sort(m_MainMatrix.getZIterator(1, 3), m_MainMatrix.getZIterator(3, 1));

    QVERIFY2(m_MainMatrix.at(0, 0) == -1 && m_MainMatrix.at(0, 1) == 1   && m_MainMatrix.at(0, 2) == 3 && m_MainMatrix.at(0, 3) == 1    && m_MainMatrix.at(0, 4) ==  4 &&
             m_MainMatrix.at(1, 0) ==  5 && m_MainMatrix.at(1, 1) == 9   && m_MainMatrix.at(1, 2) == 8 && m_MainMatrix.at(1, 3) == (-7) && m_MainMatrix.at(1, 4) == -2 &&
             m_MainMatrix.at(2, 0) ==  0 && m_MainMatrix.at(2, 1) == 2   && m_MainMatrix.at(2, 2) == 2 && m_MainMatrix.at(2, 3) == 6    && m_MainMatrix.at(2, 4) ==  8 &&
             m_MainMatrix.at(3, 0) ==  9 && m_MainMatrix.at(3, 1) == (7) && m_MainMatrix.at(3, 2) == 2 && m_MainMatrix.at(3, 3) == 9    && m_MainMatrix.at(3, 4) == 11,

             "The iterator objects don't work correctly, the matrix has not been sorted properly");

    m_MainMatrix = {4, 5, {(-1), 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, (-2), 2, 8, 9, -7, 7, 2, 9, 11}};

    std::sort(m_MainMatrix.zBegin(), m_MainMatrix.getZIterator(2, 1));

    QVERIFY2(m_MainMatrix.at(0, 0) == (-1) && m_MainMatrix.at(0, 1) ==  0  && m_MainMatrix.at(0, 2) == 1 && m_MainMatrix.at(0, 3) == 1 && m_MainMatrix.at(0, 4) == 2 &&
             m_MainMatrix.at(1, 0) ==   3 && m_MainMatrix.at(1, 1) ==   4  && m_MainMatrix.at(1, 2) == 5 && m_MainMatrix.at(1, 3) == 6 && m_MainMatrix.at(1, 4) == 8 &&
             m_MainMatrix.at(2, 0) ==   9 && m_MainMatrix.at(2, 1) == (-2) && m_MainMatrix.at(2, 2) == 2 && m_MainMatrix.at(2, 3) == 8 && m_MainMatrix.at(2, 4) == 9 &&
             m_MainMatrix.at(3, 0) ==  -7 && m_MainMatrix.at(3, 1) ==   7  && m_MainMatrix.at(3, 2) == 2 && m_MainMatrix.at(3, 3) == 9 && m_MainMatrix.at(3, 4) == 11,

             "The iterator objects don't work correctly, the matrix has not been sorted properly");

    m_MainMatrix = {4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, (-2), 2, 8, 9, -7, 7, 2, 9, 11}};

    std::sort(m_MainMatrix.getZIterator(2, 1), m_MainMatrix.zEnd());

    QVERIFY2(m_MainMatrix.at(0, 0) == -1 && m_MainMatrix.at(0, 1) == 1    && m_MainMatrix.at(0, 2) ==  3  && m_MainMatrix.at(0, 3) == 1 && m_MainMatrix.at(0, 4) == 4 &&
             m_MainMatrix.at(1, 0) ==  5 && m_MainMatrix.at(1, 1) == 9    && m_MainMatrix.at(1, 2) ==  8  && m_MainMatrix.at(1, 3) == 0 && m_MainMatrix.at(1, 4) == 6 &&
             m_MainMatrix.at(2, 0) ==  2 && m_MainMatrix.at(2, 1) == (-7) && m_MainMatrix.at(2, 2) == -2  && m_MainMatrix.at(2, 3) == 2 && m_MainMatrix.at(2, 4) == 2 &&
             m_MainMatrix.at(3, 0) ==  7 && m_MainMatrix.at(3, 1) == 8    && m_MainMatrix.at(3, 2) ==  9  && m_MainMatrix.at(3, 3) == 9 && m_MainMatrix.at(3, 4) == 11,

             "The iterator objects don't work correctly, the matrix has not been sorted properly");
}

QTEST_APPLESS_MAIN(ZIteratorTests)

#include "tst_ziteratortests.moc"
