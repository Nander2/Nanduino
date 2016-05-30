/*
	LM35.h - Library for LM35 temperature sensor.
	Created by Ricardo Sequeira, February 13, 2014.
	Released into the public domain.
*/
#ifndef __LM35__
#define __LM35__

#include "Arduino.h"

class LM35 {

	int _pin;

public:
	LM35(int pin);
	~LM35();

	double read();
	double read(int times);

};

#endif