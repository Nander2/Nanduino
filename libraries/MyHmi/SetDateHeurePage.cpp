#include "SetDateHeurePage.h"
#include "HmiNavigation.h"
#include <LiquidCrystal.h>
#include <DS3232RTC.h>

#define DheDay		2
#define DheMonth	1
#define DheYear		0
#define DheHour		3
#define DheMinute	4
#define DheLast		5

extern LiquidCrystal lcd;

SetDateHeurePage::SetDateHeurePage()
{
	CurrentSettedElement = DheYear;
}

void SetDateHeurePage::Enter()
{
	TimeEntry = now();
}

void SetDateHeurePage::Refresh()
{
	lcd.setCursor(4, 0);
	
	int CurrDay = day(TimeEntry);
	
	if(CurrDay < 10)
		lcd.print("0");
	lcd.print(CurrDay);
	lcd.print(" ");
	lcd.print(monthShortStr(month(TimeEntry)));
	lcd.print(" ");
	lcd.print(year(TimeEntry));
	
	lcd.setCursor(7, 1);
	
	int CurrHour = hour(TimeEntry);
	int CurrMinute = minute(TimeEntry);
	
	if(CurrHour < 10)
		lcd.print("0");
	lcd.print(CurrHour);
	lcd.print(":");
	
	if(CurrMinute < 10)
		lcd.print("0");
	lcd.print(CurrMinute);
	
	switch(CurrentSettedElement)
	{
		case DheDay:
		{
			lcd.setCursor(3, 0);
			lcd.print(">");
			lcd.setCursor(6, 0);
			lcd.print("<");			
		}break;
		case DheMonth:
		{
			lcd.setCursor(6, 0);
			lcd.print(">");
			lcd.setCursor(10, 0);
			lcd.print("<");
		}break;
		case DheYear:
		{
			lcd.setCursor(10, 0);
			lcd.print(">");
			lcd.setCursor(15, 0);
			lcd.print("<");
		}break;
		case DheHour:
		{
			lcd.setCursor(6, 1);
			lcd.print(">");
			lcd.setCursor(9, 1);
			lcd.print("<");
		}break;
		case DheMinute:
		{
			lcd.setCursor(9, 1);
			lcd.print(">");
			lcd.setCursor(12, 1);
			lcd.print("<");
		}break;
	}

}

void SetDateHeurePage::Exit()
{
	lcd.clear();
}

void SetDateHeurePage::ProcessEvent(HmiNavigation::KeyBoardEventList event)
{
	tmElements_t tm;
	
	breakTime(TimeEntry,tm);
	
	switch(CurrentSettedElement)
	{
		case DheDay:
		{
			if(event == HmiNavigation::eKbShortUp || event == HmiNavigation::eKbRepeatUp)
				tm.Day++;
			else if(event == HmiNavigation::eKbShortDown || event == HmiNavigation::eKbRepeatDown)
				tm.Day--;
			
		}break;
		case DheMonth:
		{
			if(event == HmiNavigation::eKbShortUp || event == HmiNavigation::eKbRepeatUp)
				tm.Month++;
			else if(event == HmiNavigation::eKbShortDown || event == HmiNavigation::eKbRepeatDown)
				tm.Month--;
		}break;
		case DheYear:
		{
			if(event == HmiNavigation::eKbShortUp || event == HmiNavigation::eKbRepeatUp)
				tm.Year++;
			else if(event == HmiNavigation::eKbShortDown || event == HmiNavigation::eKbRepeatDown)
				tm.Year--;
		}break;
		case DheHour:
		{
			if(event == HmiNavigation::eKbShortUp || event == HmiNavigation::eKbRepeatUp)
				tm.Hour++;
			else if(event == HmiNavigation::eKbShortDown || event == HmiNavigation::eKbRepeatDown)
				tm.Hour--;
		}break;
		case DheMinute:
		{
			if(event == HmiNavigation::eKbShortUp || event == HmiNavigation::eKbRepeatUp)
				tm.Minute++;
			else if(event == HmiNavigation::eKbShortDown || event == HmiNavigation::eKbRepeatDown)
				tm.Minute--;
		}break;
	}
	
	TimeEntry = makeTime(tm);
	
	if(event == HmiNavigation::eKbShortEnter)
	{
		if(CurrentSettedElement < DheLast)
			CurrentSettedElement++;
		
		if(CurrentSettedElement == DheLast)
		{
			RTC.set(TimeEntry);
			setTime(TimeEntry);
			Navigation.ShowPage(HmiNavigation::eMainPage);
		}
		else 
		{
			lcd.clear();
		}
	}
}
