#include <cstdlib>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Gfx.h"
#include "Root.h"

SDL_Texture* loadAsTexture(SDL_Renderer *renderer, const char *file) {
	SDL_Surface *surf = IMG_Load(file);
	if(surf == NULL) {
		return NULL;
	}
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	return texture;
}

struct M {
	char symbol;
	int count;
	
	M() {
		symbol = ' ';
		count = 0;
	}
};

int main(int argc, char** argv) {
	Root root;
	root.width = 800;
	root.height = 600;
	
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
	
	SDL_Cursor *hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_Cursor *arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	
	
	SDL_Event evt;
	bool quit = false;
	const int cells = 20;
	int cellSize = root.width / cells;
	char grid[cells][cells];
	for(int row = 0; row < cells; row++) {
		for(int col = 0; col < cells; col++) {
			grid[row][col] = ' ';
		}
	}
	
	
	
	SDL_Texture *cross = loadAsTexture(root.renderer, "cross.png");
	SDL_Texture *circle = loadAsTexture(root.renderer, "circle.png");
	if(cross == NULL || circle == NULL) {
		std::cout << "cross or circle missing!";
		return 0;
	}
	
	bool nextCircle = true;
	
	while(!quit) {
		while(SDL_PollEvent(&evt)) {
			if(evt.type == SDL_MOUSEBUTTONDOWN) {
				int row = evt.motion.x / cellSize;
				int col = evt.motion.y / cellSize;
				
				if(grid[row][col] == ' ') {
					grid[row][col] = nextCircle ? 'O' : 'X';
				
					nextCircle = !nextCircle;
				}
				
			} else if(evt.type == SDL_QUIT) {
				quit = true;
				break;
			}
		}
		
		SDL_SetRenderDrawColor(root.renderer, 255, 255, 255, 255);
		SDL_RenderClear(root.renderer);
		
		
		for(int i = 0; i < cells; i++) {
			SDL_SetRenderDrawColor(root.renderer, 0, 0, 0, 255);
			SDL_RenderDrawLine(root.renderer, 0, cellSize * i, root.width, cellSize * i); 
			SDL_RenderDrawLine(root.renderer, cellSize * i, 0, cellSize*i, root.height);
		}
		
		for(int row = 0; row < cells; row++) {
			for(int col = 0; col < cells; col++) {
				SDL_Rect rect;
				rect.w = rect.h = cellSize;
				rect.x = row * cellSize;
				rect.y = col * cellSize;
				
				if(grid[row][col] == 'O') {
					SDL_RenderCopy(root.renderer, circle, NULL, &rect);
				} else if(grid[row][col] == 'X') {
					SDL_RenderCopy(root.renderer, cross, NULL, &rect);
				}
			}
		}
		
		char win = ' ';
		const int minRequired = 3;
		
		// vertical check
		for(int row = 0; row < cells; row++) {
			M vertical;
			for(int col = 0; col < cells; col++) {
				if(grid[row][col] == ' ') {
					vertical.count = 0;
				} else if(grid[row][col] == vertical.symbol) {
					vertical.count++;
					
					if(vertical.count >= minRequired) {
						win = vertical.symbol;
					}
				} else {
					vertical.symbol = grid[row][col];
					vertical.count = 1;
				}
			}
		}
		
		// horizontal
		for(int col = 0; col < cells; col++) {
			M vertical;
			for(int row = 0; row < cells; row++) {
				if(grid[row][col] == ' ') {
					vertical.count = 0;
				} else if(grid[row][col] == vertical.symbol) {
					vertical.count++;
					
					if(vertical.count >= minRequired) {
						win = vertical.symbol;
					}
				} else {
					vertical.symbol = grid[row][col];
					vertical.count = 1;
				}
			}
		}
		
		if(win != ' ') {
			if(win == 'X') {
				SDL_RenderCopy(root.renderer, cross, NULL, NULL);
			} else if(win == 'O') {
				SDL_RenderCopy(root.renderer, circle, NULL, NULL);
			}
			
			SDL_RenderPresent(root.renderer);
			
			SDL_Delay(5000);
			break;
		}
		
		
		SDL_RenderPresent(root.renderer);
	}
	
	
	return 0;
}

