//
// Created by cyberxix on 24.02.16.
//

#include "SpinnerLeft.h"


CylinderPosition SpinnerLeft::getPosition() {
    //from top to up
    if(!left_third){
        return CylinderPosition::UNDER_THIRD;
    } else {
        if (!left_up){
            return CylinderPosition::BETWEEN_THIRD_AND_UP;
        } else {
            return CylinderPosition::UP;
        }
    }
}

void SpinnerLeft::update(SensorInputId id, IOState value) {
    switch(id){
        case SensorInputId::SPINNER_LEFT_THIRD:
            left_third = value;
            break;

        case SensorInputId::SPINNER_LEFT_UP:
            left_up = value;
            break;


        default:
            break;
    }
}

SpinnerLeft::SpinnerLeft() {
    left_up = IOState::INACTIVE;
    left_third = IOState::INACTIVE;

}