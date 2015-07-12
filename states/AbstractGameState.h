#ifndef ABSTRACTGAMESTATE_H
#define	ABSTRACTGAMESTATE_H

#include "../Root.h"

enum class GameStateType {MainMenu, Game, Settings, Quit};

class AbstractGameState {
public:
	AbstractGameState(Root &root);
	virtual ~AbstractGameState();
		
	virtual void renderOneFrame() = 0;
	virtual void injectEvent(SDL_Event &evt) {}
	virtual void init() {}
	virtual void deinit() {}
	
	void reset();
	bool isQuit();
	GameStateType getNextState();
	
protected:
	Root &root;
	void setQuit(GameStateType next);
private:
	GameStateType nextState;
	bool quit;
};

#endif	/* ABSTRACTGAMESTATE_H */

