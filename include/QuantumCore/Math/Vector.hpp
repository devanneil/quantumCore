#pragma once
#define QUANTUM_VECTOR
#include <cstddef>
#include <initializer_list>
#include <algorithm>
#include <utility>
#include <type_traits>
#include <format>
#include <math.h>
using std::size_t;
namespace Quantum {
template<typename T, size_t n>
class Vector
{
public:
    Vector();
    /**
     * @brief Construct a vector from an initializer list
     * 
     * @param values The values to be copied
     * 
     * @throws std::invalid_argument
     * If the length of values is greater than n
     */
    Vector(std::initializer_list<T> values);
    Vector(const Vector& other) = default;
    Vector(Vector&& other) noexcept = default;
    Vector& operator=(const Vector& other) = default;
    Vector& operator=(Vector&& other) noexcept = default;
    /**
     * @brief Construct a vector by converting to another vector type
     * 
     * Each element is converted using static_cast<T>().
     * @tparam U Source element type.
     *
     * @param other Vector to copy.
     */
    template<typename U>
    Vector(const Vector<U,n>& other);

    ~Vector() = default;

    T& operator()(size_t index);
    const T& operator()(size_t index) const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    template<typename U>
    Vector<std::common_type_t<T,U>,n> operator+(const Vector<U,n>& rhs) const;
    template<typename U>
    Vector<std::common_type_t<T,U>,n> operator-(const Vector<U,n>& rhs) const;
    template<typename U>
    Vector<std::common_type_t<T,U>,n> operator*(const Vector<U,n>& rhs) const;
    template<typename U>
    Vector<std::common_type_t<T,U>,n> operator*(U scalar) const;
    template<typename U>
    Vector<T,n>& operator+=(const Vector<U,n>& rhs);
    template<typename U>
    Vector<T,n>& operator-=(const Vector<U,n>& rhs);
    template<typename U>
    Vector<T,n>& operator*=(U scalar);
    template<typename U>
    bool operator==(const Vector<U,n>& rhs) const;

     /**
     * @brief Returns a pointer to the contiguous vector storage.
     *
     * The returned pointer remains valid until the vector is destroyed.
     *
     * @return Pointer to the first vector element.
     */
    constexpr T* data() noexcept;
    /**
     * @brief Returns a const pointer to the vector storage.
     */
    constexpr const T* data() const noexcept;

    /**
     * @brief Returns an iterator to the first element.
     */
    constexpr T* begin() noexcept;
    /**
     * @brief Returns an iterator one past the last element.
     */
    constexpr T* end() noexcept;

    /**
     * @brief Returns a const iterator to the first element.
     */
    constexpr const T* begin() const noexcept;
    /**
     * @brief Returns a const iterator one past the last element.
     */
    constexpr const T* end() const noexcept;

    /**
     * @brief Returns the number of stored elements.
     */
    constexpr size_t size() const noexcept;

    /**
     * @brief Returns the value at the specified index.
     *
     * @param index Index to get value at.
     *
     * @throws std::runtime_error
     * Thrown if index >= size().
     */
    T getIndex(size_t index) const;

    /**
     * @brief Adds two vectors inline
     * 
     * @param rhs Vector to be added
     */
    template<typename U>
    void vectorAdd(const Vector<U,n>& rhs) noexcept;
    /**
     * @brief Subtracts two vectors inline
     * 
     * @param rhs Vector to be subtracted
     */
    template<typename U>
    void vectorSub(const Vector<U,n>& rhs) noexcept;
    /**
     * @brief Computes the hadamard product inline
     * 
     * @param rhs Vector to be multiplied
     */
    template<typename U>
    void hadamardProduct(const Vector<U,n>& rhs) noexcept;
    /**
     * @brief Computes the dot product of 2 vectors
     * 
     * @param rhs Vector to be multiplied
     */
    template<typename U>
    T dotProduct(const Vector<U,n>& rhs) const noexcept;
    /**
     * @brief Scales the vector by a linear scalar
     * 
     * @param scalar Value to be scaled by
     */
    template<typename U>
    void vectorScale(const U scalar) noexcept;

    /**
     * @brief Scales the vector by a linear scalar
     * 
     * @param scalar Value to be scaled by
     */
    template<typename U>
    bool vectorEqual(const Vector<U,n>& rhs) const noexcept;

    double magnitude() const noexcept;
    Vector<T, n> normalize() const;
private:
    T data_[n];
};

template<typename T>
using Vector4 = Vector<T,4>;
template<typename T>
using Vector3 = Vector<T,3>;
template<typename T>
using Vector2 = Vector<T,2>;

template<typename T, typename U>
Vector3<std::common_type_t<T, U>> vectorCrossProduct(const Vector3<T>& lhs, const Vector3<U>& rhs) noexcept;

}

#include "Vector.inl"
