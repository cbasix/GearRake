#include "Arduino.h"
#include "task_management.h"
#include "tasks.h"
#include "input_output.h"
#include "util.h"


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

	//notify others that this task is ready
	if(mapped_input_type == TYPE_MESSAGE){ //TODO <- type test Everywhere
		tm->addMessage(mapped_input_id, INACTIVE, task_id);
	}
}

void SimpleCylinderTask::timer() {
}




CylinderTimerTaskpart::CylinderTimerTaskpart(int task_id_to_set,
		int input_type,
		int input_id,
		int output_id_move_out,
		int output_id_move_in_or_float,
		int cylinder_state,
		unsigned long run_duration_parm){

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
		//tm->addError(154,0);
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

	//notify others that this parttask is ready
	tm->addMessage(mapped_input_id, INACTIVE, task_id);
}

void CylinderTimerTaskpart::timer() {
	if(start_time + run_duration < millis()){
		//Serial.println("timer timerkill");

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
		unsigned long timeout_parm){

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

	if(tm->inp->getInputState(sensor_input_id) == ACTIVE){
		tm->stopTask(task_id);
	}
}

void CylinderSensorTaskpart::update(EventData* inp) {
	if (inp->input_type == mapped_input_type
			&& (inp->input_id == mapped_input_id)
			&& inp->input_value == INACTIVE){
		tm->stopTask(task_id);

	} else if (inp->input_type == TYPE_SENSOR
			&& (inp->input_id == sensor_input_id)
			&& inp->input_value == ACTIVE){


		tm->stopTask(task_id);

	}
}

void CylinderSensorTaskpart::exit() {
	Task::exit();
//	Serial.print("Stopping Simple TSK: ");
//	Serial.println(task_id);
	tm->outp->setCylinder(mapped_cylinder_function_1_output_id, mapped_cylinder_function_2_output_id, CYLINDER_HOLD);

	//send message to activater task that parttask is ready
	tm->addMessage(mapped_input_id, INACTIVE, task_id);
}

void CylinderSensorTaskpart::timer() {
	if(start_time + timeout < millis()){
		//send message to activator task that timeout occured.
		tm->addTimeout(mapped_input_id);

		tm->addError(ERR_SENSOR_TIMEOUT, sensor_input_id);
		tm->stopTask(task_id);

	}
}

/**--------------
 *
 */
MessageSensorTaskpart::MessageSensorTaskpart(int task_id_to_set,
		int input_type,
		int input_id,
		int mapped_output_message_id_,
		int sensor_input_id_parm,
		unsigned long timeout_){

	task_state = STATE_STOPPED;
	task_id = task_id_to_set;
	mapped_input_type = input_type;
	mapped_input_id = input_id;
	mapped_output_message_id = mapped_output_message_id_;
	timeout = timeout_;
	sensor_input_id = sensor_input_id_parm;
}
void MessageSensorTaskpart::testStartConditions(EventData* inp) {
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
void MessageSensorTaskpart::start() {
	Task::start();
//	Serial.print("Starting Simple TSK: ");
//	Serial.println(task_id);
	start_time = millis();

	tm->addMessage(mapped_output_message_id, ACTIVE, task_id);

	if(tm->inp->getInputState(sensor_input_id) == ACTIVE){
		tm->addMessage(mapped_output_message_id, INACTIVE, task_id);
		tm->stopTask(task_id);
	}
}

void MessageSensorTaskpart::update(EventData* inp) {
	if (inp->input_type == mapped_input_type
			&& (inp->input_id == mapped_input_id)
			&& inp->input_value == INACTIVE){
		tm->stopTask(task_id);

	} else if (inp->input_type == TYPE_SENSOR
			&& (inp->input_id == sensor_input_id)
			&& inp->input_value == ACTIVE){
	// sensor reached -> stop subtasks
 	 	tm->addMessage(mapped_output_message_id, INACTIVE, task_id);

	//wait for the subtask to terminate
	} else if (inp->input_type == TYPE_MESSAGE
			&& inp->input_value == INACTIVE
			&& inp->additional_info != task_id //message is not from this task
			&& (inp->input_id == mapped_output_message_id)){
		tm->stopTask(task_id);
	}
}

void MessageSensorTaskpart::exit() {
	Task::exit();
//	Serial.print("Stopping Simple TSK: ");
//	Serial.println(task_id);


	//TODO TIMEOUTS MUST BE CATCHED EVERYWHERE!
	//send message to activater task that parttask is ready
	tm->addMessage(mapped_input_id, INACTIVE, task_id);

}

void MessageSensorTaskpart::timer() {
	if(start_time + timeout < millis()){
		//send message to activator task that timeout occured.
		tm->addTimeout(mapped_input_id);

		//TODO testing only to continue after timeout----------------------------------------
		//tm->addMessage(mapped_input_id, INACTIVE, task_id);

		tm->addError(ERR_SENSOR_TIMEOUT, sensor_input_id);
		tm->stopTask(task_id);

	}
}

/**--------------
 *
 */
MessageMoveToSensorTaskpart::MessageMoveToSensorTaskpart(int task_id_to_set,
		int input_type,
		int input_id,
		int output_message_id_on_sensor_active_,
		int output_message_id_on_sensor_inactive_,
		int sensor_input_id_parm,
		unsigned long timeout_){

	task_state = STATE_STOPPED;
	task_id = task_id_to_set;
	mapped_input_type = input_type;
	mapped_input_id = input_id;
	output_message_id_on_sensor_active = output_message_id_on_sensor_active_;
	output_message_id_on_sensor_inactive = output_message_id_on_sensor_inactive_;
	timeout = timeout_;
	sensor_input_id = sensor_input_id_parm;
}
void MessageMoveToSensorTaskpart::testStartConditions(EventData* inp) {
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
void MessageMoveToSensorTaskpart::start() {
	Task::start();
//	Serial.print("Starting Simple TSK: ");
//	Serial.println(task_id);
	start_time = millis();

	if(tm->inp->getInputState(sensor_input_id) == ACTIVE){
		tm->addMessage(output_message_id_on_sensor_active, ACTIVE, task_id);
	} else {
		tm->addMessage(output_message_id_on_sensor_inactive, ACTIVE, task_id);
	}
}

void MessageMoveToSensorTaskpart::update(EventData* inp) {
	if (inp->input_type == mapped_input_type
			&& (inp->input_id == mapped_input_id)
			&& inp->input_value == INACTIVE){

		tm->addMessage(output_message_id_on_sensor_active, INACTIVE, task_id);
		tm->addMessage(output_message_id_on_sensor_inactive, INACTIVE, task_id);

		tm->stopTask(task_id);

	} else if (inp->input_type == TYPE_SENSOR
			&& (inp->input_id == sensor_input_id)){

		// sensor reached -> stop subtasks
		tm->addMessage(output_message_id_on_sensor_active, INACTIVE, task_id);
		tm->addMessage(output_message_id_on_sensor_inactive, INACTIVE, task_id);


	//wait for the subtask to terminate
	}else if (inp->input_type == TYPE_MESSAGE
			&& inp->input_value == INACTIVE
			&& inp->additional_info != task_id //message is not from this task
			&& (inp->input_id == output_message_id_on_sensor_active
				|| inp->input_id ==output_message_id_on_sensor_inactive)){
		tm->stopTask(task_id);
	}

}

void MessageMoveToSensorTaskpart::exit() {
	Task::exit();
//	Serial.print("Stopping Simple TSK: ");
//	Serial.println(task_id);
	//stop possibly running subtasks


	//send message to activater task that parttask is ready
	//if(mapped_input_type == TYPE_MESSAGE){
	tm->addMessage(mapped_input_id, INACTIVE, task_id);
	//}

}

void MessageMoveToSensorTaskpart::timer() {
	if(start_time + timeout < millis()){
		//send message to activator task that timeout occured.
		tm->addTimeout(mapped_input_id);
		tm->addError(ERR_SENSOR_TIMEOUT, sensor_input_id);
		tm->addMessage(output_message_id_on_sensor_active, INACTIVE, task_id);
		tm->addMessage(output_message_id_on_sensor_inactive, INACTIVE, task_id);
		tm->stopTask(task_id);
	}
}

// -----------------------------------------
AutoMessageTask::AutoMessageTask(int task_id_to_set,
		int input_type,
		int input_id,
		int stop_input_1_type,
		int stop_input_id_1,
		int stop_input_2_type,
		int stop_input_id_2,
		int output_message_id){

	task_state = STATE_STOPPED;
	task_id = task_id_to_set;
	mapped_input_type = input_type;
	mapped_input_id = input_id;
	mapped_stop_input_1_type = stop_input_1_type;
	mapped_stop_input_id_1 = stop_input_id_1;
	mapped_stop_input_2_type = stop_input_2_type;
	mapped_stop_input_id_2 = stop_input_id_2;
	mapped_output_message_id = output_message_id;
}
void AutoMessageTask::testStartConditions(EventData* inp) {
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
void AutoMessageTask::start() {
	Task::start();
//	Serial.print("Starting Simple TSK: ");
//	Serial.println(task_id);
	tm->addMessage(mapped_output_message_id, ACTIVE, task_id);
}

void AutoMessageTask::update(EventData* inp) {
	/* Release the input button does not stop this task because its a AUTO TASK!*/

	//if subtask is ready -> stop this task
	if (inp->input_type == TYPE_MESSAGE
			&& (inp->input_id == mapped_output_message_id)
			&& inp->input_value == INACTIVE){
		tm->stopTask(task_id);

	// if one of the stop inputs -> stop this task
	} else if (inp->input_id == mapped_stop_input_id_1
			&& (inp->input_type == mapped_stop_input_1_type)
			&& inp->input_value == ACTIVE){
		tm->stopTask(task_id);

	} else if (inp->input_id == mapped_stop_input_id_2
			&& (inp->input_type == mapped_stop_input_2_type)
			&& inp->input_value == ACTIVE){
		tm->stopTask(task_id);

	}
}

void AutoMessageTask::exit() {
	Task::exit();
//	Serial.print("Stopping Simple TSK: ");
//	Serial.println(task_id);
	tm->addMessage(mapped_output_message_id, INACTIVE, task_id);

}

void AutoMessageTask::timer() {}


/**
 * startet einen task erst wenn ein button für eine bestimmte zeit lang gedrückt war
 */
DelayedStartTaskpart::DelayedStartTaskpart(int task_id_to_set, int input_type,
		int input_id, int message_to_start, unsigned long delay_) {
	task_state = STATE_STOPPED;
	delay = delay_;
	task_id = task_id_to_set;
	mapped_message_to_start = message_to_start;
	mapped_input_id = input_id;
	mapped_input_type = input_type;
	start_time = 0;
}

void DelayedStartTaskpart::testStartConditions(EventData* inp) {
	//tm->addMessage(123,INACTIVE);
	if(inp->input_id == mapped_input_id
			&& inp->input_type == mapped_input_type
			&& inp->input_value == ACTIVE){
		tm->startTask(task_id);
	}
}

void DelayedStartTaskpart::start() {
	Task::start();
	start_time = millis();

}

void DelayedStartTaskpart::update(EventData* inp) {
	if(inp->input_type == mapped_input_type
			&& inp->input_id == mapped_input_id
			&& inp->input_value == INACTIVE){

		tm->stopTask(task_id);
	}
}

void DelayedStartTaskpart::exit() {
	Task::exit();

}

void DelayedStartTaskpart::timer() {
	if(start_time + delay < millis()){
		tm->addMessage(mapped_message_to_start, ACTIVE, task_id);
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
	task_state = STATE_STOPPED;
	task_id = TSK_MODE;

	active_mode = NULL;
}

void ModeTask::testStartConditions(EventData* inp){


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
				&& (inp->input_id == IN_MOD_LR_STEER
					|| inp->input_id == IN_MOD_LR_WEEL_LEFT_TELE
					|| inp->input_id == IN_MOD_LR_WEEL_RIGHT_TELE
					|| inp->input_id == IN_MOD_OU_FRAME
					|| inp->input_id == IN_MOD_OU_SPINNER_BACK
				)
		){
			setActiveMode(inp->input_id);
		}




		//lenkmodus
		if(active_mode == IN_MOD_LR_STEER){

			if(inp->input_id == IN_MULTI_LEFT ){

				tm->addMessage(MSG_IN_STEER_LEFT, inp->input_value, task_id);

			}else if(inp->input_id == IN_MULTI_RIGHT ){

				tm->addMessage(MSG_IN_STEER_RIGHT, inp->input_value, task_id);
			}
		}

		//radteleskop links
		if(active_mode == IN_MOD_LR_WEEL_LEFT_TELE){

			if(inp->input_id == IN_MULTI_LEFT ){

				tm->addMessage(MSG_IN_WEEL_LEFT_TELE_OUT, inp->input_value, task_id);

			}else if(inp->input_id == IN_MULTI_RIGHT ){

				tm->addMessage(MSG_IN_WEEL_LEFT_TELE_IN, inp->input_value, task_id);
			}
		}

		//radteleskop links
		if(active_mode == IN_MOD_LR_WEEL_RIGHT_TELE){

			if(inp->input_id == IN_MULTI_LEFT ){

				tm->addMessage(MSG_IN_WEEL_RIGHT_TELE_IN, inp->input_value, task_id);

			}else if(inp->input_id == IN_MULTI_RIGHT ){

				tm->addMessage(MSG_IN_WEEL_RIGHT_TELE_OUT, inp->input_value, task_id);
			}
		}

		//kreiselhub hinten
		if(active_mode == IN_MOD_OU_SPINNER_BACK){

			if(inp->input_id == IN_MULTI_UP ){

				tm->addMessage(MSG_IN_SPINNER_REAR_UP, inp->input_value, task_id);

			}else if(inp->input_id == IN_MULTI_DOWN ){

				tm->addMessage(MSG_IN_SPINNER_REAR_FLOAT, inp->input_value, task_id);

			}else if(inp->input_id == IN_MULTI_PRESS ){

				tm->addMessage(MSG_IN_SPINNER_REAR_AUTO_UP, inp->input_value, task_id);
			}
		}

		//rahmenhub
		if(active_mode == IN_MOD_OU_FRAME){

			if(inp->input_id == IN_MULTI_UP ){

				tm->addMessage(MSG_IN_FRAME_UP, inp->input_value, task_id);

			}else if(inp->input_id == IN_MULTI_DOWN ){

				tm->addMessage(MSG_IN_FRAME_DOWN, inp->input_value, task_id);

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
			tm->addMessage(MSG_IN_STEER_LEFT, INACTIVE, task_id);
			tm->addMessage(MSG_IN_STEER_RIGHT, INACTIVE, task_id);

		} else if(active_mode == IN_MOD_LR_WEEL_LEFT_TELE){
			tm->outp->setLed(LED_MOD_LR_WEEL_TELE_L, INACTIVE);
			tm->addMessage(MSG_IN_WEEL_LEFT_TELE_IN, INACTIVE, task_id);
			tm->addMessage(MSG_IN_WEEL_LEFT_TELE_OUT, INACTIVE, task_id);

		} else if(active_mode == IN_MOD_LR_WEEL_RIGHT_TELE){
			tm->outp->setLed(LED_MOD_LR_WEEL_TELE_R, INACTIVE);
			tm->addMessage(MSG_IN_WEEL_RIGHT_TELE_IN, INACTIVE, task_id);
			tm->addMessage(MSG_IN_WEEL_RIGHT_TELE_OUT, INACTIVE, task_id);

		} else if(active_mode == IN_MOD_OU_FRAME){
			tm->outp->setLed(LED_MOD_OU_FRAME, INACTIVE);
			tm->addMessage(MSG_IN_FRAME_UP, INACTIVE, task_id);
			tm->addMessage(MSG_IN_FRAME_DOWN, INACTIVE, task_id);

		} else if(active_mode == IN_MOD_OU_SPINNER_BACK){
			tm->outp->setLed(LED_MOD_OU_SPINNER_BACK, INACTIVE);
			tm->addMessage(MSG_IN_SPINNER_REAR_UP, INACTIVE, task_id);
			tm->addMessage(MSG_IN_SPINNER_REAR_FLOAT, INACTIVE, task_id);
			tm->addMessage(MSG_IN_SPINNER_REAR_AUTO_UP, INACTIVE, task_id);

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
	if ((inp->input_id == SENS_SPINNER_LEFT_THIRD && inp->input_value == ACTIVE)
			|| (inp->input_id == SENS_SPINNER_LEFT_UP && inp->input_value == ACTIVE)) {
		spinner_left_is_done = true;
		tm->outp->setCylinder(OUT_SPINNER_LEFT_UP, OUT_SPINNER_LEFT_FLOAT, CYLINDER_HOLD);

	} else if ((inp->input_id == SENS_SPINNER_RIGHT_THIRD && inp->input_value == ACTIVE)
			|| (inp->input_id == SENS_SPINNER_RIGHT_UP && inp->input_value == ACTIVE)) {
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


SpinnerLeftFloatPermTask::SpinnerLeftFloatPermTask() {
	task_state = STATE_STOPPED;
	task_id = TSK_SPINNER_LEFT_FLOAT_PERM;
}

void SpinnerLeftFloatPermTask::testStartConditions(EventData* inp){
	//normal start joystick move
	if (inp->input_id == IN_SPINNER_LEFT_FLOAT
			&& inp->input_value == ACTIVE
			&& inp->input_type == TYPE_MANUAL) {

		start();
	}
}

void SpinnerLeftFloatPermTask::start() {
	Task::start();
//	Serial.println("LeftSpinnerFloatTask::start()");
	tm->outp->setCylinder(OUT_SPINNER_LEFT_UP, OUT_SPINNER_LEFT_FLOAT, CYLINDER_FUNCTION_2);
}

void SpinnerLeftFloatPermTask::update(EventData *inp) {
	exit();
}

void SpinnerLeftFloatPermTask::timer() {}

void SpinnerLeftFloatPermTask::exit() {
	Task::exit();
}


SpinnerRightFloatPermTask::SpinnerRightFloatPermTask() {
	task_state = STATE_STOPPED;
	task_id = TSK_SPINNER_RIGHT_FLOAT_PERM;
}

void SpinnerRightFloatPermTask::testStartConditions(EventData* inp){
	//normal start joystick move
	if (inp->input_id == IN_SPINNER_RIGHT_FLOAT
			&& inp->input_value == ACTIVE
			&& inp->input_type == TYPE_MANUAL) {

		start();
	}
}

void SpinnerRightFloatPermTask::start() {
	Task::start();

	tm->outp->setCylinder(OUT_SPINNER_RIGHT_UP, OUT_SPINNER_RIGHT_FLOAT, CYLINDER_FUNCTION_2);
}

void SpinnerRightFloatPermTask::update(EventData *inp) {
	exit();
}

void SpinnerRightFloatPermTask::timer() {}

void SpinnerRightFloatPermTask::exit() {
	Task::exit();
}

SpinnerRearFloatPermTask::SpinnerRearFloatPermTask() {
	task_state = STATE_STOPPED;
	task_id = TSK_SPINNER_REAR_FLOAT_PERM;
}

void SpinnerRearFloatPermTask::testStartConditions(EventData* inp){
	//normal start joystick move
	if (inp->input_id == MSG_IN_SPINNER_REAR_FLOAT
			&& inp->input_value == ACTIVE
			&& inp->input_type == TYPE_MESSAGE) {

		start();
	}
}

void SpinnerRearFloatPermTask::start() {
	Task::start();
//	Serial.println("LeftSpinnerFloatTask::start()");
	tm->outp->setCylinder(OUT_SPINNER_REAR_UP, OUT_SPINNER_REAR_FLOAT, CYLINDER_FUNCTION_2);
}

void SpinnerRearFloatPermTask::update(EventData *inp) {
	exit();
}

void SpinnerRearFloatPermTask::timer() {}

void SpinnerRearFloatPermTask::exit() {
	Task::exit();
}

FrameDownTask::FrameDownTask(unsigned long upward_time_parm) {
	task_state = STATE_STOPPED;
	task_id = TSK_FRAME_DOWN;
	manual_mode = false;
}

void FrameDownTask::testStartConditions(EventData* inp){
	//multi joystick in frame mode push away
	if (inp->input_id == MSG_IN_FRAME_DOWN
			&& inp->input_value == ACTIVE
			&& inp->input_type == TYPE_MESSAGE) {
		manual_mode = true;
		start();

	// or message from other task
	} else if (inp->input_id == MSG_TSKPART_FRAME_DOWN
			&& inp->input_value == ACTIVE
			&& inp->input_type == TYPE_MESSAGE) {
		manual_mode = false;
		start();
	}

}

void FrameDownTask::start() {
	Task::start();
//	Serial.println("LeftSpinnerFloatTask::start()");


	if (tm->inp->getInputState(IN_MOD_OU_FRAME) == ACTIVE && manual_mode){
		//spezialmodus wenn ohne framelock öffnen und ohne hochfahren direkt nach unten gefahren werden soll (z. B. Schwader unter irgendwas eingeklemmt)
		//instant move frame down
		tm->outp->setCylinder(OUT_FRAME_UP, OUT_FRAME_DOWN, CYLINDER_FUNCTION_2);

	} else {

		if(tm->inp->getInputState(SENS_FRAME_UP) == ACTIVE){
			//Frame is completely up -> no need for the 2sec up -> continue with stem 2 open framelock
			tm->addMessage(MSG_TSKPART_FRAME_LOCK_TO_UP, ACTIVE, task_id);
		} else {
			//normalweg: erst mal 2sec hochfahren, so dass frameLock geöffnet werden kann
			tm->addMessage(MSG_TSKPART_FRAME_UP_SHORT, ACTIVE, task_id);
		}

	}

}

void FrameDownTask::update(EventData *inp) {
	if(inp->input_type == TYPE_SENSOR
			&& inp->input_id == SENS_FRAME_UP
			&& inp->input_value == INACTIVE){
		//during step 1 go up the sensor "FRAME_UP" was reached -> stop the FRAME_UP_SHORT task
		// and continue with step 2: open framelock
		tm->addMessage(MSG_TSKPART_FRAME_UP_SHORT, INACTIVE, task_id);
		//tm->addMessage(MSG_TSKPART_FRAME_LOCK_TO_UP, ACTIVE, task_id);

	} else if(inp->input_type == TYPE_MESSAGE
			&& inp->input_id == MSG_TSKPART_FRAME_UP_SHORT
			&& inp->input_value == INACTIVE){
		//step 1: 2sec up is done -> start step 2: open framelock
		tm->addMessage(MSG_TSKPART_FRAME_LOCK_TO_UP, ACTIVE, task_id);

	} else if(inp->input_type == TYPE_MESSAGE
			&& inp->input_id == MSG_TSKPART_FRAME_LOCK_TO_UP
			&& inp->input_value == INACTIVE){
		//step 2: open framelock is done -> start step 3: move frame down
		tm->outp->setCylinder(OUT_FRAME_UP, OUT_FRAME_DOWN, CYLINDER_FUNCTION_2);

	//timout handling
	} else if(inp->input_type == TYPE_TIMEOUT
			&& inp->input_id == MSG_TSKPART_FRAME_LOCK_TO_UP){
		//step 2: open framelock is not done but try 3 anyway -> start step 3: frame down
		tm->outp->setCylinder(OUT_FRAME_UP, OUT_FRAME_DOWN, CYLINDER_FUNCTION_2);

	//stop conditon - joystick released or calling task dont need anymore
	} else if(inp->input_type == TYPE_MESSAGE
			&& (inp->input_id == MSG_IN_FRAME_DOWN || inp->input_id == MSG_TSKPART_FRAME_DOWN)
			&& inp->input_value == INACTIVE){
		//step3 frame down is done -> close framelock
		tm->outp->setCylinder(OUT_FRAME_UP, OUT_FRAME_DOWN, CYLINDER_HOLD);
		tm->addMessage(MSG_TSKPART_FRAME_LOCK_TO_DOWN, ACTIVE, task_id);

	} else if(inp->input_type == TYPE_MESSAGE
			&& (inp->input_id == MSG_TSKPART_FRAME_LOCK_TO_DOWN)
			&& inp->input_value == INACTIVE){
		//step4 close framelock done -> exit
		tm->stopTask(task_id);
	}
}

void FrameDownTask::timer() {

}

void FrameDownTask::exit() {
	Task::exit();
	//stop eventually running tasks
	tm->addMessage(MSG_TSKPART_FRAME_UP_SHORT, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_FRAME_LOCK_TO_UP, INACTIVE, task_id);
	tm->outp->setCylinder(OUT_FRAME_UP, OUT_FRAME_DOWN, CYLINDER_HOLD);

	//notify other tasks that this task is ready
	if(!manual_mode){
		tm->addMessage(MSG_TSKPART_FRAME_DOWN, INACTIVE, task_id);
	}

	//TODO necessary? close framelock on exit! if not already closed
	/*if(!tm->inp->getInputState("SENS_FRAME_LOCK_CLOSED")){
		tm->addMessage(MSG_TSKPART_FRAME_LOCK_TO_DOWN, ACTIVE, task_id);
	}*/

}


AutoLowTask::AutoLowTask() {
	task_state = STATE_STOPPED;
	task_id = TSK_AUTO_LOW;
}

void AutoLowTask::testStartConditions(EventData* inp) {
	//auto function if delayed start signal is received
	if(inp->input_type == TYPE_MESSAGE
			&& inp->input_id == MSG_AUTO_LOW_DELAYED
			&& inp->input_value == ACTIVE){
		//TODO FRAGE WAS darf nochmal nicht getan werden, wenn die kreisel ganz oben sind (irgendwas hinten an den zinken steht an???)
		//if another button is pressed dont start auto low task
		if(!tm->inp->getInputState(IN_AUTO_TRANSPORT)
				&& !tm->inp->getInputState(IN_AUTO_WORK)
				&& !tm->inp->getInputState(IN_MOD_LR_STEER)
				&& !tm->inp->getInputState(IN_MOD_LR_WEEL_LEFT_TELE)
				&& !tm->inp->getInputState(IN_MOD_LR_WEEL_RIGHT_TELE)
				&& !tm->inp->getInputState(IN_MOD_OU_FRAME)
				&& !tm->inp->getInputState(IN_MOD_OU_SPINNER_BACK)
				&& !tm->inp->getInputState(IN_MULTI_DOWN)
				&& !tm->inp->getInputState(IN_MULTI_LEFT)
				&& !tm->inp->getInputState(IN_MULTI_RIGHT)
				&& !tm->inp->getInputState(IN_MULTI_UP)
				&& !tm->inp->getInputState(IN_SPINNER_LEFT_FLOAT)
				&& !tm->inp->getInputState(IN_SPINNER_LEFT_TELE_IN)
				&& !tm->inp->getInputState(IN_SPINNER_LEFT_TELE_OUT)
				&& !tm->inp->getInputState(IN_SPINNER_LEFT_UP)
				&& !tm->inp->getInputState(IN_SPINNER_RIGHT_FLOAT)
				&& !tm->inp->getInputState(IN_SPINNER_RIGHT_TELE_IN)
				&& !tm->inp->getInputState(IN_SPINNER_RIGHT_TELE_OUT)
				&& !tm->inp->getInputState(IN_SPINNER_RIGHT_UP)){

			tm->startTask(TSK_AUTO_LOW);
		}

	}
}

void AutoLowTask::start() {
	Task::start();
	tm->outp->setLed(LED_AUTO_LOW, ACTIVE);
	tm->addMessage(MSG_TSKPART_FRAME_TO_LOW, ACTIVE, task_id);
}

void AutoLowTask::update(EventData* inp) {

	if(inp->input_type == TYPE_MESSAGE
			&& inp->input_id == MSG_TSKPART_FRAME_TO_LOW
			&& inp->input_value == INACTIVE){
		//step 1: FRAME_TO_LOW is done -> READY ;)
		tm->stopTask(task_id);
	}

	if(inp->input_type == TYPE_MANUAL
			&& inp->input_value == ACTIVE ){
		tm->stopTask(task_id);
	}

	//stop on timeout
	if(inp->input_type == TYPE_TIMEOUT){
		tm->stopTask(task_id);
	}

}

void AutoLowTask::exit() {
	Task::exit();



	//close framelock on exit!
	tm->addMessage(MSG_TSKPART_FRAME_TO_LOW, INACTIVE, task_id);
	tm->outp->setLed(LED_AUTO_LOW, INACTIVE);
	//todo other exit values for cylinders
}

void AutoLowTask::timer() {
}

AutoWorkTask::AutoWorkTask() {
	task_state = STATE_STOPPED;
	task_id = TSK_AUTO_WORK;
	step = 0;
	left_done = false;
	right_done = false;
}

void AutoWorkTask::testStartConditions(EventData* inp) {
	//auto function if delayed start signal is received
	if(inp->input_type == TYPE_MESSAGE
			&& inp->input_id == MSG_AUTO_WORK_DELAYED
			&& inp->input_value == ACTIVE){

		//if another button is pressed dont start auto work task
		if(!tm->inp->getInputState(IN_AUTO_TRANSPORT)
				&& !tm->inp->getInputState(IN_AUTO_LOW)
				&& !tm->inp->getInputState(IN_MOD_LR_STEER)
				&& !tm->inp->getInputState(IN_MOD_LR_WEEL_LEFT_TELE)
				&& !tm->inp->getInputState(IN_MOD_LR_WEEL_RIGHT_TELE)
				&& !tm->inp->getInputState(IN_MOD_OU_FRAME)
				&& !tm->inp->getInputState(IN_MOD_OU_SPINNER_BACK)
				&& !tm->inp->getInputState(IN_MULTI_DOWN)
				&& !tm->inp->getInputState(IN_MULTI_LEFT)
				&& !tm->inp->getInputState(IN_MULTI_RIGHT)
				&& !tm->inp->getInputState(IN_MULTI_UP)
				&& !tm->inp->getInputState(IN_SPINNER_LEFT_FLOAT)
				&& !tm->inp->getInputState(IN_SPINNER_LEFT_TELE_IN)
				&& !tm->inp->getInputState(IN_SPINNER_LEFT_TELE_OUT)
				&& !tm->inp->getInputState(IN_SPINNER_LEFT_UP)
				&& !tm->inp->getInputState(IN_SPINNER_RIGHT_FLOAT)
				&& !tm->inp->getInputState(IN_SPINNER_RIGHT_TELE_IN)
				&& !tm->inp->getInputState(IN_SPINNER_RIGHT_TELE_OUT)
				&& !tm->inp->getInputState(IN_SPINNER_RIGHT_UP)){

			tm->startTask(TSK_AUTO_WORK);
		}

	}
}

void AutoWorkTask::start() {
	Task::start();
	tm->outp->setLed(LED_AUTO_WORK, ACTIVE);

	//1st step: if weeltele left and right are allready out
	// -> continue with step 2: frameup and rear spinner next to ground
	// ELSE -> make them slide out
	step = 1;
	left_done = false;
	right_done = false;

	//first start rear spinner float (new definition 24.04.2015 Wolfgang )
	tm->outp->setCylinder(OUT_SPINNER_REAR_UP, OUT_SPINNER_REAR_FLOAT, CYLINDER_FUNCTION_2);

	if(tm->inp->getInputState(SENS_WEEL_TELE_LEFT_OUT) == ACTIVE &&
			tm->inp->getInputState(SENS_WEEL_TELE_RIGHT_OUT) == ACTIVE){

		step = 2;

		//start step 2: frameup and rear spinner next to ground
		tm->addMessage(MSG_TSKPART_FRAME_TO_UP, ACTIVE, task_id);

	} else {
		//frame down to ground, needed to get the weelteles out
		tm->addMessage(MSG_TSKPART_FRAME_TO_GROUND, ACTIVE, task_id);

	}

	/*tm->outp->setCylinder(OUT_SPINNER_REAR_UP, OUT_SPINNER_REAR_FLOAT, CYLINDER_FUNCTION_2);
	tm->addMessage(MSG_TSKPART_SPINNER_LEFT_UP_TWO_SENS, ACTIVE);
	tm->addMessage(MSG_TSKPART_SPINNER_RIGHT_UP_TWO_SENS, ACTIVE);*/
}

void AutoWorkTask::update(EventData* inp) {
	//Step 1 endbedingungen -> hochfahren links und rechts erledigt
    if(step == 1){
    	//frame is on ground -> get weelteles out
    	if(inp->input_type == TYPE_MESSAGE
    			&& inp->input_id == MSG_TSKPART_FRAME_TO_GROUND
				&& inp->input_value == INACTIVE){
        	tm->addMessage(MSG_TSKPART_WEEL_TELE_RIGHT_TO_OUT, ACTIVE, task_id);
    		tm->addMessage(MSG_TSKPART_WEEL_TELE_LEFT_TO_OUT, ACTIVE, task_id);


		} else if(inp->input_type == TYPE_MESSAGE
				&& inp->input_id == MSG_TSKPART_WEEL_TELE_RIGHT_TO_OUT
				&& inp->input_value == INACTIVE){

			right_done = true;

		} else if(inp->input_type == TYPE_MESSAGE
				&& inp->input_id == MSG_TSKPART_WEEL_TELE_LEFT_TO_OUT
				&& inp->input_value == INACTIVE){

			left_done = true;

		}

		if(left_done && right_done){
			step = 2;
			left_done = false;
			right_done = false;

			//step 2: frameup and rear spinner next to ground
			tm->addMessage(MSG_TSKPART_FRAME_TO_UP, ACTIVE, task_id);
		}
    }else if(step == 2){
    	//frame is in "up" position
    	if(inp->input_type == TYPE_MESSAGE
				&& inp->input_id == MSG_TSKPART_FRAME_TO_UP
				&& inp->input_value == INACTIVE){

    		//check if spinners are in "up" position, if not bring them to the "third" position
    		if(tm->inp->getInputState(SENS_SPINNER_LEFT_UP)){
    			left_done = true;
    		} else {
    			tm->addMessage(MSG_TSKPART_SPINNER_LEFT_TO_THIRD, ACTIVE, task_id);
    		}

    		if(tm->inp->getInputState(SENS_SPINNER_RIGHT_UP)){
				right_done = true;
			} else {
				tm->addMessage(MSG_TSKPART_SPINNER_RIGHT_TO_THIRD, ACTIVE, task_id);
			}


    	} else if(inp->input_type == TYPE_MESSAGE
				&& inp->input_id == MSG_TSKPART_SPINNER_RIGHT_TO_THIRD
				&& inp->input_value == INACTIVE){

			right_done = true;

		} else if(inp->input_type == TYPE_MESSAGE
				&& inp->input_id == MSG_TSKPART_SPINNER_LEFT_TO_THIRD
				&& inp->input_value == INACTIVE){

			left_done = true;

		}

    	if(left_done && right_done){
    		//both spinners are at "third" or on "up" position
			step = 3;
			left_done = false;
			right_done = false;
			//step 3: get spinner teles out
			if(!tm->inp->getInputState(SENS_SPINNER_LEFT_UP)){
				tm->addMessage(MSG_TSKPART_SPINNER_TELE_LEFT_TO_OUT, ACTIVE, task_id);
			} else {
				//set left done for true for step 3
				left_done = true;
			}
			if(!tm->inp->getInputState(SENS_SPINNER_RIGHT_UP)){
				tm->addMessage(MSG_TSKPART_SPINNER_TELE_RIGHT_TO_OUT, ACTIVE, task_id);
			} else {
				//set right done for true for step 3
				right_done = true;
			}
			//if the things for step 3 are already done -> exit
			if(left_done && right_done){
				step = 99;
				left_done = false;
				right_done = false;

				//READY
				tm->stopTask(TSK_AUTO_WORK);
			}
		}
    }else if(step == 3){
    	if((inp->input_type == TYPE_MESSAGE
				&& inp->input_id == MSG_TSKPART_SPINNER_TELE_LEFT_TO_OUT
				&& inp->input_value == INACTIVE)
    		|| tm->inp->getInputState(SENS_SPINNER_LEFT_UP)){

			left_done = true;

		}

    	if((inp->input_type == TYPE_MESSAGE
				&& inp->input_id == MSG_TSKPART_SPINNER_TELE_RIGHT_TO_OUT
				&& inp->input_value == INACTIVE)
			|| tm->inp->getInputState(SENS_SPINNER_RIGHT_UP)){

			right_done = true;

		}

    	if(left_done && right_done){
			step = 99;
			left_done = false;
			right_done = false;

			//READY
			tm->stopTask(TSK_AUTO_WORK);
		}

    }

	//stop condition -> wenn irgendeine taste gedrückt wird, wird der auto modus sofort unterbrochen
	if(inp->input_type == TYPE_MANUAL
			&& inp->input_value == ACTIVE ){
		tm->stopTask(task_id);
	}

	//stop on timeout
	if(inp->input_type == TYPE_TIMEOUT){
		tm->stopTask(task_id);
		//tm->resetTasks();
	}
}

void AutoWorkTask::exit() {
	Task::exit();

	tm->outp->setLed(LED_AUTO_WORK, INACTIVE);

	//stop subtasks on exit
	tm->addMessage(MSG_TSKPART_WEEL_TELE_RIGHT_TO_OUT, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_WEEL_TELE_LEFT_TO_OUT, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_FRAME_TO_GROUND, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_FRAME_TO_UP, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_SPINNER_LEFT_TO_THIRD, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_SPINNER_RIGHT_TO_THIRD, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_SPINNER_TELE_LEFT_TO_OUT, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_SPINNER_TELE_RIGHT_TO_OUT, INACTIVE, task_id);


	//todo other exit values for cylinders
}

void AutoWorkTask::timer() {
}

AutoTransportTask::AutoTransportTask() {
	task_state = STATE_STOPPED;
	task_id = TSK_AUTO_TRANSPORT;
}

void AutoTransportTask::testStartConditions(EventData* inp) {
	//auto function if delayed start signal is received
	if(inp->input_type == TYPE_MESSAGE
			&& inp->input_id == MSG_AUTO_TRANSPORT_DELAYED
			&& inp->input_value == ACTIVE){

		//if another button is pressed dont start auto transport task
		if(!tm->inp->getInputState(IN_AUTO_LOW)
				&& !tm->inp->getInputState(IN_AUTO_WORK)
				&& !tm->inp->getInputState(IN_MOD_LR_STEER)
				&& !tm->inp->getInputState(IN_MOD_LR_WEEL_LEFT_TELE)
				&& !tm->inp->getInputState(IN_MOD_LR_WEEL_RIGHT_TELE)
				&& !tm->inp->getInputState(IN_MOD_OU_FRAME)
				&& !tm->inp->getInputState(IN_MOD_OU_SPINNER_BACK)
				&& !tm->inp->getInputState(IN_MULTI_DOWN)
				&& !tm->inp->getInputState(IN_MULTI_LEFT)
				&& !tm->inp->getInputState(IN_MULTI_RIGHT)
				&& !tm->inp->getInputState(IN_MULTI_UP)
				&& !tm->inp->getInputState(IN_SPINNER_LEFT_FLOAT)
				&& !tm->inp->getInputState(IN_SPINNER_LEFT_TELE_IN)
				&& !tm->inp->getInputState(IN_SPINNER_LEFT_TELE_OUT)
				&& !tm->inp->getInputState(IN_SPINNER_LEFT_UP)
				&& !tm->inp->getInputState(IN_SPINNER_RIGHT_FLOAT)
				&& !tm->inp->getInputState(IN_SPINNER_RIGHT_TELE_IN)
				&& !tm->inp->getInputState(IN_SPINNER_RIGHT_TELE_OUT)
				&& !tm->inp->getInputState(IN_SPINNER_RIGHT_UP)){

			tm->startTask(TSK_AUTO_TRANSPORT);
		}

	}
}

void AutoTransportTask::start() {
	Task::start();
	tm->outp->setLed(LED_AUTO_TRANSPORT, ACTIVE);

	//tm->addMessage(MSG_TSKPART_FRAME_TO_LOW, ACTIVE);
	step = 0;
	left_done = false;
	right_done = false;

	tm->addMessage(MSG_IN_SPINNER_REAR_FLOAT, ACTIVE, task_id);

	//step 1: get spinner to third (if they are not "up")
	if(!tm->inp->getInputState(SENS_SPINNER_LEFT_UP)){
		tm->addMessage(MSG_TSKPART_SPINNER_LEFT_TO_THIRD, ACTIVE, task_id);
	} else {
		//set left done for true for step 1
		left_done = true;
	}
	if(!tm->inp->getInputState(SENS_SPINNER_RIGHT_UP)){
		tm->addMessage(MSG_TSKPART_SPINNER_RIGHT_TO_THIRD, ACTIVE, task_id);
	} else {
		//set left done for true for step 1
		right_done = true;
	}
	//if the things for step 0 are done -> go directly to step 1 short up left
	if(left_done && right_done){
		step = 1;
		left_done = false;
		right_done = false;

		tm->addMessage(MSG_TSKPART_SPINNER_LEFT_UP_SHORT, ACTIVE, task_id);

	}


}

void AutoTransportTask::update(EventData* inp) {
	if(step == 0){
		//step 0 spinner to "third"(1/3) position
		if(inp->input_type == TYPE_MESSAGE
					&& inp->input_id == MSG_TSKPART_SPINNER_LEFT_TO_THIRD
					&& inp->input_value == INACTIVE){
			left_done = true;

		} else if(inp->input_type == TYPE_MESSAGE
				&& inp->input_id == MSG_TSKPART_SPINNER_RIGHT_TO_THIRD
				&& inp->input_value == INACTIVE){
			right_done = true;

		}

		if(left_done && right_done){
			step = 1;
			left_done = false;
			right_done = false;

			//left up short
			tm->addMessage(MSG_TSKPART_SPINNER_LEFT_UP_SHORT, ACTIVE, task_id);


		}

	} else if(step == 1){
		//step 1 short up both after each other
		if(inp->input_type == TYPE_MESSAGE
					&& inp->input_id == MSG_TSKPART_SPINNER_LEFT_UP_SHORT
					&& inp->input_value == INACTIVE){

			//afterwards right up short
			tm->addMessage(MSG_TSKPART_SPINNER_RIGHT_UP_SHORT, ACTIVE, task_id);

		} else if(inp->input_type == TYPE_MESSAGE
				&& inp->input_id == MSG_TSKPART_SPINNER_RIGHT_UP_SHORT
				&& inp->input_value == INACTIVE){

			step = 2;

			tm->addMessage(MSG_TSKPART_SPINNER_TELE_LEFT_TO_IN, ACTIVE, task_id);
			tm->addMessage(MSG_TSKPART_SPINNER_TELE_RIGHT_TO_IN, ACTIVE, task_id);

		}


	} else if(step == 2){
		//step 2: spinnerteles in
		if(inp->input_type == TYPE_MESSAGE
				&& inp->input_id == MSG_TSKPART_SPINNER_TELE_LEFT_TO_IN
				&& inp->input_value == INACTIVE){
			//SpinnerLeftTeleIn is done
			left_done = true;
		} else if(inp->input_type == TYPE_MESSAGE
				&& inp->input_id == MSG_TSKPART_SPINNER_TELE_RIGHT_TO_IN
				&& inp->input_value == INACTIVE){
			//right is done;)
			right_done = true;
		}
		if(left_done && right_done){
			step = 21;
			left_done = false;
			right_done = false;

			tm->addMessage(MSG_TSKPART_SPINNER_LEFT_TO_UP, ACTIVE, task_id);
			tm->addMessage(MSG_TSKPART_SPINNER_RIGHT_TO_UP, ACTIVE, task_id);
		}
	} else if(step == 21){
		if(inp->input_type == TYPE_MESSAGE
				&& inp->input_id == MSG_TSKPART_SPINNER_LEFT_TO_UP
				&& inp->input_value == INACTIVE){
			//SpinnerLeftTeleIn is done
			left_done = true;
		} else if(inp->input_type == TYPE_MESSAGE
				&& inp->input_id == MSG_TSKPART_SPINNER_RIGHT_TO_UP
				&& inp->input_value == INACTIVE){
			//right is done;)
			right_done = true;
		}

		if(left_done && right_done){
			step = 3;
			left_done = false;
			right_done = false;

			//weelteles are allready in -> Frame to "middle" position ;)
			if(tm->inp->getInputState(SENS_WEEL_TELE_LEFT_IN) && tm->inp->getInputState(SENS_WEEL_TELE_RIGHT_IN)){
				//start step 5: frame to middle position
				step = 5;
				left_done = false;
				right_done = false;

				tm->addMessage(MSG_TSKPART_FRAME_TO_MIDDLE, ACTIVE, task_id);
			} else {
				//start step 3: frame down
				step = 3;
				left_done = false;
				right_done = false;

				tm->addMessage(MSG_TSKPART_FRAME_TO_GROUND, ACTIVE, task_id);
			}

		}
	} else if(step == 3){
		if(inp->input_type == TYPE_MESSAGE
				&& inp->input_id == MSG_TSKPART_FRAME_TO_GROUND
				&& inp->input_value == INACTIVE){
			step = 4;
			left_done = false;
			right_done = false;

			//Frame is down -> now get weelteles in
			tm->addMessage(MSG_TSKPART_WEEL_TELE_LEFT_TO_IN, ACTIVE, task_id);
			tm->addMessage(MSG_TSKPART_WEEL_TELE_RIGHT_TO_IN, ACTIVE, task_id);


		}
	} else if(step == 4){
		if(inp->input_type == TYPE_MESSAGE
				&& inp->input_id == MSG_TSKPART_WEEL_TELE_LEFT_TO_IN
				&& inp->input_value == INACTIVE){
			//SpinnerLeftTeleIn is done
			left_done = true;
		} else if(inp->input_type == TYPE_MESSAGE
				&& inp->input_id == MSG_TSKPART_WEEL_TELE_RIGHT_TO_IN
				&& inp->input_value == INACTIVE){
			//step 3: FRAME_TO_LOW is done -> READY ;)
			right_done = true;
		}

		if(left_done && right_done){
			step = 5;
			left_done = false;
			right_done = false;

			//weelteles are in -> frame to "middle" position
			tm->addMessage(MSG_TSKPART_FRAME_TO_MIDDLE, ACTIVE, task_id);
			// tm->stopTask(task_id);
		}
	} else if(step == 5){
		if(inp->input_type == TYPE_MESSAGE
				&& inp->input_id == MSG_TSKPART_FRAME_TO_MIDDLE
				&& inp->input_value == INACTIVE){
			//Frame to middle is done
			tm->stopTask(task_id);
		}

	}

	if(inp->input_type == TYPE_MANUAL
			&& inp->input_value == ACTIVE ){
		tm->stopTask(task_id);
	}

	//stop on timeout
	if(inp->input_type == TYPE_TIMEOUT){
		tm->stopTask(task_id);
	}

}

void AutoTransportTask::exit() {
	Task::exit();

	tm->outp->setLed(LED_AUTO_TRANSPORT, INACTIVE);

	//TODO stop all subtasks on exit !
	//stop subtasks on exit
	tm->addMessage(MSG_TSKPART_WEEL_TELE_RIGHT_TO_IN, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_WEEL_TELE_LEFT_TO_IN, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_FRAME_TO_GROUND, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_FRAME_TO_MIDDLE, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_SPINNER_LEFT_TO_THIRD, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_SPINNER_RIGHT_TO_THIRD, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_SPINNER_LEFT_TO_UP, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_SPINNER_RIGHT_TO_UP, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_SPINNER_TELE_LEFT_TO_IN, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_SPINNER_TELE_RIGHT_TO_IN, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_SPINNER_LEFT_UP_SHORT, INACTIVE, task_id);
	tm->addMessage(MSG_TSKPART_SPINNER_RIGHT_UP_SHORT, INACTIVE, task_id);

	//close framelock on exit!
	//tm->addMessage(MSG_TSKPART_FRAME_TO_LOW, INACTIVE);
}

void AutoTransportTask::timer() {
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
	tm->outp->setLed(LED_FRAME_LOCK, ACTIVE);
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

	//LED Schwimmstellung hinten
	if (tm->outp->isOutputChanging(OUT_SPINNER_REAR_FLOAT)){
		//Serial.println(" LedTask::update OutputChanging(OUT_SPINNER_LEFT_FLOAT)");

		if (tm->outp->getOutputState(OUT_SPINNER_REAR_FLOAT) == ACTIVE) {

			//Serial.println(" LedTask::update OutputChanging(OUT_SPINNER_LEFT_FLOAT) ACTIVE");
			tm->outp->setLed(LED_SPINNER_REAR_FLOAT, ACTIVE);

		} else {
			//Serial.println(" LedTask::update OutputChanging(OUT_SPINNER_LEFT_FLOAT) INACTIVE");
			tm->outp->setLed(LED_SPINNER_REAR_FLOAT, INACTIVE);

		}
	}

	//input checks
	//rahmensicherung
	if(inp->input_type == TYPE_SENSOR
			&& inp->input_id == SENS_FRAME_LOCK_CLOSED){
		if(inp->input_value == ACTIVE){
			tm->outp->setLed(LED_FRAME_LOCK, INACTIVE);
		} else {
			tm->outp->setLed(LED_FRAME_LOCK, ACTIVE);
		}
	}

	//radmittelstellung
	if(inp->input_type == TYPE_SENSOR
			&& inp->input_id == SENS_WEEL_TRACK_MIDDLE){
		if(inp->input_value == ACTIVE){
			tm->outp->setLed(LED_WEEL_TRACK_MIDDLE, ACTIVE);
		} else {
			tm->outp->setLed(LED_WEEL_TRACK_MIDDLE, INACTIVE);
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
	if(inp->input_type == TYPE_OUTPUT
			&& (inp->input_id == OUT_SPINNER_RIGHT_UP
					|| inp->input_id == OUT_SPINNER_LEFT_UP
					|| inp->input_id == OUT_SPINNER_REAR_UP
					|| inp->input_id == OUT_SPINNER_RIGHT_TELE_OUT
					|| inp->input_id == OUT_SPINNER_LEFT_TELE_OUT
					|| inp->input_id == OUT_SPINNER_RIGHT_TELE_IN
					|| inp->input_id == OUT_SPINNER_LEFT_TELE_IN
					|| inp->input_id == OUT_FRAME_UP
					|| inp->input_id == OUT_FRAME_DOWN
					|| inp->input_id == OUT_STEER_LEFT
					|| inp->input_id == OUT_STEER_RIGHT
					|| inp->input_id == OUT_WEEL_TELE_LEFT_IN
					|| inp->input_id == OUT_WEEL_TELE_RIGHT_IN
					|| inp->input_id == OUT_WEEL_TELE_LEFT_OUT
					|| inp->input_id == OUT_WEEL_TELE_RIGHT_OUT
					|| inp->input_id == OUT_FRAME_LOCK_UP
					|| inp->input_id == OUT_FRAME_LOCK_DOWN
				)
	){


	/*if (tm->outp->isOutputChanging(OUT_SPINNER_RIGHT_UP)
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
			|| tm->outp->isOutputChanging(OUT_FRAME_LOCK_DOWN)){*/

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


DiagnoseTask::DiagnoseTask() : serial_buff(200){
	task_state = STATE_STOPPED;
	task_id = TSK_DIAGNOSE;
	log_listener = false;
	in_listener = false;
	out_listener = false;
	last_run = 0;
}

void DiagnoseTask::testStartConditions(EventData* inp) {
	//Serial.println(" LedTask::testStartConditions()");

	if(inp->input_type == TYPE_MESSAGE
			&& inp->input_id == MSG_STARTUP){
		start();
	}

	last_run = millis();
}

void DiagnoseTask::start() {
	Task::start();
	tm->timer_run_intervall = DIAGNOSE_TIMER_RUN;

	last_run = millis();
	Serial.begin(9600);
}

void DiagnoseTask::update(EventData* inp) {

	if(log_listener){
		sendCommand(DIAG_SET_LOG_LISTENER, inp->input_type, inp->input_id, inp->input_value, inp->additional_info);
	}

	if(in_listener){

		for(int i = 0; i < INPUT_ID_COUNT; i++){
			//alle inputs die sich seit dem letzten Lauf geändert haben
			//unsigned long chgtime = tm->inp->input_data[i].temp_change_time;
			//sendCommand(DIAG_SET_IN_LISTENER, chgtime + DEBOUNCE_TIME, last_run, 0, 0);
			if(tm->inp->hasInputChanged(i)){
				bool state = tm->inp->getInputState(i);
				sendCommand(DIAG_SET_IN_LISTENER, i, state, 0, 0);
			}
		}
	}

	last_run = millis();

	if(out_listener){
		/*for(int i = 0; i < OUTPUT_ID_COUNT; i++){
			//alle outputs die sich geändert haben
			if(tm->outp->isOutputChanging(i)){
				bool state = tm->outp->getOutputState(i);
				sendCommand(DIAG_SET_OUT_LISTENER, i, state, 0, 0);
			}
		}*/
		if(inp->input_type == TYPE_OUTPUT){
			sendCommand(DIAG_SET_OUT_LISTENER, inp->input_id, inp->input_value, 0, 0);

		}
	}


}

void DiagnoseTask::exit() {
	Task::exit();
	tm->timer_run_intervall = DEFAULT_TIMER_RUN;
	Serial.end();
}

void DiagnoseTask::timer() {

	// protocol is "CCaaaa...", two bytes of command, two bytes per arg // command length is minimum 12 bytes, max 22 bytes
	while ( Serial.available()) {
		serial_buff.add(Serial.read());
	}


	bool frame_complete = false;
	bool escaped = false;
	int i = 0;
	char buf[10];
	int buf_len;

	while (!frame_complete){
		if(i >= serial_buff.size()){
			return;
		}

		int got = serial_buff.look_ahead(i);
		if (got == 0x1b && !escaped){
			escaped = true;
		} else if (got == 0x02 && !escaped){
			buf_len = 0;
		} else if (got == 0x03 && !escaped){
			frame_complete = true;
			//sendAck();
		} else {
			buf[buf_len] = got;
			buf_len++;
			escaped = false;
		}

		if (buf_len >= 11){
			sendCommand(DIAG_ERROR, ERR_PROTOCOL_VIOLATION, buf_len, got, 0);
			serial_buff.remove(i);
			return;
		}
		i++;
	}

	serial_buff.remove(i);

	if(buf_len != 10){
		sendCommand(DIAG_ERROR, ERR_PROTOCOL_VIOLATION, buf_len, 0, 0);
		return;
	}

	//least significant byte first
	int command = buf[0] << 8 | buf[1];
	int arg1 = buf[2] << 8 | buf[3];
	int arg2 = buf[4] << 8 | buf[5];
	int arg3 = buf[6] << 8 | buf[7];
	int arg4 = buf[8] << 8 | buf[9];

	//sendCommand(DIAG_ERROR, 50, command, arg1, arg2);

	/*if(command == DIAG_GET_ALL_SETTINGS){
	 getAllSettings();

	} else if(command == DIAG_GET_SETTING){

	 getSetting(setting_id);
	} else if(command == DIAG_SET_SETTING){

	 setSetting(setting_id, value);*/
	if(command == DIAG_SIMULATE_INPUT){
		/**/
		if(tm->inp->input_data[arg2].input_type == TYPE_MANUAL){
			if(tm->inp->getManualSimulationMode()){
				tm->inp->input_data[arg2].temp_state = arg3;
			} else {
				//simulation mode not active
				sendCommand(DIAG_ERROR, ERR_SIMULATION_MODE_NOT_ACTIVE, TYPE_MANUAL, tm->inp->getManualSimulationMode(), 0);
			}
		} else if(tm->inp->input_data[arg2].input_type == TYPE_SENSOR){
			if(tm->inp->getSensorSimulationMode()){
				tm->inp->input_data[arg2].temp_state = arg3;
			} else {
				//simulation mode not active
				sendCommand(DIAG_ERROR, ERR_SIMULATION_MODE_NOT_ACTIVE, TYPE_SENSOR, tm->inp->getSensorSimulationMode(), 0);
			}
		}
	} else if(command == DIAG_SIMULATE_MSG){
		EventData evt;
		evt.input_type = arg1;
		evt.input_id = arg2;
		evt.input_value = arg3;
		evt.additional_info = arg4;

		tm->addEvent(&evt);

	} else if(command == DIAG_SET_IN_LISTENER){
		bool activate_in_listener= arg1;
		in_listener = activate_in_listener;

	} else if(command == DIAG_SET_OUT_LISTENER){
		bool activate_out_listener= arg1;
		out_listener = activate_out_listener;

	} else if(command == DIAG_SET_LOG_LISTENER){
		bool activate_log = arg1;
		log_listener = activate_log;

	} else if(command == DIAG_GET_ALL_IN_VALUES){
		//sendCommand(DIAG_ERROR, 13, 0, 0, 0);
		for (int i = 0; i < INPUT_ID_COUNT; i++){
			bool state = tm->inp->getInputState(i);
			sendCommand(DIAG_GET_ALL_IN_VALUES, i, state, 0, 0);

		}
	}else if(command == DIAG_GET_ALL_OUT_VALUES){
		//sendCommand(DIAG_ERROR, 14, 0, 0, 0);
		for (int i = 0; i < OUTPUT_ID_COUNT; i++){
			bool state = tm->outp->getOutputState(i);
			sendCommand(DIAG_GET_ALL_OUT_VALUES, i, state, 0, 0);

		}
	}else if(command == DIAG_SIMULATE_MANUAL_INPUT_MODE){
		if(arg1 == 1){
			//activate simulate input mode
			tm->inp->setManualSimulationMode(true);
			//sendCommand(DIAG_ERROR, 125, 0, 0, 0);
		} else {
			//deactivate simulate input mode
			tm->inp->setManualSimulationMode(false);
		}
	}else if(command == DIAG_SIMULATE_SENSOR_INPUT_MODE){
		if(arg1 == 1){
			//activate simulate input mode
			tm->inp->setSensorSimulationMode(true);
			//sendCommand(DIAG_ERROR, 125, 0, 0, 0);
		} else {
			//deactivate simulate input mode
			tm->inp->setSensorSimulationMode(false);
		}
	}else if(command == DIAG_SIMULATE_OUTPUT_MODE){
		if(arg1 == 1){
			//activate simulate output mode
			tm->outp->setSimulationMode(true);
		} else {
			//deactivate simulate output mode
			tm->outp->setSimulationMode(false);
		}
	}else{
		sendCommand(DIAG_ERROR, ERR_UNKNOWN_COMMAND_OR_OUT_OF_SYNC, command, arg1, arg2);
	}


}

void DiagnoseTask::sendCommand(int command, int arg1, int arg2, int arg3, int arg4){
	char buf[10];
	char escaped_buf[20];
	//most significant byte first
	buf[1] = command;
	buf[0] = command >> 8;

	buf[3] = arg1;
	buf[2] = arg1 >> 8;

	buf[5] = arg2;
	buf[4] = arg2 >> 8;

	buf[7] = arg3;
	buf[6] = arg3 >> 8;

	buf[9] = arg4;
	buf[8] = arg4 >> 8;

	Serial.write(0x02);
	for(int i = 0; i < 10; i++){
		if(buf[i] == 0x02 || buf[i] == 0x03 || buf[i] == 0x1b){ //escape STX/ETX/ESC (ASCII Style commands used by protocol)
			Serial.write(0x1b);
		}
		Serial.write(buf[i]);
	}
	Serial.write(0x03);
}

/*void DiagnoseTask::sendAck(){
	//Send ASCII Style ACK(=0x06)
	Serial.write(0x06);
}*/




