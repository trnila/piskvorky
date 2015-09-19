#include <SDL_events.h>
#include "NormalPlayer.h"


NormalPlayer::NormalPlayer(CellType cellType, int cellSize) :
	Player(cellType), cellSize(cellSize) {}

void NormalPlayer::injectEvent(SDL_Event& evt) {
	if(evt.type == SDL_MOUSEBUTTONDOWN) {
		int row = evt.motion.x / cellSize;
		int col = evt.motion.y / cellSize;

        notifyAll(new MoveAction(*(this), row, col));
	} else if(evt.type == SDL_QUIT || (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE)) {
		notifyAll(new QuitAction(*(this)));
	}
}