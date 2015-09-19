#ifndef PISKVORKY_TIME_H
#define PISKVORKY_TIME_H

#include <chrono>
#include "graphics/Component.h"
#include "graphics/Text.h"

class Time: public Component {
public:
	Time(Window &window);
	void start();

	virtual void render();

private:
	Text text;
	std::chrono::system_clock::time_point started;
public:
	virtual void setPosition(int x, int y) override;
};


#endif //PISKVORKY_TIME_H
