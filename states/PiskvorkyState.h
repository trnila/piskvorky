#ifndef PISKVORKYSTATE_H
#define	PISKVORKYSTATE_H
#include "../Game.h"
#include "../Gfx.h"
#include "AbstractGameState.h"
#include "../Player.h"
#include "../NetworkPlayer.h"

class PiskvorkyState: public AbstractGameState, MoveListener {
public:
	PiskvorkyState(Window &window);	
	~PiskvorkyState();	
	
	void init();
	void deinit();

	void setPlayer2(Player* player) {
		player2 = player;
		player2->attach(this);
		player1->attach((NetworkPlayer*) player2);
	}

	Player* getPlayer1() {
		return player1;
	}


private:
	virtual void onMove(Action *action);

	virtual void injectEvent(SDL_Event &evt) override;

    void renderOneFrame();
	
private:
	SDL_Texture *cross;
	SDL_Texture *circle;
	Game game;
	int cellSize;
	SDL_Point mouse;
    Player *player1;
    Player *player2;
};

#endif	/* PISKVORKYSTATE_H */

