#ifndef CONTAINER_H
#define	CONTAINER_H
#include <vector>
#include <stack>
#include "Component.h"

class Container: public Component {
public:
	Container(Root &root);
	~Container();
	
	void addComponent(Component *component);
	void render();
	void injectEvent(const SDL_Event &evt);
		
private:
	std::vector<Component*> components;
	std::stack<Component*> mousedIn;

};

#endif	/* CONTAINER_H */

