//
// Created by cyberxix on 25.02.16.
//

#include "SpinnerRear.h"

CylinderPosition SpinnerRear::getPosition() {
    if(up){
        CylinderPosition::UP;
    }else{
        CylinderPosition::UNDER_UP;
    }
}

void SpinnerRear::update(SensorInputId id, bool value) {
    switch(id){
        case SensorInputId::SPINNER_REAR_UP:
            up = value;
            break;

        default:
            break;
    }
}

SpinnerRear::SpinnerRear() {

}

OutputId SpinnerRear::getOutputId(CylinderDirection direction) {
    if(direction == CylinderDirection::UP){
        return OutputId::SPINNER_REAR_UP;
    } else if(direction == CylinderDirection::DOWN) {
        return OutputId::SPINNER_REAR_FLOAT;
    } else {
        return OutputId::NONE;
    }
}

bool SpinnerRear::downNeedsPressure() {
    return false;
}
