#ifndef ARDUINO_H
#define ARDUINO_H

#include <iostream>
#include <sys/time.h>
#include <iostream>

#define OUTPUT 1
#define INPUT_PULLUP 2
#define A0 1041

inline unsigned long millis(){
	timespec ts;
	// clock_gettime(CLOCK_MONOTONIC, &ts); // Works on FreeBSD
	clock_gettime(CLOCK_REALTIME, &ts); // Works on Linux
	return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

inline bool digitalRead(int pin){
	return true;
}

inline int analogRead(int pin){
	return 1001;
}

inline void digitalWrite(int pin, bool value){
	std::cout << "Set arduino output: " << pin << " to ACTIVE(0) or INACTIVE(1):"<< value  << std::endl;
}

inline void exp1_digitalWrite(int pin, bool value){
	std::cout << "Set exp1 output: " << pin << " to ACTIVE(0) or INACTIVE(1):"<< value  << std::endl;
}

inline void pinMode(int pin, int mode){
	std::cout << "Pinmode arduino: " << pin << " to mode:"<< mode  << std::endl;
}

#endif /* ARDUINO_H */
