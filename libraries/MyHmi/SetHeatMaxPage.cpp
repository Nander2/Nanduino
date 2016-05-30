#include "SetHeatMaxPage.h"
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

SetHeatMaxPage::SetHeatMaxPage()
{
	EnterBlkValue = configuration.HeatMax;
	EnterMillisValue = millis();
}

void SetHeatMaxPage::Enter()
{
}

void SetHeatMaxPage::Refresh()
{
	byte LastBlkPwmValue = configuration.HeatMax;
  
	// set the cursor to column 0, line 0
	lcd.setCursor(0, 0);
	lcd.print("Puissance chaud");

	lcd.setCursor(9, 1);

	if(configuration.HeatMax < 100)
	lcd.print("0");
	if(configuration.HeatMax < 10)
	lcd.print("0");

	lcd.print(configuration.HeatMax);
	
	if((millis() - EnterMillisValue) >= PageDuration)
	{
		configuration.HeatMax = this->EnterBlkValue;
		Navigation.ShowPage(HmiNavigation::eMainPage);
	}
}

void SetHeatMaxPage::Exit()
{
	lcd.clear();
}

void SetHeatMaxPage::ProcessEvent(HmiNavigation::KeyBoardEventList event)
{
	if((event == HmiNavigation::eKbShortUp || event == HmiNavigation::eKbRepeatUp)&& configuration.HeatMax < 100)
	{
		configuration.HeatMax++;
		this->EnterMillisValue = millis();
	}
	else if((event == HmiNavigation::eKbShortDown || event == HmiNavigation::eKbRepeatDown) && configuration.HeatMax > 0)
	{
		configuration.HeatMax--;
		this->EnterMillisValue = millis();
	}

	if(event == HmiNavigation::eKbShortEnter)
	{
		EEPROM_writeAnything(0, configuration);
		Navigation.ShowPage(HmiNavigation::eMainPage);
	}
}
