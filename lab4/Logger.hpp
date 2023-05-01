#ifndef LAB4_LOGGER_HPP
#define LAB4_LOGGER_HPP

#include <fstream>
#include <sstream>
#include <thread>
#include <mutex>
#include "Util.hpp"

namespace Lab4 {

	class Logger {
	private:
		Logger() = default;

	public:
		static Logger& instance() noexcept {
			static Logger logger;
			return logger;
		}

		template<typename ...Args>
		void log(Args&& ...args) {
			std::stringstream ss;
			ss << '[' << currentDateTime() << "]\t";
			ss << '[' << std::this_thread::get_id() << "]\t";
			(ss << ... << args);
			
			std::lock_guard lock{ m_mutex };
			m_file << ss.str() << '\n';
		}

	private:
		std::ofstream m_file{ "log.txt", std::ios_base::app };
		std::mutex m_mutex{};
	};

}

#define LOG(...) \
    Lab4::Logger::instance().log('[', __FUNCTION__, ':', __LINE__, "]\t", __VA_ARGS__)

#endif // !LAB4_LOGGER_HPP
