//
// Created by cyberxix on 19.02.16.
//

#include <actions/auto/Low.h>
#include <actions/auto/Work.h>
#include <actions/auto/Transport.h>
#include <actions/Timer.h>
#include "Master.h"
#include "constants.h"
#include "interfaces.h"
#include "Move.h"

Master::Master(Controller *c) {
    this->comm_id = Message::generateCommunicationId();
    this->switchMode(c, MasterMode::SPINNER_REAR, true);

    //for each manual started task save the comm_id
    for (int i = 0; i < (int) ManualInputId::ENUM_COUNT; ++i) {
        inp_comm_ids[i] = Message::generateCommunicationId();
    }
}

ActionType Master::getType() {
    return ActionType::MASTER;
}

void Master::onMessage(Controller *c, Message *m) {
    if (m->getType() == MessageType::MANUAL_INPUT_CHANGE) {

        //some input activated
        if ((IOState) m->getValue(MessageField::MANUAL_INPUT_CHANGE__VALUE) == IOState::ACTIVE) {
            ManualInputId input_id = (ManualInputId) m->getValue(MessageField::MANUAL_INPUT_CHANGE__ID);

            handleStandardMoveMessages(c, input_id);
            handleStateChangeMesages(c, input_id);
            handleStateDependentMessages(c, input_id);
            handleAutoMoveMessages(c, input_id);

        }
    } else if (m->getType() == MessageType::TIMER_REQUEST){
        //start timer on timer request
        int timer_parent_comm_id = m->getCommunicationId();
        Timing timer_timing = (Timing) m->getValue(MessageField::TIMER_REQUEST__TIMING);

        c->registerProducer((Producer*)new Timer(timer_parent_comm_id, timer_timing, false));

    } else if (m->getType() == MessageType::MOVE_DIRECTION_REQUEST){
        //start move direction on
        CylinderId cylinder_id = (CylinderId) m->getValue(MessageField::MOVE_DIRECTION_REQUEST__CYLINDER);
        CylinderDirection direction = (CylinderDirection) m->getValue(MessageField::MOVE_DIRECTION_REQUEST__DIRECTION);

        c->registerConsumer((Consumer*)new MoveDirection(c, m->getCommunicationId(), cylinder_id, direction, false));

    } else if (m->getType() == MessageType::MOVE_POSITION_REQUEST){
        //start move direction on
        CylinderId cylinder_id = (CylinderId) m->getValue(MessageField::MOVE_POSITION_REQUEST__CYLINDER);
        CylinderPosition position = (CylinderPosition) m->getValue(MessageField::MOVE_POSITION_REQUEST__POSITION);

        c->registerConsumer((Consumer*)new MovePosition(c, m->getCommunicationId(), cylinder_id, position));

    } else if (m->getType() == MessageType::MOVE_TIME_REQUEST){
        //start move direction on
        CylinderId cylinder_id = (CylinderId) m->getValue(MessageField::MOVE_TIME_REQUEST__CYLINDER);
        Timing timing = (Timing) m->getValue(MessageField::MOVE_TIME_REQUEST__TIMING);
        CylinderDirection direction = (CylinderDirection) m->getValue(MessageField::MOVE_TIME_REQUEST__DIRECTION);

        c->registerConsumer((Consumer*)new MoveTime(c, m->getCommunicationId(), cylinder_id, direction, timing));

    } else if (m->getType() == MessageType::DIAG_SETTING_REQUEST){
        //start move direction on
        CylinderId cylinder_id = (CylinderId) m->getValue(MessageField::MOVE_TIME_REQUEST__CYLINDER);
        Timing timing = (Timing) m->getValue(MessageField::MOVE_TIME_REQUEST__TIMING);
        CylinderDirection direction = (CylinderDirection) m->getValue(MessageField::MOVE_TIME_REQUEST__DIRECTION);

        c->registerConsumer((Consumer*)new MoveTime(c, m->getCommunicationId(), cylinder_id, direction, timing));

    }

}

void Master::handleAutoMoveMessages(Controller *c, const ManualInputId &input_id) {//handle auto start messages
    switch(input_id){
        case ManualInputId::AUTO_LOW:
            c->registerConsumer((Consumer*)new Low(c, inp_comm_ids[(int) input_id]));
            break;
        case ManualInputId::AUTO_WORK:
            //todo c->registerConsumer((Consumer*)new Work(c, inp_comm_ids[(int) input_id]));
            break;
        case ManualInputId::AUTO_TRANSPORT:
            //todo c->registerConsumer((Consumer*)new Transport(c, inp_comm_ids[(int) input_id]));
            break;
        default:
            break;
    }
}

void Master::handleStandardMoveMessages(Controller *c, const ManualInputId &input_id) {//standard actions mode independent
    switch (input_id) {
        case ManualInputId::SPINNER_LEFT_UP :
            c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                  CylinderId::SPINNER_LEFT, CylinderDirection::UP, false));
            break;
        case ManualInputId::SPINNER_LEFT_FLOAT :
            c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                  CylinderId::SPINNER_LEFT, CylinderDirection::FLOAT, true));
            break;
        case ManualInputId::SPINNER_RIGHT_UP :
            c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                  CylinderId::SPINNER_RIGHT, CylinderDirection::UP, false));
            break;
        case ManualInputId::SPINNER_RIGHT_FLOAT :
            c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                  CylinderId::SPINNER_RIGHT, CylinderDirection::FLOAT, true));
            break;
        case ManualInputId::SPINNER_LEFT_TELE_IN :
            c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                  CylinderId::SPINNER_TELE_LEFT, CylinderDirection::IN, false));
            break;
        case ManualInputId::SPINNER_LEFT_TELE_OUT :
            c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                  CylinderId::SPINNER_TELE_LEFT, CylinderDirection::OUT, false));
            break;
        case ManualInputId::SPINNER_RIGHT_TELE_IN :
            c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                  CylinderId::SPINNER_TELE_RIGHT, CylinderDirection::IN, false));
            break;
        case ManualInputId::SPINNER_RIGHT_TELE_OUT :
            c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                  CylinderId::SPINNER_TELE_RIGHT, CylinderDirection::OUT, false));
            break;
        case ManualInputId::SPINNER_LEFT_AUTO_THIRD :
            c->registerConsumer((Consumer*)new MovePosition(c, inp_comm_ids[(int) input_id],
                                                 CylinderId::SPINNER_LEFT, CylinderPosition::THIRD));
            break;
        case ManualInputId::SPINNER_RIGHT_AUTO_THIRD :
            c->registerConsumer((Consumer*)new MovePosition(c, inp_comm_ids[(int) input_id],
                                                 CylinderId::SPINNER_RIGHT, CylinderPosition::THIRD));
            break;
        case ManualInputId::REAR_SPINNER_REAR_UP:
            c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                  CylinderId::SPINNER_REAR, CylinderDirection::UP, false));
            break;
        case ManualInputId::REAR_SPINNER_REAR_DOWN:
            c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                  CylinderId::SPINNER_REAR, CylinderDirection::DOWN, false));
            break;

        default:
            break;
    }
}

void Master::handleStateChangeMesages( Controller *c, const ManualInputId &input_id) {
    switch(input_id){
        //mode changer
        case ManualInputId::MOD_OU_FRAME:
            switchMode(c, MasterMode::FRAME);
            break;

        case ManualInputId::MOD_OU_SPINNER_REAR:
            switchMode(c, MasterMode::SPINNER_REAR);
            break;

        case ManualInputId::MOD_LR_STEER:
            switchMode(c, MasterMode::WEEL_STEER);
            break;

        case ManualInputId::MOD_LR_WEEL_LEFT_TELE:
            switchMode(c, MasterMode::WEEL_TELE_LEFT);
            break;

        case ManualInputId::MOD_LR_WEEL_RIGHT_TELE:
            switchMode(c, MasterMode::WEEL_TELE_RIGHT);
            break;

        default:
            break;
    }
}

void Master::handleStateDependentMessages(Controller *c, const ManualInputId &input_id) {//mode dependent starts
    if (mode == MasterMode::SPINNER_REAR) {
        switch (input_id) {
            case ManualInputId::MULTI_UP :
                c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                      CylinderId::SPINNER_REAR, CylinderDirection::UP, false));
                break;
            case ManualInputId::MULTI_DOWN :
                c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                      CylinderId::SPINNER_REAR, CylinderDirection::FLOAT,
                                                      true));
                break;

            default:
                break;
        }

    } else if (mode == MasterMode::WEEL_STEER) {

        switch (input_id) {
            case ManualInputId::MULTI_LEFT :
                c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                      CylinderId::WEEL_STEER, CylinderDirection::LEFT, false));
                break;
            case ManualInputId::MULTI_RIGHT :
                c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                      CylinderId::WEEL_STEER, CylinderDirection::RIGHT, false));
                break;

            default:
                break;
        }

    } else if (mode == MasterMode::WEEL_TELE_LEFT) {

        switch (input_id) {
            case ManualInputId::MULTI_LEFT :
                c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                      CylinderId::WEEL_TELE_LEFT, CylinderDirection::OUT, false));
                break;
            case ManualInputId::MULTI_RIGHT :
                c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                      CylinderId::WEEL_TELE_LEFT, CylinderDirection::IN, false));
                break;

            default:
                break;
        }

    } else if (mode == MasterMode::WEEL_TELE_RIGHT) {

        switch (input_id) {
            case ManualInputId::MULTI_LEFT :
                c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                      CylinderId::WEEL_TELE_RIGHT, CylinderDirection::IN, false));
                break;
            case ManualInputId::MULTI_RIGHT :
                c->registerConsumer((Consumer*)new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                      CylinderId::WEEL_TELE_RIGHT, CylinderDirection::OUT, false));
                break;

            default:
                break;
        }

    }
}

void Master::switchMode(Controller* c, MasterMode new_active_mode, bool first_init) {

    if (new_active_mode != mode || first_init) {


        if(!first_init) {
            //deactivate possible running tasks of old mode
            Message::createActionState(c, getType(), inp_comm_ids[(int)ManualInputId::MULTI_RIGHT], ActionState::STOPPING);
            Message::createActionState(c, getType(), inp_comm_ids[(int)ManualInputId::MULTI_LEFT], ActionState::STOPPING);
            Message::createActionState(c, getType(), inp_comm_ids[(int)ManualInputId::MULTI_UP], ActionState::STOPPING);
            Message::createActionState(c, getType(), inp_comm_ids[(int)ManualInputId::MULTI_DOWN], ActionState::STOPPING);


            //deactivate old led
            if (mode == MasterMode::WEEL_STEER) {
                Message::createLedRequest(c, getType(), comm_id, OutputId::LED_MOD_LR_STEER, IOState::INACTIVE);

            } else if (mode == MasterMode::WEEL_TELE_LEFT) {
                Message::createLedRequest(c, getType(), comm_id, OutputId::LED_MOD_LR_WEEL_TELE_L, IOState::INACTIVE);

            } else if (mode == MasterMode::WEEL_TELE_RIGHT) {
                Message::createLedRequest(c, getType(), comm_id, OutputId::LED_MOD_LR_WEEL_TELE_R, IOState::INACTIVE);

            } else if (mode == MasterMode::FRAME) {
                Message::createLedRequest(c, getType(), comm_id, OutputId::LED_MOD_OU_FRAME, IOState::INACTIVE);

            } else if (mode == MasterMode::SPINNER_REAR) {
                Message::createLedRequest(c, getType(), comm_id, OutputId::LED_MOD_OU_SPINNER_BACK, IOState::INACTIVE);
            }
        }

        //activate new led
        if (new_active_mode == MasterMode::WEEL_STEER) {
            Message::createLedRequest(c, getType(), comm_id, OutputId::LED_MOD_LR_STEER, IOState::ACTIVE);

        } else if (new_active_mode == MasterMode::WEEL_TELE_LEFT) {
            Message::createLedRequest(c, getType(), comm_id, OutputId::LED_MOD_LR_WEEL_TELE_L, IOState::ACTIVE);

        } else if (new_active_mode == MasterMode::WEEL_TELE_RIGHT) {
            Message::createLedRequest(c, getType(), comm_id, OutputId::LED_MOD_LR_WEEL_TELE_R, IOState::ACTIVE);

        } else if (new_active_mode == MasterMode::FRAME) {
            Message::createLedRequest(c, getType(), comm_id, OutputId::LED_MOD_OU_FRAME, IOState::ACTIVE);

        } else if (new_active_mode == MasterMode::SPINNER_REAR) {
            Message::createLedRequest(c, getType(), comm_id, OutputId::LED_MOD_OU_SPINNER_BACK, IOState::ACTIVE);
        }

        mode = new_active_mode;
    }
}
