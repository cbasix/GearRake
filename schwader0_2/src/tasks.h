// ids for tasks must be continous! (stored in array with id as index)
#define TSK_LIST_LENGTH 7

#define TSK_SPINNER_BOTH_UP 0
#define TSK_SPINNER_RIGHT_UP 1
#define TSK_SPINNER_LEFT_UP 2
#define TSK_SPINNER_RIGHT_FLOAT 3
#define TSK_SPINNER_LEFT_FLOAT 4

#define TSK_LED 5 //LED Task muss am ende der Tasklist stehen, sodass er die isOutputChanging() Funktion nutzen kann.
#define TSK_PRESSURE 6

//messages
#define MESSAGE_STARTUP 12001


/**
 * Spawner Task Activates Other Tasks depending on Input
 *
 */
class SpawnerTask : public Task {
	public:
		SpawnerTask();

		void start();
		void update(InputEventData* inp);
		void exit();
		void timer();
		void testStartConditions(InputEventData* inp);

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

class LeftSpinnerUpTask : public Task {
	public:
		LeftSpinnerUpTask();

		void start();
		void update(InputEventData *inp);
		void exit();
		void timer();
		void testStartConditions(InputEventData* inp);
};

class RightSpinnerUpTask : public Task {
	public:
		RightSpinnerUpTask();

		void start();
		void update(InputEventData *inp);
		void exit();
		void timer();
		void testStartConditions(InputEventData* inp);
};

class LeftSpinnerFloatTask : public Task {
	public:
		LeftSpinnerFloatTask();

		void start();
		void update(InputEventData *inp);
		void exit();
		void timer();
		void testStartConditions(InputEventData* inp);
};

class RightSpinnerFloatTask : public Task {
	public:
		RightSpinnerFloatTask();

		void start();
		void update(InputEventData *inp);
		void exit();
		void timer();
		void testStartConditions(InputEventData* inp);
};




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



