#ifndef LAB1_STRING_CONVERTIBLE_HPP
#define LAB1_STRING_CONVERTIBLE_HPP

#include <string>

namespace Lab1
{
	struct StringConvertible
	{
		virtual operator std::string() const noexcept
		{
			return "StringConvertible";
		};

		virtual ~StringConvertible() = default;
	};
}

#endif // !LAB1_STRING_CONVERTIBLE_HPP
