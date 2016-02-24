//
// Created by cyberxix on 24.02.16.
//
#include "interfaces.h"
#include "wrapper.h"

#ifndef GEARRAKE_OUTPUT_H
#define GEARRAKE_OUTPUT_H

class OutputData {
public:
    OutputData(int output_pin);
    int output_pin;
    IOState state;
};

class Output : public Consumer{
public:
    Output(ExpanderWrapper exp[], int exp_len, OutputData out[], int out_len);
    ActionType getType();
    void onMessage(Controller *c, Message *m);

private:
    ExpanderWrapper* exp;
    int exp_len;
};


#endif //GEARRAKE_OUTPUT_H
