#ifndef STARTUPPAGE_h
#define STARTUPPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include "MotherHmiPage.h"

class StartUpPage : public MotherHmiPage
{
	public:
		StartUpPage();
		void Enter();
		void Refresh();
		void Exit();
	private:
		long EnterMillisValue;
};
#endif