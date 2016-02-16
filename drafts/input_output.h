#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

class TaskManager;

#include "Arduino.h"
#include "task_management.h"
#include "Adafruit_MCP23017.h"

struct EventData
{
	int input_id;
	bool input_value;
	int input_type;
	int additional_info;
};

struct InputData {
	int input_pin;
	int input_type;
	bool debounced_state;
	bool temp_state;
	unsigned int temp_change_time;
	bool active;
	bool state_changed;
};

struct OutputData {
	int output_pin;
	//int output_type;
	bool state;
	bool state_changed;
};

class InputObject{
	public:
		InputObject(TaskManager *tm);
		bool getInputState(int input_id);
		//void setTaskMonitor(TaskMonitor *tm);
		void readInput();
		bool hasInputChanged(int input_id);
		InputData input_data[INPUT_ID_COUNT];
		void setManualSimulationMode(bool enabled);
		bool getManualSimulationMode();
		void setSensorSimulationMode(bool enabled);
		bool getSensorSimulationMode();
	private:
		TaskManager *tm;
		bool simulate_manual_input_mode;
		bool simulate_sensor_input_mode;
};

class OutputObject{
	public:
		OutputObject(TaskManager* task_monitor);
		void setRawOutput(int output_id, bool output_value);
		void setLed(int output_id, bool output_value);
		void setCylinder(int function_1_output_id, int function_2_output_id, int cylinder_state);

		bool getOutputState(int output_id);
		bool isOutputChanging(int output_id);
		void writeOutput();
		void setSimulationMode(bool enabled);
		bool getSimulationMode();
		void resetOutputs();

	private:
		bool simulate_output_mode;
		OutputData output_data[OUTPUT_ID_COUNT];
		TaskManager* tm;
		Adafruit_MCP23017* exp1;
		Adafruit_MCP23017* exp2;
		Adafruit_MCP23017* exp3;
		void setOutput(int output_id, bool output_value);
};


#endif /* INPUT_OUTPUT_H */
