#ifndef TEXT_H
#define	TEXT_H
#include "Component.h"
#include "Font.h"

enum class TextType {Variable, Fixed};

class Text: public Component {
public:
	Text(Root &root, Font *font, TextType type);
	void setText(const std::string &text);
	std::string& getText();
	
	void setPosition(const SDL_Point &position);
	void setRect(const SDL_Rect rect);
	void setColor(const SDL_Color &color);
	
	void setFontSize(int size);
	void render();
	
private:
	Font *font;
	std::string text;
	SDL_Color color;
	int fontSize;
	TextType textType;
	
	SDL_Rect maxRect;
};

#endif	/* TEXT_H */

