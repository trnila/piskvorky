#ifndef PISKVORKY_PLAYER_H
#define PISKVORKY_PLAYER_H

#include <vector>
#include <mutex>
#include "MoveListener.h"
#include "Action.h"

class Player {
public:
	Player(CellType cellType);
    void attach(MoveListener *listener);
	void detach(MoveListener *listener);

	CellType getCellType();
	void setCellType(CellType type) {
		cellType = type;
	}
	virtual bool isAvailable();

protected:
    void notifyAll(Action *action);
private:
    std::vector<MoveListener*> listeners;
    CellType cellType;
};


#endif //PISKVORKY_PLAYER_H
