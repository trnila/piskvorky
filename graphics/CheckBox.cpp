#include "CheckBox.h"

CheckBox::CheckBox(Window &window): Component(window), checked(false) {
	emptyTexture = loadAsTexture(window.getRenderer(), "tick.png");
	checkedTexture = loadAsTexture(window.getRenderer(), "tick-checked.png");

	rect.w = 20;
	rect.h = 20;

	onClick.push_back([&]() -> void {
		checked = !checked;
	});
}

void CheckBox::setPosition(SDL_Point point) {
	rect.x = point.x;
	rect.y = point.y;
}

void CheckBox::setChecked(bool checked) {
	this->checked = checked;
}

bool CheckBox::isChecked() {
	return checked;
}

void CheckBox::render() {
	SDL_RenderCopy(window.getRenderer(), checked ? checkedTexture : emptyTexture, NULL, &rect);
}