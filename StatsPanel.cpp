#include "StatsPanel.h"
StatsPanel::StatsPanel(Component *window) : Component(window), time(NULL) { }

void StatsPanel::render(Window &window) {
	//time.setPosition(getRect().x, getRect().y);
	time.render(window);
}