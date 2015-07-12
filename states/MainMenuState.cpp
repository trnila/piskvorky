#include "MainMenuState.h"

MainMenuState::MainMenuState(Window &window, Font &font): AbstractGameState(window), container(window){
	Text *header = new Text(window, &font, TextType::Variable);
	header->setText("Piskvorky");
	header->setPosition({100, 100});
	header->setColor({0, 0, 0});

	Text *newGame = new Text(window, &font, TextType::Variable);
	newGame->setText("new game");
	newGame->setPosition({100, 200});
	newGame->setColor({0, 0, 255});

	Text *settings = new Text(window, &font, TextType::Variable);
	settings->setText("Settings");
	settings->setPosition({100, 300});
	settings->setColor({0, 0, 255});

	Text *quitBtn = new Text(window, &font, TextType::Variable);
	quitBtn->setText("Quit");
	quitBtn->setPosition({100, 400});
	quitBtn->setColor({0, 0, 255});

	Input *i = new Input(window, &font, {400, 400, 100, 100});

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
	SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(window.getRenderer());

	container.render();
}

void MainMenuState::injectEvent(SDL_Event &evt) {
	container.injectEvent(evt);
}