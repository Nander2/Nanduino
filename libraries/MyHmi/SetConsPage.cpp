#include "SetConsPage.h"
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

SetConsPage::SetConsPage()
{
	if(configuration.TempConsigne == NAN)
		configuration.TempConsigne = 16.0;

	EnterConsValue = configuration.TempConsigne;
	EnterMillisValue = millis();
}

int SetConsPage::GetPageId()
{
	return HmiNavigation::eSetConsPage;
}

void SetConsPage::Enter()
{
}

void SetConsPage::Refresh()
{
	// set the cursor to column 0, line 0
	lcd.setCursor(0, 0);
	lcd.print("Consigne temperature");

	lcd.setCursor(9, 1);

	double ConsValue = (double)(configuration.TempConsigne)/10.;

	if(ConsValue < 10)
	lcd.print("0");

	lcd.print(ConsValue);
	
	if((millis() - EnterMillisValue) >= PageDuration)
	{
		configuration.TempConsigne = EnterConsValue;
		Navigation.ShowPage(HmiNavigation::eMainPage);
	}
}

void SetConsPage::Exit()
{
	lcd.clear();
}

void SetConsPage::ProcessEvent(HmiNavigation::KeyBoardEventList event)
{
	if((event == HmiNavigation::eKbShortUp || event == HmiNavigation::eKbRepeatUp) && configuration.TempConsigne < 250)
	{
		configuration.TempConsigne+=5;
		this->EnterMillisValue = millis();
	}
	else if((event == HmiNavigation::eKbShortDown || event == HmiNavigation::eKbRepeatDown) && configuration.TempConsigne > 0)
	{
		configuration.TempConsigne-=5;
		this->EnterMillisValue = millis();
	}

	if(event == HmiNavigation::eKbShortEnter)
	{
		EEPROM_writeAnything(0, configuration);
		Navigation.ShowPage(HmiNavigation::eMainPage);
	}
}
