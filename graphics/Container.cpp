#include "Container.h"

Container::Container(Component *parent): Component(parent) {}
Container::~Container() {
	for(Component* component : components) {
		delete component;
	}
}

void Container::addComponent(Component *component) {
	components.push_back(component);
}
	
void Container::render(Window &window) {
	Component::render(window);
	for(Component* component : components) {
		if(component->isVisible()) {
			component->render(window);
		}
	}
}

void Container::injectEvent(const SDL_Event &evt) {
	for(Component* child: components) {
		child->injectEvent(evt);
	}
}



