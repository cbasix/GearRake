// ids for tasks must be continous! (stored in array with id as index)
#define TSK_LIST_LENGTH 11

#define TSK_SPINNER_BOTH_UP 0
#define TSK_SPINNER_RIGHT_UP 1
#define TSK_SPINNER_LEFT_UP 2

#define TSK_SPINNER_RIGHT_FLOAT 3
#define TSK_SPINNER_LEFT_FLOAT 4

#define TSK_SPINNER_RIGHT_TELE_OUT 5
#define TSK_SPINNER_RIGHT_TELE_IN 6

#define TSK_SPINNER_LEFT_TELE_OUT 7
#define TSK_SPINNER_LEFT_TELE_IN 8

#define TSK_LED 9 //LED Task muss am ende der Tasklist stehen, sodass er die isOutputChanging() Funktion nutzen kann.
#define TSK_PRESSURE 10

//messages
#define MESSAGE_STARTUP 12001

#define MESSAGE_IN_STEER_LEFT 12002
#define MESSAGE_IN_STEER_RIGHT 12003

#define MESSAGE_IN_WEEL_RIGHT_TELE_OUT 12003
#define MESSAGE_IN_WEEL_RIGHT_TELE_IN 12004

#define MESSAGE_IN_WEEL_LEFT_TELE_OUT 12003
#define MESSAGE_IN_WEEL_LEFT_TELE_IN 12004

#define MESSAGE_IN_SPINNER_BACK_UP 12003
#define MESSAGE_IN_SPINNER_BACK_DOWN 12004

#define MESSAGE_IN_FRAME_UP 12003
#define MESSAGE_IN_FRAME_DOWN 12003



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

class SimpleCylinderMappingTask : public Task {
	public:
		SimpleCylinderMappingTask(int task_id_to_set, int input_id, int output_id_move_out, int output_id_move_in_or_float, int cylinder_state);

		void start();
		void update(InputEventData *inp);
		void exit();
		void timer();
		void testStartConditions(InputEventData* inp);

	private:
		int mapped_input_id;
		int mapped_output_id_move_out;
		int mapped_output_id_move_in_or_float;
		int mapped_cylinder_state;
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

/**
 * Beim Hochfahren werden beide Ventile aktiviert, es fahren aber nicht beide
 * Kreisel gleichzeitig nach oben deshalb muss der Kreisel der zuerst bei 1/3 Stellung ankommt
 * abgeschalten werden. Task beendet wenn beide Kreisel auf 1/3 Stellung angekommen.
 */
class BothSpinnerUpTask : public Task {
	public:
		BothSpinnerUpTask();

		void start();
		void update(InputEventData *inp);
		void exit();
		void timer();
		void testStartConditions(InputEventData* inp);
	private:
			bool spinner_left_is_done;
			bool spinner_right_is_done;
};

class SpinnerLeftUpTask : public Task {
	public:
		SpinnerLeftUpTask();

		void start();
		void update(InputEventData *inp);
		void exit();
		void timer();
		void testStartConditions(InputEventData* inp);
};

class SpinnerRightUpTask : public Task {
	public:
		SpinnerRightUpTask();

		void start();
		void update(InputEventData *inp);
		void exit();
		void timer();
		void testStartConditions(InputEventData* inp);
};

class SpinnerLeftFloatTask : public Task {
	public:
		SpinnerLeftFloatTask();

		void start();
		void update(InputEventData *inp);
		void exit();
		void timer();
		void testStartConditions(InputEventData* inp);
};

class SpinnerRightFloatTask : public Task {
	public:
		SpinnerRightFloatTask();

		void start();
		void update(InputEventData *inp);
		void exit();
		void timer();
		void testStartConditions(InputEventData* inp);
};

//last in tasks to executep need to use the isOutputChanged Method
class LedTask : public Task {
	public:
		LedTask();

		void start();
		void update(InputEventData *inp);
		void exit();
		void timer();
		void testStartConditions(InputEventData* inp);
};

class PressureTask : public Task {
	public:
		PressureTask();

		void start();
		void update(InputEventData *inp);
		void exit();
		void timer();
		void testStartConditions(InputEventData* inp);
};



