#ifndef TASK_MANAGEMENT_H
#define TASK_MANAGEMENT_H


#define STATE_RUNNING 1
#define STATE_STOPPED 0

#define DEFAULT_TIMER_RUN 200
#define DIAGNOSE_TIMER_RUN 10



struct EventData;
class InputObject;
class FifoQueue;
class OutputObject;

#include "Arduino.h"
#include "input_output.h"
#include "logging.h"

/*class Task
  public:
    Task();
    //boolean readPin(int pin);
    unsigned long getTimeNextRun();
    int onStart();
    int onInput(int input);
    int onTimer();
    int onStop();
    int getID();
    int getStatus();
  protected:
    unsigned long _timeNextRun;


};*/
class TaskManager; //Forward Declaration

class Task {
	public:
		//Task();
		int getId();
		int getState();


		virtual void start();
		virtual void update(EventData *inp) = 0;
		virtual void exit();
		virtual void timer();
		virtual void testStartConditions(EventData *inp) = 0;

		void setTaskManager(TaskManager* tm);

		//virtual ~Task() = 0;

	protected:
		int task_id;
		int task_state;
		TaskManager* tm;

};

//MANAGER
class TaskManager{
	public:
		TaskManager();

		void beginn();

		void addEvent(EventData *inp);
		void addMessage(int message_id, bool message_state);
		void addError(int error_id, int error_param);
		void addTimeout(int sensor_id);
		void addDebug(int debug_id, int debug_data, int test);
		void addOutput(int output_id, int value);

		void processInputQueue();
		void processTimers();


		void startTask(int task_id);
		void stopTask(int task_id);

		int getTaskStatus(int task_id);

		InputObject* inp;
		OutputObject* outp;

		MyDisplay dsp;

		unsigned long timer_run_intervall;

	private:
		//Task* taskList[];
		//ist ehere eine Event queue als eine input queue
		FifoQueue* evt_queue;

		Task* task_list[100];
		//int task_list_length;

		unsigned long timer_last_run;


};
//END MANGER




#endif /* TASK_MANAGEMENT_H */
