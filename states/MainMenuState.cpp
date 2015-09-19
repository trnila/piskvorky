#include "MainMenuState.h"
#include "../graphics/Text.h"
#include "../graphics/Input.h"
#include "AbstractGameState.h"

MainMenuState::MainMenuState(Window &window) : AbstractGameState(window), container(nullptr){
	container.setDimension(window.getWidth(), window.getHeight());
	container.setBackground(245, 245, 245, 255);

	Text *header = new Text(&container);
	header->setText("Piskvorky");
	header->setPosition(100, 100);
	header->setFontSize(40);
	header->setColor({255, 0, 0});

	Text *newGame = new Text(&container);
	newGame->setText("new game");
	newGame->setPosition(100, 200);
	newGame->setColor({0, 0, 255});

	Text *settings = new Text(&container);
	settings->setText("Settings");
	settings->setPosition(100, 250);
	settings->setColor({0, 0, 255});

	Text *quitBtn = new Text(&container);
	quitBtn->setText("Quit");
	quitBtn->setPosition(100, 300);
	quitBtn->setColor({0, 0, 255});

	Input *i = new Input(&container);
	i->setPosition(300, 200);
	i->setDimension(100, 20);
	i->setBackground(0, 255, 0, 255);
	i->setBorder(255, 0, 0, 255);
	i->setValue("test");

	newGame->onClick.push_back([&]() ->  void {
		this->setQuit(GameStateType::Game);
	});

	quitBtn->onClick.push_back([&]() -> void {
		setQuit(GameStateType::Quit);
	});

	settings->onClick.push_back([&]() -> void {
		setQuit(GameStateType::Settings);
	});

	// move out
	quitBtn->onMouseMoveOut.push_back([=]() -> void{
		quitBtn->setColor({0, 0, 255});
	});

	newGame->onMouseMoveOut.push_back([=]() -> void{
		newGame->setColor({0, 0, 255});
	});

	// move in
	newGame->onMouseMoveIn.push_back([=]() -> void{
		newGame->setColor({255, 0, 0});
	});

	quitBtn->onMouseMoveIn.push_back([=]() -> void{
		quitBtn->setColor({255, 0, 0});
	});

	container.addComponent(header);
	container.addComponent(newGame);
	container.addComponent(settings);
	container.addComponent(quitBtn);
	container.addComponent(i);
}

void MainMenuState::renderOneFrame() {
	container.render(window);
}

void MainMenuState::injectEvent(SDL_Event &evt) {
	container.injectEvent(evt);
}