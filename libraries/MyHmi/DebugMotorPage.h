#ifndef DEBUGMOTORPAGE_h
#define DEBUGMOTORPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include "MotherHmiPage.h"

class DebugMotorPage : public MotherHmiPage
{
	public:
		DebugMotorPage();
		void Enter();
		void Refresh();
		void Exit();
		void ProcessEvent(HmiNavigation::KeyBoardEventList event);
		
	private:
		byte spare0;
		byte spare1;
		int ShownMenu;
		long EnterMillisValue;
		bool hasChanged;
};
#endif