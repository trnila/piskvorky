#ifndef PISKVORKY_NORMALPLAYER_H
#define PISKVORKY_NORMALPLAYER_H


#include "Player.h"
#include "states/AbstractGameState.h"
#include "Game.h"

class NormalPlayer: public Player {
public:
    NormalPlayer(CellType cellType, int cellSize);
    void injectEvent(SDL_Event & evt);

	virtual void process();

private:
    int cellSize;
};


#endif //PISKVORKY_NORMALPLAYER_H
