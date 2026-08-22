#pragma once
#define QUANTUM_UTILS
#include<QuantumCore/Math/Matrix.hpp>
#include<QuantumCore/Math/Vector.hpp>

#include<math.h>

using std::size_t;
namespace Quantum {

template<typename T>
inline Matrix4<T> RZ(float theta);
template<typename T>
inline Matrix4<T> RY(float theta);
template<typename T>
inline Matrix4<T> RX(float theta);
template<typename T>
inline Matrix4<T> RotationMatrix(float tx, float ty, float tz);
template<typename T>
inline Matrix4<T> TranslationMatrix(float dx, float dy, float dz);
template<typename T>
inline Matrix4<T> TransformationMatrix(float dx, float dy, float dz, float tx, float ty, float tz);
template<typename L, size_t n, size_t m, typename R>
Vector<R, n> rightSideVectorMultiply(const Matrix<L, n, m>& matrix, const Vector<R, m>& vector);
template<typename T>
Matrix4<T> identityMatrix();
}
#include "Utils.inl"
