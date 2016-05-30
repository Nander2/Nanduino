#include "StartUpPage.h"
#include "HmiNavigation.h"
#include <LiquidCrystal.h>

#define PageDuration	5000	//5 secondes

extern LiquidCrystal lcd;

StartUpPage::StartUpPage()
{
	lcd.setCursor(5, 0);
	lcd.print("HomeBrouw");
}

void StartUpPage::Enter()
{
	EnterMillisValue = millis();
}

void StartUpPage::Refresh()
{
	if((millis() - EnterMillisValue) >= PageDuration)
		Navigation.ShowPage(HmiNavigation::eMainPage);
}

void StartUpPage::Exit()
{
	
}
