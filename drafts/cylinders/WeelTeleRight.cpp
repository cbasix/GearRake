//
// Created by cyberxix on 24.02.16.
//

#include "WeelTeleRight.h"
CylinderPosition WeelTeleRight::getPosition() {
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

void WeelTeleRight::update(SensorInputId id, IOState value) {
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

WeelTeleRight::WeelTeleRight() {
    tele_out = IOState::INACTIVE;
    tele_in = IOState::INACTIVE;

}