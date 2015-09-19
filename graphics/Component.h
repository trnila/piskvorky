#ifndef COMPONENT_H
#define	COMPONENT_H
#include <vector>
#include <functional>
#include "../graphics/Window.h"

class Component {
public:
	Component(Component *parent);
	virtual ~Component();
		
	bool isVisible();
	void setVisible(bool visible);

	void setPosition(int x, int y);
	void setDimension(int width, int height);
	void setBackground(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void setBorder(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	int getWidth();
	int getHeight();
	
	virtual void render(Window &window);
	void injectEvent(const SDL_Event &evt);

	std::vector<std::function<void()>> onClick;
	std::vector<std::function<void()>> onMouseMoveIn;
	std::vector<std::function<void()>> onMouseMoveOut;
	std::vector<std::function<void()>> onBlur;
	std::vector<std::function<void(const SDL_Event &evt)>> onKeyDown;
	std::vector<std::function<void(const SDL_Event &evt)>> onTextInput;

protected:
	Component *parent;
	bool visible;
	bool mousedIn;
	bool focused;

	SDL_Color background;
	SDL_Color borderColor;
	SDL_Point position;

	int width, height;
	
	bool match(int x, int y);
	const SDL_Point& getPosition();
	SDL_Point getAbsolutePosition();
};

#endif	/* COMPONENT_H */

