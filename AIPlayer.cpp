#include <thread>
#include <chrono>
#include "AIPlayer.h"


AIPlayer::AIPlayer(const CellType &cellType) : Player(cellType) {
	std::thread thread([&]() -> void {
		for(;;) {
			std::this_thread::sleep_for(std::chrono::seconds(3));
			notifyAll(new MoveAction(*(this), rand() % 10, rand() % 10));
		}
	});
	thread.detach();
}
