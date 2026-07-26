#include <gtest/gtest.h>

#include <QuantumCore/Math/Matrix.hpp>


TEST(Matrix, CompilesAllScalarTypes)
{
    Quantum::Matrix<float,4,4> a;
    Quantum::Matrix<double,4,4> b;
    Quantum::Matrix<int,4,4> c;
}

TEST(Matrix, FlatInitializer)
{
    Quantum::Matrix<int,2,2> M =
    {
        1,2,
        3,4
    };

    EXPECT_EQ(M.getValue(0,0),1);
    EXPECT_EQ(M.getValue(1,1),4);
}

TEST(Matrix, NestedInitializer)
{
    Quantum::Matrix<int,2,2> M =
    {
        {1,2},
        {3,4}
    };

    EXPECT_EQ(M.getIndex(0),1);
    EXPECT_EQ(M.getIndex(3),4);
}

TEST(Matrix, InvalidInitializer)
{
    EXPECT_THROW(
        (Quantum::Matrix<int,2,2>(
            {1,2,3}
        )),
        std::invalid_argument
    );
}

TEST(Matrix, InvalidNestedRows)
{
    EXPECT_THROW(
        (Quantum::Matrix<int,2,2>(
            {
                {1,2}
            }
        )),
        std::invalid_argument
    );
}

TEST(Matrix, InvalidNestedColumns)
{
    EXPECT_THROW(
        (Quantum::Matrix<int,2,2>(
            {
                {1},
                {3,4}
            }
        )),
        std::invalid_argument
    );
}

template<typename From, typename To>
void TestConversion()
{
    Quantum::Matrix<From,2,2> source =
    {
        {1,2},
        {3,4}
    };

    Quantum::Matrix<To,2,2> converted(source);

    EXPECT_EQ(converted.getValue(0,0), static_cast<To>(1));
    EXPECT_EQ(converted.getValue(0,1), static_cast<To>(2));
    EXPECT_EQ(converted.getValue(1,0), static_cast<To>(3));
    EXPECT_EQ(converted.getValue(1,1), static_cast<To>(4));
}
TEST(MatrixConversion, IntegerToFloat)
{
    TestConversion<int,float>();
}

TEST(MatrixConversion, FloatToDouble)
{
    TestConversion<float,double>();
}

TEST(MatrixConversion, DoubleToInt)
{
    TestConversion<double,int>();
}

TEST(Matrix, DataPointer)
{
    Quantum::Matrix<float,4,4> matrixf;
    matrixf.data();
    Quantum::Matrix<double,4,4> matrixd;
    matrixd.data();
    Quantum::Matrix<int,4,4> matrixn;
    matrixn.data();
}
TEST(Matrix, BeginEnd)
{
    Quantum::Matrix<int,2,2> matrix = {1, 2, 3, 4};
    for (auto it = matrix.begin(); it != matrix.end(); ++it) {
        *it += 1;
    }
    EXPECT_EQ(matrix.getIndex(0), 2);
    EXPECT_EQ(matrix.getIndex(1), 3);
    EXPECT_EQ(matrix.getIndex(2), 4);
    EXPECT_EQ(matrix.getIndex(3), 5);
}
TEST(Matrix, Size)
{
    Quantum::Matrix<int,2,2> matrix = {1, 2, 3, 4};
    EXPECT_EQ(matrix.size(), 4);
}
TEST(Matrix, Rows)
{
    Quantum::Matrix<int,2,2> matrix = {1, 2, 3, 4};
    EXPECT_EQ(matrix.rows(), 2);
}
TEST(Matrix, Cols)
{
    Quantum::Matrix<int,2,2> matrix = {1, 2, 3, 4};
    EXPECT_EQ(matrix.cols(), 2);
}

TEST(Matrix, GetValue)
{
    Quantum::Matrix<int,2,2> matrix = {1, 2, 3, 4};
    EXPECT_EQ(matrix.getValue(1,0), 3);
}
TEST(Matrix, GetValueThrows)
{
    Quantum::Matrix<int,2,2> matrix = {1, 2, 3, 4};
    EXPECT_THROW(
        matrix.getValue(2,0),
        std::runtime_error
    );
}

TEST(Matrix, GetIndex)
{
    Quantum::Matrix<int,2,2> matrix = {1, 2, 3, 4};
    EXPECT_EQ(matrix.getIndex(2), 3);
}
TEST(Matrix, GetIndexThrows)
{
    Quantum::Matrix<int,2,2> matrix = {1, 2, 3, 4};
    EXPECT_THROW(
        matrix.getIndex(4),
        std::runtime_error
    );
}