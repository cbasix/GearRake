//
// Created by cyberxix on 19.02.16.
//

#ifndef GEARRAKE_DIAGNOSE_H
#define GEARRAKE_DIAGNOSE_H

#include "SerialProtocol.h"
#include "interfaces.h"

class Diagnose : public Producer, public Consumer{
public:
    Diagnose();
    ~Diagnose();

    ActionType getType();
    void onMessage(Controller *c, Message *m);
    void produce(Controller *c);

private:
    SerialProtocol proto;

    bool log_update;
    bool failure_storage_update;
    bool status_update;
    bool active_update;

    void sendTimeoutSettingState(Message &m, Message &answ, int setting_id);
    void sendTimerSettingState(Message &m, Message &answ, int setting_id);
};


#endif //GEARRAKE_DIAGNOSE_H
