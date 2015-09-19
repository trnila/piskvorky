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

	Player* getPlayer1() {
		return human;
	}

	void newOponent(Player *oponent);

private:
	virtual void onMove(Action *action);
	virtual void injectEvent(SDL_Event &evt) override;
    void renderOneFrame();

	SDL_Texture *cross;
	SDL_Texture *circle;
	Game game;
	int cellSize;
	SDL_Point mouse;
    Player *human;
    Player *oponent;
};

#endif	/* PISKVORKYSTATE_H */

