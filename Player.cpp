#include <algorithm>
#include "Player.h"


Player::Player(CellType cellType): cellType(cellType) {}

void Player::attach(MoveListener *listener) {
    listeners.push_back(listener);
}

void Player::detach(MoveListener *listener) {
	listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
}

void Player::notifyAll(Action *action) {
    for(auto listener: listeners) {
        listener->onMove(action);
    }
}

CellType Player::getCellType() {
	return cellType;
}

bool Player::isAvailable() {
	return true;
}
