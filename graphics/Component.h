#ifndef COMPONENT_H
#define	COMPONENT_H
#include <vector>
#include <functional>
#include "../Root.h"

class Component {
public:
	Component(Root &root);
	virtual ~Component();
		
	bool isVisible() {
		return visible;
	}
	
	void setVisible(bool visible) {
		this->visible = visible;
	}	
	
	const SDL_Rect& getRect() {
		return rect;
	}
	
	virtual void render() = 0;
	void injectEvent(const SDL_Event &evt);
		
	std::vector<std::function<void()>> onClick;
	std::vector<std::function<void()>> onMouseMoveIn;
	std::vector<std::function<void()>> onMouseMoveOut;
	std::vector<std::function<void()>> onBlur;
	std::vector<std::function<void(const SDL_Event &evt)>> onKeyDown;
	std::vector<std::function<void(const SDL_Event &evt)>> onTextInput;
		
protected:
	Root &root;
	bool visible;
	SDL_Rect rect;
	
	bool mousedIn;
	bool focused;
	
	bool match(int x, int y, SDL_Rect rect) {
		return x > rect.x && x < (rect.x + rect.w) && y > rect.y && y < (rect.y + rect.h);
	}	
};

#endif	/* COMPONENT_H */

