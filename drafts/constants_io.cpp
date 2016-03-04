//
// Created by cyberxix on 24.02.16.
//

#include "constants_io.h"

int ManualInputPin::getPin(ManualInputId id){

    if(id == (ManualInputId)ManualInputId::SPINNER_LEFT_UP){
        return PIN_ARDUINO_ANALOG_POSITIVE_START + 0;
     } else if(id == (ManualInputId)ManualInputId::SPINNER_LEFT_FLOAT){
         return PIN_ARDUINO_ANALOG_NEGATIVE_START + 0;
     } else if(id == (ManualInputId)ManualInputId::SPINNER_LEFT_TELE_OUT){
         return PIN_ARDUINO_ANALOG_POSITIVE_START + 1;
     } else if(id == (ManualInputId)ManualInputId::SPINNER_LEFT_TELE_IN){
         return PIN_ARDUINO_ANALOG_NEGATIVE_START + 1;
     } else if(id == (ManualInputId)ManualInputId::SPINNER_LEFT_AUTO_THIRD){
         return PIN_ARDUINO_START + 51;
     } else

    //Right Joystick
    if(id == (ManualInputId)ManualInputId::SPINNER_RIGHT_UP){
         return PIN_ARDUINO_ANALOG_POSITIVE_START + 2;
     } else if(id == (ManualInputId)ManualInputId::SPINNER_RIGHT_FLOAT){
         return PIN_ARDUINO_ANALOG_NEGATIVE_START + 2;
     } else if(id == (ManualInputId)ManualInputId::SPINNER_RIGHT_TELE_OUT){
         return PIN_ARDUINO_ANALOG_NEGATIVE_START + 3;
     } else if(id == (ManualInputId)ManualInputId::SPINNER_RIGHT_TELE_IN){
         return PIN_ARDUINO_ANALOG_POSITIVE_START + 3;
     } else if(id == (ManualInputId)ManualInputId::SPINNER_RIGHT_AUTO_THIRD){
         return PIN_ARDUINO_START + 52;
     } else

    //Middle Joystick
    if(id == (ManualInputId)ManualInputId::MULTI_UP){
         return PIN_ARDUINO_ANALOG_POSITIVE_START + 4;
     } else if(id == (ManualInputId)ManualInputId::MULTI_DOWN){
         return PIN_ARDUINO_ANALOG_NEGATIVE_START + 4;
     } else if(id == (ManualInputId)ManualInputId::MULTI_RIGHT){
         return PIN_ARDUINO_ANALOG_NEGATIVE_START + 5;
     } else if(id == (ManualInputId)ManualInputId::MULTI_LEFT){
         return PIN_ARDUINO_ANALOG_POSITIVE_START + 5;
     } else if(id == (ManualInputId)ManualInputId::MULTI_PRESS){
         return PIN_ARDUINO_START + 53;
     } else

    //Top Buttons
    if(id == (ManualInputId)ManualInputId::AUTO_TRANSPORT){
         return PIN_ARDUINO_START + 2;
     } else if(id == (ManualInputId)ManualInputId::AUTO_LOW){
         return PIN_ARDUINO_START + 3;
     } else if(id == (ManualInputId)ManualInputId::AUTO_WORK){
         return PIN_ARDUINO_START + 4;
     } else

    //Modifier Buttons Links Rechts
    if(id == (ManualInputId)ManualInputId::MOD_LR_STEER){
         return PIN_ARDUINO_START + 6;
     } else if(id == (ManualInputId)ManualInputId::MOD_LR_WEEL_RIGHT_TELE){
         return PIN_ARDUINO_START + 9;
     } else if(id == (ManualInputId)ManualInputId::MOD_LR_WEEL_LEFT_TELE){
         return PIN_ARDUINO_START + 8;
     } else

        //Modifier Buttons oben unten
    if(id == (ManualInputId)ManualInputId::MOD_OU_SPINNER_REAR){
         return PIN_ARDUINO_START + 5;
     } else if(id == (ManualInputId)ManualInputId::MOD_OU_FRAME){
         return PIN_ARDUINO_START + 7;
     } else
        //spinner rear buttons on the back
    if(id == (ManualInputId)ManualInputId::REAR_SPINNER_REAR_UP){
         return PIN_ARDUINO_START + 10;
     } else if(id == (ManualInputId)ManualInputId::REAR_SPINNER_REAR_DOWN){
         return PIN_ARDUINO_START + 11;
     }

}

int SensorInputPin::getPin(SensorInputId id) {
    if(id == SensorInputId::SPINNER_LEFT_THIRD){
         return PIN_ARDUINO_START + 22;
     } else
    if(id == SensorInputId::SPINNER_RIGHT_THIRD){
         return PIN_ARDUINO_START + 24;
     } else

    if(id == SensorInputId::SPINNER_LEFT_UP){
         return PIN_ARDUINO_START + 23;
    } else
    if(id == SensorInputId::SPINNER_RIGHT_UP){
         return PIN_ARDUINO_START + 25;
    } else
    if(id == SensorInputId::SPINNER_REAR_UP){
         return PIN_ARDUINO_START + 29;
    } else

    if(id == SensorInputId::SPINNER_LEFT_TELE_OUT){
         return PIN_ARDUINO_START + 26;
    } else
    if(id == SensorInputId::SPINNER_LEFT_TELE_IN){
         return PIN_ARDUINO_START + 27;
    } else

    if(id == SensorInputId::SPINNER_RIGHT_TELE_OUT){
         return PIN_ARDUINO_START + 28;
    } else
    if(id == SensorInputId::SPINNER_RIGHT_TELE_IN){
         return PIN_ARDUINO_START + 30;
    } else

    if(id == SensorInputId::FRAME_UP){
         return PIN_ARDUINO_START + 33;
    } else
    if(id == SensorInputId::FRAME_MIDDLE){
         return PIN_ARDUINO_START + 34;
    } else
    if(id == SensorInputId::FRAME_LOW){
         return PIN_ARDUINO_START + 35;
    } else
    if(id == SensorInputId::FRAME_GROUND){
         return PIN_ARDUINO_START + 36;
    } else

    if(id == SensorInputId::FRAME_LOCK_OPEN){
         return PIN_ARDUINO_START + 31;
    } else
    if(id == SensorInputId::FRAME_LOCK_CLOSED){
         return PIN_ARDUINO_START + 32;
    } else

    if(id == SensorInputId::WEEL_TELE_RIGHT_OUT){
         return PIN_ARDUINO_START + 39;
    } else
    if(id == SensorInputId::WEEL_TELE_RIGHT_IN){
         return PIN_ARDUINO_START + 40;
    } else
    if(id == SensorInputId::WEEL_TELE_LEFT_OUT){
         return PIN_ARDUINO_START + 37;
    } else
    if(id == SensorInputId::WEEL_TELE_LEFT_IN){
         return PIN_ARDUINO_START + 38;
    } else

    if(id == SensorInputId::WEEL_TRACK_MIDDLE){
         return PIN_ARDUINO_START + 41;
    }

}

int OutputPin::getPin(OutputId id) {
    //NOTE numbers on relay boards are higher by one because pin numbering on relay board starts with 1
    if(id == (OutputId)OutputId::SPINNER_RIGHT_UP){
         return PIN_EXP1_START + 2; //3;
    } else
    if(id == (OutputId)OutputId::SPINNER_LEFT_UP){
         return PIN_EXP1_START + 0; //1
    } else
    if(id == (OutputId)OutputId::SPINNER_REAR_UP){
         return PIN_EXP1_START + 11; //12
    } else

    if(id == (OutputId)OutputId::SPINNER_RIGHT_FLOAT){
         return PIN_EXP1_START + 3;  //4
    } else
    if(id == (OutputId)OutputId::SPINNER_LEFT_FLOAT){
         return PIN_EXP1_START + 1;  //2
    } else
    if(id == (OutputId)OutputId::SPINNER_REAR_FLOAT){
         return PIN_EXP1_START + 10; //11
    } else

    if(id == (OutputId)OutputId::SPINNER_RIGHT_TELE_OUT){
         return PIN_EXP1_START + 6;  //7
    } else
    if(id == (OutputId)OutputId::SPINNER_LEFT_TELE_OUT){
         return PIN_EXP1_START + 4; //5
    } else

    if(id == (OutputId)OutputId::SPINNER_RIGHT_TELE_IN){
         return PIN_EXP1_START + 7;  //8
    } else
    if(id == (OutputId)OutputId::SPINNER_LEFT_TELE_IN){
         return PIN_EXP1_START + 5; //6
    } else

    if(id == (OutputId)OutputId::FRAME_UP){
         return PIN_EXP1_START + 15;  //16
    } else
    if(id == (OutputId)OutputId::FRAME_DOWN){
         return PIN_EXP1_START + 14; //15
    } else

    if(id == (OutputId)OutputId::STEER_LEFT){
         return PIN_EXP1_START + 9;  //10
    } else
    if(id == (OutputId)OutputId::STEER_RIGHT){
         return PIN_EXP1_START + 8; //9
    } else

    if(id == (OutputId)OutputId::FRAME_LOCK_UP){
         return PIN_EXP1_START + 13;  //14
    } else
    if(id == (OutputId)OutputId::FRAME_LOCK_DOWN){
         return PIN_EXP1_START + 12; //13
    } else

    //expander 2
    if(id == (OutputId)OutputId::WEEL_TELE_LEFT_IN){
         return PIN_EXP2_START + 2;  //3
    } else
    if(id == (OutputId)OutputId::WEEL_TELE_RIGHT_IN){
         return PIN_EXP2_START + 4; //5
    } else

    if(id == (OutputId)OutputId::WEEL_TELE_LEFT_OUT){
         return PIN_EXP2_START + 1;  //2
    } else
    if(id == (OutputId)OutputId::WEEL_TELE_RIGHT_OUT){
         return PIN_EXP2_START + 3; //4
    } else

    if(id == (OutputId)OutputId::PRESSURE){
         return PIN_EXP2_START + 0; //1
    } else

    //Leds
    if(id == (OutputId)OutputId::LED_WEEL_TRACK_MIDDLE){
         return PIN_EXP3_START + 0; //1
    } else
    if(id == (OutputId)OutputId::LED_FRAME_LOCK){
         return PIN_EXP3_START + 1; //2
    } else

    //Top Buttons
    if(id == (OutputId)OutputId::LED_AUTO_TRANSPORT){
         return PIN_EXP3_START + 2; //3
    } else
    if(id == (OutputId)OutputId::LED_AUTO_LOW){
         return PIN_EXP3_START + 3; //4
    } else
    if(id == (OutputId)OutputId::LED_AUTO_WORK){
         return PIN_EXP3_START + 4; //5
    } else

    //Float Leds
    if(id == (OutputId)OutputId::LED_SPINNER_RIGHT_FLOAT){
         return PIN_EXP3_START + 6; //7
    } else
    if(id == (OutputId)OutputId::LED_SPINNER_LEFT_FLOAT){
         return PIN_EXP3_START + 5; //6
    } else
    if(id == (OutputId)OutputId::LED_SPINNER_REAR_FLOAT){
         return PIN_EXP3_START + 8; //9
    } else

    //Modifier Leds Links Rechts
    if(id == (OutputId)OutputId::LED_MOD_LR_STEER){
         return PIN_EXP3_START + 9; //10
    } else
    if(id == (OutputId)OutputId::LED_MOD_LR_WEEL_TELE_R){
         return PIN_EXP3_START + 12; //13
    } else
    if(id == (OutputId)OutputId::LED_MOD_LR_WEEL_TELE_L){
         return PIN_EXP3_START + 11; //12
    } else

    //Modifier Leds Links Rechts
    if(id == (OutputId)OutputId::LED_MOD_OU_SPINNER_BACK){
         return PIN_EXP3_START + 7; //8
    } else
    if(id == (OutputId)OutputId::LED_MOD_OU_FRAME){
         return PIN_EXP3_START + 10; //11
    }
}
