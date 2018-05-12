#include "Arduino.h"
#include "task_management.h"
#include "tasks.h"
#include "input_output.h"
#include "logging.h"

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

void Task::setTaskManager(TaskManager* task_monitor) {
	tm = task_monitor;
}

void Task::exit() {
	task_state = STATE_STOPPED;
}
//END TASK--------------------------------------------

//TASK MONITOR ---------------------------------------

TaskManager::TaskManager() {
	timer_last_run = 0;
	timer_run_intervall = DEFAULT_TIMER_RUN;

	outp = NULL;
	inp = NULL;
	evt_queue = NULL;
	//dsp = MyDisplay();//39 0x27 I2C address


}

void TaskManager::beginn() {
	outp = new OutputObject(this);
	inp = new InputObject(this);
	evt_queue = new FifoQueue;

	//spinner ----------------------------------------------------------------
	task_list[TSK_SPINNER_BOTH_UP] = new BothSpinnerUpTask();
	task_list[TSK_SPINNER_RIGHT_UP] = new SpinnerRightUpTask();
	task_list[TSK_SPINNER_LEFT_UP] = new SpinnerLeftUpTask();
	task_list[TSK_SPINNER_REAR_UP] = new SimpleCylinderTask(
					TSK_SPINNER_REAR_UP,
					TYPE_MESSAGE,
					MSG_IN_SPINNER_REAR_UP,
					OUT_SPINNER_REAR_UP,
					OUT_SPINNER_REAR_FLOAT,
					CYLINDER_FUNCTION_1);
	task_list[TSK_SPINNER_RIGHT_FLOAT_PERM] = new SpinnerRightFloatPermTask();
	task_list[TSK_SPINNER_LEFT_FLOAT_PERM] = new SpinnerLeftFloatPermTask();
	task_list[TSK_SPINNER_REAR_FLOAT_PERM] = new SpinnerRearFloatPermTask();

	task_list[TSK_SPINNER_LEFT_AUTO_THIRD] = new AutoMessageTask(
			TSK_SPINNER_LEFT_AUTO_THIRD,
			TYPE_MANUAL,
			IN_SPINNER_LEFT_AUTO_THIRD,
			TYPE_MANUAL,
			IN_SPINNER_LEFT_UP,
			TYPE_MANUAL,
			IN_SPINNER_LEFT_FLOAT,
			MSG_TSKPART_SPINNER_LEFT_TO_THIRD);
	task_list[TSK_SPINNER_RIGHT_AUTO_THIRD] = new AutoMessageTask(
			TSK_SPINNER_RIGHT_AUTO_THIRD,
			TYPE_MANUAL,
			IN_SPINNER_RIGHT_AUTO_THIRD,
			TYPE_MANUAL,
			IN_SPINNER_RIGHT_UP,
			TYPE_MANUAL,
			IN_SPINNER_RIGHT_FLOAT,
			MSG_TSKPART_SPINNER_RIGHT_TO_THIRD);
	task_list[TSK_SPINNER_REAR_AUTO_UP] = new AutoMessageTask(
			TSK_SPINNER_REAR_AUTO_UP,
			TYPE_MESSAGE,
			MSG_IN_SPINNER_REAR_AUTO_UP,
			TYPE_MESSAGE,
			MSG_IN_SPINNER_REAR_UP,
			TYPE_MESSAGE,
			MSG_IN_SPINNER_REAR_FLOAT,
			MSG_TSKPART_SPINNER_REAR_TO_UP);
	task_list[TSKPART_SPINNER_LEFT_UP] = new SimpleCylinderTask(
			TSKPART_SPINNER_LEFT_UP,
			TYPE_MESSAGE,
			MSG_TSKPART_SPINNER_LEFT_UP,
			OUT_SPINNER_LEFT_UP,
			OUT_SPINNER_LEFT_FLOAT,
			CYLINDER_FUNCTION_1);
	task_list[TSKPART_SPINNER_LEFT_FLOAT] = new SimpleCylinderTask(
			TSKPART_SPINNER_LEFT_FLOAT,
			TYPE_MESSAGE,
			MSG_TSKPART_SPINNER_LEFT_FLOAT,
			OUT_SPINNER_LEFT_UP,
			OUT_SPINNER_LEFT_FLOAT,
			CYLINDER_FUNCTION_2);
	task_list[TSKPART_SPINNER_LEFT_TO_UP] = new CylinderSensorTaskpart(
			TSKPART_SPINNER_LEFT_TO_UP,
			TYPE_MESSAGE,
			MSG_TSKPART_SPINNER_LEFT_TO_UP,
			OUT_SPINNER_LEFT_UP,
			OUT_SPINNER_LEFT_FLOAT,
			CYLINDER_FUNCTION_1,
			SENS_SPINNER_LEFT_UP,
			25000);
	task_list[TSKPART_SPINNER_LEFT_TO_THIRD] = new MessageMoveToSensorTaskpart(
			TSKPART_SPINNER_LEFT_TO_THIRD,
			TYPE_MESSAGE,
			MSG_TSKPART_SPINNER_LEFT_TO_THIRD,
			MSG_TSKPART_SPINNER_LEFT_FLOAT,
			MSG_TSKPART_SPINNER_LEFT_UP,
			SENS_SPINNER_LEFT_THIRD,
			25000);
	task_list[TSKPART_SPINNER_RIGHT_UP] = new SimpleCylinderTask(
			TSKPART_SPINNER_RIGHT_UP,
			TYPE_MESSAGE,
			MSG_TSKPART_SPINNER_RIGHT_UP,
			OUT_SPINNER_RIGHT_UP,
			OUT_SPINNER_RIGHT_FLOAT,
			CYLINDER_FUNCTION_1);
	task_list[TSKPART_SPINNER_RIGHT_FLOAT] = new SimpleCylinderTask(
			TSKPART_SPINNER_RIGHT_FLOAT,
			TYPE_MESSAGE,
			MSG_TSKPART_SPINNER_RIGHT_FLOAT,
			OUT_SPINNER_RIGHT_UP,
			OUT_SPINNER_RIGHT_FLOAT,
			CYLINDER_FUNCTION_2);
	task_list[TSKPART_SPINNER_RIGHT_TO_UP] = new CylinderSensorTaskpart(
			TSKPART_SPINNER_RIGHT_TO_UP,
			TYPE_MESSAGE,
			MSG_TSKPART_SPINNER_RIGHT_TO_UP,
			OUT_SPINNER_RIGHT_UP,
			OUT_SPINNER_RIGHT_FLOAT,
			CYLINDER_FUNCTION_1,
			SENS_SPINNER_RIGHT_UP,
			25000);
	task_list[TSKPART_SPINNER_RIGHT_TO_THIRD] = new MessageMoveToSensorTaskpart(
			TSKPART_SPINNER_RIGHT_TO_THIRD,
			TYPE_MESSAGE,
			MSG_TSKPART_SPINNER_RIGHT_TO_THIRD,
			MSG_TSKPART_SPINNER_RIGHT_FLOAT,
			MSG_TSKPART_SPINNER_RIGHT_UP,
			SENS_SPINNER_RIGHT_THIRD,
			25000);
	task_list[TSKPART_SPINNER_REAR_FLOAT_LONG] = new CylinderTimerTaskpart(
			TSKPART_SPINNER_REAR_FLOAT_LONG,
			TYPE_MESSAGE,
			MSG_TSKPART_SPINNER_REAR_FLOAT_LONG,
			OUT_SPINNER_REAR_UP,
			OUT_SPINNER_REAR_FLOAT,
			CYLINDER_FUNCTION_2,
			3000);
	task_list[TSKPART_SPINNER_REAR_UP_SHORT] = new CylinderTimerTaskpart(
			TSKPART_SPINNER_REAR_UP_SHORT,
			TYPE_MESSAGE,
			MSG_TSKPART_SPINNER_REAR_UP_SHORT,
			OUT_SPINNER_REAR_UP,
			OUT_SPINNER_REAR_FLOAT,
			CYLINDER_FUNCTION_1,
			1000);
	task_list[TSKPART_SPINNER_REAR_TO_UP] = new CylinderSensorTaskpart(
			TSKPART_SPINNER_REAR_TO_UP,
			TYPE_MESSAGE,
			MSG_TSKPART_SPINNER_REAR_TO_UP,
			OUT_SPINNER_REAR_UP,
			OUT_SPINNER_REAR_FLOAT,
			CYLINDER_FUNCTION_1,
			SENS_SPINNER_REAR_UP,
			15000);
	task_list[TSK_SPINNER_REAR_UP_IN_REAR] = new SimpleCylinderTask(
			TSK_SPINNER_REAR_UP_IN_REAR,
			TYPE_MANUAL,
			IN_REAR_SPINNER_REAR_UP,
			OUT_SPINNER_REAR_UP,
			OUT_SPINNER_REAR_FLOAT,
			CYLINDER_FUNCTION_1);
	task_list[TSKPART_SPINNER_REAR_DOWN_IN_REAR] = new SimpleCylinderTask(
			TSKPART_SPINNER_REAR_DOWN_IN_REAR,
			TYPE_MANUAL,
			IN_REAR_SPINNER_REAR_DOWN,
			OUT_SPINNER_REAR_UP,
			OUT_SPINNER_REAR_FLOAT,
			CYLINDER_FUNCTION_2);
	//spinner tele ---------------------------------------------------
	task_list[TSK_SPINNER_TELE_RIGHT_OUT] = new SimpleCylinderTask(
			TSK_SPINNER_TELE_RIGHT_OUT,
			TYPE_MANUAL,
			IN_SPINNER_RIGHT_TELE_OUT,
			OUT_SPINNER_RIGHT_TELE_OUT,
			OUT_SPINNER_RIGHT_TELE_IN,
			CYLINDER_FUNCTION_1);
	task_list[TSK_SPINNER_TELE_RIGHT_IN] = new SimpleCylinderTask(
			TSK_SPINNER_TELE_RIGHT_IN,
			TYPE_MANUAL,
			IN_SPINNER_RIGHT_TELE_IN,
			OUT_SPINNER_RIGHT_TELE_OUT,
			OUT_SPINNER_RIGHT_TELE_IN,
			CYLINDER_FUNCTION_2);
	task_list[TSK_SPINNER_TELE_LEFT_OUT] = new SimpleCylinderTask(
			TSK_SPINNER_TELE_LEFT_OUT,
			TYPE_MANUAL,
			IN_SPINNER_LEFT_TELE_OUT,
			OUT_SPINNER_LEFT_TELE_OUT,
			OUT_SPINNER_LEFT_TELE_IN,
			CYLINDER_FUNCTION_1);
	task_list[TSK_SPINNER_TELE_LEFT_IN] = new SimpleCylinderTask(
			TSK_SPINNER_TELE_LEFT_IN,
			TYPE_MANUAL,
			IN_SPINNER_LEFT_TELE_IN,
			OUT_SPINNER_LEFT_TELE_OUT,
			OUT_SPINNER_LEFT_TELE_IN,
			CYLINDER_FUNCTION_2);
	task_list[TSKPART_SPINNER_TELE_LEFT_TO_IN] = new CylinderSensorTaskpart(
			TSKPART_SPINNER_TELE_LEFT_TO_IN,
			TYPE_MESSAGE,
			MSG_TSKPART_SPINNER_TELE_LEFT_TO_IN,
			OUT_SPINNER_LEFT_TELE_IN,
			OUT_SPINNER_LEFT_TELE_OUT,
			CYLINDER_FUNCTION_1,
			SENS_SPINNER_LEFT_TELE_IN,
			25000);
	task_list[TSKPART_SPINNER_TELE_LEFT_TO_OUT] = new CylinderSensorTaskpart(
			TSKPART_SPINNER_TELE_LEFT_TO_OUT,
			TYPE_MESSAGE,
			MSG_TSKPART_SPINNER_TELE_LEFT_TO_OUT,
			OUT_SPINNER_LEFT_TELE_IN,
			OUT_SPINNER_LEFT_TELE_OUT,
			CYLINDER_FUNCTION_2,
			SENS_SPINNER_LEFT_TELE_OUT,
			25000);
	task_list[TSKPART_SPINNER_TELE_RIGHT_TO_IN] = new CylinderSensorTaskpart(
			TSKPART_SPINNER_TELE_RIGHT_TO_IN,
			TYPE_MESSAGE,
			MSG_TSKPART_SPINNER_TELE_RIGHT_TO_IN,
			OUT_SPINNER_RIGHT_TELE_IN,
			OUT_SPINNER_RIGHT_TELE_OUT,
			CYLINDER_FUNCTION_1,
			SENS_SPINNER_RIGHT_TELE_IN,
			25000);
	task_list[TSKPART_SPINNER_TELE_RIGHT_TO_OUT] = new CylinderSensorTaskpart(
			TSKPART_SPINNER_TELE_RIGHT_TO_OUT,
			TYPE_MESSAGE,
			MSG_TSKPART_SPINNER_TELE_RIGHT_TO_OUT,
			OUT_SPINNER_RIGHT_TELE_IN,
			OUT_SPINNER_RIGHT_TELE_OUT,
			CYLINDER_FUNCTION_2,
			SENS_SPINNER_RIGHT_TELE_OUT,
			25000);
	task_list[TSKPART_SPINNER_LEFT_UP_SHORT] = new CylinderTimerTaskpart(
			TSKPART_SPINNER_LEFT_UP_SHORT,
			TYPE_MESSAGE,
			MSG_TSKPART_SPINNER_LEFT_UP_SHORT,
			OUT_SPINNER_LEFT_UP,
			OUT_SPINNER_LEFT_FLOAT,
			CYLINDER_FUNCTION_1,
			2000);
	task_list[TSKPART_SPINNER_RIGHT_UP_SHORT] = new CylinderTimerTaskpart(
			TSKPART_SPINNER_RIGHT_UP_SHORT,
			TYPE_MESSAGE,
			MSG_TSKPART_SPINNER_RIGHT_UP_SHORT,
			OUT_SPINNER_RIGHT_UP,
			OUT_SPINNER_RIGHT_FLOAT,
			CYLINDER_FUNCTION_1,
			2000);


	//steer left and right -------------------------------------------------------
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

	//weeltele -----------------------------------------------------------------
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
	task_list[TSKPART_WEEL_TELE_LEFT_TO_IN] = new CylinderSensorTaskpart(
			TSKPART_WEEL_TELE_LEFT_TO_IN,
			TYPE_MESSAGE,
			MSG_TSKPART_WEEL_TELE_LEFT_TO_IN,
			OUT_WEEL_TELE_LEFT_IN,
			OUT_WEEL_TELE_LEFT_OUT,
			CYLINDER_FUNCTION_1,
			SENS_WEEL_TELE_LEFT_IN,
			25000);
	task_list[TSKPART_WEEL_TELE_RIGHT_TO_IN] = new CylinderSensorTaskpart(
			TSKPART_WEEL_TELE_RIGHT_TO_IN,
			TYPE_MESSAGE,
			MSG_TSKPART_WEEL_TELE_RIGHT_TO_IN,
			OUT_WEEL_TELE_RIGHT_IN,
			OUT_WEEL_TELE_RIGHT_OUT,
			CYLINDER_FUNCTION_1,
			SENS_WEEL_TELE_RIGHT_IN,
			25000);
	task_list[TSKPART_WEEL_TELE_LEFT_TO_OUT] = new CylinderSensorTaskpart(
			TSKPART_WEEL_TELE_LEFT_TO_OUT,
			TYPE_MESSAGE,
			MSG_TSKPART_WEEL_TELE_LEFT_TO_OUT,
			OUT_WEEL_TELE_LEFT_IN,
			OUT_WEEL_TELE_LEFT_OUT,
			CYLINDER_FUNCTION_2,
			SENS_WEEL_TELE_LEFT_OUT,
			25000);
	task_list[TSKPART_WEEL_TELE_RIGHT_TO_OUT] = new CylinderSensorTaskpart(
			TSKPART_WEEL_TELE_RIGHT_TO_OUT,
			TYPE_MESSAGE,
			MSG_TSKPART_WEEL_TELE_RIGHT_TO_OUT,
			OUT_WEEL_TELE_RIGHT_IN,
			OUT_WEEL_TELE_RIGHT_OUT,
			CYLINDER_FUNCTION_2,
			SENS_WEEL_TELE_RIGHT_OUT,
			25000);

	//Frame----------------------------------------------------------------------
	task_list[TSK_FRAME_UP] = new SimpleCylinderTask(
			TSK_FRAME_UP,
			TYPE_MESSAGE,
			MSG_IN_FRAME_UP,
			OUT_FRAME_UP,
			OUT_FRAME_DOWN,
			CYLINDER_FUNCTION_1);
	task_list[TSKPART_FRAME_UP] = new SimpleCylinderTask(
			TSKPART_FRAME_UP,
			TYPE_MESSAGE,
			MSG_TSKPART_FRAME_UP,
			OUT_FRAME_UP,
			OUT_FRAME_DOWN,
			CYLINDER_FUNCTION_1);
	//todo aus eeeprom auslesen
	task_list[TSK_FRAME_DOWN] = new FrameDownTask(2000);
	/*task_list[TSKPART_FRAME_DOWN_DIRECT] = new SimpleCylinderTask(
			TSKPART_FRAME_DOWN_DIRECT,
			TYPE_MESSAGE,
			MSG_TSKPART_FRAME_DOWN_DIRECT,
			OUT_FRAME_UP,
			OUT_FRAME_DOWN,
			CYLINDER_FUNCTION_2,
			SENS_FRAME_GROUND,
			5000);*/
	task_list[TSKPART_FRAME_TO_GROUND] = new MessageSensorTaskpart(
			TSKPART_FRAME_TO_GROUND,
			TYPE_MESSAGE,
			MSG_TSKPART_FRAME_TO_GROUND,
			MSG_TSKPART_FRAME_DOWN,
			SENS_FRAME_GROUND,
			20000);
	task_list[TSKPART_FRAME_TO_LOW] = new MessageMoveToSensorTaskpart(
			TSKPART_FRAME_TO_LOW,
			TYPE_MESSAGE,
			MSG_TSKPART_FRAME_TO_LOW,
			MSG_TSKPART_FRAME_UP,
			MSG_TSKPART_FRAME_DOWN,
			SENS_FRAME_LOW,
			15000);
	task_list[TSKPART_FRAME_TO_MIDDLE] = new MessageMoveToSensorTaskpart(
			TSKPART_FRAME_TO_MIDDLE,
			TYPE_MESSAGE,
			MSG_TSKPART_FRAME_TO_MIDDLE,
			MSG_TSKPART_FRAME_UP,
			MSG_TSKPART_FRAME_DOWN,
			SENS_FRAME_MIDDLE,
			13000);
	task_list[TSKPART_FRAME_TO_UP] = new MessageSensorTaskpart(
			TSKPART_FRAME_TO_UP,
			TYPE_MESSAGE,
			MSG_TSKPART_FRAME_TO_UP,
			MSG_TSKPART_FRAME_UP,
			SENS_FRAME_UP,
			20000);
	task_list[TSKPART_FRAME_UP_SHORT] = new CylinderTimerTaskpart(
			TSKPART_FRAME_UP_SHORT,
			TYPE_MESSAGE,
			MSG_TSKPART_FRAME_UP_SHORT,
			OUT_FRAME_UP,
			OUT_FRAME_DOWN,
			CYLINDER_FUNCTION_1,
			1000);

	// framelock --------------------------------------------------------------
	task_list[TSKPART_FRAME_LOCK_TO_UP] = new CylinderSensorTaskpart(
			TSKPART_FRAME_LOCK_TO_UP,
			TYPE_MESSAGE,
			MSG_TSKPART_FRAME_LOCK_TO_UP,
			OUT_FRAME_LOCK_UP,
			OUT_FRAME_LOCK_DOWN,
			CYLINDER_FUNCTION_1,
			SENS_FRAME_LOCK_OPEN,
			1000);
	task_list[TSKPART_FRAME_LOCK_TO_DOWN] = new CylinderSensorTaskpart(
			TSKPART_FRAME_LOCK_TO_DOWN,
			TYPE_MESSAGE,
			MSG_TSKPART_FRAME_LOCK_TO_DOWN,
			OUT_FRAME_LOCK_UP,
			OUT_FRAME_LOCK_DOWN,
			CYLINDER_FUNCTION_2,
			SENS_FRAME_LOCK_CLOSED,
			1000);

	//auto functions ------------------------------------------------------------
	task_list[TSKPART_AUTO_LOW_DELAY] = new DelayedStartTaskpart(
			TSKPART_AUTO_LOW_DELAY,
			TYPE_MANUAL,
			IN_AUTO_LOW,
			MSG_AUTO_LOW_DELAYED,
			3000);
	task_list[TSK_AUTO_LOW] = new AutoLowTask();
	task_list[TSKPART_AUTO_WORK_DELAY] = new DelayedStartTaskpart(
			TSKPART_AUTO_WORK_DELAY,
			TYPE_MANUAL,
			IN_AUTO_WORK,
			MSG_AUTO_WORK_DELAYED,
			3000);
	task_list[TSK_AUTO_WORK] = new AutoWorkTask();
	task_list[TSKPART_AUTO_TRANSPORT_DELAY] = new DelayedStartTaskpart(
			TSKPART_AUTO_TRANSPORT_DELAY,
			TYPE_MANUAL,
			IN_AUTO_TRANSPORT,
			MSG_AUTO_TRANSPORT_DELAYED,
			3000);
	task_list[TSK_AUTO_TRANSPORT] = new AutoTransportTask();


	task_list[TSK_MODE] = new ModeTask();

	/*task_list[TSKPART_START_DIAG_DELAY] = new DelayedStartTaskpart(
				TSKPART_START_DIAG_DELAY,
				TYPE_MANUAL,
				IN_AUTO_LOW,
				MSG_START_DIAG,
				10000);*/

	//LED Task / Pressure Task müssen ganz am ende der Tasklist stehen, sodass die isOutputChanging() Funktion genutzt werden können.
	task_list[TSK_LED] = new LedTask();
	task_list[TSK_PRESSURE] = new PressureTask();
	task_list[TSK_DIAGNOSE] = new DiagnoseTask();


	for(int i = 0; i < TSK_LIST_LENGTH; i++){
		task_list[i]->setTaskManager(this);
	}

	//send startup event
	EventData startupEvent;
	startupEvent.input_id = MSG_STARTUP;
	startupEvent.input_type = TYPE_MESSAGE;
	startupEvent.input_value = 0;
	this->addEvent(&startupEvent);
}

void TaskManager::addEvent(EventData* inp) {
	evt_queue->add(*inp);

//#if ENVIRONMENT == 0*/
//	Serial.print(">>> Event <<< Id: ");
//	Serial.print(inp->input_id);
//	Serial.print(" Type: ");
//	Serial.print(inp->input_type);
//	Serial.print(" Value 1->A/0->IA: ");
//	Serial.println(inp->input_value);

//#endif

}

void TaskManager::addMessage(int message_id, bool message_value, int sender){
	EventData e;
	e.input_id = message_id;
	e.input_type = TYPE_MESSAGE;
	e.input_value = message_value;
	e.additional_info = sender;

	addEvent(&e);
}

void TaskManager::addError(int error_id, int error_param){
	EventData e;
	e.input_id = error_id;
	e.input_type = TYPE_ERROR;
	e.input_value = -1;
	e.additional_info = error_param;

	addEvent(&e);
}

void TaskManager::addTimeout(int task_id){
	EventData e;
	e.input_id = task_id;
	e.input_type = TYPE_TIMEOUT;
	e.input_value = -1;
	e.additional_info = -1;

	addEvent(&e);
}

void TaskManager::addDebug(int debug_id, int debug_data, int test){
	EventData e;
	e.input_id = debug_id;
	e.input_type = TYPE_DEBUG;
	e.input_value = -1;
	e.additional_info = debug_data;

	addEvent(&e);
}

void TaskManager::addOutput(int output_id, int value){
	EventData e;
	e.input_id = output_id;
	e.input_type = TYPE_OUTPUT;
	e.input_value = value;
	e.additional_info = -1;

	addEvent(&e);
}

void TaskManager::resetTasks(){
	//stop all tasks
	for(int i = 0; i < TSK_LIST_LENGTH; i++){
		stopTask(i);
	}

	//all outputs to 0
	outp->resetOutputs();

	//empty event queue
	while(evt_queue->size() > 0){
		evt_queue->get();
	}

	//sentd startup event -> restart tasks that start on startup
	EventData startupEvent;
	startupEvent.input_id = MSG_STARTUP;
	startupEvent.input_type = TYPE_MESSAGE;
	startupEvent.input_value = 0;
	this->addEvent(&startupEvent);
}


void TaskManager::processInputQueue() {
	//TODO get InputEvent from queue
	if(evt_queue->size() > 0){
		EventData* inp = evt_queue->get();
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

void TaskManager::processTimers() {
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

void TaskManager::startTask(int task_id) {
	task_list[task_id]->start();
}

void TaskManager::stopTask(int task_id) {
	if(task_list[task_id]->getState() != STATE_STOPPED){
		task_list[task_id]->exit();
	}
}

int TaskManager::getTaskStatus(int task_id) {
	return task_list[task_id]->getState();
}


//END TASK MONITOR ------------------------------------





