#include<QuantumCore/Math/Utils.hpp>

namespace Quantum {
template<typename T>
inline Matrix4<T> RZ(float theta)
{
    return Matrix4<T>
    {
        {cos(theta), -sin(theta), 0, 0},
        {sin(theta), cos(theta), 0 , 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
}
template<typename T>
inline Matrix4<T> RY(float theta)
{
    return Matrix4<T>
    {
        {cos(theta), 0, sin(theta), 0},
        {0, 1, 0, 0},
        {-sin(theta), 0, cos(theta), 0},
        {0, 0, 0, 1}
    };
}
template<typename T>
inline Matrix4<T> RX(float theta)
{
    return Matrix4<T>
    {
        {1, 0, 0, 0},
        {0, cos(theta), -sin(theta), 0},
        {0, -sin(theta), cos(theta), 0},
        {0, 0, 0, 1}
    };
}
template<typename T>
inline Matrix4<T> RotationMatrix(float tx, float ty, float tz)
{
    Matrix4<T> XY = multiplyMatrices(RX<T>(tx), RY<T>(ty));
    return multiplyMatrices(XY, RZ<T>(tz));
}

template<typename T>
inline Matrix4<T> TranslationMatrix(float dx, float dy, float dz)
{
    return Matrix4<T>
    {
        {1, 0, 0, dx},
        {0, 1, 0, dy},
        {0, 0, 1, dz},
        {0, 0, 0, 1}
    };
}

template<typename T>
inline Matrix4<T> TransformationMatrix(float dx, float dy, float dz, float tx, float ty, float tz)
{
    return multiplyMatrices(TranslationMatrix<T>(dx, dy, dz), RotationMatrix<T>(dx, dy, dz));
}

template<typename L, size_t n, size_t m, typename R>
Vector<R, n> rightSideVectorMultiply(const Matrix<L, n, m>& matrix, const Vector<R, m>& vector)
{
    Vector<R, n> result{};

    for (size_t row = 0; row < n; row++)
    {
        R sum = R{};

        for (size_t col = 0; col < m; col++)
        {
            sum += static_cast<R>(matrix(row, col)) * vector[col];
        }

        result[row] = sum;
    }

    return result;
}

template<typename T>
Matrix4<T> identityMatrix()
{
    return Matrix4<T> {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
}
}