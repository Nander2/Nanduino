#ifndef SIMPLEMOTORCONTROLER_H
#define SIMPLEMOTORCONTROLER_H

#include <SoftwareSerial.h>

// some variable IDs
#define ERROR_STATUS 0
#define LIMIT_STATUS 3
#define TARGET_SPEED 20
#define CURRENT_SPEED 21
#define INPUT_VOLTAGE 23
#define TEMPERATURE 24
 
// some motor limit IDs
#define FORWARD_ACCELERATION 5
#define REVERSE_ACCELERATION 9
#define DECELERATION 2

class SimpleMotorControler
{
	private:
		int readByte();
		SoftwareSerial *smcSerial;
	public:
		SimpleMotorControler();
		void begin();
		void exitSafeStart();
		void setMotorSpeed(int speed);
		unsigned char setMotorLimit(unsigned char  limitID, unsigned int limitValue);
		unsigned int getVariable(unsigned char variableID);
		bool IsInError();
};
#endif