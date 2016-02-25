//
// Created by cyberxix on 19.02.16.
//

#include <ConfigStore.h>
#include "Diagnose.h"

Diagnose::Diagnose() {
#ifndef TESTING
    Serial.begin(SERIAL_RATE);
#endif
}

Diagnose::~Diagnose() {
#ifndef TESTING
    Serial.end();
#endif
}


ActionType Diagnose::getType() {
    return ActionType::DIAGNOSE;
}

void Diagnose::onMessage(Controller *c, Message *m) {
    //TODO Implement

}

void Diagnose::produce(Controller *c) {
#ifndef TESTING
    while ( Serial.available()) {
		proto.add(Serial.read());
	}
#endif
    Message m;
    //read input messages
    if(proto.readMessage(&m)){
        if(m.getType() == MessageType::LOG_REQUEST){
            log_update = m.getValue(MessageField::LOG_REQUEST__ACTIVE) != 0;

        } else if(m.getType() == MessageType::FAILURE_STORAGE_REQUEST){
            failure_storage_update = m.getValue(MessageField::FAILURE_STORAGE_REQUEST__ACTIVE) != 0;
            if(failure_storage_update){
                //TODO request all from in failure storage
            }

        } else if(m.getType() == MessageType::STATUS_UPDATE_REQUEST){
            status_update = m.getValue(MessageField::STATUS_UPDATE_REQUEST__ACTIVE) != 0;
            if(status_update){
                //TODO send all status
            }

        } else if(m.getType() == MessageType::ACTIVE_UPDATE_REQUEST){
            active_update = m.getValue(MessageField::ACTIVE_UPDATE_REQUEST__ACTIVE) != 0;
            if(active_update){
                Message m;
                ArrayList<Consumer*>* cons = c->getConsumers();
                for (int i = 0; i < cons->getSize(); ++i) {
                    Consumer* s = cons->get(i);
                    m = Message(MessageType::ACTIVE_STATUS, ActionType::DIAGNOSE, m.getCommunicationId());
                    m.setValue(MessageField::ACTIVE_STATUS__TYPE, (int)s->getType());
                    m.setValue(MessageField::ACTIVE_STATUS__CLASS, (int)ActionClass::CONSUMER);
                    m.setValue(MessageField::ACTIVE_STATUS__ACTIVE, true);

                    proto.send(&m);
                }
                ArrayList<Producer*>* prods = c->getProducers();
                for (int i = 0; i < prods->getSize(); ++i) {
                    Producer* s = prods->get(i);
                    m = Message(MessageType::ACTIVE_STATUS, ActionType::DIAGNOSE, m.getCommunicationId());
                    m.setValue(MessageField::ACTIVE_STATUS__TYPE, (int)s->getType());
                    m.setValue(MessageField::ACTIVE_STATUS__CLASS, (int)ActionClass::PRODUCER);
                    m.setValue(MessageField::ACTIVE_STATUS__ACTIVE, true);

                    proto.send(&m);
                }
            }

        } else if(m.getType() == MessageType::SETTING_REQUEST){
            int setting_type = m.getValue(MessageField::SETTING_REQUEST__TYPE);
            int setting_id = m.getValue(MessageField::SETTING_REQUEST__ID);
            Message answ;
            if(setting_id == 0 || setting_type == 0){
                //send all timeout configs // timeouts are per cylinder position
                for (int i = 0; i < (int)EepromConfig::MAX_TIMEOUTS ; ++i) {
                    sendTimeoutSettingState(m, answ, i);
                }
                //send all timings
                for (int i = 0; i < (int)EepromConfig::MAX_TIMING ; ++i) {
                    sendTimerSettingState(m, answ, i);
                }
            } else {
                if (setting_type == (int)SettingType::TIMEOUT) {
                    sendTimeoutSettingState(m, answ, setting_id);
                } else if (setting_type == (int)SettingType::TIMING) {
                    sendTimerSettingState(m, answ, setting_id);
                }
            }
        } else if(m.getType() == MessageType::SETTING_UPDATE) {
            int setting_type = m.getValue(MessageField::SETTING_UPDATE__TYPE);
            int setting_id = m.getValue(MessageField::SETTING_UPDATE__ID);
            int setting_val = m.getValue(MessageField::SETTING_UPDATE__VALUE);

            if(setting_type == (int)SettingType::TIMEOUT
                    && setting_id < (int) CylinderPosition::ENUM_COUNT
                    && setting_id > 0){
                ConfigStore::setTimeout((CylinderPosition) setting_id, setting_val);

            } else if (setting_type == (int)SettingType::TIMING
                       && setting_id < (int)Timing::ENUM_COUNT
                       && setting_id > 0) {
                ConfigStore::setTimer((Timing) setting_id, setting_val);
            }

        }
    }

    //write outgoing messages - ONLY ONE FRAME PER produce call!
    char last = 0;
    while(proto.getOutSize() > 0 && last != SerialChar::END) {
#ifndef TESTING
        last = proto.getOut();
        Serial.write(char);
#endif
#ifdef TESTING
        last = proto.getOut();
#endif
    }
}

void Diagnose::sendTimerSettingState(Message &m, Message &answ, int setting_id) {
    int val = ConfigStore::getTimerValue((Timing) setting_id);
    answ = Message(MessageType::SETTING_STATE, ActionType::DIAGNOSE, m.getCommunicationId());
    answ.setValue(MessageField::SETTING_STATE__TYPE, (int)SettingType::TIMING);
    answ.setValue(MessageField::SETTING_STATE__ID, setting_id);
    answ.setValue(MessageField::SETTING_STATE__VALUE, val);
    proto.send(&answ);
}

void Diagnose::sendTimeoutSettingState(Message &m, Message &answ, int setting_id) {
    int val = ConfigStore::getTimeoutValue((CylinderPosition) setting_id);
    answ = Message(MessageType::SETTING_STATE, ActionType::DIAGNOSE, m.getCommunicationId());
    answ.setValue(MessageField::SETTING_STATE__TYPE, (int)SettingType::TIMEOUT);
    answ.setValue(MessageField::SETTING_STATE__ID, setting_id);
    answ.setValue(MessageField::SETTING_STATE__VALUE, val);
    proto.send(&answ);
}