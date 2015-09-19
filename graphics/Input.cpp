#include "Input.h"

Input::Input(Component *parent) : Component(parent) {
	editing = false;

	blink = 0;
	counter = 0;

	text = new Text(this);

	onMouseMoveIn.push_back([&]() -> void {
		//root.setTextCursor();
	});

	onMouseMoveOut.push_back([&]() -> void {
		//root.setDefaultCursor();			
	});

	onClick.push_back([&]() -> void {
		editing = true;
		SDL_StartTextInput();
	});

	onBlur.push_back([&]() -> void {
		editing = false;
		SDL_StopTextInput();
	});

	onKeyDown.push_back([&](const SDL_Event &evt) -> void {
		if(editing) {
			switch(evt.key.keysym.sym) {
				case SDLK_BACKSPACE:
					text->popLastCharacter();
					break;
				case SDLK_LEFT:
					break;
			}
		}
	});

	onTextInput.push_back([&](const SDL_Event &evt) {
		if(editing) {
			text->getText().append(evt.edit.text);
		}
	});
}

Input::~Input() {
	delete text;
}

void Input::render(Window &window) {
	Component::render(window);

	text->render(window);

	if(editing) {
		if(counter++ >= 10) {	
			blink = !blink;
			counter = 0;
		}

		if(blink) {
			SDL_SetRenderDrawColor(window.getRenderer(), 255, 0, 0, 255);

			int x = getAbsolutePosition().x;
			int y = getAbsolutePosition().y;

			SDL_RenderDrawLine(
				window.getRenderer(), 
				x + text->getCoveredDimension().w,
				y,
				x + text->getCoveredDimension().w,
				y + getHeight()
			);
		}
	}
}

void Input::setValue(std::string value) {
	text->setText(value);
}
