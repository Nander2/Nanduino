#include "SetDeltaTempPage.h"
#include "HmiNavigation.h"
#include "Configuration.h"
#include <LiquidCrystal.h>
#include <Button.h>
#include <EEPROM.h>
#include <EEPROMAnything.h>

#define PageDuration	60000	//1 minute

extern LiquidCrystal lcd;
extern Button UpBtn;
extern Button EnterBtn;
extern Button DownBtn;
extern config_t configuration;

SetDeltaTempPage::SetDeltaTempPage()
{
	EnterBlkValue = configuration.DeltatTemp;
	EnterMillisValue = millis();
}

void SetDeltaTempPage::Enter()
{
}

void SetDeltaTempPage::Refresh()
{
	byte LastBlkPwmValue = configuration.DeltatTemp;
  
	// set the cursor to column 0, line 0
	lcd.setCursor(0, 0);
	lcd.print("Diff de temperature");

	lcd.setCursor(9, 1);

	lcd.print(((double)configuration.DeltatTemp)/10.);
	
	if((millis() - EnterMillisValue) >= PageDuration)
	{
		configuration.DeltatTemp = this->EnterBlkValue;
		Navigation.ShowPage(HmiNavigation::eMainPage);
	}
}

void SetDeltaTempPage::Exit()
{
	lcd.clear();
}

void SetDeltaTempPage::ProcessEvent(HmiNavigation::KeyBoardEventList event)
{
	if((event == HmiNavigation::eKbShortUp || event == HmiNavigation::eKbRepeatUp)&& configuration.DeltatTemp < 100.)
	{
		configuration.DeltatTemp++;
		this->EnterMillisValue = millis();
	}
	else if((event == HmiNavigation::eKbShortDown || event == HmiNavigation::eKbRepeatDown) && configuration.DeltatTemp > 0.)
	{
		configuration.DeltatTemp--;
		this->EnterMillisValue = millis();
	}

	if(event == HmiNavigation::eKbShortEnter)
	{
		EEPROM_writeAnything(0, configuration);
		Navigation.ShowPage(HmiNavigation::eMainPage);
	}
}
