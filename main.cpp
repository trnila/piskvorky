#include <cstdlib>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "states/AbstractGameState.h"
#include "states/SettingsState.h"
#include "states/MainMenuState.h"
#include "states/PiskvorkyState.h"
#include <sstream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
int main(int argc, char** argv) {
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
	
	
	Window window(800, 600);
	MainMenuState mainMenu(window);
	PiskvorkyState gameScene(window);
	SettingsState settingsState(window);
	
	SDL_Event evt;

	GameStateType nextState = GameStateType::MainMenu;

	int port = 0;
	std::string host;
	po::options_description desc("Allowed options");
	desc.add_options()
			("help", "produce help message")
			("port", po::value<int>(&port), "port")
			("host", po::value<std::string>(&host), "host")
			;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		std::cout << desc << "\n";
		return 1;
	}

	if(port) {
		if(host.length()) {
			gameScene.newOponent(new NetworkPlayer(CellType::Circle, host, port));
			gameScene.getPlayer1()->setCellType(CellType::Cross);
			window.setTitle("client");
		} else {
			gameScene.newOponent(new NetworkPlayer(CellType::Cross, port));
			window.setTitle("server");
		}

		nextState = GameStateType::Game;
	}


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

			SDL_RenderPresent(window.getRenderer());
		}
		
		nextState = state->getNextState();
		
		state->deinit();
	}
		
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	
	return 0;
}

