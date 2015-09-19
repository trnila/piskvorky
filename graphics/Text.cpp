#include "Input.h"
#include "Text.h"

Text::Text(Component *parent) : Component(parent) {
	fontSize = 15;
	coveredDimension = {0, 0, 0, 0};
}

void Text::setText(const std::string &text) {
	this->text = text;
}

std::string& Text::getText() {
	return text;
}

void Text::setColor(const SDL_Color &color) {
	this->color = color;
}

void Text::setFontSize(int size) {
	this->fontSize = size;
}

void Text::render(Window &window) {
	Component::render(window);

	coveredDimension.x = getAbsolutePosition().x;
	coveredDimension.y = getAbsolutePosition().y;

	coveredDimension = window.getFont()->write(text.c_str(), coveredDimension, color, fontSize);
}

void Text::popLastCharacter() {
	while(text.length() > 0) {
		char c = text.back();
		text.pop_back();

		if((c & 0xC0) != 0x80) {
			break;
		}
	}
}

SDL_Rect Text::getCoveredDimension() {
	return coveredDimension;
}
