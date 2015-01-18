
#include "input_output.h"
#include "Arduino.h"
#include "Adafruit_MCP23017.h"


FifoInputQueue::FifoInputQueue() {
	next_in = 0;
	next_out = 0;
}


void FifoInputQueue::add(EventData evt) {

	//if queue is full the oldest input gets overwritten
	if(size() >= EVENT_QUEUE_SIZE - 1){
		next_out++;
		if(next_out >= EVENT_QUEUE_SIZE){
			next_out = 0;
		}
	}

	event_data[next_in] = evt;

	next_in++;
	if(next_in >= EVENT_QUEUE_SIZE){
		next_in = 0;
	}



}

EventData* FifoInputQueue::get() {

	if(size() > 0){


		EventData* temp =  &event_data[next_out];

		next_out++;
		if(next_out >= EVENT_QUEUE_SIZE){
			next_out = 0;
		}

		return temp;
	}

	//TODO Bullshit
	return 0;
}

int FifoInputQueue::size() {
	if(next_in > next_out){
		return next_in - next_out;

	} else if (next_in < next_out){
		return (EVENT_QUEUE_SIZE - next_out) + next_in;
	}

	return 0;
}


InputObject::InputObject(TaskMonitor* task_monitor) {
	tm = task_monitor;

	//Initialize input array -> Pin mapping definition
	//all inputs must be on arduino!

	//loop for default values
	unsigned int now = millis();
	for(int i = 0; i < INPUT_ID_COUNT; i++){
			input_data[i].debounced_state = INACTIVE;
			input_data[i].temp_change_time = now;
			input_data[i].input_type = TYPE_SENSOR;
			input_data[i].temp_state = INACTIVE;
			input_data[i].active = true;

	}


	//Left Joystick
	input_data[IN_SPINNER_LEFT_UP].input_pin = PIN_ARDUINO_ANALOG_POSITIVE_START + 0;
	input_data[IN_SPINNER_LEFT_UP].input_type = TYPE_MANUAL;
	input_data[IN_SPINNER_LEFT_UP].active = false;
	//!
	input_data[IN_SPINNER_LEFT_FLOAT].input_pin = PIN_ARDUINO_ANALOG_NEGATIVE_START + 0;
	input_data[IN_SPINNER_LEFT_FLOAT].input_type = TYPE_MANUAL;
	input_data[IN_SPINNER_LEFT_FLOAT].active = false;

	input_data[IN_SPINNER_LEFT_TELE_OUT].input_pin = PIN_ARDUINO_ANALOG_POSITIVE_START + 1;
	input_data[IN_SPINNER_LEFT_TELE_OUT].input_type = TYPE_MANUAL;
	input_data[IN_SPINNER_LEFT_TELE_OUT].active = false;

	input_data[IN_SPINNER_LEFT_TELE_IN].input_pin = PIN_ARDUINO_ANALOG_NEGATIVE_START + 1;
	input_data[IN_SPINNER_LEFT_TELE_IN].input_type = TYPE_MANUAL;
	input_data[IN_SPINNER_LEFT_TELE_IN].active = false;



	//Right Joystick
	input_data[IN_SPINNER_RIGHT_UP].input_pin = PIN_ARDUINO_ANALOG_POSITIVE_START + 2;
	input_data[IN_SPINNER_RIGHT_UP].input_type = TYPE_MANUAL;
	input_data[IN_SPINNER_RIGHT_UP].active = false;

	input_data[IN_SPINNER_RIGHT_FLOAT].input_pin = PIN_ARDUINO_ANALOG_NEGATIVE_START + 2;
	input_data[IN_SPINNER_RIGHT_FLOAT].input_type = TYPE_MANUAL;
	input_data[IN_SPINNER_RIGHT_FLOAT].active = false;

	//!
	input_data[IN_SPINNER_RIGHT_TELE_OUT].input_pin = PIN_ARDUINO_ANALOG_POSITIVE_START + 3;
	input_data[IN_SPINNER_RIGHT_TELE_OUT].input_type = TYPE_MANUAL;
	input_data[IN_SPINNER_RIGHT_TELE_OUT].active = false;

	input_data[IN_SPINNER_RIGHT_TELE_IN].input_pin = PIN_ARDUINO_ANALOG_NEGATIVE_START + 3;
	input_data[IN_SPINNER_RIGHT_TELE_IN].input_type = TYPE_MANUAL;
	input_data[IN_SPINNER_RIGHT_TELE_IN].active = false;


	//Middle Joystick
	//!
	input_data[IN_MULTI_UP].input_pin = PIN_ARDUINO_ANALOG_POSITIVE_START + 4;
	input_data[IN_MULTI_UP].input_type = TYPE_MANUAL;
	//input_data[IN_MULTI_UP].active = false;

	input_data[IN_MULTI_DOWN].input_pin = PIN_ARDUINO_ANALOG_NEGATIVE_START + 4;
	input_data[IN_MULTI_DOWN].input_type = TYPE_MANUAL;
	//input_data[IN_MULTI_DOWN].active = false;


	//!
	input_data[IN_MULTI_RIGHT].input_pin = PIN_ARDUINO_ANALOG_POSITIVE_START + 5;
	input_data[IN_MULTI_RIGHT].input_type = TYPE_MANUAL;
	//input_data[IN_MULTI_RIGHT].active = false;

	input_data[IN_MULTI_LEFT].input_pin = PIN_ARDUINO_ANALOG_NEGATIVE_START + 5;
	input_data[IN_MULTI_LEFT].input_type = TYPE_MANUAL;
	//input_data[IN_MULTI_LEFT].active = false;


	//Top Buttons
	input_data[IN_AUTO_TRANSPORT].input_pin = PIN_ARDUINO_START + 2;
	input_data[IN_AUTO_TRANSPORT].input_type = TYPE_MANUAL;

	input_data[IN_AUTO_LOW].input_pin = PIN_ARDUINO_START + 3;
	input_data[IN_AUTO_LOW].input_type = TYPE_MANUAL;

	input_data[IN_AUTO_WORK].input_pin = PIN_ARDUINO_START + 4;
	input_data[IN_AUTO_WORK].input_type = TYPE_MANUAL;


	//Modifier Buttons Links Rechts
	input_data[IN_MOD_LR_STEER].input_pin = PIN_ARDUINO_START + 5;
	input_data[IN_MOD_LR_STEER].input_type = TYPE_MANUAL;

	input_data[IN_MOD_LR_UNUSED1].input_pin = PIN_ARDUINO_START + 6;
	input_data[IN_MOD_LR_UNUSED1].input_type = TYPE_MANUAL;

	input_data[IN_MOD_LR_UNUSED2].input_pin = PIN_ARDUINO_START + 7;
	input_data[IN_MOD_LR_UNUSED2].input_type = TYPE_MANUAL;

	input_data[IN_MOD_LR_WEEL_RIGHT_TELE].input_pin = PIN_ARDUINO_START + 8;
	input_data[IN_MOD_LR_WEEL_RIGHT_TELE].input_type = TYPE_MANUAL;

	input_data[IN_MOD_LR_WEEL_LEFT_TELE].input_pin = PIN_ARDUINO_START + 9;
	input_data[IN_MOD_LR_WEEL_LEFT_TELE].input_type = TYPE_MANUAL;


	//Modifier Buttons oben unten
	input_data[IN_MOD_OU_SPINNER_BACK].input_pin = PIN_ARDUINO_START + 10;
	input_data[IN_MOD_OU_SPINNER_BACK].input_type = TYPE_MANUAL;

	input_data[IN_MOD_OU_FRAME].input_pin = PIN_ARDUINO_START + 11;
	input_data[IN_MOD_OU_FRAME].input_type = TYPE_MANUAL;

	input_data[IN_MOD_OU_UNUSED].input_pin = PIN_ARDUINO_START + 12;
	input_data[IN_MOD_OU_UNUSED].input_type = TYPE_MANUAL;


	//Sensors
	input_data[SENS_SPINNER_LEFT_THIRD].input_pin = PIN_ARDUINO_START + 22;

	input_data[SENS_SPINNER_RIGHT_THIRD].input_pin = PIN_ARDUINO_START + 23;


	input_data[SENS_SPINNER_LEFT_UP].input_pin = PIN_ARDUINO_START + 24;

	input_data[SENS_SPINNER_RIGHT_UP].input_pin = PIN_ARDUINO_START + 25;

	input_data[SENS_SPINNER_REAR_UP].input_pin = PIN_ARDUINO_START + 26;


	input_data[SENS_SPINNER_LEFT_TELE_OUT].input_pin = PIN_ARDUINO_START + 27;

	input_data[SENS_SPINNER_LEFT_TELE_IN].input_pin = PIN_ARDUINO_START + 28;


	input_data[SENS_SPINNER_RIGHT_TELE_OUT].input_pin = PIN_ARDUINO_START + 29;

	input_data[SENS_SPINNER_RIGHT_TELE_IN].input_pin = PIN_ARDUINO_START + 30;


	input_data[SENS_FRAME_UP].input_pin = PIN_ARDUINO_START + 31;

	input_data[SENS_FRAME_MIDDLE].input_pin = PIN_ARDUINO_START + 32;

	input_data[SENS_FRAME_LOW].input_pin = PIN_ARDUINO_START + 33;

	input_data[SENS_FRAME_DOWN].input_pin = PIN_ARDUINO_START + 34;


	input_data[SENS_FRAME_LOCK_OPEN].input_pin = PIN_ARDUINO_START + 35;

	input_data[SENS_FRAME_LOCK_CLOSED].input_pin = PIN_ARDUINO_START + 36;


	input_data[SENS_WEEL_TELE_RIGHT_OUT].input_pin = PIN_ARDUINO_START + 37;

	input_data[SENS_WEEL_TELE_RIGHT_IN].input_pin = PIN_ARDUINO_START + 38;


	input_data[SENS_WEEL_TELE_LEFT_OUT].input_pin = PIN_ARDUINO_START + 39;

	input_data[SENS_WEEL_TELE_LEFT_IN].input_pin = PIN_ARDUINO_START + 40;


	input_data[SENS_WEEL_TRACK_MIDDLE].input_pin = PIN_ARDUINO_START + 41;



	for(int i = 0; i < INPUT_ID_COUNT; i++){

		if(input_data[i].input_pin >= PIN_ARDUINO_START &&
				input_data[i].input_pin <= PIN_ARDUINO_END){
			pinMode(input_data[i].input_pin, INPUT_PULLUP);

			////Serial.print(" PIN MODE to INPUT Arduino: ");
			////Serial.println(input_data[i].input_pin - PIN_ARDUINO_START);

		} else  if(input_data[i].input_pin >= PIN_ARDUINO_ANALOG_POSITIVE_START &&
				input_data[i].input_pin <= PIN_ARDUINO_ANALOG_POSITIVE_END){

			pinMode(A0 + (input_data[i].input_pin - PIN_ARDUINO_ANALOG_POSITIVE_START), INPUT_PULLUP);

			////Serial.print(" PIN MODE to INPUT Arduino Analog Pos: ");
			////Serial.println(input_data[i].input_pin - PIN_ARDUINO_START);

		} else  if(input_data[i].input_pin >= PIN_ARDUINO_ANALOG_NEGATIVE_START &&
				input_data[i].input_pin <= PIN_ARDUINO_ANALOG_NEGATIVE_END){

			pinMode(A0 + (input_data[i].input_pin - PIN_ARDUINO_ANALOG_NEGATIVE_START), INPUT_PULLUP);

			////Serial.print(" PIN MODE to INPUT Arduino Analog Neg: ");
			////Serial.println(input_data[i].input_pin - PIN_ARDUINO_START);
		}
	}

}

bool InputObject::getInputState(int input_id) {
	return input_data[input_id].debounced_state;
}


void InputObject::readInput(){
	unsigned int now = millis();

	/*unsigned static int count = 0;
	unsigned static int diff = 0;
	unsigned static int now2 = millis();

	unsigned int temp_diff = millis() - now2;
	diff = (diff * count + temp_diff) / (count + 1);
	count++;

	if(count == 10000){
		////Serial.print("Ms per round:");
		////Serial.println(diff);

		count = 0;
	}*/


	for(int i = 0; i < INPUT_ID_COUNT; i++){
		if(!input_data[i].active){
			continue;
		}

		bool readed;

		if(input_data[i].input_pin >= PIN_ARDUINO_START
				&& input_data[i].input_pin <= PIN_ARDUINO_END){

			//inputs are all pulled up if input button is pressed digitalRead outputs 0 -> negate with !
			readed = !digitalRead(input_data[i].input_pin);



		} else if(input_data[i].input_pin >= PIN_ARDUINO_ANALOG_NEGATIVE_START
				&& input_data[i].input_pin <= PIN_ARDUINO_ANALOG_NEGATIVE_END){

			int temp = analogRead(input_data[i].input_pin - PIN_ARDUINO_ANALOG_NEGATIVE_START);

//			//Serial.print("Analog Read Pin:");
//			//Serial.print(input_data[i].input_pin);
//			//Serial.print(" Value: ");
//			//Serial.println(temp);

			if(temp < JOY_MIDDLE - JOY_TOLERANCE){
				readed = ACTIVE;
			} else {
				readed = INACTIVE;
			}


		} else if(input_data[i].input_pin >= PIN_ARDUINO_ANALOG_POSITIVE_START
				&& input_data[i].input_pin <= PIN_ARDUINO_ANALOG_POSITIVE_END){

			int temp = analogRead(input_data[i].input_pin - PIN_ARDUINO_ANALOG_POSITIVE_START);

//			//Serial.print("Analog Read Pin:");
//			//Serial.print(input_data[i].input_pin);
//			//Serial.print(" Value: ");
//			//Serial.println(temp);

			if(temp > JOY_MIDDLE + JOY_TOLERANCE){
				readed = ACTIVE;
			} else {
				readed = INACTIVE;
			}


		}


		//debouncing
		if (readed != input_data[i].temp_state){
			input_data[i].temp_state = readed;
			input_data[i].temp_change_time = now;
		}

		if(input_data[i].temp_state != input_data[i].debounced_state
				&& input_data[i].temp_change_time + DEBOUNCE_TIME < now){

			input_data[i].debounced_state = input_data[i].temp_state;

			EventData e;
			e.input_id = i;
			e.input_type = input_data[i].input_type;
			e.input_value = input_data[i].debounced_state;

			tm->addInput(&e);

		}

	}

}


OutputObject::OutputObject(TaskMonitor* task_monitor){
	tm = task_monitor;

	//////Serial.println("Setting up expanders");
	/* all pins on expander used as outputs!*/
	exp1 = new Adafruit_MCP23017();
	exp1->begin(EXP1_ADDR);

	exp2 = new Adafruit_MCP23017();
	exp2->begin(EXP2_ADDR);

	exp3 = new Adafruit_MCP23017();
	exp3->begin(EXP3_ADDR);
	//////Serial.println("Settup expanders done");

	//NOTE numbers on relay boards are higher by one because pin numbering on relay board starts with 1
	output_data[OUT_SPINNER_RIGHT_UP].output_pin = PIN_EXP1_START + 0;
	output_data[OUT_SPINNER_LEFT_UP].output_pin = PIN_EXP1_START + 1;
	output_data[OUT_SPINNER_REAR_UP].output_pin = PIN_EXP1_START + 2;

	output_data[OUT_SPINNER_RIGHT_FLOAT].output_pin = PIN_EXP1_START + 3;
	output_data[OUT_SPINNER_LEFT_FLOAT].output_pin = PIN_EXP1_START + 4;
	output_data[OUT_SPINNER_REAR_FLOAT].output_pin = PIN_EXP1_START + 5;

	output_data[OUT_SPINNER_RIGHT_TELE_OUT].output_pin = PIN_EXP1_START + 6;
	output_data[OUT_SPINNER_LEFT_TELE_OUT].output_pin = PIN_EXP1_START + 7;

	output_data[OUT_SPINNER_RIGHT_TELE_IN].output_pin = PIN_EXP1_START + 8;
	output_data[OUT_SPINNER_LEFT_TELE_IN].output_pin = PIN_EXP1_START + 9;

	output_data[OUT_FRAME_UP].output_pin = PIN_EXP1_START + 10;
	output_data[OUT_FRAME_DOWN].output_pin = PIN_EXP1_START + 11;

	output_data[OUT_STEER_LEFT].output_pin = PIN_EXP1_START + 12;
	output_data[OUT_STEER_RIGHT].output_pin = PIN_EXP1_START + 13;

	//expander 2
	output_data[OUT_WEEL_TELE_LEFT_IN].output_pin = PIN_EXP1_START + 14;
	output_data[OUT_WEEL_TELE_RIGHT_IN].output_pin = PIN_EXP1_START + 15;

	output_data[OUT_WEEL_TELE_LEFT_OUT].output_pin = PIN_EXP2_START + 0;
	output_data[OUT_WEEL_TELE_RIGHT_OUT].output_pin = PIN_EXP2_START + 1;

	output_data[OUT_FRAME_LOCK_UP].output_pin = PIN_EXP2_START + 2;
	output_data[OUT_FRAME_LOCK_DOWN].output_pin = PIN_EXP2_START + 3;

	output_data[OUT_PRESSURE].output_pin = PIN_EXP2_START + 4;

	//Leds
	output_data[LED_WEEL_TRACK_MIDDLE].output_pin = PIN_EXP2_START + 5;
	output_data[LED_FRAME_LOCK].output_pin = PIN_EXP2_START + 6;

	//Top Buttons
	output_data[LED_AUTO_TRANSPORT].output_pin = PIN_EXP2_START + 7;
	output_data[LED_AUTO_LOW].output_pin = PIN_EXP2_START + 8;
	output_data[LED_AUTO_WORK].output_pin = PIN_EXP2_START + 9;

	//Float Leds
	output_data[LED_SPINNER_RIGHT_FLOAT].output_pin = PIN_EXP2_START + 10;
	output_data[LED_SPINNER_LEFT_FLOAT].output_pin = PIN_EXP2_START + 11;
	output_data[LED_SPINNER_REAR_FLOAT].output_pin = PIN_EXP2_START + 12;

	//Modifier Leds Links Rechts
	output_data[LED_MOD_LR_STEER].output_pin = PIN_EXP2_START + 13;
	output_data[LED_MOD_LR_UNUSED1].output_pin = PIN_EXP2_START + 14;
	output_data[LED_MOD_LR_UNUSED2].output_pin = PIN_EXP2_START + 15;
	output_data[LED_MOD_LR_WEEL_TELE_R].output_pin = PIN_EXP3_START + 0;
	output_data[LED_MOD_LR_WEEL_TELE_L].output_pin = PIN_EXP3_START + 1;

	//Modifier Leds Links Rechts
	output_data[LED_MOD_OU_SPINNER_BACK].output_pin = PIN_EXP3_START + 2;
	output_data[LED_MOD_OU_FRAME].output_pin = PIN_EXP3_START + 3;
	output_data[LED_MOD_OU_UNUSED].output_pin = PIN_EXP3_START + 4;


	//all initalisations inverted because outputs are active when connected to ground and internal active = 1
	for(int i = 0; i < OUTPUT_ID_COUNT; i++){
		output_data[i].state = INACTIVE;
		output_data[i].state_changed = false;

		if(output_data[i].output_pin >= PIN_ARDUINO_START &&
				output_data[i].output_pin <= PIN_ARDUINO_END){

			pinMode(output_data[i].output_pin - PIN_ARDUINO_START, OUTPUT);
			digitalWrite(output_data[i].output_pin - PIN_ARDUINO_START, !INACTIVE);

			////Serial.print(" PIN MODE to OUTPUT Arduino: ");
			////Serial.println(output_data[i].output_pin - PIN_ARDUINO_START);

		} else if(output_data[i].output_pin >= PIN_EXP1_START &&
				output_data[i].output_pin <= PIN_EXP1_END){

			exp1->pinMode(output_data[i].output_pin - PIN_EXP1_START, OUTPUT);
			exp1->digitalWrite(output_data[i].output_pin - PIN_EXP1_START, !INACTIVE);

			////Serial.print(" PIN MODE to OUTPUT exp1: ");
			////Serial.println(output_data[i].output_pin - PIN_EXP1_START);

		} else if(output_data[i].output_pin >= PIN_EXP2_START &&
				output_data[i].output_pin <= PIN_EXP2_END){

			exp2->pinMode(output_data[i].output_pin - PIN_EXP2_START, OUTPUT);
			exp2->digitalWrite(output_data[i].output_pin - PIN_EXP2_START, !INACTIVE);

			////Serial.print(" PIN MODE to OUTPUT exp2: ");
			////Serial.println(output_data[i].output_pin - PIN_EXP2_START);

		} else if(output_data[i].output_pin >= PIN_EXP3_START &&
				output_data[i].output_pin <= PIN_EXP3_END){

			exp3->pinMode(output_data[i].output_pin - PIN_EXP3_START, OUTPUT);
			exp3->digitalWrite(output_data[i].output_pin - PIN_EXP3_START, !INACTIVE);

			////Serial.print(" PIN MODE to OUTPUT exp3: ");
			////Serial.println(output_data[i].output_pin - PIN_EXP3_START);
		}

	}
}

void OutputObject::setOutput(int output_id, bool output_value){
//	Serial.println(" OutputObject::setOutput()");
	if(output_data[output_id].state != output_value){
//		Serial.println(" OutputObject::setOutput() CHANGED VALUE");
		output_data[output_id].state = output_value;
		output_data[output_id].state_changed = true;
	}
}

void OutputObject::setLed(int output_id, bool output_value){
	////Serial.println(" OutputObject::setLed()");
	setOutput(output_id, output_value);
	//std::cout << "Set output: " << output_id << " to value:"<< output_value  << std::endl;
}

void OutputObject::setRawOutput(int output_id, bool output_value){
	setOutput(output_id, output_value);
	//std::cout << "Set output: " << output_id << " to value:"<< output_value  << std::endl;
}

void OutputObject::setCylinder(int output_id_function_1, int output_id_function_2, int cylinder_state){
	//output id 1 ist für ausfahren outputid 2 ist für einfahren oder schwimmstellung, je nach zylindertyp
	if(cylinder_state == CYLINDER_HOLD){

//		Serial.println("OutputObject::setCylinder CYLINDER_HOLD");

		setOutput(output_id_function_1, INACTIVE);
		setOutput(output_id_function_2, INACTIVE);

	} else if (cylinder_state == CYLINDER_FUNCTION_1){

//		Serial.print(output_id_move_out);
//		Serial.println(" OutputObject::setCylinder FUNCTION_1");

		setOutput(output_id_function_1, ACTIVE);
		setOutput(output_id_function_2, INACTIVE);

	} else if (cylinder_state == CYLINDER_FUNCTION_2){

//		Serial.println("OutputObject::setCylinder CYLINDER_FUNCTION_2");

		setOutput(output_id_function_1, INACTIVE);
		setOutput(output_id_function_2, ACTIVE);
	}
	//std::cout << "Set output: " << output_id << " to value:"<< output_value  << std::endl;
}


void OutputObject::writeOutput() {
	//std::cout << "Write output." << std::endl;
	for(int i = 0; i < OUTPUT_ID_COUNT; i++){
		if(output_data[i].state_changed){

			//ALL OUTPUTS ARE INVERTED! They are active when they are connected to ground. -> invert output with !

			//Serial.print("              <<| PIN: ");
			//Serial.print(output_data[i].output_pin);

			output_data[i].state_changed = false;

			if(output_data[i].output_pin >= PIN_ARDUINO_START &&
							output_data[i].output_pin <= PIN_ARDUINO_END){

				digitalWrite(output_data[i].output_pin - PIN_ARDUINO_START, !output_data[i].state);

				//Serial.print(" Arduino pin: ");
				//Serial.print(output_data[i].output_pin - PIN_ARDUINO_START);
				//Serial.print(" State: ");
				//Serial.print(output_data[i].state);

			} else if(output_data[i].output_pin >= PIN_EXP1_START &&
					output_data[i].output_pin <= PIN_EXP1_END){

				exp1->digitalWrite(output_data[i].output_pin - PIN_EXP1_START, !output_data[i].state);

				//Serial.print(" exp1 pin: ");
				//Serial.print(output_data[i].output_pin - PIN_EXP1_START);
				//Serial.print(" State: ");
				//Serial.print(output_data[i].state);

			} else if(output_data[i].output_pin >= PIN_EXP2_START &&
					output_data[i].output_pin <= PIN_EXP2_END){

				exp2->digitalWrite(output_data[i].output_pin - PIN_EXP2_START, !output_data[i].state);

				//Serial.print(" exp2 pin: ");
				//Serial.print(output_data[i].output_pin - PIN_EXP2_START);
				//Serial.print(" State: ");
				//Serial.print(output_data[i].state);

			} else if(output_data[i].output_pin >= PIN_EXP3_START &&
					output_data[i].output_pin <= PIN_EXP3_END){

				exp3->digitalWrite(output_data[i].output_pin - PIN_EXP3_START, !output_data[i].state);

				//Serial.print(" exp3 pin: ");
				//Serial.print(output_data[i].output_pin - PIN_EXP3_START);
				//Serial.print(" State: ");
				//Serial.print(output_data[i].state);

			}

			//Serial.println(" |>> ");
		}

	}

}

bool OutputObject::getOutputState(int output_id){
	return output_data[output_id].state;
}

bool OutputObject::isOutputChanging(int output_id){
	return output_data[output_id].state_changed;
}



