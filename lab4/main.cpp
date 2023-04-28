#include <iostream>
#include "NotificationQueue.hpp"
#include "QueueAnalyzer.hpp"
#include "Logger.hpp"
#include "Timer.hpp"

using namespace Lab4;
using namespace std::chrono_literals;


int main() {
	NotificationQueue<int> notificationQueue{ 10 };
	QueueAnalyzer<int> queueAnalyzer{ notificationQueue };

	const auto addMessageInterval = [&notificationQueue, timer = Timer()]() {
		LOG("START\n");
		while (timer.getElapsedTime() <= 10000ms) {
			notificationQueue.addMessage({ 3, 100ms, MessagePriority::Low });
			std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000));
		}
	};

	const auto getMessageInterval = [&notificationQueue, timer = Timer()]() {
		LOG("START\n");
		while (timer.getElapsedTime() <= 10000ms) {
			const auto& message = notificationQueue.getMessage();
			std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000));
		}
	};

	std::jthread th1(getMessageInterval);
	std::jthread th2(addMessageInterval);
	std::jthread th3(getMessageInterval);
	std::jthread th4(addMessageInterval);
	std::jthread th5(getMessageInterval);
	std::jthread th6(getMessageInterval);
	return 0;
}
