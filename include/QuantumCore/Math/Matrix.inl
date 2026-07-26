#include<QuantumCore/Math/Matrix.hpp>

namespace Quantum {
template<typename T, size_t n, size_t m>
Matrix<T, n, m>::Matrix() 
{
    std::fill(data_, data_ + n, T{});
}
template<typename T, size_t n, size_t m>
Matrix<T, n, m>::Matrix(const std::initializer_list<T> values) 
{
    if (values.size() != n * m)
        throw std::invalid_argument("Incorrect number of values!");
    std::copy(values.begin(), values.end(), data_);
}
template<typename T, size_t n, size_t m>
Matrix<T, n, m>::Matrix(const std::initializer_list<std::initializer_list<T>> values) 
{
    if (values.size() != n)
        throw std::invalid_argument("Incorrect number of rows!");

    size_t row = 0;

    for (const auto& r : values)
    {
        if (r.size() != m)
            throw std::invalid_argument("Incorrect number of columns.");

        std::copy(r.begin(), r.end(), data_ + row * m);
        ++row;
    }
}

template<typename T, size_t n, size_t m>
template<typename U>
Matrix<T, n, m>::Matrix(const Matrix<U,n,m>& other)
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

template<typename T, size_t n, size_t m>
constexpr T* Matrix<T, n, m>::data() noexcept
{
    return data_;
}
template<typename T, size_t n, size_t m>
constexpr const T* Matrix<T, n, m>::data() const noexcept
{
    return data_;
}
template<typename T, size_t n, size_t m>
constexpr T* Matrix<T, n, m>:: begin() noexcept
{
    return data_;
}
template<typename T, size_t n, size_t m>
constexpr T* Matrix<T, n, m>:: end() noexcept
{
    return data_ + m * n;
}

template<typename T, size_t n, size_t m>
constexpr const T* Matrix<T, n, m>:: begin() const noexcept
{
    return data_;
}

template<typename T, size_t n, size_t m>
constexpr const T* Matrix<T, n, m>:: end() const noexcept
{
    return data_ + m * n;
}

template<typename T, size_t n, size_t m>
constexpr size_t Matrix<T, n, m>::size() const noexcept
{
    return n*m;
}

template<typename T, size_t n, size_t m>
constexpr size_t Matrix<T, n, m>::rows() const noexcept
{
    return n;
}

template<typename T, size_t n, size_t m>
constexpr size_t Matrix<T, n, m>::cols() const noexcept
{
    return m;
}

template<typename T, size_t n, size_t m>
T Matrix<T, n, m>::getValue(size_t row, size_t col)
{
    if (row >= n) {
        throw std::runtime_error(std::format("Invalid matrix row: {} of {}", row, n));
    }
    if (col >= m) {
        throw std::runtime_error(std::format("Invalid matrix col: {} of {}", col, m));
    }
    return data_[row * m + col];
}
template<typename T, size_t n, size_t m>
T Matrix<T, n, m>::getIndex(size_t index)
{
    if (index >= m * n) {
        throw std::runtime_error(std::format("Invalid matrix ind: {} of {}", index, m*n));
    }
    return data_[index];
}

// template<typename T, size_t n, size_t m>
// void Matrix<T, n, m>::matrixAdd(const Matrix& rhs)
// {

// }
// template<typename T, size_t n, size_t m>
// void Matrix<T, n, m>::matrixSub(const Matrix& rhs)
// {

// }
// template<typename T, size_t n, size_t m>
// void Matrix<T, n, m>::matrixMultiply(const Matrix& rhs)
// {

// }

// template<typename T, size_t n, size_t m>
// template<typename U>
// void Matrix<T, n, m>::matrixScale(U scalar)
// {

// }
}