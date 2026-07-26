#ifndef QUANTUM_MATRIX
#define QUANTUM_MATRIX
#include <cstddef>
#include <initializer_list>
#include <algorithm>
#include <utility>
#include <type_traits>
#include <format>

using std::size_t;
namespace Quantum {
template<typename T, size_t n, size_t m>
class Matrix {
    public:
    Matrix(); 
    /**
     * @brief Construct a matrix from a flat initializer list.
     *
     * Elements are copied in row-major order.
     *
     * @param values Flat list containing exactly rows()*cols() elements.
     *
     * @throws std::invalid_argument
     * Thrown if the initializer list does not contain exactly
     * rows()*cols() elements.
     */
    Matrix(const std::initializer_list<T> values);
    /**
     * @brief Construct a matrix from nested initializer lists.
     *
     * Each nested list represents a row.
     *
     * @param values Nested initializer lists.
     *
     * @throws std::invalid_argument
     * Thrown if the row or column count does not match the matrix dimensions.
     */
    Matrix(const std::initializer_list<std::initializer_list<T>> values);
    Matrix(const Matrix& other) = default;
    Matrix(Matrix&& other) noexcept = default;
    Matrix& operator=(const Matrix& other) = default;
    Matrix& operator=(Matrix&& other) noexcept = default;
    /**
     * @brief Construct a matrix by converting another matrix type.
     *
     * Each element is converted using static_cast<T>().
     *
     * @tparam U Source element type.
     *
     * @param other Matrix to copy.
     */
    template<typename U>
    Matrix(const Matrix<U,n,m>& other);

    ~Matrix() = default; 

    T& operator()(size_t row, size_t col);
    const T& operator()(size_t row, size_t col) const;
    T& operator[](size_t index);

    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs) const;
    template<typename U>
    Matrix operator*(U scalar) const;

    Matrix& operator+=(const Matrix& rhs);
    template<typename U>
    Matrix& operator*=(U scalar);

    bool operator==(const Matrix& rhs) const;

    /**
     * @brief Returns a pointer to the contiguous matrix storage.
     *
     * The returned pointer remains valid until the matrix is destroyed.
     *
     * @return Pointer to the first matrix element.
     */
    constexpr T* data() noexcept;
    /**
     * @brief Returns a const pointer to the matrix storage.
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
     * @brief Returns the number of matrix rows.
     */
    constexpr size_t rows() const noexcept;

    /**
     * @brief Returns the number of matrix columns.
     */
    constexpr size_t cols() const noexcept;

    
    /**
     * @brief Returns the value at the specified row and column.
     *
     * @param row Zero-based row.
     * @param col Zero-based column.
     *
     * @throws std::runtime_error
     * Thrown if the requested element is outside the matrix.
     */
    T getValue(size_t row, size_t col);
    /**
     * @brief Returns the value at the specified linear index.
     *
     * Elements are stored in row-major order.
     *
     * @param index Linear index.
     *
     * @throws std::runtime_error
     * Thrown if index >= size().
     */
    T getIndex(size_t index);

    void matrixAdd(const Matrix& rhs);
    void matrixSub(const Matrix& rhs);
    void matrixMultiply(const Matrix& rhs);

    template<typename U>
    void matrixScale(U scalar);

    protected:

    private:
    T data_[n*m];
};

using Matrix4f = Matrix<float,4,4>;
using Matrix3f = Matrix<float,3,3>;
using Matrix4d = Matrix<double,4,4>;
using Matrix3d = Matrix<double,3,3>;
using Matrix4n = Matrix<int,4,4>;
using Matrix3n = Matrix<int,3,3>;

}

#include "Matrix.inl"

#endif