#ifndef SETCOOLPWMPAGE_h
#define SETCOOLPWMPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include "MotherHmiPage.h"

class SetPwmCoolFanPage : public MotherHmiPage
{
	public:
		SetPwmCoolFanPage();
		void Enter();
		void Refresh();
		void Exit();
		void ProcessEvent(HmiNavigation::KeyBoardEventList event);
		
	private:
		long EnterMillisValue;
		byte EnterBlkValue;
};
#endif