#include "Component.h"

Component::Component(Window &window): window(window), visible(true), mousedIn(false), focused(false){}
Component::~Component() {}

void Component::injectEvent(const SDL_Event &evt) {
	if(evt.type == SDL_MOUSEMOTION) {
		 if(match(evt.motion.x, evt.motion.y, rect)) {
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
		if(match(evt.motion.x, evt.motion.y, rect)) {
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
