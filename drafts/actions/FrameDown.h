//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_STATEACTION_H
#define GEARRAKE_STATEACTION_H


#include <interfaces.h>

class FrameDown : public Consumer{
public:
    virtual void onMessage(Controller c, Message m);
    FrameDown(Controller c);

private:
    typedef enum LocalState { STATE_STARTUP, STATE_SHORT_FRAME_UP, STATE_OPEN_LOCK, STATE_FRAME_DOWN, STATE_CLOSE_LOCK};
    LocalState state = STATE_STARTUP;
    int communication_id = 0;
};


#endif //GEARRAKE_STATEACTION_H
