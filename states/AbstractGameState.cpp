#include "AbstractGameState.h"

AbstractGameState::AbstractGameState(Root &root): root(root) {
	quit = false;
}

AbstractGameState::~AbstractGameState() {
	deinit();
}

void AbstractGameState::reset() {
	quit = false;
}

bool AbstractGameState::isQuit() {
	return quit;
}

GameStateType AbstractGameState::getNextState() {
	return nextState;
}

void AbstractGameState::setQuit(GameStateType next) {
	this->quit = true;
	this->nextState = next;
}