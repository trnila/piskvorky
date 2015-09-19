#include "StatsPanel.h"
StatsPanel::StatsPanel(Window &window) : Component(window), time(window) { }

void StatsPanel::render() {
	time.setPosition(getRect().x, getRect().y);
	time.render();
}