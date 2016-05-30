#ifndef HMI_NAVIGATION_h
#define HMI_NAVIGATION_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

class MotherHmiPage;

class HmiNavigation
{
	public:
		typedef enum
		{
			eStartUpPage = 0,
			eMainPage,
			eMainMenuPage,
			eSetDateHeurePage,
			eSetBlkPage,
			eSetConsPage,
			eSetDeltatTempPage,
			eSetPwmCoolFanPage,
			eSetPwmHeatFanPage,
			eSetHeatMaxPage,
			eSetCoolMaxPage,
			eDebugPage,
			eLastPageId, //must stay the last
		}PageIdList;
		
		typedef enum
		{
			eKbShortUp = 0,
			eKbLongUp,
			eKbRepeatUp,
			eKbShortEnter,
			eKbLongEnter,
			eKbRepeatEnter,
			eKbShortDown,
			eKbLongDown,
			eKbRepeatDown,
		}KeyBoardEventList;
		
		HmiNavigation();
		void ShowPage(int PageId);
		void Run();
		void SendEvent(KeyBoardEventList event);
	
	protected:
		MotherHmiPage * Current_Page;
	
};

extern HmiNavigation Navigation;
#endif