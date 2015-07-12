#include "Input.h"

Input::Input(Window &window, Font *font, SDL_Rect rect): Component(window) {
	this->rect = rect;

	editing = false;

	blink = 0;
	counter = 0;

	text = new Text(window, font, TextType::Fixed);
	text->setRect(rect);
	text->setColor({255, 0, 0});
	text->setText("Daniel");

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
			if(evt.key.keysym.sym == SDLK_BACKSPACE) {
				if(text->getText().length() > 0) {
					text->getText().pop_back();
				}
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

void Input::render() {
	SDL_SetRenderDrawColor(window.getRenderer(), 255, 0, 0, 0);
	SDL_RenderDrawRect(window.getRenderer(), &rect);

	text->render();

	if(editing) {
		if(counter++ >= 10) {	
			blink = !blink;
			counter = 0;
		}

		if(blink) {
			SDL_Rect r = text->getRect();
			SDL_RenderDrawLine(
				window.getRenderer(), 
				r.x + r.w + 10,
				r.y,
				r.x + r.w + 10,
				r.y + r.h
			);
		}
	}
}