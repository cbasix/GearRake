//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_STATEACTION_H
#define GEARRAKE_STATEACTION_H


#include <interfaces.h>
#include "FrameDown.h"

class FrameDown : public Consumer{
public:
    virtual ActionType getType();
    FrameDown(Controller* c, int parent_communication_id);
    virtual void onMessage(Controller* c, Message* m);
    enum class LocalState : int { SHORT_FRAME_UP, OPEN_LOCK, FRAME_DOWN, CLOSE_LOCK};

private:
    LocalState state;
    int communication_id;
    int parent_communication_id;
    bool timeout_occured ;

#ifdef TESTING
public:
    void setState(FrameDown::LocalState state);
    void setTimeoutOccured(bool occured);
    void setCommunicationId(int communication_id);
    FrameDown::LocalState getState();
#endif

};


#endif //GEARRAKE_STATEACTION_H
