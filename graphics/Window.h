#ifndef WINDOW_H
#define	WINDOW_H
#include <stdexcept>
#include <SDL.h>
#include "Font.h"

class Window {
public:
	Window(int width, int height);
	virtual ~Window();
	
	SDL_Renderer* getRenderer() {
		return renderer;
	}
	
	int getWidth() {
		return width;
	}
	
	int getHeight() {
		return height;
	}

	void setTitle(std::string title) {
		SDL_SetWindowTitle(window, title.c_str());
	}

	Font * getFont() {
		return font;
	}
private:
	int width;
	int height;
	SDL_Window *window;
	SDL_Renderer *renderer;

	Font *font;
};

class WindowCreationException: public std::exception {
public:
	WindowCreationException(const char* msg): msg(msg){};
	const char* what() {
		return msg;
	}
private:
	const char* msg;
};

#endif	/* WINDOW_H */

