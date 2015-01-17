#include "Arduino.h"
#include "task_management.h"
#include "tasks.h"


//General Abstact Tasks
SimpleCylinderMappingTask::SimpleCylinderMappingTask(int task_id_to_set,
		int input_id,
		int output_id_move_out,
		int output_id_move_in_or_float,
		int cylinder_state){

	task_state = STATE_STOPPED;
	task_id = task_id_to_set;
	mapped_input_id = input_id;
	mapped_output_id_move_out = output_id_move_out;
	mapped_output_id_move_in_or_float = output_id_move_in_or_float;
	mapped_cylinder_state = cylinder_state;
}
void SimpleCylinderMappingTask::testStartConditions(InputEventData* inp) {
//	Serial.print("Test Start TSK: ");
//	Serial.print(task_id);
//	Serial.print(" Expected INP_ID: ");
//	Serial.print(mapped_input_id);
//	Serial.print(" got INP_ID: ");
//	Serial.println(inp->input_id);


	if (inp->input_type == TYPE_MANUAL
			&& (inp->input_id == mapped_input_id)
			&& inp->input_value == ACTIVE){
//		Serial.print("Starting TSK: ");
//		Serial.println(task_id);

		tm->startTask(task_id);
	}
}
void SimpleCylinderMappingTask::start() {
	Task::start();
//	Serial.print("Starting Simple TSK: ");
//	Serial.println(task_id);

	tm->outp->setCylinder(mapped_output_id_move_out, mapped_output_id_move_in_or_float, mapped_cylinder_state);
}

void SimpleCylinderMappingTask::update(InputEventData* inp) {
	if (inp->input_type == TYPE_MANUAL
			&& (inp->input_id == mapped_input_id)
			&& inp->input_value == INACTIVE){
		tm->stopTask(task_id);
	}
}

void SimpleCylinderMappingTask::exit() {
	Task::exit();
//	Serial.print("Stopping Simple TSK: ");
//	Serial.println(task_id);

	tm->outp->setCylinder(mapped_output_id_move_out, mapped_output_id_move_in_or_float, CYLINDER_HOLD);
}

void SimpleCylinderMappingTask::timer() {
}




//MINIMAL TASK
/*MinimalTask::MinimalTask() {
	task_state = STATE_STOPPED;
	task_id = TSK_...;
}

void MinimalTask::start() {
	Task::start();

	tm->outp->setOutput(OUT_..., ACTIVE);

}

void MinimalTask::update(InputEventData *inp) {
 if (end) {
		exit();
	}
}

void MinimalTask::timer() {}

void MinimalTask::exit() {
	Task::exit();

	tm->outp->setOutput(OUT_..., INACTIVE);
}*/
ModeTask::ModeTask() {
	active_mode = NULL;
}

void ModeTask::testStartConditions(InputEventData* inp){
	//Serial.println(" LedTask::testStartConditions()");

	if(inp->input_type == TYPE_MESSAGE
			&& inp->input_id == MESSAGE_STARTUP){
		start();
	}
}

void ModeTask::start() {
	Task::start();
	setActiveMode(IN_MOD_OU_SPINNER_BACK);

}

void ModeTask::update(InputEventData* inp) {
	if(inp->input_type == TYPE_MANUAL){
		if(inp->input_value == ACTIVE){
			setActiveMode(inp->input_id);
		}



		//lenkmodus
		if(active_mode == IN_MOD_LR_STEER){

			if(inp->input_id == IN_MULTI_LEFT ){

				tm->addMessage(MESSAGE_IN_STEER_LEFT, inp->input_value);

			}else if(inp->input_id == IN_MULTI_RIGHT ){

				tm->addMessage(MESSAGE_IN_STEER_RIGHT, inp->input_value);
			}
		}

		//radteleskop links
		if(active_mode == IN_MOD_LR_WEEL_LEFT_TELE){

			if(inp->input_id == IN_MULTI_LEFT ){

				tm->addMessage(MESSAGE_IN_WEEL_LEFT_TELE_OUT, inp->input_value);

			}else if(inp->input_id == IN_MULTI_RIGHT ){

				tm->addMessage(MESSAGE_IN_WEEL_LEFT_TELE_IN, inp->input_value);
			}
		}

		//radteleskop links
		if(active_mode == IN_MOD_LR_WEEL_RIGHT_TELE){

			if(inp->input_id == IN_MULTI_LEFT ){

				tm->addMessage(MESSAGE_IN_WEEL_LEFT_TELE_IN, inp->input_value);

			}else if(inp->input_id == IN_MULTI_RIGHT ){

				tm->addMessage(MESSAGE_IN_WEEL_LEFT_TELE_OUT, inp->input_value);
			}
		}

		//kreiselhub hinten
		if(active_mode == IN_MOD_OU_SPINNER_BACK){

			if(inp->input_id == IN_MULTI_UP ){

				tm->addMessage(MESSAGE_IN_SPINNER_BACK_UP, inp->input_value);

			}else if(inp->input_id == IN_MULTI_DOWN ){

				tm->addMessage(MESSAGE_IN_SPINNER_BACK_DOWN, inp->input_value);
			}
		}

		//rahmenhub
		if(active_mode == IN_MOD_OU_FRAME){

			if(inp->input_id == IN_MULTI_UP ){

				tm->addMessage(MESSAGE_IN_FRAME_UP, inp->input_value);

			}else if(inp->input_id == IN_MULTI_DOWN ){

				tm->addMessage(MESSAGE_IN_FRAME_DOWN, inp->input_value);

			}
		}
	}
}

void ModeTask::exit() {
	Task::exit();
}

void ModeTask::timer() {
}

void ModeTask::setActiveMode(int new_active_mode){
	if(new_active_mode != active_mode){
		//disable old mode led
		if(active_mode == IN_MOD_LR_STEER){
			tm->outp->setLed(LED_MOD_LR_STEER, INACTIVE);
			tm->addMessage(IN_MOD_LR_STEER, INACTIVE);

		} else if(active_mode == IN_MOD_LR_WEEL_LEFT_TELE){
			tm->outp->setLed(LED_MOD_LR_WEEL_TELE_L, INACTIVE);
			tm->addMessage(IN_MOD_LR_WEEL_LEFT_TELE, INACTIVE);

		} else if(active_mode == IN_MOD_LR_WEEL_RIGHT_TELE){
			tm->outp->setLed(LED_MOD_LR_WEEL_TELE_R, INACTIVE);
			tm->addMessage(IN_MOD_LR_WEEL_RIGHT_TELE, INACTIVE);

		} else if(active_mode == IN_MOD_OU_FRAME){
			tm->outp->setLed(LED_MOD_OU_FRAME, INACTIVE);
			tm->addMessage(IN_MOD_OU_FRAME, INACTIVE);

		} else if(active_mode == IN_MOD_OU_SPINNER_BACK){
			tm->outp->setLed(LED_MOD_OU_SPINNER_BACK, INACTIVE);
			tm->addMessage(IN_MOD_OU_SPINNER_BACK, INACTIVE);

		}

		if(new_active_mode == IN_MOD_LR_STEER){
			tm->outp->setLed(LED_MOD_LR_STEER, ACTIVE);

		} else if(new_active_mode == IN_MOD_LR_WEEL_LEFT_TELE){
			tm->outp->setLed(LED_MOD_LR_WEEL_TELE_L, ACTIVE);

		} else if(new_active_mode == IN_MOD_LR_WEEL_RIGHT_TELE){
			tm->outp->setLed(LED_MOD_LR_WEEL_TELE_R, ACTIVE);

		} else if(new_active_mode == IN_MOD_OU_FRAME){
			tm->outp->setLed(LED_MOD_OU_FRAME, ACTIVE);

		} else if(new_active_mode == IN_MOD_OU_SPINNER_BACK){
			tm->outp->setLed(LED_MOD_OU_SPINNER_BACK, ACTIVE);

		}

		active_mode = new_active_mode;
	}



}


//OTHER TASKS------------------------------------------

BothSpinnerUpTask::BothSpinnerUpTask() {
	task_state = STATE_STOPPED;
	task_id = TSK_SPINNER_BOTH_UP;
	spinner_left_is_done = false;
	spinner_right_is_done = false;
}

void BothSpinnerUpTask::testStartConditions(InputEventData* inp){
	if (inp->input_type == TYPE_MANUAL
			&& (inp->input_id == IN_SPINNER_LEFT_UP || inp->input_id == IN_SPINNER_RIGHT_UP)
			&& inp->input_value == ACTIVE
			&& tm->inp->getInputState(IN_SPINNER_LEFT_UP) == ACTIVE
			&& tm->inp->getInputState(IN_SPINNER_RIGHT_UP)  == ACTIVE) {

		tm->stopTask(TSK_SPINNER_RIGHT_UP);
		tm->stopTask(TSK_SPINNER_LEFT_UP);
		tm->startTask(TSK_SPINNER_BOTH_UP);
	}
}

void BothSpinnerUpTask::start() {
	Task::start();
	spinner_left_is_done = false;
	spinner_right_is_done = false;

	tm->outp->setCylinder(OUT_SPINNER_LEFT_UP, OUT_SPINNER_LEFT_FLOAT, CYLINDER_MOVE_OUT);
	tm->outp->setCylinder(OUT_SPINNER_RIGHT_UP, OUT_SPINNER_RIGHT_FLOAT, CYLINDER_MOVE_OUT);
}

void BothSpinnerUpTask::update(InputEventData *inp) {
	if (inp->input_id == SENS_SPINNER_LEFT_THIRD && inp->input_value == ACTIVE) {
		spinner_left_is_done = true;
		tm->outp->setCylinder(OUT_SPINNER_LEFT_UP, OUT_SPINNER_LEFT_FLOAT, CYLINDER_HOLD);

	} else if (inp->input_id == SENS_SPINNER_RIGHT_THIRD
			&& inp->input_value == ACTIVE) {
		spinner_right_is_done = true;
		tm->outp->setCylinder(OUT_SPINNER_RIGHT_UP, OUT_SPINNER_RIGHT_FLOAT, CYLINDER_HOLD);
	}

	if (spinner_left_is_done && spinner_right_is_done) {
		exit();
	}
}

void BothSpinnerUpTask::timer() {}

void BothSpinnerUpTask::exit() {
	Task::exit();

	tm->outp->setCylinder(OUT_SPINNER_LEFT_UP, OUT_SPINNER_LEFT_FLOAT, CYLINDER_HOLD);
	tm->outp->setCylinder(OUT_SPINNER_RIGHT_UP, OUT_SPINNER_RIGHT_FLOAT, CYLINDER_HOLD);

}

// Left Spinner up ----------------------------------------------------
SpinnerLeftUpTask::SpinnerLeftUpTask() {
	task_state = STATE_STOPPED;
	task_id = TSK_SPINNER_LEFT_UP;
}

void SpinnerLeftUpTask::testStartConditions(InputEventData *inp){
	//normal start joystick move
	if (inp->input_type == TYPE_MANUAL
			&& inp->input_id == IN_SPINNER_LEFT_UP
			&& inp->input_value == ACTIVE
			&& !tm->getTaskStatus(TSK_SPINNER_BOTH_UP) == STATE_RUNNING) {

		start();

	//special start coming from TSK_SPINNER_BOTH_UP released one joystick
	} else if (tm->getTaskStatus(TSK_SPINNER_BOTH_UP) == STATE_RUNNING
			&& inp->input_id == IN_SPINNER_RIGHT_UP
			&& inp->input_value == INACTIVE
			&& inp->input_type == TYPE_MANUAL) {

		tm->stopTask(TSK_SPINNER_BOTH_UP);
		start();

	}

}

void SpinnerLeftUpTask::start() {
	Task::start();

	//Serial.println("LeftSpinnerUpTask::start()");

	tm->outp->setCylinder(OUT_SPINNER_LEFT_UP, OUT_SPINNER_LEFT_FLOAT, CYLINDER_MOVE_OUT);
}

void SpinnerLeftUpTask::update(InputEventData *inp) {
	if (inp->input_id == SENS_SPINNER_LEFT_UP
			&& inp->input_value == ACTIVE) {
		exit();

	} else if (inp->input_id == IN_SPINNER_LEFT_UP
			&& inp->input_value == INACTIVE) {
		exit();
	}
}

void SpinnerLeftUpTask::timer() {}

void SpinnerLeftUpTask::exit() {
	Task::exit();

	//Serial.println("LeftSpinnerUpTask::exit()");

	tm->outp->setCylinder(OUT_SPINNER_LEFT_UP, OUT_SPINNER_LEFT_FLOAT, CYLINDER_HOLD);
}


SpinnerRightUpTask::SpinnerRightUpTask() {
	task_state = STATE_STOPPED;
	task_id = TSK_SPINNER_RIGHT_UP;
}

void SpinnerRightUpTask::testStartConditions(InputEventData *inp){
	//normal start joystick move
	if (inp->input_type == TYPE_MANUAL
			&& inp->input_id == IN_SPINNER_RIGHT_UP
			&& inp->input_value == ACTIVE
			&& !tm->getTaskStatus(TSK_SPINNER_BOTH_UP) == STATE_RUNNING) {

		start();

	//special start coming from TSK_SPINNER_BOTH_UP released one joystick
	} else if (tm->getTaskStatus(TSK_SPINNER_BOTH_UP) == STATE_RUNNING
			&& inp->input_id == IN_SPINNER_LEFT_UP
			&& inp->input_value == INACTIVE
			&& inp->input_type == TYPE_MANUAL) {

		tm->stopTask(TSK_SPINNER_BOTH_UP);
		start();

	}

}

void SpinnerRightUpTask::start() {
	Task::start();

	tm->outp->setCylinder(OUT_SPINNER_RIGHT_UP, OUT_SPINNER_RIGHT_FLOAT, CYLINDER_MOVE_OUT);

}

void SpinnerRightUpTask::update(InputEventData *inp) {
	if (inp->input_id == SENS_SPINNER_RIGHT_UP
			&& inp->input_value == ACTIVE) {
		exit();

	} else if (inp->input_id == IN_SPINNER_RIGHT_UP
			&& inp->input_value == INACTIVE) {
		exit();
	}
}

void SpinnerRightUpTask::timer() {}

void SpinnerRightUpTask::exit() {
	Task::exit();

	tm->outp->setCylinder(OUT_SPINNER_RIGHT_UP, OUT_SPINNER_RIGHT_FLOAT, CYLINDER_HOLD);
}


SpinnerLeftFloatTask::SpinnerLeftFloatTask() {
	task_state = STATE_STOPPED;
	task_id = TSK_SPINNER_LEFT_FLOAT;
}

void SpinnerLeftFloatTask::testStartConditions(InputEventData* inp){
	//normal start joystick move
	if (inp->input_id == IN_SPINNER_LEFT_FLOAT
			&& inp->input_value == ACTIVE
			&& inp->input_type == TYPE_MANUAL) {

		start();
	}
}

void SpinnerLeftFloatTask::start() {
	Task::start();
//	Serial.println("LeftSpinnerFloatTask::start()");
	tm->outp->setCylinder(OUT_SPINNER_LEFT_UP, OUT_SPINNER_LEFT_FLOAT, CYLINDER_MOVE_IN_OR_FLOAT);
}

void SpinnerLeftFloatTask::update(InputEventData *inp) {
	exit();
}

void SpinnerLeftFloatTask::timer() {}

void SpinnerLeftFloatTask::exit() {
	Task::exit();
}


SpinnerRightFloatTask::SpinnerRightFloatTask() {
	task_state = STATE_STOPPED;
	task_id = TSK_SPINNER_RIGHT_FLOAT;
}

void SpinnerRightFloatTask::testStartConditions(InputEventData* inp){
	//normal start joystick move
	if (inp->input_id == IN_SPINNER_RIGHT_FLOAT
			&& inp->input_value == ACTIVE
			&& inp->input_type == TYPE_MANUAL) {

		start();
	}
}

void SpinnerRightFloatTask::start() {
	Task::start();

	tm->outp->setCylinder(OUT_SPINNER_RIGHT_UP, OUT_SPINNER_RIGHT_FLOAT, CYLINDER_MOVE_IN_OR_FLOAT);
}

void SpinnerRightFloatTask::update(InputEventData *inp) {
	exit();
}

void SpinnerRightFloatTask::timer() {}

void SpinnerRightFloatTask::exit() {
	Task::exit();
}


//---------------------------------END TASKS-------------------------------------
//LED Task muss ganz am ende der Tasklist stehen, sodass er die isOutputChanging() Funktion nutzen kann.

LedTask::LedTask() {
	task_state = STATE_STOPPED;
	task_id = TSK_LED;


}

void LedTask::testStartConditions(InputEventData* inp){
	//Serial.println(" LedTask::testStartConditions()");

	if(inp->input_type == TYPE_MESSAGE
			&& inp->input_id == MESSAGE_STARTUP){
		start();
	}
}

void LedTask::start() {
	Task::start();
	//Serial.println(" LedTask::start()");
}

void LedTask::update(InputEventData *inp) {
	//Serial.println(" LedTask::update()");
	// LED Schwimmstellung rechts
	if (tm->outp->isOutputChanging(OUT_SPINNER_RIGHT_FLOAT)){
		//Serial.println(" LedTask::update OutputChanging(OUT_SPINNER_RIGHT_FLOAT)");

		if(tm->outp->getOutputState(OUT_SPINNER_RIGHT_FLOAT) == ACTIVE) {

			tm->outp->setLed(LED_SPINNER_RIGHT_FLOAT, ACTIVE);
			//Serial.println(" LedTask::update OutputChanging(OUT_SPINNER_RIGHT_FLOAT) ACTIVE");
		} else {

			tm->outp->setLed(LED_SPINNER_RIGHT_FLOAT, INACTIVE);
			//Serial.println(" LedTask::update OutputChanging(OUT_SPINNER_RIGHT_FLOAT) INACTIVE");
		}
	}

	//LED Schwimmstellung links
	if (tm->outp->isOutputChanging(OUT_SPINNER_LEFT_FLOAT)){
		//Serial.println(" LedTask::update OutputChanging(OUT_SPINNER_LEFT_FLOAT)");

		if (tm->outp->getOutputState(OUT_SPINNER_LEFT_FLOAT) == ACTIVE) {

			//Serial.println(" LedTask::update OutputChanging(OUT_SPINNER_LEFT_FLOAT) ACTIVE");
			tm->outp->setLed(LED_SPINNER_LEFT_FLOAT, ACTIVE);

		} else {
			//Serial.println(" LedTask::update OutputChanging(OUT_SPINNER_LEFT_FLOAT) INACTIVE");
			tm->outp->setLed(LED_SPINNER_LEFT_FLOAT, INACTIVE);

		}
	}
}

void LedTask::timer() {}

void LedTask::exit() {
	Task::exit();

	tm->outp->setLed(LED_SPINNER_LEFT_FLOAT, INACTIVE);
	tm->outp->setLed(LED_SPINNER_LEFT_FLOAT, INACTIVE);
}

//Pressure Task muss ganz am ende der Tasklist stehen, sodass er die isOutputChanging() Funktion nutzen kann.

PressureTask::PressureTask() {
	task_state = STATE_STOPPED;
	task_id = TSK_PRESSURE;


}

void PressureTask::testStartConditions(InputEventData* inp){
	//Serial.println(" LedTask::testStartConditions()");

	if(inp->input_type == TYPE_MESSAGE
			&& inp->input_id == MESSAGE_STARTUP){
		start();
	}
}

void PressureTask::start() {
	Task::start();
	//Serial.println(" LedTask::start()");
}

void PressureTask::update(InputEventData *inp) {
	//Serial.println(" LedTask::update()");
	// LED Schwimmstellung rechts
	if (tm->outp->isOutputChanging(OUT_SPINNER_RIGHT_UP)
			|| tm->outp->isOutputChanging(OUT_SPINNER_LEFT_UP)
			|| tm->outp->isOutputChanging(OUT_SPINNER_REAR_UP)
			|| tm->outp->isOutputChanging(OUT_SPINNER_RIGHT_TELE_OUT)
			|| tm->outp->isOutputChanging(OUT_SPINNER_LEFT_TELE_OUT)
			|| tm->outp->isOutputChanging(OUT_SPINNER_RIGHT_TELE_IN)
			|| tm->outp->isOutputChanging(OUT_SPINNER_LEFT_TELE_IN)
			|| tm->outp->isOutputChanging(OUT_FRAME_UP)
			|| tm->outp->isOutputChanging(OUT_FRAME_DOWN)
			|| tm->outp->isOutputChanging(OUT_STEER_LEFT)
			|| tm->outp->isOutputChanging(OUT_STEER_RIGHT)
			|| tm->outp->isOutputChanging(OUT_WEEL_TELE_LEFT_IN)
			|| tm->outp->isOutputChanging(OUT_WEEL_TELE_RIGHT_IN)
			|| tm->outp->isOutputChanging(OUT_WEEL_TELE_LEFT_OUT)
			|| tm->outp->isOutputChanging(OUT_WEEL_TELE_RIGHT_OUT)
			|| tm->outp->isOutputChanging(OUT_FRAME_LOCK_UP)
			|| tm->outp->isOutputChanging(OUT_FRAME_LOCK_DOWN)){

		if(tm->outp->getOutputState(OUT_SPINNER_RIGHT_UP) == ACTIVE
				|| tm->outp->getOutputState(OUT_SPINNER_LEFT_UP) == ACTIVE
				|| tm->outp->getOutputState(OUT_SPINNER_REAR_UP) == ACTIVE
				|| tm->outp->getOutputState(OUT_SPINNER_RIGHT_TELE_OUT) == ACTIVE
				|| tm->outp->getOutputState(OUT_SPINNER_LEFT_TELE_OUT) == ACTIVE
				|| tm->outp->getOutputState(OUT_SPINNER_RIGHT_TELE_IN) == ACTIVE
				|| tm->outp->getOutputState(OUT_SPINNER_LEFT_TELE_IN) == ACTIVE
				|| tm->outp->getOutputState(OUT_FRAME_UP) == ACTIVE
				|| tm->outp->getOutputState(OUT_FRAME_DOWN) == ACTIVE
				|| tm->outp->getOutputState(OUT_STEER_LEFT) == ACTIVE
				|| tm->outp->getOutputState(OUT_STEER_RIGHT) == ACTIVE
				|| tm->outp->getOutputState(OUT_WEEL_TELE_LEFT_IN) == ACTIVE
				|| tm->outp->getOutputState(OUT_WEEL_TELE_RIGHT_IN) == ACTIVE
				|| tm->outp->getOutputState(OUT_WEEL_TELE_LEFT_OUT) == ACTIVE
				|| tm->outp->getOutputState(OUT_WEEL_TELE_RIGHT_OUT) == ACTIVE
				|| tm->outp->getOutputState(OUT_FRAME_LOCK_UP) == ACTIVE
				|| tm->outp->getOutputState(OUT_FRAME_LOCK_DOWN) == ACTIVE) {

			tm->outp->setRawOutput(OUT_PRESSURE, ACTIVE);
			//Serial.println(" PressureTask::update setOutputRaw(OUT_PRESSURE) ACTIVE");
		} else {

			tm->outp->setRawOutput(OUT_PRESSURE, INACTIVE);
			//Serial.println(" PressureTask::update setOutputRaw(OUT_PRESSURE) INACTIVE");
		}
	}
}

void PressureTask::timer() {}

void PressureTask::exit() {
	Task::exit();

	tm->outp->setRawOutput(OUT_PRESSURE, INACTIVE);
}


