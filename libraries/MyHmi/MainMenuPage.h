#ifndef MAINMENUPAGE_h
#define MAINMENUPAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include "MotherHmiPage.h"

class MainMenuPage : public MotherHmiPage
{
	public:
		MainMenuPage();
		void Enter();
		void Refresh();
		void Exit();
		void ProcessEvent(HmiNavigation::KeyBoardEventList event);
		
	private:
		int FirstShownMenuLine;
		int SelectionCursorLine;
		long EnterMillisValue;
};
#endif