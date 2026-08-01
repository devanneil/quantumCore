#ifndef QUANTUM_CAMERA
#define QUANTUM_CAMERA

#include <QuantumCore/Math/Matrix.hpp>
#include <QuantumCore/Core/Shader.hpp>

namespace Quantum
{
struct Camera
{
    Matrix4<float> transform;
    std::shared_ptr<Shader> shader;
};

Camera createPinholeCamera(Matrix4<float> transform, float FoV);
}

#endif