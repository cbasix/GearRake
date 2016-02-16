#include "util.h"

// ids for tasks must be continous! (stored in array with id as index)
enum  tasks {
	TSK_SPINNER_BOTH_UP, //0
	TSK_SPINNER_RIGHT_UP,
	TSK_SPINNER_LEFT_UP,
	TSK_SPINNER_REAR_UP,
	TSK_SPINNER_RIGHT_FLOAT_PERM,
	TSK_SPINNER_LEFT_FLOAT_PERM,
	TSK_SPINNER_REAR_FLOAT_PERM,

	TSK_SPINNER_LEFT_AUTO_THIRD,
	TSK_SPINNER_RIGHT_AUTO_THIRD,
	TSK_SPINNER_REAR_AUTO_UP,

	TSKPART_SPINNER_LEFT_UP, //10
	TSKPART_SPINNER_LEFT_FLOAT,
	TSKPART_SPINNER_LEFT_TO_UP,
	TSKPART_SPINNER_LEFT_TO_THIRD,
	TSKPART_SPINNER_LEFT_UP_SHORT,
	TSKPART_SPINNER_RIGHT_UP,
	TSKPART_SPINNER_RIGHT_FLOAT,
	TSKPART_SPINNER_RIGHT_TO_UP,
	TSKPART_SPINNER_RIGHT_TO_THIRD,
	TSKPART_SPINNER_RIGHT_UP_SHORT,
	TSKPART_SPINNER_REAR_FLOAT_LONG, //20
	TSKPART_SPINNER_REAR_UP_SHORT,
	TSKPART_SPINNER_REAR_TO_UP,
	TSK_SPINNER_REAR_UP_IN_REAR,
	TSKPART_SPINNER_REAR_DOWN_IN_REAR,

	TSK_SPINNER_TELE_RIGHT_OUT,
	TSK_SPINNER_TELE_RIGHT_IN,
	TSK_SPINNER_TELE_LEFT_OUT,
	TSK_SPINNER_TELE_LEFT_IN,
	TSKPART_SPINNER_TELE_LEFT_TO_IN,
	TSKPART_SPINNER_TELE_LEFT_TO_OUT,//30
	TSKPART_SPINNER_TELE_RIGHT_TO_IN,
	TSKPART_SPINNER_TELE_RIGHT_TO_OUT,

	TSK_STEER_LEFT,
	TSK_STEER_RIGHT,

	TSK_WEEL_RIGHT_TELE_OUT,
	TSK_WEEL_RIGHT_TELE_IN,
	TSK_WEEL_LEFT_TELE_OUT,
	TSK_WEEL_LEFT_TELE_IN,
	TSKPART_WEEL_TELE_RIGHT_TO_IN,
	TSKPART_WEEL_TELE_RIGHT_TO_OUT, //40
	TSKPART_WEEL_TELE_LEFT_TO_IN,
	TSKPART_WEEL_TELE_LEFT_TO_OUT,

	TSK_FRAME_UP,
	TSKPART_FRAME_UP,
	TSK_FRAME_DOWN,
	TSKPART_FRAME_TO_GROUND,
	TSKPART_FRAME_TO_LOW,
	TSKPART_FRAME_TO_MIDDLE,
	TSKPART_FRAME_TO_UP,
	TSKPART_FRAME_UP_SHORT, //50

	TSKPART_FRAME_LOCK_TO_UP,
	TSKPART_FRAME_LOCK_TO_DOWN,

	TSKPART_AUTO_LOW_DELAY,
	TSK_AUTO_LOW,

	TSKPART_AUTO_WORK_DELAY,
	TSK_AUTO_WORK,

	TSKPART_AUTO_TRANSPORT_DELAY,
	TSK_AUTO_TRANSPORT,

	TSK_MODE,

//Diese Tasks müssen am ende der Tasklist stehen, sodass die isOutputChanging() Funktion genutzt werden kann.
	TSK_LED, //60
	TSK_PRESSURE,
	TSK_DIAGNOSE,
	TSK_LIST_LENGTH
};

//messages
enum messages {
	MSG_STARTUP = 12001,

	MSG_IN_STEER_LEFT = 12010,
	MSG_IN_STEER_RIGHT = 12020,

	MSG_IN_WEEL_RIGHT_TELE_OUT = 12030,
	MSG_IN_WEEL_RIGHT_TELE_IN = 12040,

	MSG_IN_WEEL_LEFT_TELE_OUT = 12050,
	MSG_IN_WEEL_LEFT_TELE_IN = 12060,

	MSG_IN_SPINNER_REAR_UP = 12070,
	MSG_IN_SPINNER_REAR_FLOAT = 12080,
	MSG_IN_SPINNER_REAR_AUTO_UP = 12085,


	MSG_IN_FRAME_UP = 12090,
	MSG_IN_FRAME_DOWN = 12100,

	MSG_TSKPART_FRAME_DOWN = 12110,
	MSG_TSKPART_FRAME_UP = 12120,
	MSG_TSKPART_FRAME_TO_GROUND = 12130,
	MSG_TSKPART_FRAME_TO_LOW = 12140,
	MSG_TSKPART_FRAME_TO_MIDDLE = 12150,
	MSG_TSKPART_FRAME_TO_UP = 12160,
	MSG_TSKPART_FRAME_UP_SHORT = 12170,

	MSG_TSKPART_FRAME_LOCK_TO_UP = 12180,
	MSG_TSKPART_FRAME_LOCK_TO_DOWN = 12190,

	MSG_TSKPART_SPINNER_LEFT_UP = 12195,
	MSG_TSKPART_SPINNER_RIGHT_UP = 12196,
	MSG_TSKPART_SPINNER_LEFT_FLOAT = 12197,
	MSG_TSKPART_SPINNER_RIGHT_FLOAT = 12198,
	MSG_TSKPART_SPINNER_LEFT_TO_UP = 12200,
	MSG_TSKPART_SPINNER_RIGHT_TO_UP = 12210,
	MSG_TSKPART_SPINNER_LEFT_TO_THIRD = 12220,
	MSG_TSKPART_SPINNER_RIGHT_TO_THIRD = 12230,
	MSG_TSKPART_SPINNER_REAR_TO_UP = 12235,
	MSG_TSKPART_SPINNER_LEFT_UP_SHORT = 12236,
	MSG_TSKPART_SPINNER_RIGHT_UP_SHORT = 12237,

	MSG_TSKPART_WEEL_TELE_RIGHT_TO_IN = 12240,
	MSG_TSKPART_WEEL_TELE_RIGHT_TO_OUT = 12250,
	MSG_TSKPART_WEEL_TELE_LEFT_TO_IN = 12260,
	MSG_TSKPART_WEEL_TELE_LEFT_TO_OUT = 12270,

	MSG_TSKPART_SPINNER_TELE_LEFT_TO_IN = 12280,
	MSG_TSKPART_SPINNER_TELE_LEFT_TO_OUT = 12290,
	MSG_TSKPART_SPINNER_TELE_RIGHT_TO_IN = 12300,
	MSG_TSKPART_SPINNER_TELE_RIGHT_TO_OUT = 12310,

	MSG_TSKPART_SPINNER_REAR_FLOAT_LONG = 12320,
	MSG_TSKPART_SPINNER_REAR_UP_SHORT = 12330,


	MSG_START_DIAG = 14000,

//delayed input messages ( auto buttons erst nach bestimmter drückdauer aktiv)
			MSG_AUTO_LOW_DELAYED = 13001,
	MSG_AUTO_WORK_DELAYED = 13002,
	MSG_AUTO_TRANSPORT_DELAYED = 13003
};

//DIAG commands
enum commands{
	DIAG_ERROR = 1,

	DIAG_GET_SETTING = 10,
	DIAG_SET_SETTING = 11,
	DIAG_GET_ALL_SETTINGS = 12,

	DIAG_SIMULATE_INPUT = 21,
	DIAG_SIMULATE_MSG = 22,

	DIAG_GET_ALL_ERRORS = 32,
	DIAG_CLEAR_ALL_ERRORS = 34,

	DIAG_GET_ALL_IN_VALUES = 41,
	DIAG_GET_ALL_OUT_VALUES = 42,

	DIAG_SET_LOG_LISTENER = 50,

	DIAG_SET_IN_LISTENER = 60,
	DIAG_SET_OUT_LISTENER = 61,

	DIAG_SIMULATE_MANUAL_INPUT_MODE = 71,
	DIAG_SIMULATE_OUTPUT_MODE = 72,
	DIAG_SIMULATE_SENSOR_INPUT_MODE = 73
};

//ERROR values
enum errors {
	ERR_SIMULATION_MODE_NOT_ACTIVE = 2,
	ERR_UNKNOWN_COMMAND_OR_OUT_OF_SYNC = 1,
	ERR_PROTOCOL_VIOLATION = 3,
	ERR_UNEXPECTED_END = 4
};


//GENERAL Abstact Tasks
/*class SimpleMappingTask : public Task {
	public:
	SimpleMappingTask(int task_id_to_set, int input_id, int output_id);

		void start();
		void update(InputEventData *inp);
		void exit();
		void timer();
		void testStartConditions(InputEventData* inp);

	private:
		int mapped_input_id;
		int mapped_output_id;
};*/

class SimpleCylinderTask : public Task {
	public:
		SimpleCylinderTask(int task_id_to_set,
				int input_type,
				int input_id,
				int cylinder_function_1_output_id,
				int cylinder_function_2_output_id,
				int cylinder_state);

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);

	private:
		int mapped_input_type;
		int mapped_input_id;
		int mapped_cylinder_function_1_output_id;
		int mapped_cylinder_function_2_output_id;
		int mapped_cylinder_state;
};

//moves a cylinder till a specified amout of time
class CylinderTimerTaskpart : public Task {
	public:
		CylinderTimerTaskpart(int task_id_to_set,
				int input_type,
				int input_id,
				int cylinder_function_1_output_id,
				int cylinder_function_2_output_id,
				int cylinder_state,
				unsigned long run_duration );

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);

	private:
		int mapped_input_type;
		int mapped_input_id;
		int mapped_cylinder_function_1_output_id;
		int mapped_cylinder_function_2_output_id;
		int mapped_cylinder_state;
		unsigned long start_time;
		unsigned long run_duration;
};

//moves a cylinder till a specified sensor input or timeout
class CylinderSensorTaskpart : public Task {
	public:
		CylinderSensorTaskpart(int task_id_to_set,
				int input_type,
				int input_id,
				int cylinder_function_1_output_id,
				int cylinder_function_2_output_id,
				int cylinder_state,
				int sensor_input_id,
				unsigned long timeout);

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);

	private:
		int mapped_input_type;
		int mapped_input_id;
		int mapped_cylinder_function_1_output_id;
		int mapped_cylinder_function_2_output_id;
		int mapped_cylinder_state;
		unsigned long start_time;
		int sensor_input_id;
		unsigned long timeout;
};

/*class CylinderTwoSensorTaskpart : public Task {
	public:
		CylinderTwoSensorTaskpart(int task_id_to_set,
				int input_type,
				int input_id,
				int cylinder_function_1_output_id,
				int cylinder_function_2_output_id,
				int cylinder_state,
				int sensor_1_input_id,
				int sensor_2_input_id,
				unsigned long timeout);

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);

	private:
		int mapped_input_type;
		int mapped_input_id;
		int mapped_cylinder_function_1_output_id;
		int mapped_cylinder_function_2_output_id;
		int mapped_cylinder_state;
		unsigned long start_time;
		int sensor_1_input_id;
		int sensor_2_input_id;
		unsigned long timeout;
};*/

//sends a message MSG_* = ACTIVE. And the corresponding MSG_* = INACTIVE when a specified sensor input or timeout occours
//with this one can reuse other taskparts which are listening to the corresponding messages.
class MessageSensorTaskpart : public Task {
	public:
		MessageSensorTaskpart(int task_id_to_set,
				int input_type,
				int input_id,
				int output_message_id,
				int sensor_input_id,
				unsigned long timeout);

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);

	private:
		int mapped_input_type;
		int mapped_input_id;
		int mapped_output_message_id;
		unsigned long start_time;
		int sensor_input_id;
		unsigned long timeout;
};

//See "message sensor taskpart" BUT FROM BOTH SIDES sensor = 0 -> move till sensor = 1
// begin sensor = 1 move till sensor = 0
class MessageMoveToSensorTaskpart : public Task {
	public:
		MessageMoveToSensorTaskpart(int task_id_to_set,
				int input_type,
				int input_id,
				int output_message_id_on_sensor_active,
				int output_message_id_on_sensor_inactive,
				int sensor_input_id,
				unsigned long timeout);

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);

	private:
		int mapped_input_type;
		int mapped_input_id;
		int output_message_id_on_sensor_active;
		int output_message_id_on_sensor_inactive;
		unsigned long start_time;
		int sensor_input_id;
		unsigned long timeout;
};

class AutoMessageTask : public Task {
	public:
	AutoMessageTask(int task_id_to_set,
				int input_type,
				int input_id,
				int stop_input_1_type,
				int stop_input_id_1,
				int stop_input_2_type,
				int stop_input_id_2,
				int output_message_id);

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);

	private:
		int mapped_input_type;
		int mapped_input_id;
		int mapped_stop_input_1_type;
		int mapped_stop_input_id_1;
		int mapped_stop_input_2_type;
		int mapped_stop_input_id_2;
		int mapped_output_message_id;
};

class DelayedStartTaskpart : public Task {
	public:
		DelayedStartTaskpart(int task_id_to_set,
				int input_type,
				int input_id,
				int task_id_to_start,
				unsigned long delay);

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);

	private:
		int mapped_input_type;
		int mapped_input_id;
		int mapped_message_to_start;

		unsigned long start_time;
		unsigned long delay;
};


//minimal task
/*class MinimalTask : public Task {
	public:
		MinimalTask();

		void start();
		void update(InputEventData *inp);
		void exit();
		void timer();
		void testStartConditions(InputEventData* inp);
};*/

class ModeTask : public Task {
	public:
		ModeTask();

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);
	private:
		int active_mode;
		void setActiveMode(int active_mode);
};

/**
 * Beim Hochfahren werden beide Ventile aktiviert, es fahren aber nicht beide
 * Kreisel gleichzeitig nach oben deshalb muss der Kreisel der zuerst bei 1/3 Stellung ankommt
 * abgeschalten werden. Task beendet wenn beide Kreisel auf 1/3 Stellung angekommen.
 */
class BothSpinnerUpTask : public Task {
	public:
		BothSpinnerUpTask();

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);
	private:
			bool spinner_left_is_done;
			bool spinner_right_is_done;
};

class SpinnerLeftUpTask : public Task {
	public:
		SpinnerLeftUpTask();

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);
};

class SpinnerRightUpTask : public Task {
	public:
		SpinnerRightUpTask();

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);
};

class SpinnerLeftFloatPermTask : public Task {
	public:
		SpinnerLeftFloatPermTask();

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);
};

class SpinnerRightFloatPermTask : public Task {
	public:
		SpinnerRightFloatPermTask();

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);
};

class SpinnerRearFloatPermTask : public Task {
	public:
		SpinnerRearFloatPermTask();

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);
};

class FrameDownTask : public Task {
	public:
		FrameDownTask(unsigned long upward_time);

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);
	private:
		bool manual_mode;
};

class AutoLowTask : public Task {
	public:
		AutoLowTask();

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);
};

class AutoWorkTask : public Task {
	public:
		AutoWorkTask();

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);

	private:
		int step;
		bool left_done;
		bool right_done;
};

class AutoTransportTask : public Task {
	public:
		AutoTransportTask();

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);

	private:
		int step;
		bool left_done;
		bool right_done;
};

/*class AutoWorkTask : public Task {
	public:
		AutoWorkTask();

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);
};

class ButterflyTaskPart : public Task {
	public:
		AutoWorkTask();

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);
};*/

//last in tasks to executep need to use the isOutputChanged Method
class LedTask : public Task {
	public:
		LedTask();

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);
};

class PressureTask : public Task {
	public:
		PressureTask();

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);
};

class DiagnoseTask : public Task {
	public:
		DiagnoseTask();

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);
	private:
		bool log_listener;
		bool in_listener;
		bool out_listener;
		unsigned long last_run;
		void sendCommand(int command, int arg1, int arg2, int arg3, int arg4);
		//void sendAck();
		CircularQueue<char> serial_buff;
};


