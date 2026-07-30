#include <gtest/gtest.h>

#include <QuantumCore/Math/Matrix.hpp>

TEST(MatrixBasicArithmetic, MatrixAdd)
{
    Quantum::Matrix<float,2,2> M1 = {1, 2, 3, 4};
    Quantum::Matrix<float,2,2> M2 = {1, 2, 3, 4};
    M1.matrixAdd(M2);
    EXPECT_EQ(M1.getIndex(0), 2);
    EXPECT_EQ(M1.getIndex(3), 8);
    EXPECT_EQ(M2.getIndex(0), 1);
}

TEST(MatrixBasicArithmetic, MatrixSub)
{
    Quantum::Matrix<float,2,2> M1 = {1, 2, 3, 4};
    Quantum::Matrix<float,2,2> M2 = {1, 2, 3, 4};
    M1.matrixSub(M2);
    EXPECT_EQ(M1.getIndex(0), 0);
    EXPECT_EQ(M1.getIndex(3), 0);
    EXPECT_EQ(M2.getIndex(0), 1);
}

TEST(MatrixBasicArithmetic, MatrixScale)
{
    Quantum::Matrix<float,2,2> M1 = {1, 2, 3, 4};
    M1.matrixScale(2.0);
    EXPECT_EQ(M1.getIndex(0), 2);
    EXPECT_EQ(M1.getIndex(3), 8);
}

TEST(MatrixBasicArithmetic, TypeConversions)
{
    Quantum::Matrix<float,2,2> M1 = {1,2,3,4};
    Quantum::Matrix<double,2,2> M2 = {1,2,3,4};
    M1.matrixAdd(M2);
    M1.matrixSub(M2);
    M1.matrixScale(0.5);
    EXPECT_EQ(M1.getIndex(3), 2);
}

TEST(MatrixBasicArithmetic, MatrixMultiply)
{
    Quantum::Matrix<float,2,2> M1 = {1,2,3,4};
    Quantum::Matrix<double,2,2> M2 = {1,2,3,4};
    Quantum::Matrix<float,2,2> result = Quantum::multiplyMatrices(M1,M2);
    EXPECT_EQ(result.getIndex(0), 7);
    EXPECT_EQ(M1.getIndex(0), 1);
}

TEST(MatrixOperatorOverloading, TestAll)
{
    Quantum::Matrix<float,2,2> M1 = {1,2,3,4};
    Quantum::Matrix<double,2,2> M2 = {1,2,3,4};
    Quantum::Matrix<float,2,2> result = M1 + M2;
    result = M1 - M2;
    result = M1 * M2;
    [[maybe_unused]] bool tmp = M1==M2;
    result = M1 * 2.0;
    result += M1;
    result -= M1;
    result *= 2.0;
}