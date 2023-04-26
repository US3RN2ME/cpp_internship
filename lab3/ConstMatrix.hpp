#ifndef LAB3_CONST_MATRIX_HPP
#define LAB3_CONST_MATRIX_HPP

#include <type_traits>
#include <ostream>

namespace Lab3 {

	template <class _Ty, std::size_t _Rows, std::size_t _Cols>
	class ConstMatrix {
	public:
		using ValueType			= _Ty;
		using Pointer			= _Ty*;
		using ConstPointer		= _Ty* const;
		using ConstPointerConst = const _Ty* const;
		using SizeType			= std::size_t;
		using Rows				= std::integral_constant<std::size_t, _Rows>;
		using Cols				= std::integral_constant<std::size_t, _Cols>;

	public:
		constexpr ConstMatrix() = default;

		template <typename... _Args, typename = 
			std::enable_if_t<sizeof...(_Args) <= _Rows * _Cols &&
			std::conjunction_v<std::is_convertible<_Args, ValueType>...>>
			>
		constexpr ConstMatrix(_Args&&... args)
			: m_data{ static_cast<ValueType>(args)... }
		{}

	public:
		constexpr ConstPointerConst operator[](SizeType row) const {
			return m_data[row];
		}

		constexpr ConstPointer operator[](SizeType row) {
			return m_data[row];
		}

	public:
		template <class _Pred = std::less<ValueType>>
		constexpr void sortRows(_Pred pred = _Pred()) {
			for (SizeType i = 0; i < _Rows; ++i)
				std::sort(m_data[i], m_data[i] + _Cols, pred);
		}

		template <class _Pred = std::less<ValueType>>
		constexpr void sortCols(_Pred pred = _Pred()) {
			ConstMatrix<_Ty, _Cols, _Rows> transposed;

			for (SizeType i = 0; i < _Cols; ++i)
				for (SizeType j = 0; j < _Rows; ++j)
					transposed[i][j] = m_data[j][i];

			for (SizeType i = 0; i < _Cols; ++i)
				std::sort(transposed[i], transposed[i] + _Rows, pred);

			for (SizeType i = 0; i < _Rows; ++i)
				for (SizeType j = 0; j < _Cols; ++j)
					m_data[i][j] = transposed[j][i];
		}

	public:
		friend std::ostream& operator<<(std::ostream& os, const ConstMatrix& matrix) {
			for (SizeType i = 0; i < ConstMatrix::Rows::value; ++i) {
				for (SizeType j = 0; j < ConstMatrix::Cols::value; ++j)
					if constexpr (std::is_integral_v<ConstMatrix::ValueType>) 
						os << matrix[i][j] << " ; ";
					else 
						os << matrix[i][j] << " | ";
				os << '\n';
			}
			return os;
		}

		friend constexpr ConstMatrix operator+(const ConstMatrix& left, const ConstMatrix& right) {
			ConstMatrix result;
			for (SizeType i = 0; i < ConstMatrix::Rows::value; ++i)
				for (SizeType j = 0; j < ConstMatrix::Cols::value; ++j)
					result[i][j] = left[i][j] + right[i][j];

			return result;
		}

		friend constexpr ConstMatrix operator-(const ConstMatrix& left, const ConstMatrix& right) {
			ConstMatrix result;
			for (SizeType i = 0; i < ConstMatrix::Rows::value; ++i)
				for (SizeType j = 0; j < ConstMatrix::Cols::value; ++j)
					result[i][j] = left[i][j] - right[i][j];

			return result;
		}

	private:
		ValueType m_data[_Rows][_Cols];
	};
}

#endif // !LAB3_CONST_MATRIX_HPP
