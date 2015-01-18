#include "Arduino.h"
#include "task_management.h"
#include "tasks.h"
#include "input_output.h"

//TASK------------------------------

int Task::getId() {
	return task_id;
}

int Task::getState() {
	return task_state;
}

void Task::start() {
	task_state = STATE_RUNNING;
}

void Task::update(EventData *inp) {
}

void Task::timer() {}

void Task::setTaskMonitor(TaskMonitor* task_monitor) {
	tm = task_monitor;
}

void Task::exit() {
	task_state = STATE_STOPPED;
}
//END TASK--------------------------------------------

//TASK MONITOR ---------------------------------------

TaskMonitor::TaskMonitor() {
	timer_last_run = 0;
	timer_run_intervall = 200;

	outp = NULL;
	inp = NULL;
	inp_queue = NULL;


}

void TaskMonitor::beginn() {
	outp = new OutputObject(this);
	inp = new InputObject(this);
	inp_queue = new FifoInputQueue;

	// todo prüfen
	//SpawnerTask spawner_task;
	//BothSpinnerUpTask both_spinner_up_task;

	task_list[TSK_SPINNER_BOTH_UP] = new BothSpinnerUpTask();
	task_list[TSK_SPINNER_LEFT_UP] = new SpinnerLeftUpTask();
	task_list[TSK_SPINNER_RIGHT_UP] = new SpinnerRightUpTask();

	task_list[TSK_SPINNER_LEFT_FLOAT] = new SpinnerLeftFloatTask();
	task_list[TSK_SPINNER_RIGHT_FLOAT] = new SpinnerRightFloatTask();

	//spinner back
	task_list[TSK_SPINNER_REAR_UP] = new SimpleCylinderTask(
				TSK_SPINNER_REAR_UP,
				TYPE_MESSAGE,
				MSG_IN_SPINNER_REAR_UP,
				OUT_SPINNER_REAR_UP,
				OUT_WEEL_TELE_LEFT_IN,
				CYLINDER_FUNCTION_1);

	task_list[TSK_SPINNER_REAR_FLOAT] = new SpinnerRearFloatTask();

	//spinner tele out both sides
	task_list[TSK_SPINNER_LEFT_TELE_OUT] = new SimpleCylinderTask(
			TSK_SPINNER_LEFT_TELE_OUT,
			TYPE_MANUAL,
			IN_SPINNER_LEFT_TELE_OUT,
			OUT_SPINNER_LEFT_TELE_OUT,
			OUT_SPINNER_LEFT_TELE_IN,
			CYLINDER_FUNCTION_1);
	task_list[TSK_SPINNER_RIGHT_TELE_OUT] = new SimpleCylinderTask(
			TSK_SPINNER_RIGHT_TELE_OUT,
			TYPE_MANUAL,
			IN_SPINNER_RIGHT_TELE_OUT,
			OUT_SPINNER_RIGHT_TELE_OUT,
			OUT_SPINNER_RIGHT_TELE_IN,
			CYLINDER_FUNCTION_1);

	//spinner tele in both sides
	task_list[TSK_SPINNER_LEFT_TELE_IN] = new SimpleCylinderTask(
			TSK_SPINNER_LEFT_TELE_IN,
			TYPE_MANUAL,
			IN_SPINNER_LEFT_TELE_IN,
			OUT_SPINNER_LEFT_TELE_OUT,
			OUT_SPINNER_LEFT_TELE_IN,
			CYLINDER_FUNCTION_2);
	task_list[TSK_SPINNER_RIGHT_TELE_IN] = new SimpleCylinderTask(
			TSK_SPINNER_RIGHT_TELE_IN,
			TYPE_MANUAL,
			IN_SPINNER_RIGHT_TELE_IN,
			OUT_SPINNER_RIGHT_TELE_OUT,
			OUT_SPINNER_RIGHT_TELE_IN,
			CYLINDER_FUNCTION_2);

	//steer left and right
	task_list[TSK_STEER_LEFT] = new SimpleCylinderTask(
			TSK_STEER_LEFT,
			TYPE_MESSAGE,
			MSG_IN_STEER_LEFT,
			OUT_STEER_LEFT,
			OUT_STEER_RIGHT,
			CYLINDER_FUNCTION_1);
	task_list[TSK_STEER_RIGHT] = new SimpleCylinderTask(
			TSK_STEER_RIGHT,
			TYPE_MESSAGE,
			MSG_IN_STEER_RIGHT,
			OUT_STEER_LEFT,
			OUT_STEER_RIGHT,
			CYLINDER_FUNCTION_2);

	//weeltele right
	task_list[TSK_WEEL_RIGHT_TELE_OUT] = new SimpleCylinderTask(
			TSK_WEEL_RIGHT_TELE_OUT,
			TYPE_MESSAGE,
			MSG_IN_WEEL_RIGHT_TELE_OUT,
			OUT_WEEL_TELE_RIGHT_OUT,
			OUT_WEEL_TELE_RIGHT_IN,
			CYLINDER_FUNCTION_1);
	task_list[TSK_WEEL_RIGHT_TELE_IN] = new SimpleCylinderTask(
			TSK_WEEL_RIGHT_TELE_IN,
			TYPE_MESSAGE,
			MSG_IN_WEEL_RIGHT_TELE_IN,
			OUT_WEEL_TELE_RIGHT_OUT,
			OUT_WEEL_TELE_RIGHT_IN,
			CYLINDER_FUNCTION_2);

	//weeltele LEFT
	task_list[TSK_WEEL_LEFT_TELE_OUT] = new SimpleCylinderTask(
			TSK_WEEL_LEFT_TELE_OUT,
			TYPE_MESSAGE,
			MSG_IN_WEEL_LEFT_TELE_OUT,
			OUT_WEEL_TELE_LEFT_OUT,
			OUT_WEEL_TELE_LEFT_IN,
			CYLINDER_FUNCTION_1);
	task_list[TSK_WEEL_LEFT_TELE_IN] = new SimpleCylinderTask(
			TSK_WEEL_LEFT_TELE_IN,
			TYPE_MESSAGE,
			MSG_IN_WEEL_LEFT_TELE_IN,
			OUT_WEEL_TELE_LEFT_OUT,
			OUT_WEEL_TELE_LEFT_IN,
			CYLINDER_FUNCTION_2);

	//Frame
	task_list[TSK_FRAME_UP] = new SimpleCylinderTask(
			TSK_FRAME_UP,
			TYPE_MESSAGE,
			MSG_IN_FRAME_UP,
			OUT_FRAME_UP,
			OUT_FRAME_DOWN,
			CYLINDER_FUNCTION_1);
	//todo aus eeeprom auslesen
	task_list[TSK_FRAME_DOWN] = new FrameDownTask(2000);


	//reusable taskparts
	task_list[TSKPART_FRAME_SHORT_UP] = new CylinderTimerTaskpart(
			TSKPART_FRAME_SHORT_UP,
			TYPE_MESSAGE,
			MSG_TSKPART_FRAME_SHORT_UP,
			OUT_FRAME_UP,
			OUT_FRAME_DOWN,
			CYLINDER_FUNCTION_1,
			2000);

	task_list[TSKPART_FRAME_LOCK_UP] = new CylinderSensorTaskpart(
			TSKPART_FRAME_LOCK_UP,
			TYPE_MESSAGE,
			MSG_TSKPART_FRAME_LOCK_UP,
			OUT_FRAME_LOCK_UP,
			OUT_FRAME_LOCK_DOWN,
			CYLINDER_FUNCTION_1,
			SENS_FRAME_LOCK_OPEN,
			5000);
	task_list[TSKPART_FRAME_LOCK_DOWN] = new CylinderSensorTaskpart(
			TSKPART_FRAME_LOCK_DOWN,
			TYPE_MESSAGE,
			MSG_TSKPART_FRAME_LOCK_DOWN,
			OUT_FRAME_LOCK_UP,
			OUT_FRAME_LOCK_DOWN,
			CYLINDER_FUNCTION_2,
			SENS_FRAME_LOCK_CLOSED,
			5000);


	//LED Task / Pressure Task müssen ganz am ende der Tasklist stehen, sodass die isOutputChanging() Funktion genutzt werden können.
	task_list[TSK_LED] = new LedTask();
	task_list[TSK_PRESSURE] = new PressureTask();


	for(int i = 0; i < TSK_LIST_LENGTH; i++){
		task_list[i]->setTaskMonitor(this);
	}

	//send startup event
	EventData startupEvent;
	startupEvent.input_id = MSG_STARTUP;
	startupEvent.input_type = TYPE_MESSAGE;
	startupEvent.input_value = 0;
	this->addInput(&startupEvent);
}

void TaskMonitor::addInput(EventData* inp) {
	inp_queue->add(*inp);

//#if ENVIRONMENT == 0*/
//	Serial.print(">>> Event <<< Id: ");
//	Serial.print(inp->input_id);
//	Serial.print(" Type: ");
//	Serial.print(inp->input_type);
//	Serial.print(" Value 1->A/0->IA: ");
//	Serial.println(inp->input_value);

//#endif

}

void TaskMonitor::addMessage(int message_id, bool message_value){
	EventData e;
	e.input_id = message_id;
	e.input_type = TYPE_MESSAGE;
	e.input_value = message_value;

	addInput(&e);
}

void TaskMonitor::addError(int error_id, int error_param){
	EventData e;
	e.input_id = error_id;
	e.input_type = TYPE_ERROR;
	e.input_value = ACTIVE;
	e.additional_info = error_param;

	addInput(&e);
}

void TaskMonitor::addTimeout(int task_id){
	EventData e;
	e.input_id = task_id;
	e.input_type = TYPE_TIMEOUT;
	e.input_value = ACTIVE;

	addInput(&e);
}


void TaskMonitor::processInputQueue() {
	//TODO get InputEvent from queue
	if(inp_queue->size() > 0){
		EventData* inp = inp_queue->get();
		for(int i = 0; i < TSK_LIST_LENGTH; i++){
			if(task_list[i]->getState() == STATE_RUNNING){
				task_list[i]->update(inp);
//				Serial.print(">> Event toTask <<  Id: ");
//				Serial.print(inp->input_id);
//				Serial.print(" Send to active task: ");
//				Serial.println(i);
			} else if (task_list[i]->getState() == STATE_STOPPED) {
				task_list[i]->testStartConditions(inp);
			}
		}
	}
}

void TaskMonitor::processTimers() {
	unsigned long millisec = millis();
	if(timer_last_run + timer_run_intervall < millisec){
		timer_last_run = millis();

		for(int i = 0; i < TSK_LIST_LENGTH; i++){

			if(task_list[i]->getState() == STATE_RUNNING){
				task_list[i]->timer();
			}
		}
	}
}

void TaskMonitor::startTask(int task_id) {
	task_list[task_id]->start();
}

void TaskMonitor::stopTask(int task_id) {
	if(task_list[task_id]->getState() != STATE_STOPPED){
		task_list[task_id]->exit();
	}
}

int TaskMonitor::getTaskStatus(int task_id) {
	return task_list[task_id]->getState();
}


//END TASK MONITOR ------------------------------------





