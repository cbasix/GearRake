//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_STATEACTION_H
#define GEARRAKE_STATEACTION_H


#include <interfaces.h>

class FrameDown : public Consumer{
public:
    virtual ActionType getType();
    FrameDown(int parrent_communication_id);
    virtual void onMessage(Controller* c, Message* m);
    FrameDown(Controller* c);

private:
    enum class LocalState : int { STARTUP, SHORT_FRAME_UP, OPEN_LOCK, FRAME_DOWN, CLOSE_LOCK};
    LocalState state = LocalState::STARTUP;
    int communication_id = 0;
    int parrent_communication_id = 0;
};


#endif //GEARRAKE_STATEACTION_H
