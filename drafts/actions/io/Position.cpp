//
// Created by cyberxix on 24.02.16.
//

#include "Position.h"

Position::Position(Cylinder* cylinder[], int cyl_len) {
    this->cylinders = cylinder;
    this->cyl_len = cyl_len;
    for (int i = 0; i < (int)CylinderId::ENUM_COUNT; ++i) {
        cylinder_pos[i] = CylinderPosition::NONE;
    }
}

ActionType Position::getType() {
    return ActionType::POSITION ;
}

void Position::onMessage(Controller *c, Message *m) {
    if(m->getType() == MessageType::SENSOR_INPUT_CHANGE
            && m->getSenderActionType() == ActionType::INPUT ){

        SensorInputId sensor_id = (SensorInputId) m->getValue(MessageField::SENSOR_INPUT_CHANGE__ID);
        IOState state = (IOState) m->getValue(MessageField::SENSOR_INPUT_CHANGE__VALUE);
        for (int i = 0; i < cyl_len ; ++i) {
            cylinders[i]->update(sensor_id, (bool)state);
            CylinderPosition new_pos = cylinders[i]->getPosition();

            if(cylinder_pos[i] != new_pos){
                cylinder_pos[i] = new_pos;
                Message::createPositionChange(c, getType(), m->getCommunicationId(), (CylinderId)i, new_pos);
            }
        }
    } else if(m->getType() == MessageType::POSITION_REQUEST) {

        int id = m->getValue(MessageField::POSITION_REQUEST__CYLINDER);
        //return saved position for cylinder
        if (id < cyl_len) {
            CylinderPosition pos = cylinder_pos[id];

            Message::createPositionState(c, getType(), m->getCommunicationId(), (CylinderId)id, pos);
        }

    }
}
