#include <stdexcept>
#include "Font.h"

Font::Font(SDL_Renderer *renderer, const char *path) {
	this->renderer = renderer;
	this->path = path;
}

TTF_Font *Font::createFont(int size) {
	TTF_Font *font = TTF_OpenFont(this->path, size);
	if (font == nullptr){
		throw std::runtime_error(TTF_GetError());
	}
	return font;
}

TTF_Font* Font::getFont(int size) {
	auto it = fonts.find(size);
	if(it != fonts.end()) {
		return it->second;
	}

	return fonts[size] = createFont(size);
}

Font::~Font() {
	for(auto i: fonts) {
		TTF_CloseFont(i.second);
	}
}

SDL_Rect Font::write(const char *msg, const SDL_Rect &rect, const SDL_Color &color, int fontSize) {
	if(strlen(msg) == 0) {
		return {0, 0, 0, 0};
	}

	SDL_Surface *surface = TTF_RenderUTF8_Blended(getFont(fontSize), msg, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect r;
	r.x = rect.x;
	r.y = rect.y;
	r.h = surface->h;
	r.w = surface->w;
	SDL_RenderCopy(renderer, texture, NULL, &r);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);

	return r;
}

