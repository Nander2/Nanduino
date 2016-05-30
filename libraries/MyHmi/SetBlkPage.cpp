#include "SetBlkPage.h"
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

SetBlkPage::SetBlkPage()
{
	EnterBlkValue = configuration.BlkPwmValue;
	EnterMillisValue = millis();
}

void SetBlkPage::Enter()
{
}

void SetBlkPage::Refresh()
{
	byte LastBlkPwmValue = configuration.BlkPwmValue;
  
	// set the cursor to column 0, line 0
	lcd.setCursor(0, 0);
	lcd.print("Luminosite Backlight");

	lcd.setCursor(9, 1);

	if(configuration.BlkPwmValue < 100)
	lcd.print("0");
	if(configuration.BlkPwmValue < 10)
	lcd.print("0");

	lcd.print(configuration.BlkPwmValue);
	
	if((millis() - EnterMillisValue) >= PageDuration)
	{
		configuration.BlkPwmValue = this->EnterBlkValue;
		analogWrite(BlkPwmPin,map(configuration.BlkPwmValue,100,0,0,255));
		Navigation.ShowPage(HmiNavigation::eMainPage);
	}
}

void SetBlkPage::Exit()
{
	lcd.clear();
}

void SetBlkPage::ProcessEvent(HmiNavigation::KeyBoardEventList event)
{
	if((event == HmiNavigation::eKbShortUp || event == HmiNavigation::eKbRepeatUp)&& configuration.BlkPwmValue < 100)
	{
		configuration.BlkPwmValue++;
		analogWrite(BlkPwmPin,map(configuration.BlkPwmValue,100,0,0,255));
		this->EnterMillisValue = millis();
	}
	else if((event == HmiNavigation::eKbShortDown || event == HmiNavigation::eKbRepeatDown) && configuration.BlkPwmValue > 0)
	{
		configuration.BlkPwmValue--;
		analogWrite(BlkPwmPin,map(configuration.BlkPwmValue,100,0,0,255));
		this->EnterMillisValue = millis();
	}

	if(event == HmiNavigation::eKbShortEnter)
	{
		EEPROM_writeAnything(0, configuration);
		Navigation.ShowPage(HmiNavigation::eMainPage);
	}
}
