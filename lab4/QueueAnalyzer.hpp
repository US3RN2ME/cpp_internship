#ifndef LAB4_QUEUE_ANALYZER_HPP
#define LAB4_QUEUE_ANALYZER_HPP

#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
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
		void analyze(std::string filename) const {
			std::ofstream file(filename);

			auto t = std::time(nullptr);
			auto tm = *std::localtime(&t);

			file << "NotificationQueue analysis report:\n";

			file << "Date: " << std::put_time(&tm, "%d-%m-%Y %H:%M:%S") << '\n';

			file << "Queue size: " << m_queue.size() << " elements, "
				<< queueSizeKb() << " KB\n";

			file << "Low priority messages percentage: "
				<< countPriorityPercentage(MessagePriority::Low) << "%\n";
			file << "Medium priority messages percentage: "
				<< countPriorityPercentage(MessagePriority::Medium) << "%\n";
			file << "High priority messages percentage: "
				<< countPriorityPercentage(MessagePriority::High) << "%\n";

			file << "Max expiry time difference: " << maxExpiryTimeDiff<std::chrono::seconds>().count() << "s\n";
		}

	private:

		double queueSizeKb() const noexcept {
			return m_queue.size() * sizeof(QueueType::Message) / 1024.;
		}

		double countPriorityPercentage(MessagePriority priority) const {
			const auto count = std::count_if(
				m_queue.m_data.begin(), m_queue.m_data.end(),
				[&priority](const auto& left) {
					return static_cast<int>(left.getPriority()) ==
						static_cast<int>(priority);
				});

			return count * 100. / m_queue.size();
		}

		template <class Duration>
		Duration maxExpiryTimeDiff() const {
			const auto [min, max] = std::minmax_element(
				m_queue.m_data.begin(), m_queue.m_data.end(),
				[](const auto& left, const auto& right) {
					return left.getExpiryTime() < right.getExpiryTime();
				});

			return std::chrono::duration_cast<Duration>(
				(*max).getExpiryTime() - (*min).getExpiryTime());
		}

	private:
		const QueueType& m_queue;
	};
}

#endif // !LAB4_QUEUE_ANALYZER_HPP
