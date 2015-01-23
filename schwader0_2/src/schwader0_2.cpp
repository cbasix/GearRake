//============================================================================
// Name        : schwader0_2.cpp
// Author      : Sebastian Fassmann
// Version     :
// Copyright   : Copyright Familie Fassmann 2014
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "task_management.h"
#include "tasks.h"
#include "input_output.h"

using namespace std;

#define ENVIRONMENT 100

int main() {
	//cout << "Hello Schwader" << endl; // prints Hello Schwader

	/*
	 * task_list = {new BothSpinnerUpTask(),
	 * 				new LeftSpinnerUpTask(),
	 * 				new RightSpinnerUpTask(), ...}
	 *
	 * tm = new TaskMonitor(task_list)
	 *
	 *	loop() {
	 *		readInputs(tm) (inclusive tm.addInput)
	 *		tm.processInputQueue();
	 *		tm.processTimers();
	 *
	 *
	 *	}
	 *
	 */


	/*
	Task *t1 =  new BothSpinnerUpTask();

	t1->start();
	*/

	EventData *inp_left_b_h = new EventData();
	inp_left_b_h->input_id = IN_SPINNER_LEFT_UP;
	inp_left_b_h->input_type = TYPE_MANUAL;
	inp_left_b_h->input_value = HIGH;

	EventData *inp_right_b_h = new EventData();
	inp_right_b_h->input_id = IN_SPINNER_RIGHT_UP;
	inp_right_b_h->input_type = TYPE_MANUAL;
	inp_right_b_h->input_value = HIGH;

	EventData *inp_left_b_l = new EventData();
	inp_left_b_l->input_id = IN_SPINNER_LEFT_UP;
	inp_left_b_l->input_type = TYPE_MANUAL;
	inp_left_b_l->input_value = LOW;

	EventData *inp_right_b_l = new EventData();
	inp_right_b_l->input_id = IN_SPINNER_RIGHT_UP;
	inp_right_b_l->input_type = TYPE_MANUAL;
	inp_right_b_l->input_value = LOW;


	EventData *inp_left_h = new EventData();
	inp_left_h->input_id = SENS_SPINNER_LEFT_THIRD;
	inp_left_h->input_type = TYPE_SENSOR;
	inp_left_h->input_value = HIGH;
	//t1->update(inp_left_h);
	//delete inp_left_h;

	EventData* inp_left_l = new EventData();
	inp_left_l->input_id = SENS_SPINNER_LEFT_THIRD;
	inp_left_l->input_type = TYPE_SENSOR;
	inp_left_l->input_value = LOW;
	//t1->update(inp_left_l);
	//delete inp_left_l;

	EventData* inp_right_h = new EventData();
	inp_right_h->input_id = SENS_SPINNER_RIGHT_THIRD;
	inp_right_h->input_type = TYPE_SENSOR;
	inp_right_h->input_value = HIGH;
	//t1->update(inp_right_h);
	//delete inp_right_h;

	EventData* inp_right_l = new EventData();
	inp_right_l->input_id = SENS_SPINNER_RIGHT_THIRD;
	inp_right_l->input_type = TYPE_SENSOR;
	inp_right_l->input_value = LOW;
	//t1->update(inp_right_l);
	//delete inp_right_l;
	/*

	//t1->exit();


	FifoInputQueue q;
	q.add(*inp_left_h);
	q.add(*inp_left_l);
	q.add(*inp_right_h);
	q.add(*inp_right_l);
	q.add(*inp_right_l);
	q.add(*inp_right_l);

	cout << "q 1 size:" << q.size() << endl;

	q.get();
	q.get();
	q.get();
	q.get();
	q.get();
	q.get();

	cout << "q 2 size:" << q.size() << endl;

	q.add(*inp_left_h);
	q.add(*inp_left_l);
	q.add(*inp_right_h);
	q.add(*inp_right_l);
	q.add(*inp_right_l);
	q.add(*inp_right_l);
	q.add(*inp_right_l);

	cout << "q 3 size:" << q.size() << endl;
	*/

	TaskMonitor tm;
	tm.beginn();

	tm.addEvent(inp_left_b_h);
	tm.addEvent(inp_left_b_l);

	tm.addEvent(inp_right_h);
	tm.addEvent(inp_left_h);
	tm.addEvent(inp_right_h);
	tm.addEvent(inp_right_h);
	tm.addEvent(inp_left_h);
	tm.addEvent(inp_left_l);
	tm.addEvent(inp_right_h);
	tm.addEvent(inp_right_l);

	while(true){
		tm.inp->readInput();
		tm.processInputQueue();
		tm.processTimers();
		tm.outp->writeOutput();
	}

	return 0;
}

