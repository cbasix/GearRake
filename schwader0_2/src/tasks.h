// ids for tasks must be continous! (stored in array with id as index)
#define TSK_LIST_LENGTH 26

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

#define TSKPART_FRAME_SHORT_UP 19

#define TSKPART_FRAME_LOCK_UP 20
#define TSKPART_FRAME_LOCK_DOWN 21

#define TSK_MODE 22

//Diese Tasks müssen am ende der Tasklist stehen, sodass die isOutputChanging() Funktion genutzt werden kann.
#define TSK_LED 23
#define TSK_PRESSURE 24
#define TSK_DIAGNOSE 25


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


