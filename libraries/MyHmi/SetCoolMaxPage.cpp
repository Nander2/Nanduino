#include "SetCoolMaxPage.h"
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

SetCoolMaxPage::SetCoolMaxPage()
{
	EnterBlkValue = configuration.CoolMax;
	EnterMillisValue = millis();
}

void SetCoolMaxPage::Enter()
{
}

void SetCoolMaxPage::Refresh()
{
	byte LastBlkPwmValue = configuration.CoolMax;
  
	// set the cursor to column 0, line 0
	lcd.setCursor(0, 0);
	lcd.print("Puissance Froid");

	lcd.setCursor(9, 1);

	if(configuration.CoolMax < 100)
	lcd.print("0");
	if(configuration.CoolMax < 10)
	lcd.print("0");

	lcd.print(configuration.CoolMax);
	
	if((millis() - EnterMillisValue) >= PageDuration)
	{
		configuration.CoolMax = this->EnterBlkValue;
		Navigation.ShowPage(HmiNavigation::eMainPage);
	}
}

void SetCoolMaxPage::Exit()
{
	lcd.clear();
}

void SetCoolMaxPage::ProcessEvent(HmiNavigation::KeyBoardEventList event)
{
	if((event == HmiNavigation::eKbShortUp || event == HmiNavigation::eKbRepeatUp)&& configuration.CoolMax < 100)
	{
		configuration.CoolMax++;
		this->EnterMillisValue = millis();
	}
	else if((event == HmiNavigation::eKbShortDown || event == HmiNavigation::eKbRepeatDown) && configuration.CoolMax > 0)
	{
		configuration.CoolMax--;
		this->EnterMillisValue = millis();
	}

	if(event == HmiNavigation::eKbShortEnter)
	{
		EEPROM_writeAnything(0, configuration);
		Navigation.ShowPage(HmiNavigation::eMainPage);
	}
}
