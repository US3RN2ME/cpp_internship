#include <type_traits>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


int main()
{
	StringConvertible Sstring;
	std::string string = "string_first";

	StringBuffer SBuffer;		// buffer = ""
	SBuffer += string;			// buffer = "CTS:string_first"
	SBuffer += 42;				// buffer = "CTS:string_first Ar:42"
	SBuffer += 4.2;				// buffer = "CTS:string_first Ar:42 Ar:4.2"
	SBuffer += -42424224244242;	// buffer = "CTS:string_first Ar:42 Ar:4.2 Ar:-42424224244242"
	SBuffer += Sstring;			// buffer = "CTS:string_first Ar:42 Ar:4.2 Ar:-42424224244242 CTS:StringConvertible"
	SBuffer += false;			// buffer = "CTS:string_first Ar:42 Ar:4.2 Ar:-42424224244242 CTS:StringConvertible B:false"

	std::cout << SBuffer.getBuffer() << std::endl;

	// CTS - Convert To String template overload
	// Ar  - Arithmetic template overload
	// B   - Boolean template overload

	return 0;
}
