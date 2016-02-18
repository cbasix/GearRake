//
// Created by cyberxix on 18.02.16.
//

#ifndef GEARRAKE_MESSAGEGENERATOR_H
#define GEARRAKE_MESSAGEGENERATOR_H

#include "Message.h"
#define MSG_GEN_MAX_FIELD_VALUE 10
#define MSG_GEN_MAX_COMM_ID 20


class MessageGenerator {
public:
    MessageGenerator(Message *right_message, int communcation_id, bool isTypeVariable,
                     bool isSenderActionTypeVariable, bool isCommunicationIdVariable);
    void setFieldVariable(MessageField i);
    bool isTypeVariable;
    bool isSenderActionTypeVariable;
    bool isCommIdVariable;
    Message* right_message;
    void generate(Controller* c, Consumer* cons);
    bool datatest[(int)MessageField::ENUM_COUNT];
    int communciation_id;
};


#endif //GEARRAKE_MESSAGEGENERATOR_H
