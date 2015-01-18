#include "Arduino.h"
#include "task_management.h"
#include "tasks.h"


//General Abstact Tasks
SimpleCylinderTask::SimpleCylinderTask(int task_id_to_set,
		int input_type,
		int input_id,
		int output_id_move_out,
		int output_id_move_in_or_float,
		int cylinder_state){

	task_state = STATE_STOPPED;
	task_id = task_id_to_set;
	mapped_input_type = input_type;
	mapped_input_id = input_id;
	mapped_cylinder_function_1_output_id = output_id_move_out;
	mapped_cylinder_function_2_output_id = output_id_move_in_or_float;
	mapped_cylinder_state = cylinder_state;
}
void SimpleCylinderTask::testStartConditions(EventData* inp) {
//	Serial.print("Test Start TSK: ");
//	Serial.print(task_id);
//	Serial.print(" Expected INP_ID: ");
//	Serial.print(mapped_input_id);
//	Serial.print(" got INP_ID: ");
//	Serial.println(inp->input_id);


	if (inp->input_type == mapped_input_type
			&& (inp->input_id == mapped_input_id)
			&& inp->input_value == ACTIVE){
//		Serial.print("Starting TSK: ");
//		Serial.println(task_id);

		tm->startTask(task_id);
	}
}
void SimpleCylinderTask::start() {
	Task::start();
//	Serial.print("Starting Simple TSK: ");
//	Serial.println(task_id);

	tm->outp->setCylinder(mapped_cylinder_function_1_output_id, mapped_cylinder_function_2_output_id, mapped_cylinder_state);
}

void SimpleCylinderTask::update(EventData* inp) {
	if (inp->input_type == mapped_input_type
			&& (inp->input_id == mapped_input_id)
			&& inp->input_value == INACTIVE){
		tm->stopTask(task_id);
	}
}

void SimpleCylinderTask::exit() {
	Task::exit();
//	Serial.print("Stopping Simple TSK: ");
//	Serial.println(task_id);

	tm->outp->setCylinder(mapped_cylinder_function_1_output_id, mapped_cylinder_function_2_output_id, CYLINDER_HOLD);
}

void SimpleCylinderTask::timer() {
}




CylinderTimerTaskpart::CylinderTimerTaskpart(int task_id_to_set,
		int input_type,
		int input_id,
		int output_id_move_out,
		int output_id_move_in_or_float,
		int cylinder_state,
		unsigned int run_duration_parm){

	task_state = STATE_STOPPED;
	task_id = task_id_to_set;
	mapped_input_type = input_type;
	mapped_input_id = input_id;
	mapped_cylinder_function_1_output_id = output_id_move_out;
	mapped_cylinder_function_2_output_id = output_id_move_in_or_float;
	mapped_cylinder_state = cylinder_state;
	run_duration = run_duration_parm;
}
void CylinderTimerTaskpart::testStartConditions(EventData* inp) {
//	Serial.print("Test Start TSK: ");
//	Serial.print(task_id);
//	Serial.print(" Expected INP_ID: ");
//	Serial.print(mapped_input_id);
//	Serial.print(" got INP_ID: ");
//	Serial.println(inp->input_id);


	if (inp->input_type == mapped_input_type
			&& (inp->input_id == mapped_input_id)
			&& inp->input_value == ACTIVE){
//		Serial.print("Starting TSK: ");
//		Serial.println(task_id);

		tm->startTask(task_id);
	}
}
void CylinderTimerTaskpart::start() {
	Task::start();
//	Serial.print("Starting Simple TSK: ");
//	Serial.println(task_id);
	start_time = millis();
	tm->outp->setCylinder(mapped_cylinder_function_1_output_id, mapped_cylinder_function_2_output_id, mapped_cylinder_state);
}

void CylinderTimerTaskpart::update(EventData* inp) {
	if (inp->input_type == mapped_input_type
			&& (inp->input_id == mapped_input_id)
			&& inp->input_value == INACTIVE){
		tm->stopTask(task_id);
	}
}

void CylinderTimerTaskpart::exit() {
	Task::exit();
//	Serial.print("Stopping Simple TSK: ");
//	Serial.println(task_id);

	tm->outp->setCylinder(mapped_cylinder_function_1_output_id, mapped_cylinder_function_2_output_id, CYLINDER_HOLD);
}

void CylinderTimerTaskpart::timer() {
	if(start_time + run_duration < millis()){

		//send message back to activator task that work of this parttask is done
		tm->addMessage(task_id, INACTIVE);
		tm->stopTask(task_id);
	}
}


CylinderSensorTaskpart::CylinderSensorTaskpart(int task_id_to_set,
		int input_type,
		int input_id,
		int output_id_move_out,
		int output_id_move_in_or_float,
		int cylinder_state,
		int sensor_input_id_parm,
		unsigned int timeout_parm){

	task_state = STATE_STOPPED;
	task_id = task_id_to_set;
	mapped_input_type = input_type;
	mapped_input_id = input_id;
	mapped_cylinder_function_1_output_id = output_id_move_out;
	mapped_cylinder_function_2_output_id = output_id_move_in_or_float;
	mapped_cylinder_state = cylinder_state;
	timeout = timeout_parm;
	sensor_input_id = sensor_input_id_parm;
}
void CylinderSensorTaskpart::testStartConditions(EventData* inp) {
//	Serial.print("Test Start TSK: ");
//	Serial.print(task_id);
//	Serial.print(" Expected INP_ID: ");
//	Serial.print(mapped_input_id);
//	Serial.print(" got INP_ID: ");
//	Serial.println(inp->input_id);


	if (inp->input_type == mapped_input_type
			&& (inp->input_id == mapped_input_id)
			&& inp->input_value == ACTIVE){
//		Serial.print("Starting TSK: ");
//		Serial.println(task_id);

		tm->startTask(task_id);
	}
}
void CylinderSensorTaskpart::start() {
	Task::start();
//	Serial.print("Starting Simple TSK: ");
//	Serial.println(task_id);
	start_time = millis();
	tm->outp->setCylinder(mapped_cylinder_function_1_output_id, mapped_cylinder_function_2_output_id, mapped_cylinder_state);
}

void CylinderSensorTaskpart::update(EventData* inp) {
	if (inp->input_type == mapped_input_type
			&& (inp->input_id == mapped_input_id)
			&& inp->input_value == INACTIVE){
		tm->stopTask(task_id);

	} else if (inp->input_type == TYPE_SENSOR
			&& (inp->input_id == sensor_input_id)
			&& inp->input_value == ACTIVE){

		//send message to activater task that parttask is ready
		tm->addMessage(mapped_input_id, INACTIVE);
		tm->stopTask(task_id);
	}
}

void CylinderSensorTaskpart::exit() {
	Task::exit();
//	Serial.print("Stopping Simple TSK: ");
//	Serial.println(task_id);

	tm->outp->setCylinder(mapped_cylinder_function_1_output_id, mapped_cylinder_function_2_output_id, CYLINDER_HOLD);
}

void CylinderSensorTaskpart::timer() {
	if(start_time + timeout < millis()){
		//send message to activator task that timeout occured.
		tm->addTimeout(task_id);
		tm->addError(ERR_SENSOR_TIMEOUT, sensor_input_id);
		tm->stopTask(task_id);
	}
}


CylinderTwoSensorTaskpart::CylinderTwoSensorTaskpart(int task_id_to_set,
		int input_type,
		int input_id,
		int output_id_move_out,
		int output_id_move_in_or_float,
		int cylinder_state,
		int sensor_1_input_id_parm,
		int sensor_2_input_id_parm,
		unsigned int timeout_parm){

	task_state = STATE_STOPPED;
	task_id = task_id_to_set;
	mapped_input_type = input_type;
	mapped_input_id = input_id;
	mapped_cylinder_function_1_output_id = output_id_move_out;
	mapped_cylinder_function_2_output_id = output_id_move_in_or_float;
	mapped_cylinder_state = cylinder_state;
	timeout = timeout_parm;
	sensor_1_input_id = sensor_1_input_id_parm;
	sensor_2_input_id = sensor_2_input_id_parm;
}
void CylinderTwoSensorTaskpart::testStartConditions(EventData* inp) {
//	Serial.print("Test Start TSK: ");
//	Serial.print(task_id);
//	Serial.print(" Expected INP_ID: ");
//	Serial.print(mapped_input_id);
//	Serial.print(" got INP_ID: ");
//	Serial.println(inp->input_id);


	if (inp->input_type == mapped_input_type
			&& (inp->input_id == mapped_input_id)
			&& inp->input_value == ACTIVE){
//		Serial.print("Starting TSK: ");
//		Serial.println(task_id);

		tm->startTask(task_id);
	}
}
void CylinderTwoSensorTaskpart::start() {
	Task::start();
//	Serial.print("Starting Simple TSK: ");
//	Serial.println(task_id);
	start_time = millis();
	tm->outp->setCylinder(mapped_cylinder_function_1_output_id, mapped_cylinder_function_2_output_id, mapped_cylinder_state);
}

void CylinderTwoSensorTaskpart::update(EventData* inp) {
	if (inp->input_type == mapped_input_type
			&& (inp->input_id == mapped_input_id)
			&& inp->input_value == INACTIVE){
		tm->stopTask(task_id);

	} else if (inp->input_type == TYPE_SENSOR
			&& (inp->input_id == sensor_1_input_id)
			&& inp->input_value == ACTIVE){

		//send message to activater task that parttask is ready
		tm->addMessage(mapped_input_id, INACTIVE);
		tm->stopTask(task_id);

	} else if (inp->input_type == TYPE_SENSOR
			&& (inp->input_id == sensor_2_input_id)
			&& inp->input_value == ACTIVE){

		//send message to activater task that parttask is ready
		tm->addMessage(mapped_input_id, INACTIVE);
		tm->stopTask(task_id);
	}
}

void CylinderTwoSensorTaskpart::exit() {
	Task::exit();
//	Serial.print("Stopping Simple TSK: ");
//	Serial.println(task_id);

	tm->outp->setCylinder(mapped_cylinder_function_1_output_id, mapped_cylinder_function_2_output_id, CYLINDER_HOLD);
}

void CylinderTwoSensorTaskpart::timer() {
	if(start_time + timeout < millis()){
		//send message to activator task that timeout occured.
		tm->addTimeout(task_id);
		tm->addError(ERR_SENSOR_TIMEOUT, sensor_1_input_id);
		tm->addError(ERR_SENSOR_TIMEOUT, sensor_2_input_id);
		tm->stopTask(task_id);
	}
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
	active_mode = IN_MOD_OU_SPINNER_BACK;
}

void ModeTask::testStartConditions(EventData* inp){
	//Serial.println(" LedTask::testStartConditions()");

	if(inp->input_type == TYPE_MESSAGE
			&& inp->input_id == MSG_STARTUP){
		start();
	}
}

void ModeTask::start() {
	Task::start();
	setActiveMode(IN_MOD_OU_SPINNER_BACK);

}

void ModeTask::update(EventData* inp) {
	if(inp->input_type == TYPE_MANUAL){
		if(inp->input_value == ACTIVE
				&& (inp->input_value == IN_MOD_LR_STEER
					|| inp->input_value == IN_MOD_LR_WEEL_LEFT_TELE
					|| inp->input_value == IN_MOD_LR_WEEL_RIGHT_TELE
					|| inp->input_value == IN_MOD_OU_FRAME
					|| inp->input_value == IN_MOD_OU_SPINNER_BACK
				)
		){
			setActiveMode(inp->input_id);
		}




		//lenkmodus
		if(active_mode == IN_MOD_LR_STEER){

			if(inp->input_id == IN_MULTI_LEFT ){

				tm->addMessage(MSG_IN_STEER_LEFT, inp->input_value);

			}else if(inp->input_id == IN_MULTI_RIGHT ){

				tm->addMessage(MSG_IN_STEER_RIGHT, inp->input_value);
			}
		}

		//radteleskop links
		if(active_mode == IN_MOD_LR_WEEL_LEFT_TELE){

			if(inp->input_id == IN_MULTI_LEFT ){

				tm->addMessage(MSG_IN_WEEL_LEFT_TELE_OUT, inp->input_value);

			}else if(inp->input_id == IN_MULTI_RIGHT ){

				tm->addMessage(MSG_IN_WEEL_LEFT_TELE_IN, inp->input_value);
			}
		}

		//radteleskop links
		if(active_mode == IN_MOD_LR_WEEL_RIGHT_TELE){

			if(inp->input_id == IN_MULTI_LEFT ){

				tm->addMessage(MSG_IN_WEEL_LEFT_TELE_IN, inp->input_value);

			}else if(inp->input_id == IN_MULTI_RIGHT ){

				tm->addMessage(MSG_IN_WEEL_LEFT_TELE_OUT, inp->input_value);
			}
		}

		//kreiselhub hinten
		if(active_mode == IN_MOD_OU_SPINNER_BACK){

			if(inp->input_id == IN_MULTI_UP ){

				tm->addMessage(MSG_IN_SPINNER_REAR_UP, inp->input_value);

			}else if(inp->input_id == IN_MULTI_DOWN ){

				tm->addMessage(MSG_IN_SPINNER_REAR_FLOAT, inp->input_value);
			}
		}

		//rahmenhub
		if(active_mode == IN_MOD_OU_FRAME){

			if(inp->input_id == IN_MULTI_UP ){

				tm->addMessage(MSG_IN_FRAME_UP, inp->input_value);

			}else if(inp->input_id == IN_MULTI_DOWN ){

				tm->addMessage(MSG_IN_FRAME_DOWN, inp->input_value);

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

void BothSpinnerUpTask::testStartConditions(EventData* inp){
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

	tm->outp->setCylinder(OUT_SPINNER_LEFT_UP, OUT_SPINNER_LEFT_FLOAT, CYLINDER_FUNCTION_1);
	tm->outp->setCylinder(OUT_SPINNER_RIGHT_UP, OUT_SPINNER_RIGHT_FLOAT, CYLINDER_FUNCTION_1);
}

void BothSpinnerUpTask::update(EventData *inp) {
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

void SpinnerLeftUpTask::testStartConditions(EventData *inp){
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

	tm->outp->setCylinder(OUT_SPINNER_LEFT_UP, OUT_SPINNER_LEFT_FLOAT, CYLINDER_FUNCTION_1);
}

void SpinnerLeftUpTask::update(EventData *inp) {
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

void SpinnerRightUpTask::testStartConditions(EventData *inp){
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

	tm->outp->setCylinder(OUT_SPINNER_RIGHT_UP, OUT_SPINNER_RIGHT_FLOAT, CYLINDER_FUNCTION_1);

}

void SpinnerRightUpTask::update(EventData *inp) {
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

void SpinnerLeftFloatTask::testStartConditions(EventData* inp){
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
	tm->outp->setCylinder(OUT_SPINNER_LEFT_UP, OUT_SPINNER_LEFT_FLOAT, CYLINDER_FUNCTION_2);
}

void SpinnerLeftFloatTask::update(EventData *inp) {
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

void SpinnerRightFloatTask::testStartConditions(EventData* inp){
	//normal start joystick move
	if (inp->input_id == IN_SPINNER_RIGHT_FLOAT
			&& inp->input_value == ACTIVE
			&& inp->input_type == TYPE_MANUAL) {

		start();
	}
}

void SpinnerRightFloatTask::start() {
	Task::start();

	tm->outp->setCylinder(OUT_SPINNER_RIGHT_UP, OUT_SPINNER_RIGHT_FLOAT, CYLINDER_FUNCTION_2);
}

void SpinnerRightFloatTask::update(EventData *inp) {
	exit();
}

void SpinnerRightFloatTask::timer() {}

void SpinnerRightFloatTask::exit() {
	Task::exit();
}

SpinnerRearFloatTask::SpinnerRearFloatTask() {
	task_state = STATE_STOPPED;
	task_id = TSK_SPINNER_REAR_FLOAT;
}

void SpinnerRearFloatTask::testStartConditions(EventData* inp){
	//normal start joystick move
	if (inp->input_id == MSG_IN_SPINNER_REAR_FLOAT
			&& inp->input_value == ACTIVE
			&& inp->input_type == TYPE_MANUAL) {

		start();
	}
}

void SpinnerRearFloatTask::start() {
	Task::start();
//	Serial.println("LeftSpinnerFloatTask::start()");
	tm->outp->setCylinder(OUT_SPINNER_REAR_UP, OUT_SPINNER_REAR_FLOAT, CYLINDER_FUNCTION_2);
}

void SpinnerRearFloatTask::update(EventData *inp) {
	exit();
}

void SpinnerRearFloatTask::timer() {}

void SpinnerRearFloatTask::exit() {
	Task::exit();
}

FrameDownTask::FrameDownTask(unsigned int upward_time_parm) {
	task_state = STATE_STOPPED;
	task_id = TSK_FRAME_DOWN;
	upward_time = upward_time_parm;
}

void FrameDownTask::testStartConditions(EventData* inp){
	//multi joystick in frame mode push away
	if (inp->input_id == MSG_IN_FRAME_DOWN
			&& inp->input_value == ACTIVE
			&& inp->input_type == TYPE_MESSAGE) {

		start();
	}
}

void FrameDownTask::start() {
	Task::start();
//	Serial.println("LeftSpinnerFloatTask::start()");

	//erst mal 2sec hochfahren, so dass frameLock geöffnet werden kann
	tm->addMessage(TSKPART_FRAME_SHORT_UP, ACTIVE);
}

void FrameDownTask::update(EventData *inp) {
	if(inp->input_type == TYPE_MESSAGE
			&& inp->input_id == TSKPART_FRAME_SHORT_UP
			&& inp->input_value == INACTIVE){
		//step 1: 2sec up is done -> start step 2: open framelock
		tm->addMessage(TSKPART_FRAME_LOCK_UP, ACTIVE);

	} else if(inp->input_type == TYPE_MESSAGE
			&& inp->input_id == TSKPART_FRAME_LOCK_UP
			&& inp->input_value == INACTIVE){
		//step 2: open framelock is done -> start step 3: move frame down
		tm->outp->setCylinder(OUT_FRAME_UP, OUT_FRAME_DOWN, CYLINDER_FUNCTION_2);

	//timout handling
	} else if(inp->input_type == TYPE_TIMEOUT
			&& inp->input_id == TSKPART_FRAME_SHORT_UP){
		//step 2: open framelock is not done but try 3 anyway -> start step 3: frame down
		tm->outp->setCylinder(OUT_FRAME_UP, OUT_FRAME_DOWN, CYLINDER_FUNCTION_2);

	//stop conditon
	} else if(inp->input_type == TYPE_MESSAGE
			&& inp->input_id == MSG_IN_FRAME_DOWN
			&& inp->input_value == INACTIVE){
		tm->stopTask(task_id);
	}


	exit();
}

void FrameDownTask::timer() {

}

void FrameDownTask::exit() {
	Task::exit();
	//stop eventually running tasks
	tm->addMessage(TSKPART_FRAME_SHORT_UP, INACTIVE);
	tm->addMessage(TSKPART_FRAME_LOCK_UP, INACTIVE);
	tm->outp->setCylinder(OUT_FRAME_UP, OUT_FRAME_DOWN, CYLINDER_HOLD);

	//close framelock on exit!
	tm->addMessage(TSKPART_FRAME_LOCK_DOWN, ACTIVE);


}


//---------------------------------END TASKS-------------------------------------
//LED Task muss ganz am ende der Tasklist stehen, sodass er die isOutputChanging() Funktion nutzen kann.

LedTask::LedTask() {
	task_state = STATE_STOPPED;
	task_id = TSK_LED;


}

void LedTask::testStartConditions(EventData* inp){
	//Serial.println(" LedTask::testStartConditions()");

	if(inp->input_type == TYPE_MESSAGE
			&& inp->input_id == MSG_STARTUP){
		start();
	}
}

void LedTask::start() {
	Task::start();
	//Serial.println(" LedTask::start()");
}

void LedTask::update(EventData *inp) {
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

void PressureTask::testStartConditions(EventData* inp){
	//Serial.println(" LedTask::testStartConditions()");

	if(inp->input_type == TYPE_MESSAGE
			&& inp->input_id == MSG_STARTUP){
		start();
	}
}

void PressureTask::start() {
	Task::start();
	//Serial.println(" LedTask::start()");
}

void PressureTask::update(EventData *inp) {
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


