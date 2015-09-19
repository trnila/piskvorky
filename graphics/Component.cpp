#include "Component.h"

Component::Component(Component *parent): parent(parent), visible(true), mousedIn(false), focused(false){
	background = borderColor = {0, 0, 0, 0};
	setPosition(0, 0);
	setDimension(100, 100);
}
Component::~Component() {}

bool Component::isVisible() {
	return visible;
}

void Component::setVisible(bool visible) {
	this->visible = visible;
}

void Component::setBackground(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	background = {r, g, b, a};
}

void Component::setBorder(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	borderColor = {r, g, b, a};
}

void Component::injectEvent(const SDL_Event &evt) {
	if(evt.type == SDL_MOUSEMOTION) {
		 if(match(evt.motion.x, evt.motion.y)) {
			for(auto fn : onMouseMoveIn) {
				fn();
			}

			mousedIn = true;
		 } else if(mousedIn) {
			for(auto fn : onMouseMoveOut) {
				fn();
			}

			mousedIn = false;
		 }
	} else if(evt.type == SDL_MOUSEBUTTONDOWN) {
		if(match(evt.motion.x, evt.motion.y)) {
			for(auto fn : onClick) {
				fn();
			}
			focused = true;
		} else if(focused) {
			for(auto fn : onBlur) {
				fn();
			}

			focused = false;
		}
	} else if(evt.type ==  SDL_TEXTINPUT) {
		for(auto fn : onTextInput) {
			fn(evt);
		}
	} else if(evt.type == SDL_KEYDOWN) {
		for(auto fn : onKeyDown) {
			fn(evt);
		}
	}
}


void Component::render(Window &window) {
	SDL_Rect rect;
	rect.x = getAbsolutePosition().x;
	rect.y = getAbsolutePosition().y;
	rect.w = getWidth();
	rect.h = getHeight();

	// fill background
	SDL_SetRenderDrawColor(window.getRenderer(), background.r, background.g, background.b, background.a);
	SDL_RenderFillRect(window.getRenderer(), &rect);

	// fill border
	SDL_SetRenderDrawColor(window.getRenderer(), borderColor.r, borderColor.g, borderColor.b, borderColor.a);
	SDL_RenderDrawRect(window.getRenderer(), &rect);
}

void Component::setPosition(int x, int y) {
	position.x = x;
	position.y = y;
}

void Component::setDimension(int width, int height) {
	this->width = width;
	this->height = height;
}

int Component::getWidth() {
	return width;
}

int Component::getHeight() {
	return height;
}

SDL_Point Component::getAbsolutePosition() {
	SDL_Point point;
	point.x = getPosition().x;
	point.y = getPosition().y;

	if(parent) {
		point.x += parent->getAbsolutePosition().x;
		point.y += parent->getAbsolutePosition().y;
	}

	return point;
}

bool Component::match(int x, int y) {
	int myX = getAbsolutePosition().x;
	int myY = getAbsolutePosition().y;

	return x > myX && x < (myX + getWidth())
	       && y > myY && y < (myY + getHeight());
}

const SDL_Point& Component::getPosition() {
	return position;
}