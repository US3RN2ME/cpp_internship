#ifndef LAB4_NOTIFICATION_QUEUE_HPP
#define LAB4_NOTIFICATION_QUEUE_HPP

#include <algorithm>
#include <deque>
#include <optional>
#include "Message.hpp"

namespace Lab4 {

	template<class T>
	class NotificationQueue {
		template <class U>
		friend class QueueAnalyzer;

	public:
		using ValueType = T;
		using Message	= Message<ValueType>;
		using Container = std::deque<Message>;
		using SizeType	= typename Container::size_type;

	public:
		explicit NotificationQueue(SizeType capacity)
			: m_capacity{ capacity }
		{ }

		bool addMessage(const Message& message) {
			if (isFull() && !cleanupExpiredMessages()) {
				return false;
			}

			auto it = std::lower_bound(m_data.begin(), m_data.end(), message,
				[](const auto& left, const auto& right) {
					return static_cast<int>(left.getPriority()) >=
						static_cast<int>(right.getPriority());
				});

			m_data.insert(it, message);

			return true;
		}

		std::optional<Message> getMessage() noexcept {
			while (!isEmpty()) {

				auto msg = std::move(m_data.front());
				m_data.pop_front();

				if (msg.isExpired()) {
					continue;
				}

				return msg;
			}
			return {};
		}

		SizeType cleanupExpiredMessages() {
			auto it = std::remove_if(m_data.begin(), m_data.end(),
				[](const auto& left) {
					return left.isExpired();
				});

			m_data.erase(it, m_data.end());

			return std::distance(it, m_data.end());
		}

	public:
		bool isFull() const noexcept {
			return m_data.size() >= m_capacity;
		}

		bool isEmpty() const noexcept {
			return m_data.empty();
		}

		SizeType size() const noexcept {
			return m_data.size();
		}

		SizeType capacity() const noexcept {
			return m_capacity;
		}

	private:
		SizeType m_capacity;
		Container m_data;
	};
}

#endif // !LAB4_NOTIFICATION_QUEUE_HPP
