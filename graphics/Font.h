#ifndef FONT_H
#define	FONT_H
#include <SDL_ttf.h>

class Font {
private:
	TTF_Font *font;
	SDL_Texture *texture;
	SDL_Renderer *renderer;
	
	/* font height */
	int height;
        
	/* temp bitmap height */
	int bitmapHeight;

	/* Spacing between letters */
	int spacing;
        
	/* width of the widest font */
	int maxWidth;
	
	/* an array of invidual character width */
	int widths['~' - ' '];
public:
	Font(SDL_Renderer *renderer, TTF_Font *font);
	~Font();
	
	void build();
	SDL_Rect write(const char*, const SDL_Rect& rect, const SDL_Color &color, int fontSize = 0);
};

#endif	/* FONT_H */

