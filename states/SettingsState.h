#ifndef SETTINGSSTATE_H
#define	SETTINGSSTATE_H
#include "AbstractGameState.h"
#include "../Gfx.h"
#include "../graphics/Font.h"
#include "../graphics/Text.h"
#include "../graphics/Container.h"
#include "../graphics/CheckBox.h"

class SettingsState: public AbstractGameState {
public:
	SettingsState(Window &window);
	void injectEvent(SDL_Event& evt);
	void renderOneFrame();
	
private:
	Container container;
};

#endif	/* SETTINGSSTATE_H */

