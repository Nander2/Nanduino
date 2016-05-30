#include "LM35.h"

#define ADC_REAL_FULL_RANGE_VALUE	4.9

LM35::LM35(int pin) : _pin(pin) 
{
	analogReference(EXTERNAL);
	pinMode(pin, INPUT);
}

LM35::~LM35(){ }

double LM35::read() 
{
	int sensorValue = analogRead(_pin);
	double temperature = (ADC_REAL_FULL_RANGE_VALUE * (double)(sensorValue) * 100.0)/1024.0;
	return temperature;
}

double LM35::read(int times) 
{
	int sum = 0;

	for (int i = 0; i < times; i++) sum += analogRead(_pin);

	double average = sum / times;
	return (ADC_REAL_FULL_RANGE_VALUE * average * 100.0)/1024.0;;
}
