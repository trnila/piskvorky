#ifndef GFX_H
#define	GFX_H
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <stack>
#include <functional>
#include "Root.h"

#include <iostream>

class Component {
public:
	Component(Root &root): root(root), visible(true), mousedIn(false), focused(false) {}
	
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
	
	void injectEvent(const SDL_Event &evt) {
		if(evt.type == SDL_MOUSEMOTION) {
			 if(match(evt.motion.x, evt.motion.y, rect)) {
				for(auto fn : onMouseMoveIn) {
					fn();
				}
				
				mousedIn = true;
			 } else if(mousedIn) {
				for(auto fn : onMouseMoveOut) {
					fn();
				}
				
				mousedIn = false;
			 }
		} else if(evt.type == SDL_MOUSEBUTTONDOWN) {
			if(match(evt.motion.x, evt.motion.y, rect)) {
				for(auto fn : onClick) {
					fn();
				}
				focused = true;
			} else if(focused) {
				for(auto fn : onBlur) {
					fn();
				}
				
				focused = false;
			}
		} else if(evt.type ==  SDL_TEXTINPUT) {
			for(auto fn : onTextInput) {
				fn(evt);
			}
		} else if(evt.type == SDL_KEYDOWN) {
			for(auto fn : onKeyDown) {
				fn(evt);
			}
		}
	}
		
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

class Container : public Component {
public:
	Container(Root &root): Component(root) {}
	void addComponent(Component *component) {
		components.push_back(component);
	}
	
	void render() {	
		for(Component* component : components) {
			if(component->isVisible()) {
				component->render();
			}
		}
	}
	
	void injectEvent(const SDL_Event &evt) {
		for(Component* child: components) {
			child->injectEvent(evt);
		}
	}
		
private:
	std::vector<Component*> components;
	std::stack<Component*> mousedIn;
};

class Font {
private:
	Root *root;
	TTF_Font *font;
	SDL_Texture *texture;
	
	/* font height */
	int height;
        
	/* temp bitmap height */
	int bitmapHeight;

	/* Spacing between letters */
	int spacing;
        
	/* width of the widest font */
	int maxWidth;
	
	/* an array of invidual character width */
	int widths['~' - ' '];
public:
	Font(Root *root, TTF_Font *font);
	~Font();
	
	void build();
	SDL_Rect write(const char*, const SDL_Rect& rect, const SDL_Color &color, int fontSize = 0);
};

enum class TextType {Variable, Fixed};


class Text: public Component {
public:
	Text(Root &root, Font *font, TextType type): Component(root) {
		this->font = font;
		fontSize = 0;
		
		maxRect = rect = {0, 0, 0, 0};
		textType = type;
	}
	
	void setText(const std::string &text) {
		this->text = text;
	}
	
	std::string& getText() {
		return text;
	}
	
	void setPosition(const SDL_Point &position) {
		maxRect.x = position.x;
		maxRect.y = position.y;
	}
	
	void setRect(const SDL_Rect rect) {
		this->maxRect = rect;
	}
	
	void setColor(const SDL_Color &color) {
		this->color = color;
	}
	
	void setFontSize(int size) {
		this->fontSize = size;
	}
			
	void render() {
		rect = font->write(text.c_str(), maxRect, color, fontSize);
	}
	
private:
	Font *font;
	std::string text;
	SDL_Color color;
	int fontSize;
	TextType textType;
	
	SDL_Rect maxRect;
};

class Input: public Component {
public:
	Input(Root& root, Font *font, SDL_Rect rect): Component(root) {
		this->rect = rect;
		
		editing = false;
		
		blink = 0;
		counter = 0;
		
		text = new Text(root, font, TextType::Fixed);
		text->setRect(rect);
		text->setColor({255, 0, 0});
		text->setText("Daniel");
		
		onMouseMoveIn.push_back([&]() -> void {
			root.setTextCursor();
		});
		
		onMouseMoveOut.push_back([&]() -> void {
			root.setDefaultCursor();			
		});
		
		onClick.push_back([&]() -> void {
			editing = true;
			SDL_StartTextInput();
		});
		
		onBlur.push_back([&]() -> void {
			editing = false;
			SDL_StopTextInput();
		});
		
		onKeyDown.push_back([&](const SDL_Event &evt) -> void {
			if(editing) {
				if(evt.key.keysym.sym == SDLK_BACKSPACE) {
					if(text->getText().length() > 0) {
						text->getText().pop_back();
					}
				}	
			}
		});
		
		onTextInput.push_back([&](const SDL_Event &evt) {
			if(editing) {
				text->getText().append(evt.edit.text);
			}
		});
	}
	
	~Input() {
		delete text;
	}
	
	void render() {
		SDL_SetRenderDrawColor(root.renderer, 255, 0, 0, 0);
		SDL_RenderDrawRect(root.renderer, &rect);
		
		text->render();
		
		if(editing) {
			if(counter++ >= 10) {	
				blink = !blink;
				counter = 0;
			}

			if(blink) {
				SDL_Rect r = text->getRect();
				SDL_RenderDrawLine(
					root.renderer, 
					r.x + r.w + 10,
					r.y,
					r.x + r.w + 10,
					r.y + r.h
				);
			}
		}
	}
	
private:
	bool editing;
	Text *text;
	int counter;
	bool blink;	
};


#endif	/* GFX_H */

