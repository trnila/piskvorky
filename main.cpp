#include <cstdlib>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_events.h>
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

enum class CellType {Empty, Cross, Circle};

enum class WinType {None, Vertical, Horizontal, MainDiagonal, MinorDiagonal};

struct Win {
	CellType symbol;
	int count;
	int startRow, startCol;
	WinType type;
	
	Win() {
		symbol = CellType::Empty;
		count = 0;
	}
};

class Game {
public:	
	Game(int count, int minRequired) {
		this->count = count;
		this->minRequired = minRequired;
		nextType = CellType::Circle;
		
		cells = new CellType*[count];
		for(int row = 0; row < count; row++) {
			cells[row] = new CellType[count];
		}
		
		reset();
	};
	
	~Game() {
		for(int row = 0; row < count; row++) {
			delete[] cells[row];
		}
		delete[] cells;
	}
	
	void reset() {
		win = Win();
		
		for(int row = 0; row < count; row++) {
			for(int col = 0; col < count; col++) {
				cells[row][col] = CellType::Empty;
			}
		}
	}
	
	bool step(int row, int col) {
		if(get(row, col) == CellType::Empty) {
			cells[row][col] = nextType;
			
			nextType = nextType == CellType::Circle ? CellType::Cross : CellType::Circle;
			
			check();
			
			return true;
		}
		return false;
	}
	
	CellType get(int row, int col) {
		return cells[row][col];
	}
	
	int getCount() {
		return count;
	}
	
	int setMinRequired(int minRequired) {
		this->minRequired = minRequired;
	}
	
	bool isWin() {
		return win.symbol != CellType::Empty;
	}
	
	Win getWin() {
		return win;
	}
	
protected:
	bool check() {
		// check horizontal and vertical
		for(int row = 0; row < getCount(); row++) {
			Win vertical;
			vertical.type = WinType::Vertical;
			
			Win horizontal;
			horizontal.type = WinType::Horizontal;			
			
			for(int col = 0; col < getCount(); col++) {
				if(checkCell(row, col, vertical)) {
					win = vertical;
					return true;
				}
				
				if(checkCell(col, row, horizontal)) {
					win = horizontal;
					return true;
				}	
			}
		}
		
		// check diagonals
		int start = ceil(minRequired / sqrt(2));
		for(int i = start; i <= count; i++) {
			Win main1, main2, minor1, minor2;
			main1.type = main2.type = WinType::MainDiagonal;
			minor1.type = minor2.type = WinType::MinorDiagonal;
			
			for(int member = 0; member < i; member++) {
				int y = member;
				
				// main diagonal
				int x = count - i + member;
				if(checkCell(x, y, main1)) {
					win = main1;
					return true;
				}
				
				if(x != y && checkCell(y, x, main2)) {
					win = main2;
					return true;
				}
				
				// check minor diagonal
				x = i - member - 1;
				if(checkCell(x, y, minor1)) {
					win = minor1;
					return true;
				}
				
				x = count - member - 1;
				y = count - i + member;
				if(checkCell(x, y, minor2)) {
					win = minor2;
					return true;
				}
			}			
		}
				
		return false;
	}
	
	bool checkCell(int x, int y, Win &record) {
		if(cells[x][y] == CellType::Empty) {
			record.count = 0;
		} else if(cells[x][y] == record.symbol) {
			record.count++;
					
			if(record.count >= minRequired) {
				return true;
			}
		} else {
			record.symbol = cells[x][y];
			record.count = 1;
			record.startRow = x;
			record.startCol = y;
		}
		
		return false;
	}
	
private:
	/* count of rows/cols */
	int count;
	
	/* table of cells */
	CellType **cells;
	
	/* CellType in next step */
	CellType nextType;
	
	/* count of connected cells for win */
	int minRequired;
	
	/* How somebody win */
	Win win;
};

bool match(int x, int y, SDL_Rect &rect) {
	return x > rect.x && x < (rect.x + rect.w) && y > rect.y && y < (rect.y + rect.h);
}

void mainMenu(Root *root, Font *font) {
	bool quit = false;
	SDL_Event evt;
	
	/*TBox header(&root, font, (SDL_Rect) {100, 100, 400, 100});
	header.print("piskvorky");
	header.setColor({0, 0, 0});*/
	
	Container container(root);
	
	Text header(root, font, TextType::Variable);
	header.setText("piskvorky");
	header.setPosition({100, 100});
	header.setColor({0, 0, 0});
	
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
	
		
	Game game(20, 4);
	int cellSize = root.width / game.getCount();
			
	SDL_Event evt;
	bool quit = false;
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
			}
		}
		
		
		
		
		for(int i = 0; i < game.getCount(); i++) {
			SDL_SetRenderDrawColor(root.renderer, 0, 0, 0, 255);
			SDL_RenderDrawLine(root.renderer, 0, cellSize * i, root.width, cellSize * i); 
			SDL_RenderDrawLine(root.renderer, cellSize * i, 0, cellSize*i, root.height);
		}
		
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
		
		
		SDL_RenderPresent(root.renderer);
	}
	
	
	return 0;
}

