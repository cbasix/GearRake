//
// Created by cyberxix on 24.02.16.
//

#include "WeelTeleLeft.h"

CylinderPosition WeelTeleLeft::getPosition() {
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

void WeelTeleLeft::update(SensorInputId id, IOState value) {
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

WeelTeleLeft::WeelTeleLeft() {
    tele_out = IOState::INACTIVE;
    tele_in = IOState::INACTIVE;

}

OutputId WeelTeleLeft::getOutputId(CylinderDirection direction) {
    if(direction == CylinderDirection::OUT){
        return OutputId::WEEL_TELE_LEFT_OUT;
    } else if(direction == CylinderDirection::IN) {
        return OutputId::WEEL_TELE_LEFT_IN;
    } else {
        return OutputId::NONE;
    }
}

bool WeelTeleLeft::downNeedsPressure() {
    return true;
}
