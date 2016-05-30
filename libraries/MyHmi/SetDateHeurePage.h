#ifndef SETDATEHEUREPAGE_h
#define SETDATEHEUREPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include "MotherHmiPage.h"
#include <Time.h>

class SetDateHeurePage : public MotherHmiPage
{
	public:
		SetDateHeurePage();
		void Enter();
		void Refresh();
		void Exit();
		void ProcessEvent(HmiNavigation::KeyBoardEventList event);
		
	private:
		time_t TimeEntry;
		short spare; //probleme d'alignement de donées???
		int CurrentSettedElement;
		
};
#endif