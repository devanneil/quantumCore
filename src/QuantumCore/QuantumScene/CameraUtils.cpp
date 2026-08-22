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

Matrix4<float> lookAtMatrix(
    const Vector3<float>& cameraPosition,
    const Vector3<float>& cameraTarget,
    const Vector3<float>& globalUp)
{
    const Vector3<float> forward =
        (cameraPosition - cameraTarget).normalize();

    const Vector3<float> right =
        vectorCrossProduct(globalUp, forward).normalize();

    const Vector3<float> up =
        vectorCrossProduct(forward, right).normalize();

    return Matrix4<float>{
        {right[0],   right[1],   right[2],   0},
        {up[0],      up[1],      up[2],      0},
        {forward[0], forward[1], forward[2], 0},
        {
            -right.dotProduct(cameraPosition),
            -up.dotProduct(cameraPosition),
            -forward.dotProduct(cameraPosition),
            1
        }
    };
}
Matrix4<float> projectionMatrix(
    float fov,
    float aspect,
    float nearPlane,
    float farPlane)
{
    const float f = 1.0f / std::tan(fov * 0.5f);

    return Matrix4<float>{
        {f / aspect, 0, 0, 0},
        {0, f, 0, 0},
        {0, 0,
            (farPlane + nearPlane) / (nearPlane - farPlane),
            -1},
        {0, 0,
            (2.0f * farPlane * nearPlane) /
            (nearPlane - farPlane),
            0}
    };
}

}