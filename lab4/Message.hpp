#ifndef LAB4_MESSAGE_HPP
#define LAB4_MESSAGE_HPP

#include "Util.hpp"

namespace Lab4 {

	enum class MessagePriority {
		Low,
		Medium,
		High
	};

	template<class T>
	class Message {
	public:
		using ValueType = T;
		using Priority	= MessagePriority;

	public:
		Message(const ValueType& data, const TimePoint& expiryTime, Priority priority = Priority::Medium)
			: m_priority{ priority }
			, m_data{ data }
			, m_expiryTime{ expiryTime }
		{}

		template <class Duration>
		Message(const ValueType& data, const Duration& duration, Priority priority = Priority::Medium)
			: m_priority{ priority }
			, m_data{ data }
			, m_expiryTime{ Clock::now() + duration }
		{}

	public:
		bool isExpired() const noexcept {
			return Clock::now() >= m_expiryTime;
		}

		Priority getPriority() const noexcept {
			return m_priority;
		}

		ValueType getData() const noexcept {
			return m_data;
		}

		TimePoint getExpiryTime() const noexcept {
			return m_expiryTime;
		}

	private:
		Priority m_priority;
		ValueType m_data;
		TimePoint m_expiryTime;
	};
}

#endif // !LAB4_MESSAGE_HPP
