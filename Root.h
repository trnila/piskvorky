#ifndef ROOT_H
#define	ROOT_H
#include <SDL.h>
#include <assert.h>

class Root {
public:
	int width, height;
	SDL_Window *window;
	SDL_Renderer *renderer;
	
	Root() {
		for(int i = 0; i < 15; i++) {
			systemCursors[i] = NULL;
		}
	}
	
	~Root() {
		for(Uint8 i = 0; i < 12; i++) {
			if(systemCursors[i]) {
				SDL_FreeCursor(systemCursors[i]);
			}
		}
	}
	
	void setCursor(SDL_SystemCursor cursor) {
		if(systemCursors[cursor] == NULL) {
			systemCursors[cursor] = SDL_CreateSystemCursor(cursor);
		}
				
		SDL_SetCursor(systemCursors[cursor]);
	}
	
	void setDefaultCursor() {
		setCursor(SDL_SYSTEM_CURSOR_ARROW);
	}
	
	void setTextCursor() {
		setCursor(SDL_SYSTEM_CURSOR_IBEAM);
	}
	
	
	
private:
	SDL_Cursor* systemCursors[20];
	
};


#endif	/* ROOT_H */

