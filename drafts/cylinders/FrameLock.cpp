//
// Created by cyberxix on 24.02.16.
//

#include <constants_io.h>
#include <constants.h>
#include "FrameLock.h"
CylinderPosition FrameLock::getPosition() {
    //
    if(frame_lock_closed){
        return CylinderPosition::CLOSED;
    } else {
        if (!frame_lock_open){
            return CylinderPosition::BETWEEN_OPEN_AND_CLOSE;
        } else {
            return CylinderPosition::OPEN;
        }
    }
}

void FrameLock::update(SensorInputId id, IOState value) {
    switch(id){
        case SensorInputId::FRAME_LOCK_CLOSED:
            frame_lock_closed = value;
            break;

        case SensorInputId::FRAME_LOCK_OPEN:
            frame_lock_open = value;
            break;

        default:
            break;
    }
}

FrameLock::FrameLock() {
    frame_lock_closed = IOState::INACTIVE;
    frame_lock_open = IOState::INACTIVE;

}

