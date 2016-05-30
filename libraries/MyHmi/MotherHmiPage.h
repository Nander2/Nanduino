#ifndef MOTHER_HMI_PAGE_h
#define MOTHER_HMI_PAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif
#include <HmiNavigation.h>

class MotherHmiPage
{
	public:
		virtual void Enter() = 0;
		virtual void Refresh() = 0;
		virtual void Exit() = 0;
		virtual void ProcessEvent(HmiNavigation::KeyBoardEventList event){}
};

#endif