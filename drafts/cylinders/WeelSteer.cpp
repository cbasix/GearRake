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

void WeelSteer::update(SensorInputId id, IOState value) {
    switch(id){
        case SensorInputId::WEEL_TRACK_MIDDLE:
            middle = value;
            break;

        default:
            break;
    }
}

WeelSteer::SpinnerTeleRight() {
    middle = IOState::INACTIVE;
}