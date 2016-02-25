//
// Created by cyberxix on 19.02.16.
//

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

        //todo auto function start
        //some input activated
        if ((IOState) m->getValue(MessageField::MANUAL_INPUT_CHANGE__VALUE) == IOState::ACTIVE) {
            ManualInputId input_id = (ManualInputId) m->getValue(MessageField::MANUAL_INPUT_CHANGE__ID);

            //standard actions mode independent
            switch (input_id) {
                case ManualInputId::SPINNER_LEFT_UP :
                    c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                          CylinderId::SPINNER_LEFT, CylinderDirection::UP));
                    break;
                case ManualInputId::SPINNER_LEFT_FLOAT :
                    c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                          CylinderId::SPINNER_LEFT, CylinderDirection::FLOAT, true));
                    break;
                case ManualInputId::SPINNER_RIGHT_UP :
                    c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                          CylinderId::SPINNER_RIGHT, CylinderDirection::UP));
                    break;
                case ManualInputId::SPINNER_RIGHT_FLOAT :
                    c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                          CylinderId::SPINNER_RIGHT, CylinderDirection::FLOAT, true));
                    break;
                case ManualInputId::SPINNER_LEFT_TELE_IN :
                    c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                          CylinderId::SPINNER_TELE_LEFT, CylinderDirection::IN));
                    break;
                case ManualInputId::SPINNER_LEFT_TELE_OUT :
                    c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                          CylinderId::SPINNER_TELE_LEFT, CylinderDirection::OUT));
                    break;
                case ManualInputId::SPINNER_RIGHT_TELE_IN :
                    c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                          CylinderId::SPINNER_TELE_RIGHT, CylinderDirection::IN));
                    break;
                case ManualInputId::SPINNER_RIGHT_TELE_OUT :
                    c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                          CylinderId::SPINNER_TELE_RIGHT, CylinderDirection::OUT));
                    break;
                case ManualInputId::SPINNER_LEFT_AUTO_THIRD :
                    c->registerConsumer(new MovePosition(c, inp_comm_ids[(int) input_id],
                                                         CylinderId::SPINNER_LEFT, CylinderPosition::THIRD));
                    break;
                case ManualInputId::SPINNER_RIGHT_AUTO_THIRD :
                    c->registerConsumer(new MovePosition(c, inp_comm_ids[(int) input_id],
                                                         CylinderId::SPINNER_RIGHT, CylinderPosition::THIRD));
                    break;
                case ManualInputId::REAR_SPINNER_REAR_UP:
                    c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                          CylinderId::SPINNER_REAR, CylinderDirection::UP));
                    break;
                case ManualInputId::REAR_SPINNER_REAR_DOWN:
                    c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                          CylinderId::SPINNER_REAR, CylinderDirection::DOWN));
                    break;

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
            //mode dependent starts
            if (mode == MasterMode::SPINNER_REAR) {

                switch (input_id) {
                    case ManualInputId::MULTI_UP :
                        c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                              CylinderId::SPINNER_REAR, CylinderDirection::UP));
                        break;
                    case ManualInputId::MULTI_DOWN :
                        c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                              CylinderId::SPINNER_REAR, CylinderDirection::FLOAT,
                                                              true));
                        break;

                    default:
                        break;
                }

            } else if (mode == MasterMode::WEEL_STEER) {

                switch (input_id) {
                    case ManualInputId::MULTI_LEFT :
                        c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                              CylinderId::WEEL_STEER, CylinderDirection::LEFT));
                        break;
                    case ManualInputId::MULTI_RIGHT :
                        c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                              CylinderId::WEEL_STEER, CylinderDirection::RIGHT));
                        break;

                    default:
                        break;
                }

            } else if (mode == MasterMode::WEEL_TELE_LEFT) {

                switch (input_id) {
                    case ManualInputId::MULTI_LEFT :
                        c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                              CylinderId::WEEL_TELE_LEFT, CylinderDirection::OUT));
                        break;
                    case ManualInputId::MULTI_RIGHT :
                        c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                              CylinderId::WEEL_TELE_LEFT, CylinderDirection::IN));
                        break;

                    default:
                        break;
                }

            } else if (mode == MasterMode::WEEL_TELE_RIGHT) {

                switch (input_id) {
                    case ManualInputId::MULTI_LEFT :
                        c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                              CylinderId::WEEL_TELE_RIGHT, CylinderDirection::IN));
                        break;
                    case ManualInputId::MULTI_RIGHT :
                        c->registerConsumer(new MoveDirection(c, inp_comm_ids[(int) input_id],
                                                              CylinderId::WEEL_TELE_RIGHT, CylinderDirection::OUT));
                        break;

                    default:
                        break;
                }

            }

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
