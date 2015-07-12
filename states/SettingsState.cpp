#include "SettingsState.h"

SettingsState::SettingsState(Root &root, Font &font): AbstractGameState(root), container(root) {
	Text *header = new Text(root, &font, TextType::Variable);
	header->setText("Settings");
	header->setPosition({100, 100});
	header->setColor({0, 0, 0});

	CheckBox *box = new CheckBox(root);
	box->setPosition({100, 200});


	container.addComponent(header);		
	container.addComponent(box);
}


void SettingsState::injectEvent(SDL_Event& evt) {
	if(evt.type == SDL_KEYDOWN) {
		if(evt.key.keysym.sym == SDLK_ESCAPE) {
			setQuit(GameStateType::MainMenu);
		} else if(evt.key.keysym.sym == SDLK_g) {
			SDL_SetWindowSize(root.window, 100, 100);
		}
	}

	container.injectEvent(evt);
}


void SettingsState::renderOneFrame() {
	SDL_SetRenderDrawColor(root.renderer, 255, 255, 255, 255);
	SDL_RenderClear(root.renderer);

	container.render();
}
