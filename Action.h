#ifndef PISKVORKY_ACTION_H
#define PISKVORKY_ACTION_H

#include "Game.h"
#include "Player.h"

class Player;

class Action {
public:
    Action(Player &player);
    virtual void handle(Game &game) = 0;
	Player& getPlayer();

private:
    Player& player;
};

class QuitAction: public Action {
public:
	QuitAction(Player &player);

	virtual void handle(Game &game);
};

class MoveAction: public Action {
public:
    MoveAction(Player &player, int x, int y);
    virtual void handle(Game &game);

	int getX() {return x;}
	int getY(){return y;}
private:
    int x, y;
};


#endif //PISKVORKY_ACTION_H
