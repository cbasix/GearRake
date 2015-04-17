// ids for tasks must be continous! (stored in array with id as index)
#define TSK_LIST_LENGTH 61

#define TSK_SPINNER_BOTH_UP 0
#define TSK_SPINNER_RIGHT_UP 1
#define TSK_SPINNER_LEFT_UP 2
#define TSK_SPINNER_REAR_UP 3
#define TSK_SPINNER_RIGHT_FLOAT_PERM 4
#define TSK_SPINNER_LEFT_FLOAT_PERM 5
#define TSK_SPINNER_REAR_FLOAT_PERM 6

#define TSK_SPINNER_LEFT_AUTO_THIRD 7
#define TSK_SPINNER_RIGHT_AUTO_THIRD 8
#define TSK_SPINNER_REAR_AUTO_UP 9

#define TSKPART_SPINNER_LEFT_UP 10
#define TSKPART_SPINNER_LEFT_FLOAT 11
#define TSKPART_SPINNER_LEFT_TO_UP 12
#define TSKPART_SPINNER_LEFT_TO_THIRD 13
#define TSKPART_SPINNER_RIGHT_UP 14
#define TSKPART_SPINNER_RIGHT_FLOAT 15
#define TSKPART_SPINNER_RIGHT_TO_UP 16
#define TSKPART_SPINNER_RIGHT_TO_THIRD 17
#define TSKPART_SPINNER_REAR_FLOAT_LONG 18
#define TSKPART_SPINNER_REAR_UP_SHORT 19
#define TSKPART_SPINNER_REAR_TO_UP 20
#define TSK_SPINNER_REAR_UP_IN_REAR 21
#define TSKPART_SPINNER_REAR_DOWN_IN_REAR 22

#define TSK_SPINNER_TELE_RIGHT_OUT 23
#define TSK_SPINNER_TELE_RIGHT_IN 24
#define TSK_SPINNER_TELE_LEFT_OUT 25
#define TSK_SPINNER_TELE_LEFT_IN 26
#define TSKPART_SPINNER_TELE_LEFT_TO_IN 27
#define TSKPART_SPINNER_TELE_LEFT_TO_OUT 28
#define TSKPART_SPINNER_TELE_RIGHT_TO_IN 29
#define TSKPART_SPINNER_TELE_RIGHT_TO_OUT 30

#define TSK_STEER_LEFT 31
#define TSK_STEER_RIGHT 32

#define TSK_WEEL_RIGHT_TELE_OUT 33
#define TSK_WEEL_RIGHT_TELE_IN 34
#define TSK_WEEL_LEFT_TELE_OUT 35
#define TSK_WEEL_LEFT_TELE_IN 36
#define TSKPART_WEEL_TELE_RIGHT_TO_IN 37
#define TSKPART_WEEL_TELE_RIGHT_TO_OUT 38
#define TSKPART_WEEL_TELE_LEFT_TO_IN 39
#define TSKPART_WEEL_TELE_LEFT_TO_OUT 40

#define TSK_FRAME_UP 41
#define TSKPART_FRAME_UP 42
#define TSK_FRAME_DOWN 43
//#define TSKPART_FRAME_DOWN_DIRECT 26
#define TSKPART_FRAME_TO_GROUND 44
#define TSKPART_FRAME_TO_LOW 45
#define TSKPART_FRAME_TO_MIDDLE 46
#define TSKPART_FRAME_TO_UP 47
#define TSKPART_FRAME_UP_SHORT 48

#define TSKPART_FRAME_LOCK_TO_UP 49
#define TSKPART_FRAME_LOCK_TO_DOWN 50

#define TSKPART_AUTO_LOW_DELAY 51
#define TSK_AUTO_LOW 52

#define TSKPART_AUTO_WORK_DELAY 53
#define TSK_AUTO_WORK 54

#define TSKPART_AUTO_TRANSPORT_DELAY 55
#define TSK_AUTO_TRANSPORT 56

#define TSK_MODE 57
//#define TSKPART_START_DIAG_DELAY 26

//Diese Tasks müssen am ende der Tasklist stehen, sodass die isOutputChanging() Funktion genutzt werden kann.
#define TSK_LED 58
#define TSK_PRESSURE 59
#define TSK_DIAGNOSE 60


//messages
#define MSG_STARTUP 12001

#define MSG_IN_STEER_LEFT 12010
#define MSG_IN_STEER_RIGHT 12020

#define MSG_IN_WEEL_RIGHT_TELE_OUT 12030
#define MSG_IN_WEEL_RIGHT_TELE_IN 12040

#define MSG_IN_WEEL_LEFT_TELE_OUT 12050
#define MSG_IN_WEEL_LEFT_TELE_IN 12060

#define MSG_IN_SPINNER_REAR_UP 12070
#define MSG_IN_SPINNER_REAR_FLOAT 12080
#define MSG_IN_SPINNER_REAR_AUTO_UP 12085


#define MSG_IN_FRAME_UP 12090
#define MSG_IN_FRAME_DOWN 12100

#define MSG_TSKPART_FRAME_DOWN 12110
#define MSG_TSKPART_FRAME_UP 12120
#define MSG_TSKPART_FRAME_TO_GROUND 12130
#define MSG_TSKPART_FRAME_TO_LOW 12140
#define MSG_TSKPART_FRAME_TO_MIDDLE 12150
#define MSG_TSKPART_FRAME_TO_UP 12160
#define MSG_TSKPART_FRAME_UP_SHORT 12170

#define MSG_TSKPART_FRAME_LOCK_TO_UP 12180
#define MSG_TSKPART_FRAME_LOCK_TO_DOWN 12190

#define MSG_TSKPART_SPINNER_LEFT_UP 12195
#define MSG_TSKPART_SPINNER_RIGHT_UP 12196
#define MSG_TSKPART_SPINNER_LEFT_FLOAT 12197
#define MSG_TSKPART_SPINNER_RIGHT_FLOAT 12198
#define MSG_TSKPART_SPINNER_LEFT_TO_UP 12200
#define MSG_TSKPART_SPINNER_RIGHT_TO_UP 12210
#define MSG_TSKPART_SPINNER_LEFT_TO_THIRD 12220
#define MSG_TSKPART_SPINNER_RIGHT_TO_THIRD 12230
#define MSG_TSKPART_SPINNER_REAR_TO_UP 12235

#define MSG_TSKPART_WEEL_TELE_RIGHT_TO_IN 12240
#define MSG_TSKPART_WEEL_TELE_RIGHT_TO_OUT 12250
#define MSG_TSKPART_WEEL_TELE_LEFT_TO_IN 12260
#define MSG_TSKPART_WEEL_TELE_LEFT_TO_OUT 12270

#define MSG_TSKPART_SPINNER_TELE_LEFT_TO_IN 12280
#define MSG_TSKPART_SPINNER_TELE_LEFT_TO_OUT 12290
#define MSG_TSKPART_SPINNER_TELE_RIGHT_TO_IN 12300
#define MSG_TSKPART_SPINNER_TELE_RIGHT_TO_OUT 12310

#define MSG_TSKPART_SPINNER_REAR_FLOAT_LONG 12320
#define MSG_TSKPART_SPINNER_REAR_UP_SHORT 12330


#define MSG_START_DIAG 14000

//delayed input messages ( auto buttons erst nach bestimmter drückdauer aktiv)
#define MSG_AUTO_LOW_DELAYED 13001
#define MSG_AUTO_WORK_DELAYED 13002
#define MSG_AUTO_TRANSPORT_DELAYED 13003




//DIAG commands
#define DIAG_ERROR 1

#define DIAG_GET_SETTING 10
#define DIAG_SET_SETTING 11
#define DIAG_GET_ALL_SETTINGS 12

#define DIAG_SIMULATE_INPUT 21
#define DIAG_SIMULATE_MSG 22

#define DIAG_GET_ALL_ERRORS 32
#define DIAG_CLEAR_ALL_ERRORS 34

#define DIAG_GET_ALL_IN_VALUES 41
#define DIAG_GET_ALL_OUT_VALUES 42

#define DIAG_SET_LOG_LISTENER 50

#define DIAG_SET_IN_LISTENER 60
#define DIAG_SET_OUT_LISTENER 61

#define DIAG_SIMULATE_INPUT_MODE 71
#define DIAG_SIMULATE_OUTPUT_MODE 72

//ERROR values
#define ERR_SIMULATION_MODE_NOT_ACTIVE 2
#define ERR_UNKNOWN_COMMAND_OR_OUT_OF_SYNC 1


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
};


