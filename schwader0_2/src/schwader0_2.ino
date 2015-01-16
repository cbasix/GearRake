//============================================================================
// Name        : schwader0_2.cpp
// Author      : Sebastian Fassmann
// Version     :
// Copyright   : Copyright Familie Fassmann 2014
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <Wire.h>
#include "task_management.h"
#include "tasks.h"
#include "input_output.h"
#include "Adafruit_MCP23017.h"



//using namespace std;
TaskMonitor tm;

void setup() {

	//delay(5000);

	Serial.begin(9600);
	Serial.println("Starting");

	tm.beginn();

}

void loop(){
  //delay(5000);
  tm.inp->readInput();
  tm.processInputQueue();
  tm.processTimers();
  tm.outp->writeOutput();
 
  
}

