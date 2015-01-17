#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

class TaskMonitor;

#include "Arduino.h"
#include "task_management.h"
#include "Adafruit_MCP23017.h"

#define HIGH true
#define LOW false

#define ACTIVE true
#define INACTIVE false

#define TYPE_SENSOR 1
#define TYPE_MANUAL 2
#define TYPE_MESSAGE 3

#define CYLINDER_HOLD 0
#define CYLINDER_MOVE_OUT 1
#define CYLINDER_MOVE_IN_OR_FLOAT 2


// ids for input must be continous! (stored in array with id as index)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define INPUT_ID_COUNT 43

//Left Joystick
#define IN_SPINNER_LEFT_UP 0
#define IN_SPINNER_LEFT_FLOAT 1

#define IN_SPINNER_LEFT_TELE_OUT 2
#define IN_SPINNER_LEFT_TELE_IN 3

//Right Joystick
#define IN_SPINNER_RIGHT_UP 4
#define IN_SPINNER_RIGHT_FLOAT 5

#define IN_SPINNER_RIGHT_TELE_OUT 6
#define IN_SPINNER_RIGHT_TELE_IN 7

//Middle Joystick  UP is pulling the joystick!!!
#define IN_MULTI_UP 8
#define IN_MULTI_DOWN 9

#define IN_MULTI_RIGHT 10
#define IN_MULTI_LEFT 11

//Top Buttons
#define IN_AUTO_TRANSPORT 12
#define IN_AUTO_LOW 13
#define IN_AUTO_WORK 14

//Modifier Buttons Links Rechts
#define IN_MOD_LR_STEER 15
#define IN_MOD_LR_UNUSED1 16
#define IN_MOD_LR_UNUSED2 17
#define IN_MOD_LR_WEEL_RIGHT_TELE 18
#define IN_MOD_LR_WEEL_LEFT_TELE 19

//Modifier Buttons Oben Unten
#define IN_MOD_OU_SPINNER_BACK 20
#define IN_MOD_OU_FRAME 21
#define IN_MOD_OU_UNUSED 22

//Sensors
#define SENS_SPINNER_LEFT_THIRD 23
#define SENS_SPINNER_RIGHT_THIRD 24

#define SENS_SPINNER_LEFT_UP 25
#define SENS_SPINNER_RIGHT_UP 26

#define SENS_SPINNER_REAR_UP 27

#define SENS_SPINNER_LEFT_TELE_OUT 28
#define SENS_SPINNER_LEFT_TELE_IN 29

#define SENS_SPINNER_RIGHT_TELE_OUT 30
#define SENS_SPINNER_RIGHT_TELE_IN 31

#define SENS_FRAME_UP 32
#define SENS_FRAME_MIDDLE 33
#define SENS_FRAME_LOW 34
#define SENS_FRAME_DOWN 35

#define SENS_FRAME_LOCK_OPEN 36
#define SENS_FRAME_LOCK_CLOSED 37

#define SENS_WEEL_TELE_RIGHT_OUT 38
#define SENS_WEEL_TELE_RIGHT_IN 39

#define SENS_WEEL_TELE_LEFT_OUT 40
#define SENS_WEEL_TELE_LEFT_IN 41

#define SENS_WEEL_TRACK_MIDDLE 42


// ids for output must be continous! (stored in array with id as index)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define OUTPUT_ID_COUNT 37

#define OUT_SPINNER_RIGHT_UP 0
#define OUT_SPINNER_LEFT_UP 1
#define OUT_SPINNER_REAR_UP 2

#define OUT_SPINNER_RIGHT_FLOAT 3
#define OUT_SPINNER_LEFT_FLOAT 4
#define OUT_SPINNER_REAR_FLOAT 5

#define OUT_SPINNER_RIGHT_TELE_OUT 6
#define OUT_SPINNER_LEFT_TELE_OUT 7

#define OUT_SPINNER_RIGHT_TELE_IN 8
#define OUT_SPINNER_LEFT_TELE_IN 9

#define OUT_FRAME_UP 10
#define OUT_FRAME_DOWN 11

#define OUT_STEER_LEFT 12
#define OUT_STEER_RIGHT 13

#define OUT_WEEL_TELE_LEFT_IN 14
#define OUT_WEEL_TELE_RIGHT_IN 15

#define OUT_WEEL_TELE_LEFT_OUT 16
#define OUT_WEEL_TELE_RIGHT_OUT 17

#define OUT_FRAME_LOCK_UP 18
#define OUT_FRAME_LOCK_DOWN 19

#define OUT_PRESSURE 20

//Leds
#define LED_WEEL_TRACK_MIDDLE 21
#define LED_FRAME_LOCK 22

//Top Buttons
#define LED_AUTO_TRANSPORT 23
#define LED_AUTO_LOW 24
#define LED_AUTO_WORK 25

//Float Leds
#define LED_SPINNER_RIGHT_FLOAT 26
#define LED_SPINNER_LEFT_FLOAT 27
#define LED_SPINNER_REAR_FLOAT 28

//Modifier Leds Links Rechts
#define LED_MOD_LR_STEER 29
#define LED_MOD_LR_UNUSED1 30
#define LED_MOD_LR_UNUSED2 31
#define LED_MOD_LR_WEEL_TELE_R 32
#define LED_MOD_LR_WEEL_TELE_L 33

//Modifier Leds Links Rechts
#define LED_MOD_OU_SPINNER_BACK 34
#define LED_MOD_OU_FRAME 35
#define LED_MOD_OU_UNUSED 36


//pin ranges on different devices--------------------------------------------------------
#define PIN_ARDUINO_START 0
#define PIN_ARDUINO_END 99

#define PIN_EXP1_START 100
#define PIN_EXP1_END 199

#define PIN_EXP2_START 200
#define PIN_EXP2_END 299

#define PIN_EXP3_START 300
#define PIN_EXP3_END 399

#define PIN_ARDUINO_ANALOG_NEGATIVE_START 1000
#define PIN_ARDUINO_ANALOG_NEGATIVE_END 1099
#define PIN_ARDUINO_ANALOG_POSITIVE_START 1100
#define PIN_ARDUINO_ANALOG_POSITIVE_END 1199


#define EXP1_ADDR 0
#define EXP2_ADDR 1
#define EXP3_ADDR 2

#define JOY_TOLERANCE 300
#define JOY_MIDDLE 512

#define DEBOUNCE_TIME 5

#define INPUT_QUEUE_SIZE 100
//usable size is one less because one slot must be kept free in circular queue
//#define INPUT_DATA_SIZE 1


struct InputEventData
{
	int input_id;
	bool input_value;
	int input_type;
};

struct InputData {
	int input_pin;
	int input_type;
	bool debounced_state;
	bool temp_state;
	unsigned int temp_change_time;
	bool active;
};

struct OutputData {
	int output_pin;
	//int output_type;
	bool state;
	bool state_changed;
};

class InputObject{
	public:
		InputObject(TaskMonitor *tm);
		bool getInputState(int input_id);
		//void setTaskMonitor(TaskMonitor *tm);
		void readInput();
	private:
		InputData input_data[INPUT_ID_COUNT];
		TaskMonitor *tm;
};


class FifoInputQueue{
	public:
		FifoInputQueue();
		void add(InputEventData evt);
		InputEventData* get();
		int size();
	private:
		int next_in;
		int next_out;
		InputEventData event_data[INPUT_QUEUE_SIZE];
};

class OutputObject{
	public:
		OutputObject(TaskMonitor* task_monitor);
		void setRawOutput(int output_id, bool output_value);
		void setLed(int output_id, bool output_value);
		void setCylinder(int output_id_move_out, int output_id_move_in_or_float, int cylinder_state);

		bool getOutputState(int output_id);
		bool isOutputChanging(int output_id);
		void writeOutput();

	private:
		OutputData output_data[OUTPUT_ID_COUNT];
		TaskMonitor* tm;
		Adafruit_MCP23017* exp1;
		Adafruit_MCP23017* exp2;
		Adafruit_MCP23017* exp3;
		void setOutput(int output_id, bool output_value);
};







#endif /* INPUT_OUTPUT_H */
