#include "Text.h"

Text::Text(Window &window, TextType type) : Component(window) {
	this->font = window.getFont();
	fontSize = 15;

	maxRect = rect = {0, 0, 0, 0};
	textType = type;
}

void Text::setText(const std::string &text) {
	this->text = text;
}

std::string& Text::getText() {
	return text;
}

void Text::setPosition(const SDL_Point &position) {
	maxRect.x = position.x;
	maxRect.y = position.y;
}

void Text::setRect(const SDL_Rect rect) {
	this->maxRect = rect;
}

void Text::setColor(const SDL_Color &color) {
	this->color = color;
}

void Text::setFontSize(int size) {
	this->fontSize = size;
}

void Text::render() {
	rect = font->write(text.c_str(), maxRect, color, fontSize);
}

