#include "Container.h"

Container::Container(Root &root): Component(root) {}
Container::~Container() {
	for(Component* component : components) {
		delete component;
	}
}

void Container::addComponent(Component *component) {
	components.push_back(component);
}
	
void Container::render() {	
	for(Component* component : components) {
		if(component->isVisible()) {
			component->render();
		}
	}
}

void Container::injectEvent(const SDL_Event &evt) {
	for(Component* child: components) {
		child->injectEvent(evt);
	}
}



