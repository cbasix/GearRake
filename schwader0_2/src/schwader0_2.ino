//============================================================================
// Name        : schwader0_2.cpp
// Author      : Sebastian Fassmann
// Version     :
// Copyright   : Copyright Familie Fassmann 2014
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "task_management.h"
#include "tasks.h"
#include "input_output.h"
#include "Adafruit_MCP23017.h"
#include "logging.h"

#include "LiquidCrystal_I2C.h"
#include <Wire.h>




//using namespace std;
TaskMonitor tm;

void setup() {

	//delay(5000);
	
	//Serial.begin(9600);
	//Serial.println("Starting");
//MyDisplay d = MyDisplay();
//Serial.println("a setup");

	tm.beginn();
	

}

void loop(){
  //delay(5000);
  tm.inp->readInput();
  tm.processInputQueue();
  tm.processTimers();
  tm.outp->writeOutput();
 
  
}

