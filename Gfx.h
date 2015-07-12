#ifndef GFX_H
#define	GFX_H
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <vector>
#include <stack>
#include <functional>
#include <iostream>
#include "Root.h"

SDL_Texture* loadAsTexture(SDL_Renderer *renderer, const char *file);


#endif	/* GFX_H */

