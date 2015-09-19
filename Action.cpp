#include <stdio.h>
#include "Action.h"

Action::Action(Player &player) : player(player) {}

Player &Action::getPlayer() {
	return player;
}

QuitAction::QuitAction(Player &player) : Action(player) {}
void QuitAction::handle(Game &game) {
    game.reset();
}

MoveAction::MoveAction(Player &player, int x, int y): Action(player), x(x), y(y) {}

void MoveAction::handle(Game &game) {
	if(game.getNextType() == getPlayer().getCellType()) {
		game.step(x, y);
		printf("Moved\n");
	} else {
		printf("Move denied\n");
	}
}
