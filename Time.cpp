#include <chrono>
#include <sstream>
#include <iomanip>
#include "Time.h"

Time::Time(Window &window) : Component(window), text(window, TextType::Fixed) {
	start();
}


void Time::start() {
	started = std::chrono::system_clock::now();
}


void Time::setPosition(int x, int y) {
	Component::setPosition(x, y);
	text.setPosition({x, y});
}

void Time::render() {
	auto totalSeconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - started).count();

	int minutes = totalSeconds / 60;
	int seconds = totalSeconds - minutes * 60;

	std::ostringstream os;
	os << minutes << ":" << std::setfill('0') << std::setw(2) << seconds;
	text.setText(os.str());
	text.render();
}
