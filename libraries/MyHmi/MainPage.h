#ifndef MAINPAGE_h
#define MAINPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include "MotherHmiPage.h"
#include <Time.h>

class MainPage : public MotherHmiPage
{
	public:
		MainPage();
		void Enter();
		void Refresh();
		void Exit();
		void ProcessEvent(HmiNavigation::KeyBoardEventList event);
	private:
		time_t t;
		time_t tLast;
};
#endif