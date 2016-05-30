#ifndef SETCONSPAGE_h
#define SETCONSPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include "MotherHmiPage.h"

class SetConsPage : public MotherHmiPage
{
	public:
		SetConsPage();
		int GetPageId();
		void Enter();
		void Refresh();
		void Exit();
		void ProcessEvent(HmiNavigation::KeyBoardEventList event);
		
	private:
		long EnterMillisValue;
		int EnterConsValue;
};
#endif