#ifndef REGULATION_H
#define REGULATION_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include <SimpleMotorControler.h>
#include <PID.h>
#include <PID_AutoTune_v0.h>

class Regulation
{
	private:
		int &ExtSetPoint;
		double Kp, Ki, Kd;
		double IntSetPoint, Input, Output;
		double LastInput;
		bool TempIsRising;
		bool TempIsFalling;
		int AverageTabSize;
		int Compteur;
		
		double aTuneStep, aTuneNoise, aTuneStartValue;
		unsigned int aTuneLookBack;
		bool tuning;
		
		SimpleMotorControler *Mtc;
		PID *myPID;
		PID_ATune *aTune;
		
		long LastMillis;
		double LastOutput;
		
	public:
	
		Regulation(int &setPoint);
		void begin();
		void run();
		void tune(bool shallTune);
		double AverageInput();
		void getTempTendency(bool &Rise, bool &Fall);
		bool IsTunning();
		int getOutput();
		unsigned int getVariable(unsigned char variableID);
		void getPidConfig(double &Kpl, double &Kil, double &Kdl);
};

extern Regulation Regul;
#endif