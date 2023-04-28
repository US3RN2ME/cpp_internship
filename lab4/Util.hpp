#ifndef LAB4_UTIL_HPP
#define LAB4_UTIL_HPP

#include <chrono>
#include <format>
#include <string>

namespace Lab4 {

	using Clock = std::chrono::steady_clock;
	using TimePoint = std::chrono::time_point<Clock>;

	std::string currentDateTime() {
		const auto time = std::chrono::current_zone()->to_local(
			std::chrono::system_clock::now());
		return std::format("{:%Y-%m-%d %X}", time);
	}

}

#endif // !LAB4_UTIL_HPP
