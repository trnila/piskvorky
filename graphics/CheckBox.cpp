#include "CheckBox.h"

CheckBox::CheckBox(Root& root): Component(root), checked(false) {
	emptyTexture = loadAsTexture(root.renderer, "tick.png");
	checkedTexture = loadAsTexture(root.renderer, "tick-checked.png");

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
	SDL_RenderCopy(root.renderer, checked ? checkedTexture : emptyTexture, NULL, &rect);
}