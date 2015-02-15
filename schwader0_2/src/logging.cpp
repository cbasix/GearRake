#include "logging.h"

#include "LiquidCrystal_I2C.h"

#define LCD_ROWS 4
#define LCD_COLS 20

/*
 * logging.cpp
 *
 *  Created on: 02.02.2015
 *      Author: cyberxix
 */

MyDisplay::MyDisplay() {
	my_lcd = new LiquidCrystal_I2C(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

	//my_lcd->begin(20, 4, 5);
	setBacklight(false);
	//stringToLCD("SwStatusMonitor online. ");

}

void MyDisplay::setBacklight(bool active) {
	if(active){
		my_lcd->setBacklight(1);
	} else {
		my_lcd->setBacklight(0);
	}
}

//void Display::writeError(Error* ptr) {}
/*
void Display::stringToLCD(char* str) {
    int lineCount = 0;
    int lineNumber = 0;
    int stillProcessing = 1;
    int charCount = 1;
    my_lcd->clear();
    my_lcd->setCursor(0,0);

    while(stillProcessing) {
         if (++lineCount > LCD_COLS) {    // have we printed 20 characters yet (+1 for the logic)
              lineNumber += 1;
              if(lineNumber > LCD_ROWS-1){
                  stillProcessing = 0;
              }

              my_lcd->setCursor(0,lineNumber);   // move cursor down
              lineCount = 1;
         }

         my_lcd->print(str[charCount - 1]);

         if (!str[charCount]) {   // no more chars to process?
              stillProcessing = 0;
         }

         charCount += 1;
    }
}*/

