//
// Created by cyberxix on 24.02.16.
//

#include "SpinnerTeleLeft.h"

CylinderPosition SpinnerTeleLeft::getPosition() {
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

void SpinnerTeleLeft::update(SensorInputId id, bool value) {
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

SpinnerTeleLeft::SpinnerTeleLeft() {
    tele_out = false;
    tele_in = false;

}

OutputId SpinnerTeleLeft::getOutputId(CylinderDirection direction) {
    if(direction == CylinderDirection::UP){
        return OutputId::SPINNER_LEFT_TELE_OUT;
    } else if(direction == CylinderDirection::DOWN) {
        return OutputId::SPINNER_LEFT_TELE_IN;
    } else {
        return OutputId::NONE;
    }
}

bool SpinnerTeleLeft::downNeedsPressure() {
    return true;
}
