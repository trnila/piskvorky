#include <string.h>
#include <thread>
#include <unistd.h>
#include "NetworkPlayer.h"

enum class Command: uint8_t {
	PING,
	MOVE
};

NetworkPlayer::NetworkPlayer(const CellType &cellType, int port) : Player(cellType), port(port) {
	if((sockFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket: ");
	}
perror("kokosu");
	memset(&my, 0, sizeof(my));
	my.sin_addr.s_addr = INADDR_ANY;
	my.sin_family = AF_INET;
	my.sin_port = htons(port);

	int yes = 1;
	if ( setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 )
	{
		perror("setsockopt");
	}


	if(bind(sockFd, (struct sockaddr*)&my, sizeof(my)) != 0) {
		perror("bind: ");
	}

	if(listen(sockFd, 1) != 0) {
		perror("Listen: ");
	}

	std::thread thread([&]() -> void{
		struct sockaddr_in client_addr;
		socklen_t addrlen=sizeof(client_addr);
		clientFd = accept(sockFd, (struct sockaddr*)&client_addr, &addrlen);

		printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

		for(;;) {
			parseNextCommand();
		}

	});

	thread.detach();
}

NetworkPlayer::NetworkPlayer(const CellType &cellType, std::string address, int port) : Player(cellType), address(address), port(port) {
	std::thread thread([=]() -> void {
		int sockfd;
		struct sockaddr_in dest;
		char buffer[100];

		/*---Open socket for streaming---*/
		if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			perror("Socket");
			exit(errno);
		}

		/*---Initialize server address/port struct---*/
		bzero(&dest, sizeof(dest));
		dest.sin_family = AF_INET;
		dest.sin_port = htons(port);
		dest.sin_addr.s_addr = inet_addr(address.c_str());
			perror("f");

		/*---Connect to server---*/
		if (connect(sockfd, (struct sockaddr *) &dest, sizeof(dest)) != 0) {
			perror("Connect ");
			exit(errno);
		}

		printf("Connected\n");

		/*---Get "Hello?"---*/

		clientFd = sockfd;
		for(;;) {
			parseNextCommand();
		}
	});
	thread.detach();
}

void NetworkPlayer::parseNextCommand() {
	uint8_t command, x, y;
	if(read(clientFd, &command, sizeof(command)) <= 0) {
		notifyAll(new QuitAction(*this));
		return;
	}

	if(command == (uint8_t) Command::MOVE) {
		read(clientFd, &x, sizeof(x));
		read(clientFd, &y, sizeof(y));

		printf("%d %d\n", x, y);

		notifyAll(new MoveAction(*(this), x, y));

	} else {
		printf("Invalid command %d\n", command);
	}

	fflush(stdout);
}

void NetworkPlayer::onMove(Action *action) {
	MoveAction *a = (MoveAction*) action;

	uint8_t command = (uint8_t) Command::MOVE;
	uint8_t x = a->getX();
	uint8_t y = a->getY();

	write(clientFd, &command, sizeof(command));
	write(clientFd, &x, sizeof(x));
	write(clientFd, &y, sizeof(y));
}

bool NetworkPlayer::isAvailable() {
	return clientFd != 0;
}