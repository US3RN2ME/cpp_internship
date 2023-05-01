#ifndef LAB4_QUEUE_ANALYZER_HPP
#define LAB4_QUEUE_ANALYZER_HPP

#include <fstream>
#include <string>
#include <sstream>
#include <mutex>
#include "Util.hpp"
#include "NotificationQueue.hpp"

namespace Lab4 {

	template <class T>
	class QueueAnalyzer {
	public:
		using QueueType = NotificationQueue<T>;

	public:
		explicit QueueAnalyzer(const QueueType& queue) noexcept
			: m_queue{ queue }
		{}

	public:
		void analyze(const std::string& filename) {
			std::stringstream ss;
			ss << "NotificationQueue analysis report:\n";

			ss << "Date: " << currentDateTime() << '\n';

			ss << "Queue size: " << m_queue.size() << " elements, "
				<< queueSizeKb() << " KB\n";

			ss << "Low priority messages percentage: "
				<< countPriorityPercentage(MessagePriority::Low) << "%\n";
			ss << "Medium priority messages percentage: "
				<< countPriorityPercentage(MessagePriority::Medium) << "%\n";
			ss << "High priority messages percentage: "
				<< countPriorityPercentage(MessagePriority::High) << "%\n";

			ss << "Max expiry time difference: " << maxExpiryTimeDiff() << '\n';

			std::lock_guard lock{ m_mutex };
			++m_analyzeCount;
			std::ofstream file{ filename, std::ios::app };
			file << ss.str();
		}

		size_t getAnalyzeCount() const noexcept {
			return m_analyzeCount;
		}

	private:

		double queueSizeKb() const noexcept {
			return m_queue.size() * sizeof(QueueType::Message) / 1024.;
		}

		double countPriorityPercentage(MessagePriority priority) const {
			std::lock_guard lock{ m_queue.m_mutex };
			const auto count = std::count_if(
				m_queue.m_data.begin(), m_queue.m_data.end(),
				[&priority](const auto& left) {
					return static_cast<int>(left.getPriority()) ==
						static_cast<int>(priority);
				});

			return count * 100. / m_queue.m_data.size();
		}

		template <class Duration = std::chrono::milliseconds>
		Duration maxExpiryTimeDiff() const {
			std::lock_guard lock{ m_queue.m_mutex };
			const auto [min, max] = std::minmax_element(
				m_queue.m_data.begin(), m_queue.m_data.end(),
				[](const auto& left, const auto& right) {
					return left.getExpiryTime() < right.getExpiryTime();
				});

			return std::chrono::duration_cast<Duration>(
				(*max).getExpiryTime() - (*min).getExpiryTime());
		}

	private:
		size_t m_analyzeCount{};
		mutable std::mutex m_mutex{};
		const QueueType& m_queue;
	};

	template <typename T>
	QueueAnalyzer(const NotificationQueue<T>&) -> QueueAnalyzer<T>;

}

#endif // !LAB4_QUEUE_ANALYZER_HPP
