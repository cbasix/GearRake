//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_INPUT_H
#define GEARRAKE_INPUT_H

#include "interfaces.h"
#include "constants.h"
#include "constants_io.h"


class InputData {
public:
    InputData(int input_pin);

    int input_pin;
    //int input_type;
    IOState debounced_state;
    IOState temp_state;
    unsigned long temp_change_time;
};

class Input : public Producer{
public:
    Input(InputData inputs[], int inputs_len);
    void produce(Controller* c);
    virtual ActionType getType();

private:
    InputData inputs[];
    int inputs_len;
    int communication_id;
    bool first_run;
};




#endif //GEARRAKE_INPUT_H
