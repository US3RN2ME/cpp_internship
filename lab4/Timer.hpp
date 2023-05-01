#ifndef LAB4_TIMER_HPP
#define LAB4_TIMER_HPP

#include "Util.hpp"

namespace Lab4 {

	class Timer {
	public:
		Timer() noexcept {
			restart();
		}

	public:
		void restart() noexcept {
			last = Clock::now();
		}

		template <typename Duration = std::chrono::milliseconds>
		Duration getElapsedTime() const noexcept {
			return std::chrono::duration_cast<Duration>(Clock::now() - last);
		}

	private:
		TimePoint last;
	};

}

#endif // !LAB4_TIMER_HPP
