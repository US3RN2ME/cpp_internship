#ifndef LAB3_MATRIX_HPP
#define LAB3_MATRIX_HPP

#include <utility>

namespace Lab3 {

    template <class T = int>
    class Matrix {
    public:
        using ValueType         = T;
        using Pointer           = T**;
        using ConstPointer      = T* const;
        using ConstPointerConst = const T* const;
        using SizeType          = std::size_t;

    public:
        Matrix(SizeType rows, SizeType cols) {
            resize(rows, cols);
        }

        ~Matrix() {
            clear();
        }

        Matrix(const Matrix& other) {
            resize(other.m_rows, other.m_cols);
            for (SizeType i = 0; i < m_rows; ++i)
                for (SizeType j = 0; j < m_cols; ++j)
                    m_data[i][j] = other.m_data[i][j];
        }

        Matrix& operator=(const Matrix& other) {
            if (this != &other) {
                Matrix tmp(other);
                std::swap(m_rows, tmp.m_rows);
                std::swap(m_cols, tmp.m_cols);
                std::swap(m_data, tmp.m_data);
            }
            return *this;
        }

        Matrix(Matrix&& other) noexcept {
            std::swap(m_rows, other.m_rows);
            std::swap(m_cols, other.m_cols);
            std::swap(m_data, other.m_data);
        }

        Matrix& operator=(Matrix&& other) noexcept {
            if (this != &other) {
                clear();
                std::swap(m_rows, other.m_rows);
                std::swap(m_cols, other.m_cols);
                std::swap(m_data, other.m_data);
            }
            return *this;
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
        SizeType m_rows{};
        SizeType m_cols{};
        Pointer m_data{};
    };
}

#endif // !LAB3_MATRIX_HPP