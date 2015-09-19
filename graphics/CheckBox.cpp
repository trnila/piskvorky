#include "CheckBox.h"

CheckBox::CheckBox(Component *component): Component(component), checked(false) {
//	emptyTexture = loadAsTexture(component.getRenderer(), "tick.png");
//	checkedTexture = loadAsTexture(component.getRenderer(), "tick-checked.png");

	setDimension(20, 20);

	onClick.push_back([&]() -> void {
		checked = !checked;
	});
}

void CheckBox::setChecked(bool checked) {
	this->checked = checked;
}

bool CheckBox::isChecked() {
	return checked;
}

void CheckBox::render(Window &window) {
	throw std::runtime_error("Not implemented");
	//SDL_RenderCopy(window.getRenderer(), checked ? checkedTexture : emptyTexture, NULL, &rect);
}