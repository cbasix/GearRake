//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_CONSTANTS_H
#define GEARRAKE_CONSTANTS_H

#define VOLT_HIGH true
#define VOLT_LOW false

#define ACTIVE true
#define INACTIVE false



#define CYLINDER_HOLD 0

#define CYLINDER_FUNCTION_1 1
#define CYLINDER_FUNCTION_2 2

#define ERR_SENSOR_TIMEOUT 901



// ids for input must be continous! (stored in array with id as index)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/// THESE ARE NOT THE PIN NUMBERS. PIN NUMBERS ARE DEFINED IN THE .cpp FILE
enum class inputs {
    //Left Joystick
    IN_SPINNER_LEFT_UP = 0,
    IN_SPINNER_LEFT_FLOAT  = 1,

    IN_SPINNER_LEFT_TELE_OUT = 2,
    IN_SPINNER_LEFT_TELE_IN = 3,

    IN_SPINNER_LEFT_AUTO_THIRD = 4,

    //Right Joystick
    IN_SPINNER_RIGHT_UP = 5,
    IN_SPINNER_RIGHT_FLOAT = 6,

    IN_SPINNER_RIGHT_TELE_OUT = 7,
    IN_SPINNER_RIGHT_TELE_IN = 8,

    IN_SPINNER_RIGHT_AUTO_THIRD = 9,

    //Middle Joystick  UP is pulling the joystick!!!
    IN_MULTI_UP = 10,
    IN_MULTI_DOWN = 11,

    IN_MULTI_RIGHT = 12,
    IN_MULTI_LEFT = 13,

    IN_MULTI_PRESS = 14,

    //Top Buttons
    IN_AUTO_TRANSPORT = 15,
    IN_AUTO_LOW = 16,
    IN_AUTO_WORK = 17,

    //Modifier Buttons Links Rechts
    IN_MOD_LR_STEER = 18,
    IN_MOD_LR_WEEL_RIGHT_TELE = 19,
    IN_MOD_LR_WEEL_LEFT_TELE = 20,

    //Modifier Buttons Oben Unten
    IN_MOD_OU_SPINNER_BACK = 21,
    IN_MOD_OU_FRAME = 22,
    // IN_MOD_OU_UNUSED

    //spinner rear buttons on the back side
    IN_REAR_SPINNER_REAR_UP = 23,
    IN_REAR_SPINNER_REAR_DOWN = 24,

    //Sensors
    SENS_SPINNER_LEFT_THIRD = 25,
    SENS_SPINNER_RIGHT_THIRD = 26,

    SENS_SPINNER_LEFT_UP = 27,
    SENS_SPINNER_RIGHT_UP = 28,

    SENS_SPINNER_REAR_UP = 29,

    SENS_SPINNER_LEFT_TELE_OUT = 30,
    SENS_SPINNER_LEFT_TELE_IN = 31,

    SENS_SPINNER_RIGHT_TELE_OUT = 32,
    SENS_SPINNER_RIGHT_TELE_IN = 33,

    SENS_FRAME_UP = 34,
    SENS_FRAME_MIDDLE = 35,
    SENS_FRAME_LOW = 36,
    SENS_FRAME_GROUND = 37,

    SENS_FRAME_LOCK_OPEN = 38,
    SENS_FRAME_LOCK_CLOSED = 39,

    SENS_WEEL_TELE_RIGHT_OUT = 40,
    SENS_WEEL_TELE_RIGHT_IN = 41,

    SENS_WEEL_TELE_LEFT_OUT = 42,
    SENS_WEEL_TELE_LEFT_IN = 43,

    SENS_WEEL_TRACK_MIDDLE = 44,
    INPUT_ID_COUNT
};


// ids for output must be continous! (stored in array with id as index)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
enum class outputs {
    OUT_SPINNER_RIGHT_UP = 0,
    OUT_SPINNER_LEFT_UP = 1,
    OUT_SPINNER_REAR_UP = 2,

    OUT_SPINNER_RIGHT_FLOAT = 3,
    OUT_SPINNER_LEFT_FLOAT = 4,
    OUT_SPINNER_REAR_FLOAT = 5,

    OUT_SPINNER_RIGHT_TELE_OUT = 6,
    OUT_SPINNER_LEFT_TELE_OUT = 7,

    OUT_SPINNER_RIGHT_TELE_IN = 8,
    OUT_SPINNER_LEFT_TELE_IN = 9,

    OUT_FRAME_UP = 10,
    OUT_FRAME_DOWN = 11,

    OUT_STEER_LEFT = 12,
    OUT_STEER_RIGHT = 13,

    OUT_WEEL_TELE_LEFT_IN = 14,
    OUT_WEEL_TELE_RIGHT_IN = 15,

    OUT_WEEL_TELE_LEFT_OUT = 16,
    OUT_WEEL_TELE_RIGHT_OUT = 17,

    OUT_FRAME_LOCK_UP = 18,
    OUT_FRAME_LOCK_DOWN = 19,

    OUT_PRESSURE = 20,

//Leds
            LED_WEEL_TRACK_MIDDLE = 21,
    LED_FRAME_LOCK = 22,

//Top Buttons
            LED_AUTO_TRANSPORT = 23,
    LED_AUTO_LOW = 24,
    LED_AUTO_WORK = 25,

//Float Leds
            LED_SPINNER_RIGHT_FLOAT = 26,
    LED_SPINNER_LEFT_FLOAT = 27,
    LED_SPINNER_REAR_FLOAT = 28,

//Modifier Leds Links Rechts
            LED_MOD_LR_STEER = 29,

    LED_MOD_LR_WEEL_TELE_R = 30,
    LED_MOD_LR_WEEL_TELE_L = 31,

//Modifier Leds Links Rechts
            LED_MOD_OU_SPINNER_BACK = 32,
    LED_MOD_OU_FRAME = 33,
    OUTPUT_ID_COUNT
};


//pin ranges on different devices--------------------------------------------------------
#define PIN_ARDUINO_START 0
#define PIN_ARDUINO_END 99

#define PIN_EXP1_START 100
#define PIN_EXP1_END 199

#define PIN_EXP2_START 200
#define PIN_EXP2_END 299

#define PIN_EXP3_START 300
#define PIN_EXP3_END 399

#define PIN_ARDUINO_ANALOG_NEGATIVE_START 1000
#define PIN_ARDUINO_ANALOG_NEGATIVE_END 1099
#define PIN_ARDUINO_ANALOG_POSITIVE_START 1100
#define PIN_ARDUINO_ANALOG_POSITIVE_END 1199


#define EXP1_ADDR 0
#define EXP2_ADDR 1
#define EXP3_ADDR 2

#define JOY_TOLERANCE 300
#define JOY_MIDDLE 512

#define DEBOUNCE_TIME 5

#define EVENT_QUEUE_SIZE 100
//usable size is one less because one slot must be kept free in circular queue
//#define INPUT_DATA_SIZE 1

// NEW ##################################################

#define INPUT_ID_COUNT 50
#define TESTING

#ifdef TESTING
    #include <string>
#endif

enum class ActionType : int {
    NONE,
    MOVE_POSITION,
    MOVE_TIME,
    MOVE_DIRECTION,
    INPUT,
    LED,
    COMPLEX_MOVE,
    FRAME_DOWN,
    TIMER,

    ENUM_COUNT
};
#ifdef TESTING
const std::string ActionTypeStr[] = {
        "NONE",
        "MOVE_POSITION",
        "MOVE_TIME",
        "MOVE_DIRECTION",
        "INPUT",
        "LED",
        "COMPLEX_MOVE",
        "FRAME_DOWN",
        "TIMER"
};
#endif
enum class Cylinder : int {
    SPINNER_RIGHT,
    SPINNER_LEFT,
    SPINNER_TELE_RIGHT,
    SPINNER_TELE_LEFT,
    FRAME,
    FRAME_LOCK,
    WEEL_TELE_RIGHT,
    WEEL_TELE_LEFT,
    WEEL_STEER
};
#ifdef TESTING
const std::string CylinderStr[] = {
        "SPINNER_RIGHT",
        "SPINNER_LEFT",
        "SPINNER_TELE_RIGHT",
        "SPINNER_TELE_LEFT",
        "FRAME",
        "FRAME_LOCK",
        "WEEL_TELE_RIGHT",
        "WEEL_TELE_LEFT",
        "WEEL_STEER"
};
#endif
enum class CylinderDirection : int {
    NONE = 0,
    UP = 1,
    DOWN = 2,
    STOP = 3,
    OUT = (int)(UP),
    IN = (int)(DOWN),
    FLOAT = (int)(DOWN),

    OPEN = (int)(UP),
    CLOSE = (int)(DOWN),
};
#ifdef TESTING
const std::string CylinderDirectionStr[] = {
        "NONE",
        "UP",
        "DOWN",

};
#endif

// From bottom to top
enum class CylinderPosition : int {
    NONE,
    GROUND,
    CLOSED,
    LOW,
    MIDDLE,
    UP,
    OPEN

};
#ifdef TESTING
const std::string CylinderPositionStr[] = {
        "NONE",
        "GROUND",
        "CLOSED",
        "LOW",
        "MIDDLE",
        "UP",
        "OPEN"

};
#endif

enum class Timing : int {
    SHORT,
    MEDIUM,
    LONG
};
#ifdef TESTING
const std::string TimingStr[] = {
        "SHORT",
        "MEDIUM",
        "LONG"

};
#endif //testing

#endif //GEARRAKE_CONSTANTS_H


