#include "SettingsState.h"
#include "../graphics/CheckBox.h"

SettingsState::SettingsState(Window &window) : AbstractGameState(window), container(NULL) {
	Text *header = new Text(&container);
	header->setText("Settings");
	header->setColor({0, 0, 0});

	CheckBox *box = new CheckBox(nullptr);
	box->setPosition(100, 200);


	container.addComponent(header);		
	container.addComponent(box);
}


void SettingsState::injectEvent(SDL_Event& evt) {
	if(evt.type == SDL_KEYDOWN) {
		if(evt.key.keysym.sym == SDLK_ESCAPE) {
			setQuit(GameStateType::MainMenu);
		} else if(evt.key.keysym.sym == SDLK_g) {
			//SDL_SetWindowSize(window, 100, 100);
			//TODO: fix
		}
	}

	container.injectEvent(evt);
}


void SettingsState::renderOneFrame() {
	SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(window.getRenderer());

	container.render(window);
}
