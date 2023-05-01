#include "NotificationQueue.hpp"
#include "QueueAnalyzer.hpp"
#include "Logger.hpp"
#include "Timer.hpp"
#include "Random.hpp"

using namespace Lab4;
using namespace std::chrono_literals;

int main() {
	NotificationQueue<int> notificationQueue{ 10 };
	QueueAnalyzer<int> queueAnalyzer{ notificationQueue };

	constexpr auto duration = 5min;

	const auto addOrGetMessage = [&notificationQueue]() {
		Timer timer;
		while (timer.getElapsedTime() <= duration) {
			if (Random::nextInt(0, 1)) {
				notificationQueue.addMessage({
					Random::nextInt(0, 1000),
					std::chrono::milliseconds(Random::nextInt(100, 1000)),
					static_cast<MessagePriority>(Random::nextInt(0, 3))
				});
			}
			else {
				notificationQueue.getMessage();
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(Random::nextInt(500, 2000)));
		}
	};

	const auto getMessage = [&notificationQueue]() {
		Timer timer;
		while (timer.getElapsedTime() <= duration) {
			notificationQueue.getMessage();
			std::this_thread::sleep_for(1s);
		}

	};

	const auto analyze = [&queueAnalyzer, &notificationQueue]() {
		Timer timer;
		auto last = Clock::now();
		while (timer.getElapsedTime() <= duration) {
			if (notificationQueue.isFull() || Clock::now() - last >= 1min) {
				last = Clock::now();
				queueAnalyzer.analyze("analysis.txt");
			}
			std::this_thread::sleep_for(1s);
		}
	};

	{
		std::jthread th1(addOrGetMessage);
		std::jthread th2(addOrGetMessage);
		std::jthread th3(addOrGetMessage);
		std::jthread th4(getMessage);
		std::jthread th5(analyze);
	}

	LOG("AnalyzeCount: ", queueAnalyzer.getAnalyzeCount(), '\n');
	
	return 0;
}
