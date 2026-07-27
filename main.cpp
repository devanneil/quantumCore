#include <QuantumCore/Math/Matrix.hpp>
#include <QuantumCore/Math/Vector.hpp>
#include <QuantumCore/Math/Utils.hpp>
#include <iostream>

int main()
{
    Quantum::Matrix4f M1 {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    Quantum::Matrix4f M2 {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    Quantum::Matrix4f M3 = Quantum::multiplyMatrices(M1,M2);
}