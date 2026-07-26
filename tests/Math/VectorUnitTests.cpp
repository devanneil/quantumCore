#include <gtest/gtest.h>

#include <QuantumCore/Math/Vector.hpp>

TEST(Vector, CompilesAllScalarTypes)
{
    Quantum::Vector<float,4> a;
    Quantum::Vector<double,4> b;
    Quantum::Vector<int,4> c;
}

TEST(Vector, InitializerList)
{
    Quantum::Vector<int,4> V = {1,2,3,4};

    EXPECT_EQ(V.getIndex(0),1);
    EXPECT_EQ(V.getIndex(3),4);
}

TEST(Vector, InvalidInitializer)
{
    EXPECT_THROW(
        (Quantum::Vector<int,2>(
            {1,2,3}
        )),
        std::invalid_argument
    );
}

template<typename From, typename To>
void TestConversion()
{
    Quantum::Vector<From,4> source = {1, 2, 3, 4};

    Quantum::Vector<To,4> converted(source);

    EXPECT_EQ(converted.getIndex(0), static_cast<To>(1));
    EXPECT_EQ(converted.getIndex(1), static_cast<To>(2));
    EXPECT_EQ(converted.getIndex(2), static_cast<To>(3));
    EXPECT_EQ(converted.getIndex(3), static_cast<To>(4));
}
TEST(VectorConversion, IntegerToFloat)
{
    TestConversion<int,float>();
}

TEST(VectorConversion, FloatToDouble)
{
    TestConversion<float,double>();
}

TEST(VectorConversion, DoubleToInt)
{
    TestConversion<double,int>();
}

TEST(Vector, DataPointer)
{
    Quantum::Vector<float,4> Vectorf;
    Vectorf.data();
    Quantum::Vector<double,4> Vectord;
    Vectord.data();
    Quantum::Vector<int,4> Vectorn;
    Vectorn.data();
}
TEST(Vector, BeginEnd)
{
    Quantum::Vector<int,4> Vector = {1, 2, 3, 4};
    for (auto it = Vector.begin(); it != Vector.end(); ++it) {
        *it += 1;
    }
    EXPECT_EQ(Vector.getIndex(0), 2);
    EXPECT_EQ(Vector.getIndex(1), 3);
    EXPECT_EQ(Vector.getIndex(2), 4);
    EXPECT_EQ(Vector.getIndex(3), 5);
}
TEST(Vector, Size)
{
    Quantum::Vector<int,4> Vector = {1, 2, 3, 4};
    EXPECT_EQ(Vector.size(), 4);
}

TEST(Vector, GetIndex)
{
    Quantum::Vector<int,4> Vector = {1, 2, 3, 4};
    EXPECT_EQ(Vector.getIndex(2), 3);
}
TEST(Vector, GetIndexThrows)
{
    Quantum::Vector<int,4> Vector = {1, 2, 3, 4};
    EXPECT_THROW(
        Vector.getIndex(4),
        std::runtime_error
    );
}