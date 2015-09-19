#ifndef PISKVORKY_NETWORKPLAYER_H
#define PISKVORKY_NETWORKPLAYER_H

#include "Player.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

class NetworkPlayer: public Player, public MoveListener {
public:
	NetworkPlayer(const CellType &cellType, std::string address, int port);
	NetworkPlayer(const CellType &cellType, int port);

	virtual bool isAvailable() override;

private:
	virtual void onMove(Action *action);

private:
	int port;
	std::string address;

	int sockFd;
	int clientFd;
	struct sockaddr_in my, his;

	void parseNextCommand();
};


#endif //PISKVORKY_NETWORKPLAYER_H
