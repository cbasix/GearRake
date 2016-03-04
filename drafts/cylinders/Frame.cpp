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

void Frame::update(SensorInputId id, bool value) {
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

Frame::Frame(){
    frame_ground = false;
    frame_low = false;
    frame_up = false;
    frame_middle = false;
}

OutputId Frame::getOutputId(CylinderDirection direction) {
    if(direction == CylinderDirection::UP){
        return OutputId::FRAME_UP;
    } else if(direction == CylinderDirection::DOWN) {
        return OutputId::FRAME_DOWN;
    } else {
        return OutputId::NONE;
    }
}

bool Frame::downNeedsPressure() {
    //TODO right? check it!
    return false;
}


