// ids for tasks must be continous! (stored in array with id as index)
#define TSK_LIST_LENGTH 42

#define TSK_SPINNER_BOTH_UP 0
#define TSK_SPINNER_RIGHT_UP 1
#define TSK_SPINNER_LEFT_UP 2

#define TSK_SPINNER_RIGHT_FLOAT 3
#define TSK_SPINNER_LEFT_FLOAT 4

#define TSK_SPINNER_RIGHT_TELE_OUT 5
#define TSK_SPINNER_RIGHT_TELE_IN 6

#define TSK_SPINNER_LEFT_TELE_OUT 7
#define TSK_SPINNER_LEFT_TELE_IN 8

#define TSK_STEER_LEFT 9
#define TSK_STEER_RIGHT 10

#define TSK_WEEL_RIGHT_TELE_OUT 11
#define TSK_WEEL_RIGHT_TELE_IN 12

#define TSK_WEEL_LEFT_TELE_OUT 13
#define TSK_WEEL_LEFT_TELE_IN 14

#define TSK_SPINNER_REAR_UP 15
#define TSK_SPINNER_REAR_FLOAT 16

#define TSK_FRAME_UP 17
#define TSK_FRAME_DOWN 18

#define TSKPART_FRAME_UP_SHORT 19

#define TSKPART_FRAME_LOCK_UP 20
#define TSKPART_FRAME_LOCK_DOWN 21

#define TSKPART_AUTO_LOW_DELAY 22
#define TSK_AUTO_LOW 23

#define TSKPART_AUTO_WORK_DELAY 24
#define TSK_AUTO_WORK 25

#define TSKPART_FRAME_DOWN 26

//#define TSKPART_SPINNER_LEFT_UP 27
//#define TSKPART_SPINNER_RIGHT_UP 28

#define TSKPART_SPINNER_LEFT_FLOAT 27
#define TSKPART_SPINNER_RIGHT_FLOAT 28

#define TSKPART_SPINNER_TELE_LEFT_TO_IN 29
#define TSKPART_SPINNER_TELE_RIGHT_TO_IN 30

#define TSKPART_SPINNER_LEFT_TO_UP 31
#define TSKPART_SPINNER_RIGHT_TO_UP 32

//#define TSKPART_FRAME_UP_TWO_SENS 33

#define TSKPART_WEEL_TELE_RIGHT_TO_IN 34
#define TSKPART_WEEL_TELE_LEFT_TO_IN 35

#define TSKPART_FRAME_TO_GROUND 36
#define TSKPART_FRAME_TO_MIDDLE 37


#define TSK_MODE 38
//#define TSKPART_START_DIAG_DELAY 26

//Diese Tasks müssen am ende der Tasklist stehen, sodass die isOutputChanging() Funktion genutzt werden kann.
#define TSK_LED 39
#define TSK_PRESSURE 40
#define TSK_DIAGNOSE 41


//messages
#define MSG_STARTUP 12001

#define MSG_IN_STEER_LEFT 12003
#define MSG_IN_STEER_RIGHT 12004

#define MSG_IN_WEEL_RIGHT_TELE_OUT 12005
#define MSG_IN_WEEL_RIGHT_TELE_IN 12006

#define MSG_IN_WEEL_LEFT_TELE_OUT 12007
#define MSG_IN_WEEL_LEFT_TELE_IN 12008

#define MSG_IN_SPINNER_REAR_UP 12009
#define MSG_IN_SPINNER_REAR_FLOAT 12010

#define MSG_IN_FRAME_UP 12011
#define MSG_IN_FRAME_DOWN 12012

//taskpart start/ready messages
#define MSG_TSKPART_FRAME_SHORT_UP 12013

#define MSG_TSKPART_FRAME_LOCK_UP 12015
#define MSG_TSKPART_FRAME_LOCK_DOWN 12016

#define MSG_TSKPART_FRAME_DOWN 12017
//#define MSG_TSKPART_SPINNER_LEFT_UP_TWO_SENS 12018
//#define MSG_TSKPART_SPINNER_RIGHT_UP_TWO_SENS 12019
#define MSG_TSKPART_SPINNER_TELE_LEFT_IN 12020
#define MSG_TSKPART_SPINNER_TELE_RIGHT_IN 12021
#define MSG_TSKPART_SPINNER_LEFT_UP 12022
#define MSG_TSKPART_SPINNER_RIGHT_UP 12023
//#define MSG_TSKPART_FRAME_UP_TWO_SENS 12024
#define MSG_TSKPART_WEEL_TELE_RIGHT_IN 12025
#define MSG_TSKPART_WEEL_TELE_LEFT_IN 12026
#define MSG_TSKPART_FRAME_DOWN_TO_GROUND 12027
#define MSG_TSKPART_FRAME_DOWN_TO_MIDDLE 12028


#define MSG_START_DIAG 14000

//delayed input messages ( auto buttons erst nach bestimmter drückdauer aktiv)
#define MSG_AUTO_LOW_DELAYED 13001
#define MSG_AUTO_WORK_DELAYED 13002
#define MSG_AUTO_TRANSPORT_DELAYED 13003




//DIAG commands
#define DIAG_ERROR 0

#define DIAG_GET_SETTING 10
#define DIAG_SET_SETTING 11
#define DIAG_GET_ALL_SETTINGS 12

#define DIAG_SIMULATE_INPUT 21

#define DIAG_GET_ALL_ERRORS 32
#define DIAG_CLEAR_ALL_ERRORS 34

#define DIAG_GET_ALL_IN_VALUES 41
#define DIAG_GET_ALL_OUT_VALUES 42

#define DIAG_SET_LOG_LISTENER 50

#define DIAG_SET_IN_LISTENER 60
#define DIAG_SET_OUT_LISTENER 61

#define DIAG_SIMULATE_INPUT_MODE 71
#define DIAG_SIMULATE_OUTPUT_MODE 72

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

class CylinderTwoSensorTaskpart : public Task {
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
};

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

class SpinnerLeftFloatTask : public Task {
	public:
		SpinnerLeftFloatTask();

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);
};

class SpinnerRightFloatTask : public Task {
	public:
		SpinnerRightFloatTask();

		void start();
		void update(EventData *inp);
		void exit();
		void timer();
		void testStartConditions(EventData* inp);
};

class SpinnerRearFloatTask : public Task {
	public:
		SpinnerRearFloatTask();

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


