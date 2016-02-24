//
// Created by cyberxix on 24.02.16.
//

#include <constants.h>
#include "SpinnerRight.h"


CylinderPosition SpinnerRight::getPosition() {
    //from top to up
    if(!right_third){
        return CylinderPosition::UNDER_THIRD;
    } else {
        if (!right_up){
            return CylinderPosition::BETWEEN_THIRD_AND_UP;
        } else {
            return CylinderPosition::UP;
        }
    }
}

void SpinnerRight::update(SensorInputId id, IOState value) {
    switch(id){
        case SensorInputId::SPINNER_LEFT_THIRD:
            right_third = value;
            break;

        case SensorInputId::SPINNER_LEFT_UP:
            right_up = value;
            break;


        default:
            break;
    }
}

SpinnerRight::SpinnerRight() {
    right_up = IOState::INACTIVE;
    right_third = IOState::INACTIVE;

}