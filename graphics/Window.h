#ifndef WINDOW_H
#define	WINDOW_H
#include <stdexcept>
#include <SDL.h>

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
private:
	int width;
	int height;
	SDL_Window *window;
	SDL_Renderer *renderer;
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

