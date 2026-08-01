#include<QuantumCore/Scene/Camera.hpp>
#include<QuantumCore/Math/Matrix.hpp>
#include<QuantumCore/Core/Shader.hpp>
namespace Quantum
{
Camera createPinholeCamera(Matrix4<float> transform, float FoV)
{
    Shader pinHoleShader = createPinholeShader(FoV);
    Camera pinHoleCamera;
    pinHoleCamera.shader = std::make_shared<Shader>(pinHoleShader);
    pinHoleCamera.transform = transform;
    return pinHoleCamera;
}
}