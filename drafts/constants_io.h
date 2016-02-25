o//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_CONSTANTS_IO_H
#define GEARRAKE_CONSTANTS_IO_H

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

class ManualInputPin {
public:
    static int getPin(ManualInputId id);
};

enum class ManualInputId : int {
    SPINNER_LEFT_UP,
    SPINNER_LEFT_FLOAT,
    SPINNER_LEFT_TELE_OUT,
    SPINNER_LEFT_TELE_IN,
    SPINNER_LEFT_AUTO_THIRD,

    //Right Joystick
    SPINNER_RIGHT_UP,
    SPINNER_RIGHT_FLOAT,
    SPINNER_RIGHT_TELE_OUT,
    SPINNER_RIGHT_TELE_IN,
    SPINNER_RIGHT_AUTO_THIRD,

    //Middle Joystick
    MULTI_UP,
    MULTI_DOWN,
    MULTI_RIGHT,
    MULTI_LEFT,
    MULTI_PRESS,

    //Top Buttons
    AUTO_TRANSPORT,
    AUTO_LOW,
    AUTO_WORK,

    //Modifier Buttons Links Rechts
    MOD_LR_STEER,
    MOD_LR_WEEL_RIGHT_TELE,
    MOD_LR_WEEL_LEFT_TELE,

    //Modifier Buttons oben unten
            MOD_OU_SPINNER_REAR,
    MOD_OU_FRAME,

    REAR_SPINNER_REAR_UP,
    REAR_SPINNER_REAR_DOWN,

    ENUM_COUNT
};

enum class SensorInputId {
    //Sensors
    SPINNER_LEFT_THIRD,
    SPINNER_RIGHT_THIRD,

    SPINNER_LEFT_UP,
    SPINNER_RIGHT_UP,
    SPINNER_REAR_UP,

    SPINNER_LEFT_TELE_OUT,
    SPINNER_LEFT_TELE_IN,

    SPINNER_RIGHT_TELE_OUT,
    SPINNER_RIGHT_TELE_IN,

    FRAME_UP,
    FRAME_MIDDLE,
    FRAME_LOW,
    FRAME_GROUND,

    FRAME_LOCK_OPEN,
    FRAME_LOCK_CLOSED,

    WEEL_TELE_RIGHT_OUT,
    WEEL_TELE_RIGHT_IN,
    WEEL_TELE_LEFT_OUT,
    WEEL_TELE_LEFT_IN,

    WEEL_TRACK_MIDDLE,
    ENUM_COUNT
};

class SensorInputPin {
public:
    static int getPin(SensorInputId id);
};

class OutputPin {
public:
    static int getPin(OutputId id);
};

enum class OutputId {
    NONE, //todo good idea? test & think trought
    SPINNER_RIGHT_UP,
    SPINNER_LEFT_UP,
    SPINNER_REAR_UP,

    SPINNER_RIGHT_FLOAT,
    SPINNER_LEFT_FLOAT,
    SPINNER_REAR_FLOAT,

    SPINNER_RIGHT_TELE_OUT,
    SPINNER_LEFT_TELE_OUT,

    SPINNER_RIGHT_TELE_IN,
    SPINNER_LEFT_TELE_IN,

    FRAME_UP,
    FRAME_DOWN,

    STEER_LEFT,
    STEER_RIGHT,

    FRAME_LOCK_UP,
    FRAME_LOCK_DOWN,

    WEEL_TELE_LEFT_IN,
    WEEL_TELE_RIGHT_IN,

    WEEL_TELE_LEFT_OUT,
    WEEL_TELE_RIGHT_OUT,

    PRESSURE,

    //Leds
    LED_WEEL_TRACK_MIDDLE,
    LED_FRAME_LOCK,

    //Top Buttons
    LED_AUTO_TRANSPORT,
    LED_AUTO_LOW,
    LED_AUTO_WORK,

    //Float Leds
    LED_SPINNER_RIGHT_FLOAT,
    LED_SPINNER_LEFT_FLOAT,
    LED_SPINNER_REAR_FLOAT,

    //Modifier Leds Links Rechts
    LED_MOD_LR_STEER,
    LED_MOD_LR_WEEL_TELE_R,
    LED_MOD_LR_WEEL_TELE_L,

    //Modifier Leds Links Rechts
    LED_MOD_OU_SPINNER_BACK,
    LED_MOD_OU_FRAME,

    ENUM_COUNT
};

enum class IOState : bool{
    INACTIVE = false,
    ACTIVE = true
};


#endif //GEARRAKE_CONSTANTS_IO_H
