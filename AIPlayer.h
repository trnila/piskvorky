#ifndef PISKVORKY_AIPLAYER_H
#define PISKVORKY_AIPLAYER_H

#include <thread>
#include "Player.h"

class AIPlayer: public Player {
public:
	AIPlayer(const CellType &cellType);

private:
	std::thread thread;

	void process();
};


#endif //PISKVORKY_AIPLAYER_H
