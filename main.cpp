#include <QuantumCore/Math/Matrix.hpp>
#include <iostream>

int main()
{
    Quantum::Matrix<float, 4, 4> mat4;
    Quantum::Matrix4f mat4p;
    std::cout << "Size 1: " << sizeof(mat4) << std::endl;
    std::cout << "Size 2: " << sizeof(mat4p) << std::endl;
}