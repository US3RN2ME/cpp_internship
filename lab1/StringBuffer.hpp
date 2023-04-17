#ifndef LAB1_STRING_BUFFER_HPP
#define LAB1_STRING_BUFFER_HPP

#include <iomanip>
#include <sstream>
#include "Util.hpp"

namespace Lab1 
{
	struct StringBuffer
	{
	public:
		explicit StringBuffer(const char separator = '\n') noexcept
			: m_separator{ separator }
			, m_buffer{ }
		{}

	public:
		std::string getBuffer() const noexcept
		{
			return m_buffer.str();
		}

	public:
		template <class T>
		auto operator += (const T& value) ->
			typename std::enable_if_t<is_bool_v<T>, StringBuffer&>
		{
			m_buffer << "B:" << std::boolalpha << value << m_separator;
			return *this;
		}

		template <class T>
		auto operator += (const T& value) ->
			typename std::enable_if_t<is_nonbool_arithmetic_v<T>, StringBuffer&>
		{
			m_buffer << "Ar:" << value << m_separator;
			return *this;
		}

		template <class T>
		auto operator += (const T& value) ->
			typename std::enable_if_t<is_string_convertible_v<T>, StringBuffer&>
		{
			m_buffer << "CTS:" << static_cast<std::string>(value) << m_separator;
			return *this;
		}

	private:
		const char m_separator;
		std::stringstream m_buffer;
	};
}

#endif // !LAB1_STRING_BUFFER_HPP
