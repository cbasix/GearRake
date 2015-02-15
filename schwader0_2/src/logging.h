#ifndef LOGGING_H
#define LOGGING_H

#include "LiquidCrystal_I2C.h"


/*struct Error {
	int error_id;
	bool error_value;
	int additional_data;
};*/


/*class PermanentStorage{
	public:
		void writeError(Error* err, int addr);
		void readError(Error* write_to, int addr);
		void writeSetting(int setting, int addr);
		int readSetting(int addr);
};*/

class MyDisplay{
	public:
		MyDisplay();
		void setBacklight(bool active);
		//void writeError(Error* ptr);
	private:
		LiquidCrystal_I2C* my_lcd;
		//void stringToLCD(char* str);

};


#endif /* LOGGING_H */
