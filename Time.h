#ifndef PISKVORKY_TIME_H
#define PISKVORKY_TIME_H

#include <chrono>
#include "graphics/Component.h"
#include "graphics/Text.h"

class Time: public Component {
public:
	Time(Component *parent);
	void start();

	virtual void render(Window &window);

private:
	Text text;
	std::chrono::system_clock::time_point started;
};


#endif //PISKVORKY_TIME_H
