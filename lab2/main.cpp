#include <iostream>
#include "NotificationQueue.hpp"
#include "QueueAnalyzer.hpp"

int main() {
	using namespace Lab2;
	using namespace std::chrono_literals;

	NotificationQueue<int> notificationQueue(7);
	notificationQueue.addMessage(
		{ 1, 5s, MessagePriority::High }
	);
	notificationQueue.addMessage(
		{ 3, 100ms, MessagePriority::Low }
	);
	notificationQueue.addMessage(
		{ 4, 10s, MessagePriority::Medium }
	);
	notificationQueue.addMessage(
		{ 4, 7s, MessagePriority::Low }
	);
	notificationQueue.addMessage(
		{ 0, 10min, MessagePriority::High }
	);
	notificationQueue.addMessage({ 5, 4s });

	QueueAnalyzer<int> queueAnalyzer(notificationQueue);
	queueAnalyzer.analyze("analysis.txt");

	while (!notificationQueue.isEmpty()) {
		const auto& message = notificationQueue.getMessage();
		if (message.has_value()) {
			std::cout << message.value().getData() << '\n';
		}
	}
	return 0;
}
