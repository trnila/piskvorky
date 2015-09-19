#ifndef PISKVORKY_MOVELISTENER_H
#define PISKVORKY_MOVELISTENER_H


#include "Action.h"

class Action;

class MoveListener {
public:
    virtual void onMove(Action *action) = 0;
};


#endif //PISKVORKY_MOVELISTENER_H
