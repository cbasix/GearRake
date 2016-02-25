//
// Created by cyberxix on 24.02.16.
//

#include "SpinnerTeleRight.h"

CylinderPosition SpinnerTeleRight::getPosition() {
    //from top to up
    if(tele_in){
        return CylinderPosition::IN;
    } else {
        if (!tele_out){
            return CylinderPosition::BETWEEN_IN_AND_OUT;
        } else {
            return CylinderPosition::OUT;
        }
    }
}

void SpinnerTeleRight::update(SensorInputId id, IOState value) {
    switch(id){
        case SensorInputId::SPINNER_RIGHT_TELE_IN:
            tele_in = value;
            break;

        case SensorInputId::SPINNER_RIGHT_TELE_OUT:
            tele_out = value;
            break;

        default:
            break;
    }
}

SpinnerTeleRight::SpinnerTeleRight() {
    tele_out = IOState::INACTIVE;
    tele_in = IOState::INACTIVE;

}

OutputId SpinnerTeleRight::getOutputId(CylinderDirection direction) {
    if(direction == CylinderDirection::UP){
        return OutputId::SPINNER_RIGHT_TELE_OUT;
    } else if(direction == CylinderDirection::DOWN) {
        return OutputId::SPINNER_RIGHT_TELE_IN;
    } else {
        return OutputId::NONE;
    }
}

bool SpinnerTeleRight::downNeedsPressure() {
    return true;
}
