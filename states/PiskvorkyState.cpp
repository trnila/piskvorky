#include "PiskvorkyState.h"

PiskvorkyState::PiskvorkyState(Window &window): AbstractGameState(window), game(Game(20, 4)) {
	cross = loadAsTexture(window.getRenderer(), "cross.png");
	circle = loadAsTexture(window.getRenderer(), "circle.png");
	if(cross == NULL || circle == NULL) {
		std::cout << "cross or circle missing!";
		exit(1);
	}

	cellSize = window.getWidth() / game.getCount();
}

PiskvorkyState::~PiskvorkyState() {
	SDL_DestroyTexture(cross);
	SDL_DestroyTexture(circle);
}

void PiskvorkyState::init() {
	SDL_ShowCursor(0);
	game.reset();
}

void PiskvorkyState::deinit() {
	SDL_ShowCursor(1);
}


void PiskvorkyState::injectEvent(SDL_Event& evt) {
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

void PiskvorkyState::renderOneFrame() {
	SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(window.getRenderer());

	// redraw lines
	for(int i = 0; i < game.getCount(); i++) {
		SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
		SDL_RenderDrawLine(window.getRenderer(), 0, cellSize * i, window.getWidth(), cellSize * i); 
		SDL_RenderDrawLine(window.getRenderer(), cellSize * i, 0, cellSize*i, window.getHeight());
	}

	// draw circles, crosses
	for(int row = 0; row < game.getCount(); row++) {
		for(int col = 0; col < game.getCount(); col++) {
			SDL_Rect rect;
			rect.w = rect.h = cellSize;
			rect.x = row * cellSize;
			rect.y = col * cellSize;

			if(game.get(row, col) == CellType::Circle) {
				SDL_RenderCopy(window.getRenderer(), circle, NULL, &rect);
			} else if(game.get(row, col) == CellType::Cross) {
				SDL_RenderCopy(window.getRenderer(), cross, NULL, &rect);
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

		SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
		SDL_RenderDrawLine(
			window.getRenderer(),
			start.x,
			start.y,
			end.x,
			end.y				
		);

		if(win.symbol == CellType::Cross) {
			SDL_RenderCopy(window.getRenderer(), cross, NULL, NULL);
		} else if(win.symbol == CellType::Circle) {
			SDL_RenderCopy(window.getRenderer(), circle, NULL, NULL);
		}

		SDL_RenderPresent(window.getRenderer());

		SDL_Delay(1000);

		game.reset();
	}

	SDL_Rect r = {mouse.x - 10, mouse.y - 10, 20, 20};
	SDL_RenderCopy(window.getRenderer(), game.getNextType() == CellType::Cross ? cross : circle, NULL, &r);
}