#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <SimpleMotorControler.h>

// some variable IDs
#define ERROR_STATUS 0
#define LIMIT_STATUS 3
#define TARGET_SPEED 20
#define INPUT_VOLTAGE 23
#define TEMPERATURE 24
 
// some motor limit IDs
#define FORWARD_ACCELERATION 5
#define REVERSE_ACCELERATION 9
#define DECELERATION 2

#define MOTOR_DEBUG_PRINTF	1

#define rxPin	19
#define txPin	18	 
#define resetPin 17 // pin 5 connects to SMC nRST
#define errPin 16

SimpleMotorControler::SimpleMotorControler()
{ 
	smcSerial = new SoftwareSerial(rxPin, txPin);
}
 
void SimpleMotorControler::begin()
{
  smcSerial->begin(19200);
  
  // briefly reset SMC when Arduino starts up (optional)
  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, LOW);  // reset SMC
  delay(1);  // wait 1 ms
  pinMode(resetPin, INPUT);  // let SMC run again
 
  // must wait at least 1 ms after reset before transmitting
  delay(5);
 
  // this lets us read the state of the SMC ERR pin (optional)
  pinMode(errPin, INPUT);
 
  smcSerial->write(0xAA);  // send baud-indicator byte

  // clear the safe-start violation and let the motor run
  exitSafeStart();
}

// read a serial byte (returns -1 if nothing received after the timeout expires)
int SimpleMotorControler::readByte()
{
  char c;
  if(smcSerial->readBytes(&c, 1) == 0)
  { 
	return -1; 
  }
  return (byte)c;
}
 
// required to allow motors to move
// must be called when controller restarts and after any error
void SimpleMotorControler::exitSafeStart()
{
  smcSerial->write(0x83);
}
 
// speed should be a number from -3200 to 3200
void SimpleMotorControler::setMotorSpeed(int speed)
{
	#if (MOTOR_DEBUG_PRINTF == 1)
	Serial.print("setMotorSpeed to: ");
	Serial.println(speed);
	#endif
	
  if (speed < 0)
  {
    smcSerial->write(0x86);  // motor reverse command
    speed = -speed;  // make speed positive
  }
  else
  {
    smcSerial->write(0x85);  // motor forward command
  }
  smcSerial->write(speed & 0x1F);
  smcSerial->write(speed >> 5);
}
 
unsigned char SimpleMotorControler::setMotorLimit(unsigned char  limitID, unsigned int limitValue)
{
  smcSerial->write(0xA2);
  smcSerial->write(limitID);
  smcSerial->write(limitValue & 0x7F);
  smcSerial->write(limitValue >> 7);
  return readByte();
}
 
unsigned int SimpleMotorControler::getVariable(unsigned char variableID)
{
  smcSerial->write(0xA1);
  smcSerial->write(variableID);
  return readByte() + 256 * readByte();
}

bool SimpleMotorControler::IsInError()
{
	if(digitalRead(errPin) == HIGH)
	{
		#if (MOTOR_DEBUG_PRINTF == 1)
		Serial.print("Error Status: 0x");
		Serial.println(getVariable(ERROR_STATUS), HEX);
		#endif
		// once all other errors have been fixed,
		// this lets the motors run again
		exitSafeStart();
		return true;
	}
	return false;
}
 