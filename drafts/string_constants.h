//
// Created by cyberxix on 04.03.16.
//
#include "constants.h"
#ifdef TESTING
std::string ActionTypeStr[] = {
        "NONE",
        "MOVE_POSITION",
        "MOVE_TIME",
        "MOVE_DIRECTION",
        "INPUT",
        "LED",
        "COMPLEX_MOVE",
        "FRAME_DOWN",
        "TIMER",
        "DIAGNOSE",
        "COMMAND",
        "POSITION",
        "OUTPUT",
        "MASTER",
        "DELAYED",
        "LOW",
        "TRANSPORT",
        "WORK",

        "ENUM_COUNT"
};

std::string CylinderStr[] = {
        "NONE",
        "SPINNER_RIGHT",
        "SPINNER_LEFT",
        "SPINNER_TELE_RIGHT",
        "SPINNER_TELE_LEFT",
        "FRAME",
        "FRAME_LOCK",
        "WEEL_TELE_RIGHT",
        "WEEL_TELE_LEFT",
        "WEEL_STEER",
        "SPINNER_REAR",

        "ENUM_COUNT"
};

std::string CylinderDirectionStr[] = {
        "NONE",
        "UP",
        "DOWN",
        "STOP",
        "ENUM_COUNT"

};

std::string CylinderPositionStr[] = {
        "NONE",
        "GROUND",
        "BETWEEN_GROUND_AND_LOW",
        "LOW",
        "BETWEEN_LOW_AND_MIDDLE",
        "MIDDLE",
        "BETWEEN_MIDDLE_AND_UP",
        "UP",
        "ENUM_COUNT"

};

std::string TimingStr[] = {
        "NONE",
        "SHORT",
        "MEDIUM",
        "LONG",
        "WAIT_AUTO",
        "HUNDRED",

        "ENUM_COUNT"

};

#endif //testing