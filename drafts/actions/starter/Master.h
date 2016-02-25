//
// Created by cyberxix on 19.02.16.
//

#ifndef GEARRAKE_MASTER_H
#define GEARRAKE_MASTER_H


#include <interfaces.h>

class Master : public Consumer {
public:
    virtual ActionType getType();

    virtual void onMessage(Controller *c, Message *m);

    Master(Controller* c);
private:
    enum class MasterMode {WEEL_STEER, WEEL_TELE_LEFT, WEEL_TELE_RIGHT, SPINNER_REAR, FRAME ,ENUM_COUNT};
    int comm_id;
    MasterMode mode;
    int inp_comm_ids[];

    void switchMode(Controller* c, MasterMode new_active_mode, bool first_init=true);


};


#endif //GEARRAKE_MASTER_H
