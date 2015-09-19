#ifndef PISKVORKY_STATSPANEL_H
#define PISKVORKY_STATSPANEL_H


#include "graphics/Component.h"
#include "Time.h"

class StatsPanel: public Component {
public:
	StatsPanel(Window &window);

	virtual void render();

private:
	Time time;
	int x;
};


#endif //PISKVORKY_STATSPANEL_H
