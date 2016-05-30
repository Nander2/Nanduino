#include <KeyBoard.h>
#include <HmiNavigation.h>

#define KEYBOARD_DEBUG_PRINTF  0

#define ShortPressDuration		3
#define LongPressDuration		25
#define LongPressRepeatDelay	25
#define LongPressRepeatDuration	10

Button UpBtn = Button(52,PULLDOWN);
Button EnterBtn = Button(53,PULLDOWN);
Button DownBtn = Button(51,PULLDOWN);
KeyBoard Clavier;

KeyBoard::KeyBoard()
{
	UpBtnCpt = 0;
	EnterBtnCpt = 0;
	DownBtnCpt = 0;
}

void KeyBoard::Compute()
{
	//btn Up
	if(UpBtn.isPressed())
	{
		UpBtnCpt++;
		
		//Si on a depasser le cpt long press + repeat
		if(UpBtnCpt >= (LongPressDuration + LongPressRepeatDelay))
		{
			long RepeatCpt = UpBtnCpt - (LongPressDuration + LongPressRepeatDelay);
			if((RepeatCpt % LongPressRepeatDuration) == 0)
			{
				//on genere un evenement short press up
				#if (KEYBOARD_DEBUG_PRINTF == 1)
				Serial.println("Up ShortPress (repeat)");
				#endif
				Navigation.SendEvent(HmiNavigation::eKbRepeatUp);
			}
		}
	}
	else
	{
		if((UpBtnCpt >= ShortPressDuration) && (UpBtnCpt < LongPressDuration))
		{
			//on genere un evenement short press up
			#if (KEYBOARD_DEBUG_PRINTF == 1)
			Serial.println("Up ShortPress");
			#endif
			Navigation.SendEvent(HmiNavigation::eKbShortUp);
		}
		else if((UpBtnCpt >= LongPressDuration) && (UpBtnCpt < LongPressDuration + LongPressRepeatDelay))
		{
			//on genere un evenement long press up
			#if (KEYBOARD_DEBUG_PRINTF == 1)
			Serial.println("Up LongPress");
			#endif
			Navigation.SendEvent(HmiNavigation::eKbLongUp);
		}
		UpBtnCpt = 0;
	}
	
	//btn Enter
	if(EnterBtn.isPressed())
	{
		EnterBtnCpt++;
		
		//Si on a depasser le cpt long press + repeat
		if(EnterBtnCpt >= (LongPressDuration + LongPressRepeatDelay))
		{
			long RepeatCpt = EnterBtnCpt - (LongPressDuration + LongPressRepeatDelay);
			if((RepeatCpt % LongPressRepeatDuration) == 0)
			{
				//on genere un evenement short press enter
				#if (KEYBOARD_DEBUG_PRINTF == 1)
				Serial.println("Enter ShortPress (repeat)");
				#endif
				Navigation.SendEvent(HmiNavigation::eKbRepeatEnter);
			}
		}
	}
	else
	{
		if((EnterBtnCpt >= ShortPressDuration) && (EnterBtnCpt < LongPressDuration))
		{
			//on genere un evenement short press enter
			#if (KEYBOARD_DEBUG_PRINTF == 1)
			Serial.println("Enter ShortPress");
			#endif
			Navigation.SendEvent(HmiNavigation::eKbShortEnter);
		}
		else if((EnterBtnCpt >= LongPressDuration) && (EnterBtnCpt < LongPressDuration + LongPressRepeatDelay))
		{
			//on genere un evenement long press enter
			#if (KEYBOARD_DEBUG_PRINTF == 1)
			Serial.println("Enter LongPress");
			#endif
			Navigation.SendEvent(HmiNavigation::eKbLongEnter);
		}
		EnterBtnCpt = 0;
	}
	
	//btn Down
	if(DownBtn.isPressed())
	{
		DownBtnCpt++;
		
		//Si on a depasser le cpt long press + repeat
		if(DownBtnCpt >= (LongPressDuration + LongPressRepeatDelay))
		{
			long RepeatCpt = DownBtnCpt - (LongPressDuration + LongPressRepeatDelay);
			if((RepeatCpt % LongPressRepeatDuration) == 0)
			{
				//on genere un evenement short press down
				#if (KEYBOARD_DEBUG_PRINTF == 1)
				Serial.println("Down ShortPress (repeat)");
				#endif
				Navigation.SendEvent(HmiNavigation::eKbRepeatDown);
			}
		}
	}
	else
	{
		if((DownBtnCpt >= ShortPressDuration) && (DownBtnCpt < LongPressDuration))
		{
			//on genere un evenement short press down
			#if (KEYBOARD_DEBUG_PRINTF == 1)
			Serial.println("Down ShortPress");
			#endif
			Navigation.SendEvent(HmiNavigation::eKbShortDown);
		}
		else if((DownBtnCpt >= LongPressDuration) && (DownBtnCpt < LongPressDuration + LongPressRepeatDelay))
		{
			//on genere un evenement long press down
			#if (KEYBOARD_DEBUG_PRINTF == 1)
			Serial.println("Down LongPress");
			#endif
			Navigation.SendEvent(HmiNavigation::eKbLongDown);
		}
		DownBtnCpt = 0;
	}
	
}