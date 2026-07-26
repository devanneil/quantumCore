#ifndef QUANTUM_VECTOR
#define QUANTUM_VECTOR
#include <cstddef>
#include <initializer_list>
#include <algorithm>
#include <utility>
#include <type_traits>
#include <format>

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

    Vector operator+(const Vector& rhs) const;
    Vector operator-(const Vector& rhs) const;
    Vector operator*(const Vector& rhs) const;
    template<typename U>
    Vector operator*(U scalar) const;

    Vector& operator+=(const Vector& rhs);
    template<typename U>
    Vector& operator*=(U scalar);

    bool operator==(const Vector& rhs) const;

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
    T getIndex(size_t index);

    void vectorAdd(const Vector& rhs);
    void vectorSub(const Vector& rhs);
    void hadamardProduct(const Vector& rhs);
    void crossProduct(const Vector& rhs);
    T dotProduct(const Vector& rhs);

    template<typename U>
    void vectorScale(U scalar);
private:
    T data_[n];
};

using Vector3f = Vector<float,3>;
using Vector4f = Vector<float,4>;
using Vector3d = Vector<double,3>;
using Vector4d = Vector<double,4>;
using Vector3n = Vector<int,3>;
using Vector4n = Vector<int,4>;

}

#include "Vector.inl"

#endif