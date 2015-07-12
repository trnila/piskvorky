#include "Gfx.h"
#include "math.h"



SDL_Texture* loadAsTexture(SDL_Renderer *renderer, const char *file) {
	SDL_Surface *surf = IMG_Load(file);
	if(surf == NULL) {
		return NULL;
	}
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	return texture;
}