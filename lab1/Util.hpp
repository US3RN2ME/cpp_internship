#ifndef LAB1_UTIL_HPP
#define LAB1_UTIL_HPP

#include <type_traits>
#include <string>

namespace Lab1 
{
	template <class T>
	constexpr bool is_bool_v = std::is_same_v<std::remove_cv_t<T>, bool>;

	template <class T>
	constexpr bool is_nonbool_arithmetic_v = std::is_arithmetic_v<T> && !is_bool_v<T>;

	template <class T>
	constexpr bool is_string_convertible_v = std::is_convertible_v<T, std::string>;
}

#endif // !LAB1_UTIL_HPP
