//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_CONSTANTS_MESSAGE_H
#define GEARRAKE_CONSTANTS_MESSAGE_H

#include "constants.h"
#ifdef TESTING
    #include <string>
#endif
enum class SerialConf : int{
    BUF_SIZE = 200,

};
namespace SerialChar {
    enum SerialChar : char {
        ESCAPE = 0x1b,
        START = 0x02,
        END = 0x03,
    };
}


enum class MessageType : int{
    NONE,
    TIMEOUT_REQUEST,
    TIMER_REQUEST,
    CYLINDER_REQUEST,
    MOVE_TIME_REQUEST,
    MOVE_POSITION_REQUEST,
    MOVE_DIRECTION_REQUEST,
    ACTION_STATE,
    TIMEOUT,
    TIMER_STATE,
    POSITION_STATE,
    MANUAL_CHANGED,
    POSITION_REQUEST,
    POSITION_CHANGE,
    INPUT_CHANGE,
    SETTING_STATE,
    SETTING_UPDATE,
    SETTING_REQUEST,
    ACTIVE_UPDATE_REQUEST,
    STATUS_UPDATE_REQUEST,
    FAILURE_STORAGE_REQUEST,
    LOG_REQUEST,
    ACTIVE_STATUS,

    ENUM_COUNT
};

#ifdef TESTING
const std::string MessageTypeStr[] = {
        "NONE",
        "TIMEOUT_REQUEST",
        "TIMER_REQUEST",
        "CYLINDER_REQUEST",
        "MOVE_TIME_REQUEST",
        "MOVE_POSITION_REQUEST",
        "MOVE_DIRECTION_REQUEST",
        "ACTION_STATE",
        "TIMEOUT",
        "TIMER_STATE",
        "POSITION_STATE",
        "MANUAL_CHANGED",
        "POSITION_CHANGED",
        "POSITION_REQUEST",
        "POSITION_CHANGE",
        "INPUT_CHANGE"

};
#endif //testing

enum class MessageField : int {
    //msgCylinder
    TIMEOUT__STATE = 0,

    TIMEOUT_REQUEST__TIMEOUT = 0,

    TIMER_REQUEST__STOP_AFTER = 0,

    CYLINDER_REQUEST__CYLINDER = 0,
    CYLINDER_REQUEST__DIRECTION = 1,

    MOVE_TIME_REQUEST__CYLINDER = 0,
    MOVE_TIME_REQUEST__DIRECTION = 1,
    MOVE_TIME_REQUEST__TIMER = 2,

    MOVE_POSITION_REQUEST__CYLINDER = 0,
    MOVE_POSITION_REQUEST__POSITION = 1,

    MOVE_DIRECTION_REQUEST__CYLINDER = 0,
    MOVE_DIRECTION_REQUEST__DIRECTION = 1,

    ACTION_STATE__STATE = 0,

    POSITION_STATE__CYLINDER = 0,
    POSITION_STATE__POSITION = 1,

    MANUAL_CHANGED__STATE = 1,

    POSITION_REQUEST__CYLINDER = 0,

    POSITION_CHANGE__CYLINDER = 0,
    POSITION_CHANGE__POSITION = 1,


    INPUT_CHANGE__CYLINDER = 0,
    INPUT_CHANGE__POSITION = 1,

    SETTING_STATE__TYPE = 0,
    SETTING_STATE__ID = 1,
    SETTING_STATE__VALUE = 2,

    SETTING_UPDATE__TYPE = 0,
    SETTING_UPDATE__ID = 1,
    SETTING_UPDATE__VALUE = 2,

    SETTING_REQUEST__TYPE = 0,
    SETTING_REQUEST__ID = 1,

    ACTIVE_UPDATE_REQUEST__ACTIVE = 0,

    STATUS_UPDATE_REQUEST__ACTIVE = 0,

    FAILURE_STORAGE_REQUEST__ACTIVE = 0,

    LOG_REQUEST__ACTIVE = 0,

    ACTIVE_STATUS__TYPE = 0,
    ACTIVE_STATUS__CLASS = 1,
    ACTIVE_STATUS__ACTIVE = 2,

    ENUM_COUNT = 3
};

enum class ActionState : int {
    STARTING,
    STARTED,
    STOPPING,
    STOPPED_OK,
};


#endif //GEARRAKE_CONSTANTS_MESSAGE_H
