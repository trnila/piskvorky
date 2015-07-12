#include <cstdlib>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_events.h>
#include <SDL/SDL_image.h>
#include "states/AbstractGameState.h"
#include "states/SettingsState.h"
#include "states/MainMenuState.h"
#include "states/PiskvorkyState.h"
#include "Gfx.h"
#include "Root.h"
#include "Game.h"
#include <sstream>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>


int main(int argc, char** argv) {
	Root root;
	root.width = 800;
	root.height = 800;
	
	srand(time(NULL));

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	
	 	
	// load support for the JPG and PNG image formats
	int flags=IMG_INIT_JPG|IMG_INIT_PNG;
	int initted=IMG_Init(flags);
	if(initted&flags != flags) {
		printf("IMG_Init: Failed to init required jpg and png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
		// handle error
	}
	
	
	
	if (TTF_Init() != 0){
		SDL_Quit();
		return 1;
	}
	
	
	root.window = SDL_CreateWindow("Piskvorky", 100, 100, root.width, root.height, SDL_WINDOW_SHOWN);
	if (root.window == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	
	root.renderer = SDL_CreateRenderer(root.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (root.renderer == nullptr){
		SDL_DestroyWindow(root.window);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	
	TTF_Font *font = TTF_OpenFont("/usr/share/fonts/TTF/Vera.ttf", 50);
	if (font == nullptr){
		std::cout << "OPENFONT" << TTF_GetError();
		return 0;
	}
	
	
	Font f(&root, font);
		
	MainMenuState mainMenu(root, f);
	PiskvorkyState gameScene(root);
	SettingsState settingsState(root, f);
	
	SDL_Event evt;
	
	
	Text fps(root, &f, TextType::Fixed);
	fps.setColor({255, 0, 0});
	fps.setPosition({0, 0});
	
	int fps_lasttime = SDL_GetTicks();
	int fps_frames = 0;
	
	GameStateType nextState = GameStateType::MainMenu;
	while(nextState != GameStateType::Quit) {
		AbstractGameState *state;
		
		switch(nextState) {
			case GameStateType::MainMenu:
				state = &mainMenu;
				break;
			case GameStateType::Game:
				state = &gameScene;
				break;				
			case GameStateType::Settings:
				state = &settingsState;
				break;
		}
			
		state->reset();
		state->init();
			
		while(!state->isQuit()) {
			while(SDL_PollEvent(&evt)) {
				if(evt.type == SDL_QUIT) {
					exit(1);
					break;
				} else {
					state->injectEvent(evt);
				}
			}
			
			state->renderOneFrame();
			
			fps_frames++;
			if (fps_lasttime < SDL_GetTicks() - 1*1000) {
				fps_lasttime = SDL_GetTicks();
				
				std::stringstream out;
				out << fps_frames;
				
				fps.setText(out.str());				
				fps_frames = 0;
			}
			
			fps.render();
			SDL_RenderPresent(root.renderer);
		}
		
		nextState = state->getNextState();
		
		state->deinit();
	}
		
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	
	return 0;
}

