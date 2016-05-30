#ifndef SETBLKPAGE_h
#define SETBLKPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include "MotherHmiPage.h"

class SetBlkPage : public MotherHmiPage
{
	public:
		SetBlkPage();
		void Enter();
		void Refresh();
		void Exit();
		void ProcessEvent(HmiNavigation::KeyBoardEventList event);
		
	private:
		long EnterMillisValue;
		byte EnterBlkValue;
};
#endif