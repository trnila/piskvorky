#ifndef ROOT_H
#define	ROOT_H
#include <SDL.h>

struct Root {
	int width, height;
	SDL_Window *window;
	SDL_Renderer *renderer;
};


#endif	/* ROOT_H */

