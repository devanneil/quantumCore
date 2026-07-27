#include<QuantumCore/Math/Vector.hpp>

namespace Quantum {
template<typename T, size_t n>
Vector<T, n>::Vector()
{
    std::fill(data_, data_ + n, T{});
}
template<typename T, size_t n>
Vector<T, n>::Vector(const std::initializer_list<T> values) 
{
    std::fill(data_, data_ + n, T{});
    if (values.size() > n)
        throw std::invalid_argument("Incorrect number of values!");
    std::copy(values.begin(), values.end(), data_);
}

template<typename T, size_t n>
template<typename U>
Vector<T, n>::Vector(const Vector<U,n>& other)
{
    std::transform(
        other.begin(),
        other.end(),
        data_,
        [](const U& value)
        {
            return static_cast<T>(value);
        });
}

template<typename T, size_t n>
constexpr T* Vector<T, n>::data() noexcept
{
    return data_;
}
template<typename T, size_t n>
constexpr const T* Vector<T, n>::data() const noexcept
{
    return data_;
}
template<typename T, size_t n>
constexpr T* Vector<T, n>:: begin() noexcept
{
    return data_;
}
template<typename T, size_t n>
constexpr T* Vector<T, n>:: end() noexcept
{
    return data_ + n;
}

template<typename T, size_t n>
constexpr const T* Vector<T, n>:: begin() const noexcept
{
    return data_;
}

template<typename T, size_t n>
constexpr const T* Vector<T, n>:: end() const noexcept
{
    return data_ + n;
}

template<typename T, size_t n>
constexpr size_t Vector<T, n>::size() const noexcept
{
    return n;
}

template<typename T, size_t n>
T Vector<T, n>::getIndex(size_t index) const
{
    if (index >= n) {
        throw std::runtime_error(std::format("Invalid Vector ind: {} of {}", index, n));
    }
    return data_[index];
}

template<typename T, size_t n>
template<typename U>
void Vector<T, n>::vectorAdd(const Vector<U,n>& rhs) noexcept
{
    std::transform(begin(), end(), rhs.begin(), begin(), std::plus<int>());  
}
template<typename T, size_t n>
template<typename U>
void Vector<T, n>::vectorSub(const Vector<U,n>& rhs) noexcept
{
    std::transform(begin(), end(), rhs.begin(), begin(), std::minus<int>());  
}
template<typename T, size_t n>
template<typename U>
void Vector<T, n>::hadamardProduct(const Vector<U,n>& rhs) noexcept
{
    std::transform(begin(), end(), rhs.begin(), begin(), std::multiplies<int>());  
}
template<typename T, size_t n>
template<typename U>
const T Vector<T, n>::dotProduct(const Vector<U,n>& rhs) noexcept
{
    T dot_product = std::transform_reduce(begin(), end(), rhs.begin(), 0.0);
    return dot_product;
}

template<typename T, size_t n>
template<typename U>
void Vector<T, n>::vectorScale(const U scalar) noexcept
{
    std::transform(begin(), end(), begin(), [scalar](double val) { return static_cast<T>(val * scalar); });
}

template<typename T, size_t n>
template<typename U>
bool Vector<T, n>::vectorEqual(const Vector<U,n>& rhs) const noexcept
{
    return std::equal(begin(), end(), rhs.begin(), rhs.end());
}

template<typename T, size_t n>
T& Vector<T, n>::operator()(size_t index)
{
    if (index >= n) {
        throw std::runtime_error(std::format("Invalid Vector ind: {} of {}", index, n));
    }
    return data_[index];
}
template<typename T, size_t n>
const T& Vector<T, n>::operator()(size_t index) const
{
    if (index >= n) {
        throw std::runtime_error(std::format("Invalid Vector ind: {} of {}", index, n));
    }
    return data_[index];
}
template<typename T, size_t n>
T& Vector<T, n>::operator[](size_t index)
{
    if (index >= n) {
        throw std::runtime_error(std::format("Invalid Vector ind: {} of {}", index, n));
    }
    return data_[index];
}
template<typename T, size_t n>
const T& Vector<T, n>::operator[](size_t index) const
{
    if (index >= n) {
        throw std::runtime_error(std::format("Invalid Vector ind: {} of {}", index, n));
    }
    return data_[index];
}

template<typename T, size_t n>
template<typename U>
Vector<std::common_type_t<T,U>,n> Vector<T, n>::operator+(const Vector<U,n>& rhs) const
{
    auto result = Vector<std::common_type_t<T,U>,n>(*this);
    result.vectorAdd(rhs);
    return result;
}
template<typename T, size_t n>
template<typename U>
Vector<std::common_type_t<T,U>,n> Vector<T, n>::operator-(const Vector<U,n>& rhs) const
{
    auto result = Vector<std::common_type_t<T,U>,n>(*this);
    result.vectorSub(rhs);
    return result;
}
template<typename T, size_t n>
template<typename U>
Vector<std::common_type_t<T,U>,n> Vector<T, n>::operator*(const Vector<U,n>& rhs) const
{
    auto result = Vector<std::common_type_t<T,U>,n>(*this);
    result.hadamardProduct(rhs);
    return result;
}
template<typename T, size_t n>
template<typename U>
Vector<std::common_type_t<T,U>,n> Vector<T, n>::operator*(U scalar) const
{
    auto result = Vector<std::common_type_t<T,U>,n>(*this);
    result.vectorScale(scalar);
    return result;
}

template<typename T, size_t n>
template<typename U>
Vector<T,n>& Vector<T, n>::operator+=(const Vector<U,n>& rhs)
{
    this->vectorAdd(rhs);
    return *this;
}
template<typename T, size_t n>
template<typename U>
Vector<T,n>& Vector<T, n>::operator-=(const Vector<U,n>& rhs)
{
    this->vectorAdd(rhs);
    return *this;
}
template<typename T, size_t n>
template<typename U>
Vector<T,n>& Vector<T, n>::operator*=(U scalar)
{
    this->vectorScale(scalar);
    return *this;
}

template<typename T, size_t n>
template<typename U>
bool Vector<T, n>::operator==(const Vector<U,n>& rhs) const
{
    return this->vectorEqual(rhs);
}
};