#include "MainPage.h"
#include "HmiNavigation.h"
#include "Configuration.h"
#include "Regulation.h"
#include <LiquidCrystal.h>
#include <Adafruit_AM2315.h>
#include <LM35.h>
#include <DS3232RTC.h>
#include <Button.h>

extern LiquidCrystal lcd;
extern Adafruit_AM2315 am2315;
extern LM35 AmbientTemp;
extern Button EnterBtn;
extern config_t configuration;

byte Degree[8] = 
{
  B01110,
  B10001,
  B10001,
  B10001,
  B01110,
  B00000,
  B00000,
  B00000,
};

byte RisingSign[8] = 
{
  B00000,
  B01111,
  B00011,
  B00101,
  B01001,
  B10000,
  B00000,
  B00000,
};

byte SteadySign[8] = 
{
  B00000,
  B00000,
  B01101,
  B10010,
  B01101,
  B10010,
  B00000,
  B00000,
};

byte FallingSign[8] = 
{
  B00000,
  B00000,
  B10000,
  B01001,
  B00101,
  B00011,
  B01111,
  B00000,
};

byte ConsSign[8] = 
{
  B00000,
  B00000,
  B00100,
  B00010,
  B11111,
  B00010,
  B00100,
  B00000,
};

MainPage::MainPage()
{
	lcd.createChar(0, Degree);
	lcd.createChar(1, RisingSign);
	lcd.createChar(2, SteadySign);
	lcd.createChar(3, FallingSign);
	lcd.createChar(4, ConsSign);
	
}

void MainPage::Enter()
{
}

void MainPage::Refresh()
{
	if (timeStatus() != timeSet)
	{
		lcd.setCursor(4, 0);
		lcd.print("Time Not Set");
	}
	else
	{
		t = now();
		if (t != tLast) 
		{
			lcd.setCursor(2, 0);
			
			tLast = t;
			int CurrDay = day(t);
			
			if(CurrDay < 10)
				lcd.print("0");
			lcd.print(CurrDay);
			lcd.print("/");
			if(month(t) < 10)
				lcd.print("0");
			lcd.print(month(t));
			lcd.print("/");
			lcd.print(year(t));
			
			lcd.print(" ");
			
			int CurrHour = hour(t);
			int CurrMinute = minute(t);
			
			if(CurrHour < 10)
				lcd.print("0");
			lcd.print(CurrHour);
			lcd.print(":");
			
			if(CurrMinute < 10)
				lcd.print("0");
			lcd.print(CurrMinute);
			
			bool rising, falling;
			int RegulValue = -Regul.getOutput();
			Regul.getTempTendency(rising, falling);
			
			lcd.setCursor(0, 1);
			
			if(RegulValue > 0)
				lcd.print(" ");
			
			if(abs(RegulValue) < 1000)
				lcd.print(" ");
			
			if(abs(RegulValue) < 100)
				lcd.print(" ");
			
			if(abs(RegulValue) < 10)
				lcd.print(" ");
			
			lcd.print(RegulValue);
			
			lcd.setCursor(7, 1);
			
			double CurTemp = am2315.readTemperature();
			if(!isnan(CurTemp))
			{
				if(CurTemp < 10)
					lcd.print("0");
				lcd.print(CurTemp);
			}
			
			lcd.setCursor(13, 1);
			
			if(Regul.IsTunning())
				lcd.print("T");
			else if(rising)
				lcd.write(byte(1));
			else if(falling)
				lcd.write(byte(3));
			else
				lcd.write(byte(2));
			
			lcd.setCursor(15, 1);
			
			double tempconsigne = (double)(configuration.TempConsigne) / 10.;
			if(tempconsigne < 10)
				lcd.print("0");
			lcd.print(tempconsigne); 
		}
	}
}

void MainPage::Exit()
{
	lcd.clear();
}

void MainPage::ProcessEvent(HmiNavigation::KeyBoardEventList event)
{
	if(event == HmiNavigation::eKbShortEnter)
		Navigation.ShowPage(HmiNavigation::eMainMenuPage);
}
