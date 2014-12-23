#ifndef GFX_H
#define	GFX_H
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Root.h"

class Component {
protected:
	Root *root;

	Component(Root *root) {
		this->root = root;
	}
};

class Font: public Component {
private:
	TTF_Font *font;
	SDL_Texture *texture;
	
	/* font height */
	int height;
	
	/* width of the widest font */
	int maxWidth;
	
	/* an array of invidual character width */
	int widths['~' - ' '];
public:
	Font(Root *root, TTF_Font *font);
	~Font();
	
	void build();
	void write(const char*, const SDL_Rect& rect, const SDL_Color &color);
	
};

class TBox : public Component {
private:
	Font *font;
	std::string buffer;
	SDL_Color color;
	SDL_Color background;
	
public:
	SDL_Rect rect;
	
	TBox(Root *root, Font *font, SDL_Rect rect);
	void setColor(const SDL_Color& color) {
		this->color = color;
	}
	void print(const char *msg);
	void clear() {
		buffer.clear();
	}
	void render();
};


#endif	/* GFX_H */

