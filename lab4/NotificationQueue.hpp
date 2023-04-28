#ifndef LAB4_NOTIFICATION_QUEUE_HPP
#define LAB4_NOTIFICATION_QUEUE_HPP

#include <algorithm>
#include <deque>
#include <optional>
#include <mutex>
#include <condition_variable>
#include "Message.hpp"
#include "Logger.hpp"

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
			std::unique_lock lock{ m_mutex };

			if (m_data.size() == m_capacity && !cleanupExpiredMessages() && 
				!m_addCondition.wait_for(lock, 500ms, [this]() { return m_data.size() < m_capacity; })) {
				LOG("Queue is full\n");
				return false;
			}

			auto it = std::lower_bound(m_data.begin(), m_data.end(), message,
				[](const auto& left, const auto& right) {
					return static_cast<int>(left.getPriority()) >=
						static_cast<int>(right.getPriority());
				});

			m_data.insert(it, message);

			LOG("Message added to queue\n");

			m_getCondition.notify_one();

			return true;
		}

		std::optional<Message> getMessage() noexcept {
			using namespace std::chrono_literals;
			std::unique_lock lock{ m_mutex };

			while (m_getCondition.wait_for(lock, 500ms, [this]() { return !m_data.empty(); })) {
				auto msg = std::move(m_data.front());
				m_data.pop_front();

				LOG("Message removed from queue\n");

				m_addCondition.notify_one();

				if (msg.isExpired()) {
					continue;
				}

				return msg;
			}

			LOG("Queue is empty\n");

			return {};
		}

	public:
		bool isFull() const noexcept {
			std::lock_guard lock{ m_mutex };
			return m_data.size() >= m_capacity;
		}

		bool isEmpty() const noexcept {
			std::lock_guard lock{ m_mutex };
			return m_data.empty();
		}

		SizeType size() const noexcept {
			std::lock_guard lock{ m_mutex };
			return m_data.size();
		}

		SizeType capacity() const noexcept {
			std::lock_guard lock{ m_mutex };
			return m_capacity;
		}

	private:
		SizeType cleanupExpiredMessages() {
			auto it = std::remove_if(m_data.begin(), m_data.end(),
				[](const auto& left) {
					return left.isExpired();
				});

			const auto numRemoved = std::distance(it, m_data.end());

			m_data.erase(it, m_data.end());

			return numRemoved;
		}

	private:
		std::condition_variable m_getCondition;
		std::condition_variable m_addCondition;
		mutable std::mutex m_mutex;
		SizeType m_capacity;
		Container m_data;
	};
}

#endif // !LAB4_NOTIFICATION_QUEUE_HPP
