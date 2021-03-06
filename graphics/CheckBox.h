#ifndef CHECKBOX_H
#define	CHECKBOX_H
#include "Component.h"
#include "../Gfx.h"

class CheckBox: public Component {
public:
	CheckBox(Component *component);

	void setChecked(bool checked = true);
	bool isChecked();
	void render(Window &window);

private:
	SDL_Texture *emptyTexture;
	SDL_Texture *checkedTexture;
	bool checked;
	SDL_Point position;
};

#endif	/* CHECKBOX_H */

