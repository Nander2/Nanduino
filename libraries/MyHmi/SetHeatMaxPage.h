#ifndef SETHEATMAXPAGE_h
#define SETHEATMAXPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include "MotherHmiPage.h"

class SetHeatMaxPage : public MotherHmiPage
{
	public:
		SetHeatMaxPage();
		void Enter();
		void Refresh();
		void Exit();
		void ProcessEvent(HmiNavigation::KeyBoardEventList event);
		
	private:
		long EnterMillisValue;
		byte EnterBlkValue;
};
#endif