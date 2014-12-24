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
	Component(Root *root) {
		this->root = root;
		visible = true;
	}
	
	bool isVisible() {
		return visible;
	}
	
	void setVisible(bool visible) {
		this->visible = visible;
	}	
	
	SDL_Rect getRect() {
		return rect;
	}
	
	virtual void render() = 0;
	
	void injectEvent(SDL_Event *evt) {
		 if(evt->type == SDL_MOUSEMOTION) {
			mouseMoveIn(evt);
		} else if(evt->type == SDL_MOUSEBUTTONDOWN) {
			mouseClick(evt);
		} else if(evt->type ==  SDL_TEXTINPUT) {
			textInput(evt);
		} else if(evt->type == SDL_KEYDOWN) {
			keyDown(evt);
		}
	}
	
	virtual bool mouseMoveIn(SDL_Event *evt) {}
	virtual bool mouseMoveOut(SDL_Event *evt) {}
	virtual bool mouseClick(SDL_Event *evt) {}
	virtual bool focusOut(SDL_Event *evt) {}
	
	virtual bool textInput(SDL_Event *evt) {}
	virtual bool keyDown(SDL_Event *evt) {}
	
	std::vector<std::function<void()>> onClick;
	
protected:
	Root *root;
	bool visible;
	SDL_Rect rect;
	
	
};

class Container : public Component {
public:
	Container(Root *root): Component(root) {}
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
	
	bool mouseMoveIn(SDL_Event *evt) {
		while(!mousedIn.empty()) {
			mousedIn.top()->mouseMoveOut(evt);
			mousedIn.pop();
		}
				
		for(Component* component : components) {
			if(match(evt->motion.x, evt->motion.y, component->getRect())) {
				component->mouseMoveIn(evt);
				
				mousedIn.push(component);
			}
		}		
	}
	
	bool mouseClick(SDL_Event *evt) {
		for(Component* component : components) {
			if(match(evt->motion.x, evt->motion.y, component->getRect())) {
				component->mouseClick(evt);
			} else {
				component->focusOut(evt);
			}
		}
	}
	
	bool textInput(SDL_Event *evt) {
		for(Component* component : components) {
			component->textInput(evt);
		}
	}
	
	bool keyDown(SDL_Event *evt) {
		for(Component* component : components) {
			component->keyDown(evt);
		}
	}
	
private:
	std::vector<Component*> components;
	std::stack<Component*> mousedIn;
	
	bool match(int x, int y, SDL_Rect rect) {
		return x > rect.x && x < (rect.x + rect.w) && y > rect.y && y < (rect.y + rect.h);
	}
};

class Font {
private:
	Root *root;
	TTF_Font *font;
	SDL_Texture *texture;
	
	/* font height */
	int height;
	
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
	Text(Root *root, Font *font, TextType type):Component(root) {
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
	
	virtual bool mouseMoveIn(SDL_Event *evt) {
		setColor({255, 0, 0});
	}
	
	virtual bool mouseMoveOut(SDL_Event *evt) {
		setColor({0, 0, 0});
	}
	
	virtual bool mouseClick(SDL_Event *evt) {
		setColor({0, 255, 0});
		
		for(auto &fn : onClick) {
			fn();
		}
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
	Input(Root* root, Font *font, SDL_Rect rect): Component(root) {
		this->rect = rect;
		
		editing = false;
		
		blink = 0;
		counter = 0;
		
		text = new Text(root, font, TextType::Fixed);
		text->setRect(rect);
		text->setColor({255, 0, 0});
		text->setText("Daniel");
	}
	
	~Input() {
		delete text;
	}
	
	void render() {
		SDL_SetRenderDrawColor(root->renderer, 255, 0, 0, 0);
		SDL_RenderDrawRect(root->renderer, &rect);
		
		text->render();
		
		if(editing) {
			if(counter++ >= 10) {	
				blink = !blink;
				counter = 0;
			}

			if(blink) {
				SDL_Rect r = text->getRect();
				SDL_RenderDrawLine(
					root->renderer, 
					r.x + r.w + 10,
					r.y,
					r.x + r.w + 10,
					r.y + r.h
				);
			}
		}
	}
	
	virtual bool mouseClick(SDL_Event* evt) {
		if(!editing) {
			SDL_StartTextInput();
		}
		
		editing = true;
	}
	
	virtual bool focusOut(SDL_Event *evt) {
		SDL_StopTextInput();
		editing = false;
	}

	virtual bool textInput(SDL_Event* evt) {
		text->getText().append(evt->edit.text);
	}
	
	virtual bool keyDown(SDL_Event *evt) {
		if(evt->key.keysym.sym == SDLK_BACKSPACE) {
			if(text->getText().length() > 0) {
				text->getText().pop_back();
			}
		}
	}
	
	virtual bool mouseMoveIn(SDL_Event *evt) {
		root->setTextCursor();
	}
	
	virtual bool mouseMoveOut(SDL_Event *evt) {
		root->setDefaultCursor();
	}
	
private:
	bool editing;
	Text *text;
	int counter;
	bool blink;	
};




#endif	/* GFX_H */

