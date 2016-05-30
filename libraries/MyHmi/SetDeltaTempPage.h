#ifndef SETDELTATEMPPAGE_h
#define SETDELTATEMPPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include "MotherHmiPage.h"

class SetDeltaTempPage : public MotherHmiPage
{
	public:
		SetDeltaTempPage();
		void Enter();
		void Refresh();
		void Exit();
		void ProcessEvent(HmiNavigation::KeyBoardEventList event);
		
	private:
		long EnterMillisValue;
		byte EnterBlkValue;
};
#endif