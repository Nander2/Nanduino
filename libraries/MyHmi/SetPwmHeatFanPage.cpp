#include "SetPwmHeatFanPage.h"
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

SetPwmHeatFanPage::SetPwmHeatFanPage()
{
	EnterBlkValue = configuration.pwmHeatFan;
	EnterMillisValue = millis();
}

void SetPwmHeatFanPage::Enter()
{
}

void SetPwmHeatFanPage::Refresh()
{
	byte LastBlkPwmValue = configuration.pwmHeatFan;
  
	// set the cursor to column 0, line 0
	lcd.setCursor(0, 0);
	lcd.print("Vitesse Vent. Chaud");

	lcd.setCursor(9, 1);

	if(configuration.pwmHeatFan < 100)
	lcd.print("0");
	if(configuration.pwmHeatFan < 10)
	lcd.print("0");

	lcd.print(configuration.pwmHeatFan);
	
	if((millis() - EnterMillisValue) >= PageDuration)
	{
		configuration.pwmHeatFan = this->EnterBlkValue;
		analogWrite(HeatFanPwmPin,map(configuration.pwmHeatFan,100,0,0,255));
		Navigation.ShowPage(HmiNavigation::eMainPage);
	}
}

void SetPwmHeatFanPage::Exit()
{
	lcd.clear();
}

void SetPwmHeatFanPage::ProcessEvent(HmiNavigation::KeyBoardEventList event)
{
	if((event == HmiNavigation::eKbShortUp || event == HmiNavigation::eKbRepeatUp)&& configuration.pwmHeatFan < 100)
	{
		configuration.pwmHeatFan++;
		analogWrite(HeatFanPwmPin,map(configuration.pwmHeatFan,100,0,0,255));
		this->EnterMillisValue = millis();
	}
	else if((event == HmiNavigation::eKbShortDown || event == HmiNavigation::eKbRepeatDown) && configuration.pwmHeatFan > 0)
	{
		configuration.pwmHeatFan--;
		analogWrite(HeatFanPwmPin,map(configuration.pwmHeatFan,100,0,0,255));
		this->EnterMillisValue = millis();
	}

	if(event == HmiNavigation::eKbShortEnter)
	{
		EEPROM_writeAnything(0, configuration);
		Navigation.ShowPage(HmiNavigation::eMainPage);
	}
}
