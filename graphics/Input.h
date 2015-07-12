#ifndef INPUT_H
#define	INPUT_H
#include "Component.h"
#include "Font.h"
#include "Text.h"

class Input: public Component {
public:
	Input(Root& root, Font *font, SDL_Rect rect);
	virtual ~Input();
	void render();
	
private:
	bool editing;
	Text *text;
	int counter;
	bool blink;	
};


#endif	/* INPUT_H */

