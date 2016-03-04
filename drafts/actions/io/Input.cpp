//
// Created by cyberxix on 16.02.16.
//

#include "Input.h"
#include "constants_io.h"
#include "Timer.h"
#include "wrapper.h"
#ifndef TESTING
    #include "Arduino.h"
#endif //TESTING


Input::Input(InputData* inputs, int inputs_len) {
    communication_id = Message::generateCommunicationId();
    this->inputs = inputs;
    this->inputs_len = inputs_len;
    this->first_run = true;


    //setup all input pins
    for (int input_id = 0; input_id < inputs_len; ++input_id) {
        if (inputs[input_id].getInputPin() >= PIN_ARDUINO_START &&
            inputs[input_id].getInputPin() <= PIN_ARDUINO_END) {

            ReadWriteWrapper::pinMode(inputs[input_id].getInputPin(), ReadWriteWrapper::W_INPUT_PULLUP);

        } else if (inputs[input_id].getInputPin() >= PIN_ARDUINO_ANALOG_POSITIVE_START &&
                   inputs[input_id].getInputPin() <= PIN_ARDUINO_ANALOG_POSITIVE_END) {

            ReadWriteWrapper::pinMode(ReadWriteWrapper::W_A0 + (inputs[input_id].getInputPin() - PIN_ARDUINO_ANALOG_POSITIVE_START), ReadWriteWrapper::W_INPUT_PULLUP);


        } else if (inputs[input_id].getInputPin() >= PIN_ARDUINO_ANALOG_NEGATIVE_START &&
                   inputs[input_id].getInputPin() <= PIN_ARDUINO_ANALOG_NEGATIVE_END) {

            ReadWriteWrapper::pinMode(ReadWriteWrapper::W_A0 + (inputs[input_id].getInputPin() - PIN_ARDUINO_ANALOG_NEGATIVE_START), ReadWriteWrapper::W_INPUT_PULLUP);

        }
    }
}

void Input::produce(Controller *c) {
    //read all input changes and produce messages if changed
    for (int input_id = 0; input_id < inputs_len; ++input_id) {
        //InputData* inda = &inputs[input_id];
        unsigned long now = ClockWrapper::getTime();
        IOState readed;

        if(inputs[input_id].getInputPin() >= PIN_ARDUINO_START
                  && inputs[input_id].getInputPin() <= PIN_ARDUINO_END){

            //inputs are all pulled up if input button is pressed digitalRead outputs 0 -> negate with !
            readed = (IOState) !ReadWriteWrapper::digitalRead(inputs[input_id].getInputPin());

            //input is via analog joystick
        } else if(inputs[input_id].getInputPin() >= PIN_ARDUINO_ANALOG_NEGATIVE_START
                  && inputs[input_id].getInputPin() <= PIN_ARDUINO_ANALOG_NEGATIVE_END){

            int temp = ReadWriteWrapper::analogRead(inputs[input_id].getInputPin() - PIN_ARDUINO_ANALOG_NEGATIVE_START);
            if(temp < JOY_MIDDLE - JOY_TOLERANCE){
                readed = IOState::ACTIVE;
            } else {
                readed = IOState::INACTIVE;
            }


        } else if(inputs[input_id].getInputPin() >= PIN_ARDUINO_ANALOG_POSITIVE_START
                  && inputs[input_id].getInputPin() <= PIN_ARDUINO_ANALOG_POSITIVE_END){

            int temp = ReadWriteWrapper::analogRead(inputs[input_id].getInputPin() - PIN_ARDUINO_ANALOG_POSITIVE_START);
            if(temp > JOY_MIDDLE + JOY_TOLERANCE){
                readed = IOState::ACTIVE;
            } else {
                readed = IOState::INACTIVE;
            }


        }


        //debouncing
        if (readed != inputs[input_id].temp_state){
            inputs[input_id].temp_state = readed;
            inputs[input_id].temp_change_time = now;
        }

        if(
                (
                   inputs[input_id].temp_state != inputs[input_id].debounced_state
                    && inputs[input_id].temp_change_time + DEBOUNCE_TIME < now
                ) || first_run){

            inputs[input_id].debounced_state = inputs[input_id].temp_state;

            Message::createInputChange(c, getType(), communication_id, (ManualInputId)input_id, inputs[input_id].debounced_state);

        }

    }
}

ActionType Input::getType() {
    return ActionType::INPUT;
}

InputData::InputData(int input_pin) {
    this->input_pin = input_pin;
    this->debounced_state = IOState::INACTIVE;
    this->temp_state = IOState::INACTIVE;
    this->temp_change_time = 0;
}

int InputData::getInputPin() {
    return input_pin;
}
