#ifndef LAB3_MATRIX_HPP
#define LAB3_MATRIX_HPP

#include <algorithm>
#include <string>
#include <ostream>
#include <exception>

namespace Lab3 {

    template <class T = int>
    class Matrix {
    public:
        using ValueType         = T;
        using Pointer           = T*;
        using ConstPointer      = T* const;
        using ConstPointerConst = const T* const;
        using SizeType          = std::size_t;

    public:
        Matrix() = default;

        Matrix(SizeType rows, SizeType cols) {
            resize(rows, cols);
        }

        ~Matrix() {
            clear();
        }

        Matrix(const Matrix& other) {
            resize(other.rows(), other.cols());
            for (SizeType i = 0; i < m_rows; ++i)
                std::copy(other.m_data[i], other.m_data[i] + other.m_cols, m_data[i]);
        }

        Matrix& operator=(const Matrix& other) {
            if (this != &other) {
                Matrix tmp(other);
                swap(tmp);
            }
            return *this;
        }

        Matrix(Matrix&& other) noexcept {
            swap(other);
        }

        Matrix& operator=(Matrix&& other) noexcept {
            if (this != &other) {
                swap(other);
            }
            return *this;
        }

    public:
        template <class Pred = std::less<ValueType>>
        void sortRows(Pred pred = Pred()) {
            for (SizeType i = 0; i < m_rows; ++i)
                std::sort(m_data[i], m_data[i] + m_cols, pred);
        }

        template <class Pred = std::less<ValueType>>
        void sortCols(Pred pred = Pred()) {
            Matrix transposed(cols(), rows());

            for (SizeType i = 0; i < cols(); ++i)
                for (SizeType j = 0; j < rows(); ++j)
                    transposed[i][j] = m_data[j][i];

            for (SizeType i = 0; i < cols(); ++i)
                std::sort(transposed[i], transposed[i] + rows(), pred);

            for (SizeType i = 0; i < rows(); ++i)
                for (SizeType j = 0; j < cols(); ++j)
                    m_data[i][j] = transposed[j][i];
        }

    public:
        void resize(SizeType rows, SizeType cols) {
            clear();
            m_rows = rows;
            m_cols = cols;
            m_data = new Pointer[rows];
            for (SizeType i = 0; i < rows; ++i) 
                m_data[i] = new ValueType[cols]{};
        }

        void clear() {
            for (SizeType i = 0; i < m_rows; ++i)
                delete[] m_data[i];
            delete[] m_data;

            m_data = nullptr;
            m_rows = 0;
            m_cols = 0;
        }
        
    public:
        SizeType rows() const noexcept {
            return m_rows;
        }

        SizeType cols() const noexcept {
            return m_cols;
        }

    public:
        ConstPointer operator[](SizeType row) {
            return m_data[row];
        }

        ConstPointerConst operator[](SizeType row) const {
            return m_data[row];
        }

    private:
        void swap(Matrix& other) noexcept {
            std::swap(m_rows, other.m_rows);
            std::swap(m_cols, other.m_cols);
            std::swap(m_data, other.m_data);
        }

    private:
        SizeType m_rows{};
        SizeType m_cols{};
        Pointer* m_data{};
    };

    template <>
    class Matrix<std::string> {
    public:
        using ValueType         = std::string::value_type;
        using Pointer           = std::string*;
        using SizeType          = std::size_t;

    public:
        Matrix() = default;

        Matrix(SizeType rows, SizeType cols) {
            resize(rows, cols);
        }

        ~Matrix() {
            clear();
        }

        Matrix(const Matrix& other) {
            resize(other.rows(), other.cols());
            std::copy(other.m_data, other.m_data + other.m_rows, m_data);
        }

        Matrix& operator=(const Matrix& other) {
            if (this != &other) {
                Matrix tmp(other);
                swap(tmp);
            }
            return *this;
        }

        Matrix(Matrix&& other) noexcept {
            swap(other);
        }

        Matrix& operator=(Matrix&& other) noexcept {
            if (this != &other) {
                swap(other);
            }
            return *this;
        }

    public:
        template <class Pred = std::less<ValueType>>
        void sortRows(Pred pred = Pred()) {
            for (SizeType i = 0; i < m_rows; ++i)
                std::sort(m_data[i].begin(), m_data[i].end(), pred);
        }

        template <class Pred = std::less<ValueType>>
        void sortCols(Pred pred = Pred()) {
            Matrix transposed(cols(), rows());

            for (SizeType i = 0; i < cols(); ++i)
                for (SizeType j = 0; j < rows(); ++j)
                    transposed[i][j] = m_data[j][i];

            for (SizeType i = 0; i < cols(); ++i)
                std::sort(transposed[i].begin(), transposed[i].end(), pred);

            for (SizeType i = 0; i < rows(); ++i)
                for (SizeType j = 0; j < cols(); ++j)
                    m_data[i][j] = transposed[j][i];
        }

    public:
        void resize(SizeType rows, SizeType cols) {
            clear();
            m_rows = rows;
            m_data = new std::string[rows];
            for (SizeType i = 0; i < rows; ++i)
                m_data[i].resize(cols, ' ');
        }

        void clear() {
            delete[] m_data;
            m_data = nullptr;
            m_rows = 0;
        }

    public:
        SizeType rows() const noexcept {
            return m_rows;
        }

        SizeType cols() const noexcept {
            return m_rows ? m_data[0].size() : 0;
        }

    public:
        std::string& operator[](SizeType row) {
            return m_data[row];
        }

        const std::string& operator[](SizeType row) const {
            return m_data[row];
        }

    private:
        void swap(Matrix& other) noexcept {
            std::swap(m_rows, other.m_rows);
            std::swap(m_data, other.m_data);
        }

    private:
        SizeType m_rows{};
        Pointer m_data{};
    };

    template <class T>
    auto operator<<(std::ostream& os, const Matrix<T>& matrix) ->
        typename std::enable_if_t<std::is_integral_v<T>, std::ostream&>
    {
        for (size_t i = 0; i < matrix.rows(); ++i) {
            for (size_t j = 0; j < matrix.cols(); ++j)
                os << matrix[i][j] << " ; ";
            os << '\n';
        }
        return os;
    }

    template <class T>
    auto operator<<(std::ostream& os, const Matrix<T>& matrix) ->
        typename std::enable_if_t<!std::is_integral_v<T>, std::ostream&> 
    {
        for (size_t i = 0; i < matrix.rows(); ++i) {
            for (size_t j = 0; j < matrix.cols(); ++j)
                os << matrix[i][j] << " | ";
            os << '\n';
        }
        return os;
    }

    template <class T>
    Matrix<T> operator+(const Matrix<T>& left, const Matrix<T>& right) {
        if (left.cols() != right.cols() || left.rows() != right.rows())
            throw std::invalid_argument("matrix sizes do not match");

        Matrix<T> result(left.rows(), left.cols());
        for (size_t i = 0; i < result.rows(); ++i)
            for (size_t j = 0; j < result.cols(); ++j)
                result[i][j] = left[i][j] + right[i][j];

        return result;
    }

    template <class T>
    Matrix<T> operator-(const Matrix<T>& left, const Matrix<T>& right) {
        if (left.cols() != right.cols() || left.rows() != right.rows())
            throw std::invalid_argument("matrix sizes do not match");

        Matrix<T> result(left.rows(), left.cols());
        for (size_t i = 0; i < result.rows(); ++i)
            for (size_t j = 0; j < result.cols(); ++j)
                result[i][j] = left[i][j] - right[i][j];

        return result;
    }
}

#endif // !LAB3_MATRIX_HPP