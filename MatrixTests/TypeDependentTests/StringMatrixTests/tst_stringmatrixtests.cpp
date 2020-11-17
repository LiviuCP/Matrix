#include <QtTest>

#include "../../../MatrixLib/matrix.h"
#include "../../../MatrixLib/matrix_template_specializations.h"

using StringMatrix = Matrix<std::string>;

class StringMatrixTests : public QObject
{
    Q_OBJECT

public:
    StringMatrixTests();
    ~StringMatrixTests();

private slots:
    void testBooleanOperator();
    void testMatrixesAreEqual();
    void testMatrixesAreNotEqual();

};

StringMatrixTests::StringMatrixTests()
{

}

StringMatrixTests::~StringMatrixTests()
{

}

void StringMatrixTests::testBooleanOperator()
{
    {
        StringMatrix matrix{};

        QVERIFY2(!matrix, "The boolean operator does not return the correct value");
    }

    {
        StringMatrix matrix{2, 3, {"", "", "", "", "", ""}};

        QVERIFY2(!matrix, "The boolean operator does not return the correct value");
    }

    {
        StringMatrix matrix{2, 3, {"abcD", "-a bcd", "-0.123", " ", "1aBc-", ".A1b2"}};

        QVERIFY2(matrix, "The boolean operator does not return the correct value");
    }

    {
        StringMatrix matrix{2, 3, {"", " ", "", "", "", ""}};

        QVERIFY2(matrix, "The boolean operator does not return the correct value");
    }

    {
        StringMatrix matrix{2, 3, {"", "", "", "", "abc", ""}};

        QVERIFY2(matrix, "The boolean operator does not return the correct value");
    }
}

void StringMatrixTests::testMatrixesAreEqual()
{
    {
        StringMatrix firstMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}};
        StringMatrix secondMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}};

        QVERIFY2(firstMatrix == secondMatrix && secondMatrix == firstMatrix, "Matrixes are not equal");
    }

    {
        StringMatrix matrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}};

        QVERIFY2(matrix == matrix, "The matrix is not equal to itself");
    }

    {
        StringMatrix firstMatrix{};
        StringMatrix secondMatrix{};

        QVERIFY2(firstMatrix == secondMatrix && secondMatrix == firstMatrix, "Matrixes are not equal");
    }

    {
        StringMatrix matrix{};

        QVERIFY2(matrix == matrix, "The matrix is not equal to itself");
    }
}

void StringMatrixTests::testMatrixesAreNotEqual()
{
    {
        StringMatrix firstMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}};
        StringMatrix secondMatrix{2, 3, {"abc", "abde", "-abc", "Abc", "1abc", "-0.8333"}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        StringMatrix firstMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}};
        StringMatrix secondMatrix{2, 2, {"abc", "abdc", "Abc", "1abc"}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        StringMatrix firstMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}};
        StringMatrix secondMatrix{3, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333", "Abc", "c1D", "-A1bE2"}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        StringMatrix firstMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}};
        StringMatrix secondMatrix{3, 2, {"abc", "abdc", "Abc", "1abc", "-abc", "-0.8333"}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        StringMatrix firstMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}};
        StringMatrix secondMatrix{};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }
}

QTEST_APPLESS_MAIN(StringMatrixTests)

#include "tst_stringmatrixtests.moc"
