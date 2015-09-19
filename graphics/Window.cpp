#include "Window.h"

Window::Window(int width, int height): width(width), height(height) {
	window = SDL_CreateWindow("Piskvorky", 100, 100, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		SDL_Quit();
		throw WindowCreationException(SDL_GetError());
	}
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		SDL_DestroyWindow(window);
		SDL_Quit();
		throw WindowCreationException(SDL_GetError());
	}

	font = new Font(renderer, "/usr/share/fonts/TTF/Vera.ttf");
}

Window::~Window() {
}

