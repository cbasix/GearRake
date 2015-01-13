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

void Task::update(InputEventData *inp) {
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
	timer_run_intervall = 1000;

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
	task_list[TSK_SPINNER_LEFT_UP] = new LeftSpinnerUpTask();
	task_list[TSK_SPINNER_RIGHT_UP] = new RightSpinnerUpTask();
	task_list[TSK_SPINNER_LEFT_FLOAT] = new LeftSpinnerFloatTask();
	task_list[TSK_SPINNER_RIGHT_FLOAT] = new RightSpinnerFloatTask();


	//LED Task / Pressure Task müssen ganz am ende der Tasklist stehen, sodass die isOutputChanging() Funktion genutzt werden können.
	task_list[TSK_LED] = new LedTask();
	task_list[TSK_PRESSURE] = new PressureTask();


	for(int i = 0; i < TSK_LIST_LENGTH; i++){
		task_list[i]->setTaskMonitor(this);
	}

	//send startup event
	InputEventData startupEvent;
	startupEvent.input_id = MESSAGE_STARTUP;
	startupEvent.input_type = TYPE_MESSAGE;
	startupEvent.input_value = 0;
	this->addInput(&startupEvent);
}

void TaskMonitor::addInput(InputEventData* inp) {
	inp_queue->add(*inp);

/*#if ENVIRONMENT == 0*/
//	Serial.print(">>> Event <<< Id: ");
//	Serial.print(inp->input_id);
//	Serial.print(" Type: ");
//	Serial.print(inp->input_type);
//	Serial.print(" Value 0->A/1->IA: ");
//	Serial.println(inp->input_value);

/*#endif*/

}

void TaskMonitor::processInputQueue() {
	//TODO get InputEvent from queue
	if(inp_queue->size() > 0){
		InputEventData* inp = inp_queue->get();
		for(int i = 0; i < TSK_LIST_LENGTH; i++){
			if(task_list[i]->getState() == STATE_RUNNING){
				task_list[i]->update(inp);
				//Serial.print(">> Event toTask <<  Id: ");
				//Serial.print(inp->input_id);
				//Serial.print(" Send to active task: ");
				//Serial.println(i);
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
	task_list[task_id]->exit();
}

int TaskMonitor::getTaskStatus(int task_id) {
	return task_list[task_id]->getState();
}


//END TASK MONITOR ------------------------------------





