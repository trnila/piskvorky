#ifndef INPUT_H
#define	INPUT_H
#include "Component.h"
#include "Font.h"
#include "Text.h"

class Input: public Component {
public:
	Input(Component *root);
	virtual ~Input();
	void render(Window &window);
	void setValue(std::string value);

	Text *text;
private:
	bool editing;
	int counter;
	bool blink;
};


#endif	/* INPUT_H */

