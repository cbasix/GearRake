//
// Created by cyberxix on 24.02.16.
//

#include "Output.h"

/*
 *     // all pins on expander used as outputs!
exp1 = new Adafruit_MCP23017();
exp1->begin(EXP1_ADDR);

exp2 = new Adafruit_MCP23017();
exp2->begin(EXP2_ADDR);

exp3 = new Adafruit_MCP23017();
exp3->begin(EXP3_ADDR);
//////Serial.println("Settup expanders done");
 *
 * //all initalisations inverted because outputs are active when connected to ground and internal active = 1
    for(int i = 0; i < OUTPUT_ID_COUNT; i++){
        output_data[i].state = INACTIVE;
        output_data[i].state_changed = false;

        if(output_data[i].output_pin >= PIN_ARDUINO_START &&
           output_data[i].output_pin <= PIN_ARDUINO_END){

            digitalWrite(output_data[i].output_pin - PIN_ARDUINO_START, !INACTIVE);
            pinMode(output_data[i].output_pin - PIN_ARDUINO_START, OUTPUT);


            ////Serial.print(" PIN MODE to OUTPUT Arduino: ");
            ////Serial.println(output_data[i].output_pin - PIN_ARDUINO_START);

        } else if(output_data[i].output_pin >= PIN_EXP1_START &&
                  output_data[i].output_pin <= PIN_EXP1_END){

            exp1->digitalWrite(output_data[i].output_pin - PIN_EXP1_START, !INACTIVE);
            exp1->pinMode(output_data[i].output_pin - PIN_EXP1_START, OUTPUT);

            ////Serial.print(" PIN MODE to OUTPUT exp1: ");
            ////Serial.println(output_data[i].output_pin - PIN_EXP1_START);

        } else if(output_data[i].output_pin >= PIN_EXP2_START &&
                  output_data[i].output_pin <= PIN_EXP2_END){

            exp2->digitalWrite(output_data[i].output_pin - PIN_EXP2_START, !INACTIVE);
            exp2->pinMode(output_data[i].output_pin - PIN_EXP2_START, OUTPUT);

            ////Serial.print(" PIN MODE to OUTPUT exp2: ");
            ////Serial.println(output_data[i].output_pin - PIN_EXP2_START);

        } else if(output_data[i].output_pin >= PIN_EXP3_START &&
                  output_data[i].output_pin <= PIN_EXP3_END){

            exp3->digitalWrite(output_data[i].output_pin - PIN_EXP3_START, !INACTIVE);
            exp3->pinMode(output_data[i].output_pin - PIN_EXP3_START, OUTPUT);

            ////Serial.print(" PIN MODE to OUTPUT exp3: ");
            ////Serial.println(output_data[i].output_pin - PIN_EXP3_START);
        }

    }*/

Output::Output(ExpanderWrapper exp[], int exp_len, OutputData out[], int out_len, Cylinder* cylinders[], int cyl_len) {
    this->exp = exp;
    this->exp_len = exp_len;
    this->out = out;
    this->out_len = out_len;
    this->cylinders = cylinders;
    this->cyl_len = cyl_len;

    //set all outputs to INACTIVE
    for (int i = 0; i < out_len; i++) {
        setOutput((OutputId)i, IOState::INACTIVE, true); //set to inactive and initialize pins as outputs
    }
}

void Output::setOutput(OutputId output_id, IOState value, bool initalize) {
    int i_output_id = (int)output_id;
    if(i_output_id < 0 || i_output_id > out_len){
        return; //todo throw error?
    }
    if(!initalize && out[i_output_id].state == value){
        //is already set -> to nothing
        return;
    }

    if (out[i_output_id].output_pin >= PIN_ARDUINO_START &&
        out[i_output_id].output_pin <= PIN_ARDUINO_END) {

        out[i_output_id].state = value;
        ReadWriteWrapper::digitalWrite(out[i_output_id].output_pin - PIN_ARDUINO_START, !value);
        if (initalize) {
            ReadWriteWrapper::pinMode(out[i_output_id].output_pin - PIN_ARDUINO_START, ReadWriteWrapper::W_OUTPUT);
        }


        ////Serial.print(" PIN MODE to OUTPUT Arduino: ");
        ////Serial.println(out[i].output_pin - PIN_ARDUINO_START);

        //handle all outputs on the expanders
    } else if (out[i_output_id].output_pin >= PIN_EXP_START &&
               out[i_output_id].output_pin <= PIN_EXP_END) {

        int expander_no = out[i_output_id].output_pin / PIN_EXP_SIZE; //integer devision
        int pin_on_expander = out[i_output_id].output_pin % expander_no;

        out[i_output_id].state = value;
        exp[expander_no].digitalWrite(pin_on_expander, !value);
        if (initalize) {
            exp[expander_no].pinMode(out[i_output_id].output_pin - PIN_EXP1_START, ReadWriteWrapper::W_OUTPUT);
        }

        ////Serial.print(" PIN MODE to OUTPUT exp1: ");
        ////Serial.println(out[i].output_pin - PIN_EXP1_START);

    }
}

ActionType Output::getType() {
    return ActionType::OUTPUT;
}

void Output::onMessage(Controller *c, Message *m) {
    if (m->getType() == MessageType::CYLINDER_REQUEST) {
        int cylinder_id = m->getValue(MessageField::CYLINDER_REQUEST__CYLINDER);
        if (cylinder_id < 0 || cylinder_id > cyl_len) {
            return; //todo throw failure message?
        }
        Cylinder* cyl = cylinders[cylinder_id];
        CylinderDirection direction = (CylinderDirection) m->getValue(MessageField::CYLINDER_REQUEST__DIRECTION);

        OutputId out_up_id = cyl->getOutputId(CylinderDirection::UP);
        OutputId out_down_id = cyl->getOutputId(CylinderDirection::DOWN);

        //direction up/out/open are the same have a look at the cylerDirection definition
        if (direction == CylinderDirection::UP) {
            //stop down start up
            setOutput(out_down_id, IOState::INACTIVE);
            setOutput(out_up_id, IOState::ACTIVE);

        } else if (direction == CylinderDirection::DOWN) {
            //stop up start down
            setOutput(out_up_id, IOState::INACTIVE);
            setOutput(out_down_id, IOState::ACTIVE);

        } else {
            //stop both outputs
            setOutput(out_up_id, IOState::INACTIVE);
            setOutput(out_down_id, IOState::INACTIVE);
        }


        //decide if pressure is needed
        IOState isPressure = IOState::INACTIVE;
        for (int i = 0; i < cyl_len; ++i) {
            Cylinder* l_cyl = cylinders[i];
            IOState up_active = out[(int) l_cyl->getOutputId(CylinderDirection::UP)].state;
            IOState down_active = out[(int) l_cyl->getOutputId(CylinderDirection::UP)].state;

            if (up_active || (down_active && l_cyl->downNeedsPressure())) {
                isPressure = IOState::ACTIVE;
            }

        }
        //set pressure
        setOutput(OutputId::PRESSURE, isPressure);

    } if (m->getType() == MessageType::LED_REQUEST) {
        OutputId id = (OutputId)m->getValue(MessageField::LED_REQUEST__ID);
        IOState value = (IOState)m->getValue(MessageField::LED_REQUEST__STATE);
        setOutput(id, value);
    }

}

OutputData::OutputData(int output_pin) {
    this->output_pin = output_pin;
    this->state = IOState::INACTIVE;
}
