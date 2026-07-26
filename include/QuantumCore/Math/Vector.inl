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
T Vector<T, n>::getIndex(size_t index)
{
    if (index >= n) {
        throw std::runtime_error(std::format("Invalid Vector ind: {} of {}", index, n));
    }
    return data_[index];
}
};