#ifndef SETPWMHEATFANPAGE_h
#define SETPWMHEATFANPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include "MotherHmiPage.h"

class SetPwmHeatFanPage : public MotherHmiPage
{
	public:
		SetPwmHeatFanPage();
		void Enter();
		void Refresh();
		void Exit();
		void ProcessEvent(HmiNavigation::KeyBoardEventList event);
		
	private:
		long EnterMillisValue;
		byte EnterBlkValue;
};
#endif