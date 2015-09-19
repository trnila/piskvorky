#ifndef FONT_H
#define	FONT_H

#include <unordered_map>
#include <SDL_ttf.h>

class Font {
public:
	Font(SDL_Renderer *renderer, const char *path);
	~Font();

	SDL_Rect write(const char*, const SDL_Rect& rect, const SDL_Color &color, int fontSize = 0);
	TTF_Font* getFont(int size);
	TTF_Font* createFont(int size);

private:
	SDL_Renderer *renderer;
	const char* path;
	std::unordered_map<int, TTF_Font*> fonts;
};

#endif	/* FONT_H */

