#include <gtest/gtest.h>

#include <QuantumCore/Math/Vector.hpp>

TEST(VectorBasicArithmetic, VectorAdd)
{
    Quantum::Vector<float, 4> v1 = {1,2,3,4};
    Quantum::Vector<float, 4> v2 = {1,2,3,4};
    v1.vectorAdd(v2);
    EXPECT_EQ(v1.getIndex(0), 2);
    EXPECT_EQ(v1.getIndex(3), 8);
    EXPECT_EQ(v2.getIndex(0), 1);
}

TEST(VectorBasicArithmetic, VectorSub)
{
    Quantum::Vector<float, 4> v1 = {1,2,3,4};
    Quantum::Vector<float, 4> v2 = {1,2,3,4};
    v1.vectorSub(v2);
    EXPECT_EQ(v1.getIndex(0), 0);
    EXPECT_EQ(v1.getIndex(3), 0);
    EXPECT_EQ(v2.getIndex(0), 1);
}

TEST(VectorBasicArithmetic, HadamardMult)
{
    Quantum::Vector<float, 4> v1 = {1,2,3,4};
    Quantum::Vector<float, 4> v2 = {1,2,3,4};
    v1.hadamardProduct(v2);
    EXPECT_EQ(v1.getIndex(0), 1);
    EXPECT_EQ(v1.getIndex(3), 16);
    EXPECT_EQ(v2.getIndex(0), 1);
}

TEST(VectorBasicArithmetic, DotProduct)
{
    Quantum::Vector<float, 4> v1 = {1,2,3,4};
    Quantum::Vector<float, 4> v2 = {1,2,3,4};
    float result = v1.dotProduct(v2);
    EXPECT_EQ(result, 30);
}

TEST(VectorBasicArithmetic, VectorScale)
{
    Quantum::Vector<float, 4> v1 = {1,2,3,4};
    v1.vectorScale(2.0);
    EXPECT_EQ(v1.getIndex(0), 2);
    EXPECT_EQ(v1.getIndex(3), 8);
}

TEST(VectorBasicArithmetic, TypeConversion)
{
    Quantum::Vector<float, 4> v1 = {1,2,3,4};
    Quantum::Vector<double, 4> v2 = {1,2,3,4};
    v1.vectorAdd(v2);
    v1.vectorSub(v2);
    v1.hadamardProduct(v2);
    v1.vectorScale(0.5);
    float result = v1.dotProduct(v2);
    EXPECT_EQ(result, 50);
}

TEST(VectorOperatorOverloading, TestAll)
{
    Quantum::Vector<float,4> V1 = {1,2,3,4};
    Quantum::Vector<double,4> V2 = {1,2,3,4};
    Quantum::Vector<float,4> result = V1 + V2;
    result = V1 - V2;
    result = V1 * V2;
    V1==V2;
    result = V1 * 2.0;
    result += V1;
    result -= V1;
    result *= 2.0;
}