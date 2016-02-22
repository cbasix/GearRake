//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_INPUT_H
#define GEARRAKE_INPUT_H

#include "interfaces.h"
#include "constants.h"

class Input : public Producer{

};
struct InputData {

    int input_pin;
    int input_type;
    bool debounced_state;
    bool temp_state;
    unsigned int temp_change_time;
    bool active;
    bool state_changed;
};

class InputObject{
public:
    void onMessage(Controller* c, Message* m);
    void produce(Controller* c);
private:
    InputObject();
    bool getInputState(int input_id);
    //void setTaskMonitor(TaskMonitor *tm);
    void readInput(Controller* c);
    //bool hasInputChanged(int input_id);
    InputData input_data[INPUT_ID_COUNT];
};

//todo input task darf nicht starten wenn Bedienteil nicht korrekt verbunden (verbindung unterbrochen).


#endif //GEARRAKE_INPUT_H
