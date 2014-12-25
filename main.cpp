#include <cstdlib>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_events.h>
#include "Gfx.h"
#include "Root.h"
#include "Game.h"

SDL_Texture* loadAsTexture(SDL_Renderer *renderer, const char *file) {
	SDL_Surface *surf = IMG_Load(file);
	if(surf == NULL) {
		return NULL;
	}
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	return texture;
}

enum class GameStateType {MainMenu, Game, Quit};

class GameState {
public:
	GameState() {
		quit = false;
	}
	
	virtual void renderOneFrame() = 0;
	virtual void injectEvent(SDL_Event &evt) {}
	virtual void init() {}
	virtual void deinit() {}
	
	void reset() {
		quit = false;
	}
	
	bool isQuit() {
		return quit;
	}
	
	GameStateType getNextState() {
		return nextState;
	}

protected:
	void setQuit(GameStateType next) {
		this->quit = true;
		this->nextState = next;
	}
	
private:
	GameStateType nextState;
	bool quit;
};

class MainMenuState: public GameState {
public:
	MainMenuState(Root &root, Font &font):container(root), root(root) {
		Text *header = new Text(root, &font, TextType::Variable);
		header->setText("Piskvorky");
		header->setPosition({100, 100});
		header->setColor({0, 0, 0});

		Text *newGame = new Text(root, &font, TextType::Variable);
		newGame->setText("new game");
		newGame->setPosition({100, 200});
		newGame->setColor({0, 0, 255});

		Text *quitBtn = new Text(root, &font, TextType::Variable);
		quitBtn->setText("Quit");
		quitBtn->setPosition({100, 300});
		quitBtn->setColor({0, 0, 255});

		Input *i = new Input(root, &font, {400, 400, 100, 100});

		newGame->onClick.push_back([&]() ->  void {
			this->setQuit(GameStateType::Game);
		});

		quitBtn->onClick.push_back([&]() -> void {
			setQuit(GameStateType::Quit);
		});
		
		// move out
		quitBtn->onMouseMoveOut.push_back([=]() -> void{
			quitBtn->setColor({0, 0, 255});
		});
		
		newGame->onMouseMoveOut.push_back([=]() -> void{
			newGame->setColor({0, 0, 255});
		});
		
		// move in
		newGame->onMouseMoveIn.push_back([=]() -> void{
			newGame->setColor({255, 0, 0});
		});
		
		quitBtn->onMouseMoveIn.push_back([=]() -> void{
			quitBtn->setColor({255, 0, 0});
		});
		
		container.addComponent(header);
		container.addComponent(newGame);
		container.addComponent(quitBtn);
		container.addComponent(i);		
	}
	
	void renderOneFrame() {
		SDL_SetRenderDrawColor(root.renderer, 255, 255, 255, 255);
		SDL_RenderClear(root.renderer);
		
		container.render();

		
		SDL_RenderPresent(root.renderer);
	}
	
	void injectEvent(SDL_Event &evt) {
		container.injectEvent(evt);
	}
	
private:
	Root &root;
	Container container;
};

class PiskvorkyState: public GameState {
public:
	PiskvorkyState(Root &root): root(root), game(Game(20, 4)) {
		cross = loadAsTexture(root.renderer, "cross.png");
		circle = loadAsTexture(root.renderer, "circle.png");
		if(cross == NULL || circle == NULL) {
			std::cout << "cross or circle missing!";
			exit(1);
		}

		cellSize = root.width / game.getCount();
	}
	
	void init() {
		SDL_ShowCursor(0);
		game.reset();
	}
	
	void deinit() {
		SDL_ShowCursor(1);
	}
	

	void injectEvent(SDL_Event& evt) {
		if(evt.type == SDL_MOUSEBUTTONDOWN) {
			int row = evt.motion.x / cellSize;
			int col = evt.motion.y / cellSize;

			game.step(row, col);
		} else if(evt.type == SDL_QUIT) {
			setQuit(GameStateType::Quit);
		} else if(evt.type == SDL_MOUSEMOTION) {
			mouse.x = evt.motion.x;
			mouse.y = evt.motion.y;
		} else if(evt.type == SDL_KEYDOWN) {
			if(evt.key.keysym.sym == SDLK_ESCAPE) {
				setQuit(GameStateType::MainMenu);
			}
		}
	}

	void renderOneFrame() {
		SDL_SetRenderDrawColor(root.renderer, 255, 255, 255, 255);
		SDL_RenderClear(root.renderer);

		// redraw lines
		for(int i = 0; i < game.getCount(); i++) {
			SDL_SetRenderDrawColor(root.renderer, 0, 0, 0, 255);
			SDL_RenderDrawLine(root.renderer, 0, cellSize * i, root.width, cellSize * i); 
			SDL_RenderDrawLine(root.renderer, cellSize * i, 0, cellSize*i, root.height);
		}

		// draw circles, crosses
		for(int row = 0; row < game.getCount(); row++) {
			for(int col = 0; col < game.getCount(); col++) {
				SDL_Rect rect;
				rect.w = rect.h = cellSize;
				rect.x = row * cellSize;
				rect.y = col * cellSize;

				if(game.get(row, col) == CellType::Circle) {
					SDL_RenderCopy(root.renderer, circle, NULL, &rect);
				} else if(game.get(row, col) == CellType::Cross) {
					SDL_RenderCopy(root.renderer, cross, NULL, &rect);
				}
			}
		}

		if(game.isWin()) {
			Win win = game.getWin();

			SDL_Point start;
			start.x = win.startRow * cellSize;
			start.y = win.startCol * cellSize;

			SDL_Point end = start;
			if(win.type == WinType::Vertical) {
				end.x = start.x += cellSize / 2;
				end.y += cellSize * win.count;
			} else if(win.type == WinType::Horizontal) {
				end.y = start.y += cellSize / 2;
				end.x += cellSize * win.count;
			} else if(win.type == WinType::MainDiagonal) {
				end.x += cellSize * win.count;
				end.y += cellSize * win.count;
			} else if(win.type == WinType::MinorDiagonal) {
				start.x += cellSize;

				end.x -= cellSize * (win.count - 1);
				end.y += cellSize * win.count;
				//end.x = end.y = 0;
			}

			SDL_SetRenderDrawColor(root.renderer, 0, 0, 0, 255);
			SDL_RenderDrawLine(
				root.renderer,
				start.x,
				start.y,
				end.x,
				end.y				
			);

			if(win.symbol == CellType::Cross) {
				SDL_RenderCopy(root.renderer, cross, NULL, NULL);
			} else if(win.symbol == CellType::Circle) {
				SDL_RenderCopy(root.renderer, circle, NULL, NULL);
			}

			SDL_RenderPresent(root.renderer);

			SDL_Delay(1000);

			game.reset();
		}

		SDL_Rect r = {mouse.x - 10, mouse.y - 10, 20, 20};
		SDL_RenderCopy(root.renderer, game.getNextType() == CellType::Cross ? cross : circle, NULL, &r);

		SDL_RenderPresent(root.renderer);
	}
	
private:
	Root &root;
	SDL_Texture *cross;
	SDL_Texture *circle;
	Game game;
	int cellSize;
	SDL_Point mouse;
};

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
	
	SDL_Event evt;
	
	
	GameStateType nextState = GameStateType::MainMenu;
	while(nextState != GameStateType::Quit) {
		GameState *state;
		
		switch(nextState) {
			case GameStateType::MainMenu:
				state = &mainMenu;
				break;
			case GameStateType::Game:
				state = &gameScene;
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
		}
		
		nextState = state->getNextState();
		
		state->deinit();
	}
	
	
	
	return 0;
}

