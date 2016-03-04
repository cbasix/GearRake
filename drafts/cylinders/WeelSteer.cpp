//
// Created by cyberxix on 24.02.16.
//

#include "WeelSteer.h"
CylinderPosition WeelSteer::getPosition() {
    //from top to up
    if(middle){
        return CylinderPosition::MIDDLE;
    } else {
        return CylinderPosition::NOT_MIDDLE;

    }
}

void WeelSteer::update(SensorInputId id, bool value) {
    switch(id){
        case SensorInputId::WEEL_TRACK_MIDDLE:
            middle = value;
            break;

        default:
            break;
    }
}

WeelSteer::WeelSteer() {
    middle = false;
}

OutputId WeelSteer::getOutputId(CylinderDirection direction) {
    if(direction == CylinderDirection::LEFT){
        return OutputId::STEER_LEFT;
    } else if(direction == CylinderDirection::RIGHT) {
        return OutputId::STEER_RIGHT;
    } else {
        return OutputId::NONE;
    }
}

bool WeelSteer::downNeedsPressure() {
    return true;
}
