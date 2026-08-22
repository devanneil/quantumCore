#pragma once
#define QUANTUM_CAMERA

#include <QuantumCore/Math/Matrix.hpp>
#include <QuantumCore/Math/Vector.hpp>
#include <QuantumCore/Core/Shader.hpp>

namespace Quantum
{
struct Camera
{
    Matrix4<float> transform;
    std::shared_ptr<Shader> shader;
};

Camera createPinholeCamera(Matrix4<float> transform, float FoV);

Matrix4<float> lookAtMatrix(
    const Vector3<float>& cameraPosition, 
    const Vector3<float>& cameraTarget, 
    const Vector3<float>& globalUp = {0.0, 0.0, 1.0});

Matrix4<float> projectionMatrix(
    float fovY,
    float aspect,
    float nearPlane,
    float farPlane);

}
