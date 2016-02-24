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

Output::Output(ExpanderWrapper exp[], int exp_len, OutputData out[], int out_len) {
    this->exp = exp;
    this->exp_len = exp_len;

    //set all outputs to INACTIVE
    //all initalisations inverted because outputs are active when connected to ground and internal active = 1
    for(int i = 0; i < out_len; i++){
        if(out[i].output_pin >= PIN_ARDUINO_START &&
           out[i].output_pin <= PIN_ARDUINO_END){

            ReadWriteWrapper::digitalWrite(out[i].output_pin - PIN_ARDUINO_START, !IOState::INACTIVE);
            ReadWriteWrapper::pinMode(out[i].output_pin - PIN_ARDUINO_START, ReadWriteWrapper::OUTPUT);


            ////Serial.print(" PIN MODE to OUTPUT Arduino: ");
            ////Serial.println(out[i].output_pin - PIN_ARDUINO_START);

            //handle all outputs on the expanders
        } else if(out[i].output_pin >= PIN_EXP_START &&
                  out[i].output_pin <= PIN_EXP_END){

            int expander_no = out[i].output_pin / PIN_EXP_SIZE; //integer devision
            int pin_on_expander = out[i].output_pin % expander_no;

            exp[expander_no].digitalWrite(pin_on_expander, !IOState::INACTIVE);
            exp[expander_no].pinMode(out[i].output_pin - PIN_EXP1_START, ReadWriteWrapper::OUTPUT);

            ////Serial.print(" PIN MODE to OUTPUT exp1: ");
            ////Serial.println(out[i].output_pin - PIN_EXP1_START);

        }
    }
}

ActionType Output::getType() {
    return ActionType::OUTPUT ;
}

void Output::onMessage(Controller *c, Message *m) {

}

OutputData::OutputData(int output_pin) {
    this->output_pin = output_pin;
    this->state = IOState::INACTIVE;
}
