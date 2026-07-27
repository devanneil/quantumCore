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
T Matrix<T, n, m>::getValue(size_t row, size_t col) const
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
T Matrix<T, n, m>::getIndex(size_t index) const
{
    if (index >= m * n) {
        throw std::runtime_error(std::format("Invalid matrix ind: {} of {}", index, m*n));
    }
    return data_[index];
}

template<typename T, size_t n, size_t m>
template<typename U>
void Matrix<T, n, m>::matrixAdd(const Matrix<U,n,m>& rhs) noexcept
{
    std::transform(begin(), end(), rhs.begin(), begin(), std::plus<int>());  
}
template<typename T, size_t n, size_t m>
template<typename U>
void Matrix<T, n, m>::matrixSub(const Matrix<U,n,m>& rhs) noexcept
{
    std::transform(begin(), end(), rhs.begin(), begin(), std::minus<int>());  
}
template<typename T, size_t n, size_t m>
template<typename U>
void Matrix<T, n, m>::matrixScale(const U scalar) noexcept
{
    std::transform(begin(), end(), begin(), [scalar](double val) { return static_cast<T>(val * scalar); });
}

template<typename T, size_t n, size_t m>
template<typename U>
bool Matrix<T, n, m>::matrixEqual(const Matrix<U,n,m>& rhs) const noexcept
{
    return std::equal(begin(), end(), rhs.begin(), rhs.end());
}

template<typename T, size_t n, size_t m>
T& Matrix<T, n, m>::operator()(size_t row, size_t col)
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
const T& Matrix<T, n, m>::operator()(size_t row, size_t col) const
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
T& Matrix<T, n, m>::operator[](size_t index)
{
    if (index >= m * n) {
        throw std::runtime_error(std::format("Invalid matrix ind: {} of {}", index, m*n));
    }
    return data_[index];
}

template<typename T, size_t n, size_t m>
template<typename U>
Matrix<std::common_type_t<T,U>, n, m> Matrix<T, n, m>::operator+(const Matrix<U,n,m>& rhs) const
{
    auto result = Matrix<std::common_type_t<T,U>, n, m>(*this);
    result.matrixAdd(rhs);
    return result;
}
template<typename T, size_t n, size_t m>
template<typename U>
Matrix<std::common_type_t<T,U>, n, m> Matrix<T, n, m>::operator-(const Matrix<U,n,m>& rhs) const
{
    auto result = Matrix<std::common_type_t<T,U>, n, m>(*this);
    result.matrixSub(rhs);
    return result;
}
template<typename T, size_t n, size_t m>
template<typename U, size_t b>
Matrix<std::common_type_t<T,U>, n, b> Matrix<T, n, m>::operator*(const Matrix<U, m, b>& rhs) const
{
    return multiplyMatrices(*this, rhs);
}
template<typename T, size_t n, size_t m>
template<typename U>
Matrix<T, n, m> Matrix<T, n, m>::operator*(U scalar) const
{
    Matrix<T, n, m> result = *this;
    result.matrixScale(scalar);
    return result;
}

template<typename T, size_t n, size_t m>
template<typename U>
Matrix<T, n, m>& Matrix<T, n, m>::operator+=(const Matrix<U, n, m>& rhs)
{  
    this->matrixAdd(rhs);
    return *this;
}
template<typename T, size_t n, size_t m>
template<typename U>
Matrix<T, n, m>& Matrix<T, n, m>::operator-=(const Matrix<U, n, m>& rhs)
{  
    this->matrixSub(rhs);
    return *this;
}
template<typename T, size_t n, size_t m>
template<typename U>
Matrix<T, n, m>& Matrix<T, n, m>::operator*=(U scalar)
{
    this->matrixScale(scalar);
    return *this;
}

template<typename T, size_t n, size_t m>
template<typename U>
bool Matrix<T, n, m>::operator==(const Matrix<U, n, m>& rhs) const
{
    return this->matrixEqual(rhs);
}



template<typename L, typename R, size_t Rows, size_t Inner, size_t Cols>
Matrix<std::common_type_t<L, R>, Rows, Cols> multiplyMatrices(
    const Matrix<L, Rows, Inner>& lhs, const Matrix<R, Inner, Cols>& rhs)
{
    using T = std::common_type_t<L, R>;

    Matrix<T, Rows, Cols> result;

    for (size_t row = 0; row < Rows; ++row)
    {
        for (size_t col = 0; col < Cols; ++col)
        {
            T sum{};

            for (size_t k = 0; k < Inner; ++k)
            {
                sum += static_cast<T>(lhs(row, k)) * static_cast<T>(rhs(k, col));
            }

            result(row, col) = sum;
        }
    }

    return result;
}
}