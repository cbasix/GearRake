//
// Created by cyberxix on 24.02.16.
//
#include "interfaces.h"
#include "wrapper.h"

#ifndef GEARRAKE_OUTPUT_H
#define GEARRAKE_OUTPUT_H

class OutputData {
public:
    OutputData(int output_pin = 99999);
    int output_pin;
    IOState state;
};

class Output : public Consumer{
public:
    Output(ExpanderWrapper exp[], int exp_len, OutputData out[], int out_len, Cylinder* cylinders[], int cyl_len);
    ActionType getType();
    void onMessage(Controller *c, Message *m);

private:
    ExpanderWrapper* exp;
    int exp_len;
    OutputData* out;
    int out_len;
    Cylinder** cylinders;
    int cyl_len;

    void setOutput(OutputId output_id, IOState value, bool initialize=false);
};


#endif //GEARRAKE_OUTPUT_H