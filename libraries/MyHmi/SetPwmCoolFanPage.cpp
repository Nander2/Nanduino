#include "SetPwmCoolFanPage.h"
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

SetPwmCoolFanPage::SetPwmCoolFanPage()
{
	EnterBlkValue = configuration.PwmCoolFan;
	EnterMillisValue = millis();
}

void SetPwmCoolFanPage::Enter()
{
}

void SetPwmCoolFanPage::Refresh()
{
	// set the cursor to column 0, line 0
	lcd.setCursor(0, 0);
	lcd.print("Vitesse Vent. Froid");

	lcd.setCursor(9, 1);

	if(configuration.PwmCoolFan < 100)
	lcd.print("0");
	if(configuration.PwmCoolFan < 10)
	lcd.print("0");

	lcd.print(configuration.PwmCoolFan);
	
	if((millis() - EnterMillisValue) >= PageDuration)
	{
		configuration.PwmCoolFan = this->EnterBlkValue;
		analogWrite(CoolFanPwmPin,map(configuration.PwmCoolFan,100,0,0,255));
		Navigation.ShowPage(HmiNavigation::eMainPage);
	}
}

void SetPwmCoolFanPage::Exit()
{
	lcd.clear();
}

void SetPwmCoolFanPage::ProcessEvent(HmiNavigation::KeyBoardEventList event)
{
	if((event == HmiNavigation::eKbShortUp || event == HmiNavigation::eKbRepeatUp)&& configuration.PwmCoolFan < 100)
	{
		configuration.PwmCoolFan++;
		analogWrite(CoolFanPwmPin,map(configuration.PwmCoolFan,100,0,0,255));
		this->EnterMillisValue = millis();
	}
	else if((event == HmiNavigation::eKbShortDown || event == HmiNavigation::eKbRepeatDown) && configuration.PwmCoolFan > 0)
	{
		configuration.PwmCoolFan--;
		analogWrite(CoolFanPwmPin,map(configuration.PwmCoolFan,100,0,0,255));
		this->EnterMillisValue = millis();
	}

	if(event == HmiNavigation::eKbShortEnter)
	{
		EEPROM_writeAnything(0, configuration);
		Navigation.ShowPage(HmiNavigation::eMainPage);
	}
}
