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

void mainMenu(Root *root, Font *font) {
	bool quit = false;
	SDL_Event evt;
	
	/*TBox header(&root, font, (SDL_Rect) {100, 100, 400, 100});
	header.print("piskvorky");
	header.setColor({0, 0, 0});*/
	
	Container container(root);
	
	Text header(root, font, TextType::Variable);
	header.setText("Piskvorky");
	header.setPosition({100, 100});
	header.setColor({0, 0, 0});
       // header.setFontSize(8);
       // header.render();
	
	Text newGame(root, font, TextType::Variable);
	newGame.setText("new game");
	newGame.setPosition({100, 200});
	newGame.setColor({0, 0, 255});
	//newGame.setFontSize(18);
	
	Input i(root, font, {400, 400, 100, 100});
	
	container.addComponent(&header);
	container.addComponent(&newGame);
	container.addComponent(&i);
	
	newGame.onClick.push_back([&]() ->  void {
		quit = true;
	});
	
	while(!quit) {
		while(SDL_PollEvent(&evt)) {
			if(evt.type == SDL_QUIT) {
				quit = true;
				exit(1);
				break;
			}
			
			container.injectEvent(&evt);
		}
		
		SDL_SetRenderDrawColor(root->renderer, 255, 255, 255, 255);
		SDL_RenderClear(root->renderer);
		
		container.render();

		
		SDL_RenderPresent(root->renderer);
	}
}

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
	
	SDL_Texture *cross = loadAsTexture(root.renderer, "cross.png");
	SDL_Texture *circle = loadAsTexture(root.renderer, "circle.png");
	if(cross == NULL || circle == NULL) {
		std::cout << "cross or circle missing!";
		return 0;
	}
	
	Font f(&root, font);
	
	mainMenu(&root, &f);
	
	SDL_ShowCursor(0);
	
		
	Game game(20, 4);
	int cellSize = root.width / game.getCount();
			
	SDL_Event evt;
	bool quit = false;
	SDL_Point mouse;
	while(!quit) {
		SDL_SetRenderDrawColor(root.renderer, 255, 255, 255, 255);
		SDL_RenderClear(root.renderer);
		
		while(SDL_PollEvent(&evt)) {
			if(evt.type == SDL_MOUSEBUTTONDOWN) {
				int row = evt.motion.x / cellSize;
				int col = evt.motion.y / cellSize;
				
				game.step(row, col);
			} else if(evt.type == SDL_QUIT) {
				quit = true;
				break;
			} else if(evt.type == SDL_MOUSEMOTION) {
				mouse.x = evt.motion.x;
				mouse.y = evt.motion.y;
			}
		}
		
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
	
	
	return 0;
}

