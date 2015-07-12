#ifndef PISKVORKYSTATE_H
#define	PISKVORKYSTATE_H
#include "../Root.h"
#include "../Game.h"
#include "../Gfx.h"
#include "AbstractGameState.h"

class PiskvorkyState: public AbstractGameState {
public:
	PiskvorkyState(Root &root);	
	~PiskvorkyState();	
	
	void init();	
	void deinit();
	void injectEvent(SDL_Event& evt);
	void renderOneFrame();
	
private:
	SDL_Texture *cross;
	SDL_Texture *circle;
	Game game;
	int cellSize;
	SDL_Point mouse;
};

#endif	/* PISKVORKYSTATE_H */

