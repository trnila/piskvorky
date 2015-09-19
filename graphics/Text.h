#ifndef TEXT_H
#define	TEXT_H
#include "Component.h"
#include "Font.h"

class Text: public Component {
public:
	Text(Component *parent);
	void setText(const std::string &text);
	std::string& getText();

	void setColor(const SDL_Color &color);
	
	void setFontSize(int size);
	void render(Window &window);

	void popLastCharacter();

	SDL_Rect getCoveredDimension();

private:
	std::string text;
	SDL_Color color;
	int fontSize;

	SDL_Rect coveredDimension;
};

#endif	/* TEXT_H */

