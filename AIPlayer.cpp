#include <thread>
#include <chrono>
#include "AIPlayer.h"


AIPlayer::AIPlayer(const CellType &cellType) : Player(cellType), thread(&AIPlayer::process, this) {}

void AIPlayer::process() {
	for(;;) {
		std::this_thread::sleep_for(std::chrono::seconds(3));
		notifyAll(new MoveAction(*(this), rand() % 10, rand() % 10));
	}
}
