//
// Created by cyberxix on 24.02.16.
//

#include "Frame.h"

CylinderPosition Frame::getPosition() {
    //
    if(frame_ground){
        return CylinderPosition::GROUND;
    } else {
        if (!frame_low){
            return CylinderPosition::BETWEEN_GROUND_AND_LOW;
        } else {
            if (!frame_middle){
                return CylinderPosition::BETWEEN_LOW_AND_MIDDLE;
            } else {
                if (!frame_up){
                    return CylinderPosition::BETWEEN_MIDDLE_AND_UP;
                } else {
                    return CylinderPosition::UP;
                }
            }
        }
    }
}

void Frame::update(SensorInputId id, IOState value) {
    switch(id){
        case SensorInputId::FRAME_GROUND:
            frame_ground = value;
        break;

        case SensorInputId::FRAME_LOW:
            frame_low = value;
        break;

        case SensorInputId::FRAME_MIDDLE:
            frame_middle = value;
        break;

        case SensorInputId::FRAME_UP:
            frame_up = value;
        break;

        default:
        break;
    }
}

Frame::Frame() {
    frame_ground = IOState::INACTIVE;
    frame_low = IOState::INACTIVE;
    frame_up = IOState::INACTIVE;
    frame_middle = IOState::INACTIVE;
}
