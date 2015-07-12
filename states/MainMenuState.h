#ifndef MAINMENUSTATE_H
#define	MAINMENUSTATE_H
#include "AbstractGameState.h"
#include "../Root.h"
#include "../Gfx.h"
#include "../graphics/Font.h"
#include "../graphics/Text.h"
#include "../graphics/Container.h"
#include "../graphics/Input.h"

class MainMenuState: public AbstractGameState {
public:
	MainMenuState(Root &root, Font &font);
	void renderOneFrame();
	void injectEvent(SDL_Event &evt);
	
private:
	Container container;
};
#endif	/* MAINMENUSTATE_H */

