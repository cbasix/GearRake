//
// Created by cyberxix on 18.02.16.
//

#include "MessageGenerator.h"
#include <iostream>

MessageGenerator::MessageGenerator(Message *right_message, int commmunication_id, bool isTypeVariable, bool isSenderActionTypeVariable,
                                   bool isCommunicationIdVariable) {
    this->right_message = right_message;
    this->isCommIdVariable = isCommunicationIdVariable;
    this->isSenderActionTypeVariable = isSenderActionTypeVariable;
    this->isTypeVariable = isTypeVariable;
    this->communciation_id = commmunication_id;
    for(int i = 0; i < (int)MessageField::ENUM_COUNT; i++){
        datatest[i] = false;
    }
}
void MessageGenerator::generate(Controller* c, Consumer* cons){
    Message m;
    int msg_type = 0;
    if(!isTypeVariable){msg_type = (int)right_message->getType();}
    do {

        int sender_action_type = 0;
        if(!isSenderActionTypeVariable){sender_action_type = (int)right_message->getSenderActionType();}
        do {

            //one third of the testet com ids should be higher than the current one.
            int comm_id = communciation_id-(MSG_GEN_MAX_COMM_ID-(MSG_GEN_MAX_COMM_ID/3));
            if(!isCommIdVariable){comm_id = right_message->getCommunicationId();}
            do {

                m = Message((MessageType) msg_type, (ActionType) sender_action_type, comm_id);
                for (int data_i = 0; data_i < (int)MessageField::ENUM_COUNT ; data_i++) {
                    int rand = 0;
                    if(!datatest[data_i]){rand = right_message->getValue((MessageField)data_i);}
                    do {
                        m.setValue((MessageField) data_i, rand);

                        //PrintTo(m, &std::cout);
                        //std::cout << "\n";
                        if(m == *right_message){
                            rand++;
                            continue;
                        }

                        cons->onMessage(c, &m);

                        rand++;
                    } while (rand < MSG_GEN_MAX_FIELD_VALUE && datatest[data_i]);
                }
                comm_id++;
            } while ( comm_id < (communciation_id+(MSG_GEN_MAX_COMM_ID/3)) && isCommIdVariable);
            sender_action_type++;
        } while ( sender_action_type < (int)ActionType::ENUM_COUNT && isSenderActionTypeVariable);
        msg_type++;
    } while (msg_type < (int)MessageType::ENUM_COUNT && isTypeVariable);
}

void MessageGenerator::setFieldVariable(MessageField i) {
    datatest[(int)i] = true;
}
