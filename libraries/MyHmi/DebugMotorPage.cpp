#include "DebugMotorPage.h"
#include "HmiNavigation.h"
#include "Configuration.h"
#include <LiquidCrystal.h>
#include <Button.h>
#include <EEPROM.h>
#include <EEPROMAnything.h>
#include "Regulation.h"

#define PageDuration	60000	//1 minute

extern LiquidCrystal lcd;
extern Button UpBtn;
extern Button EnterBtn;
extern Button DownBtn;
extern config_t configuration;

DebugMotorPage::DebugMotorPage()
{
	EnterMillisValue = millis();
}

void DebugMotorPage::Enter()
{
	ShownMenu = 0;
	hasChanged = true;
}

void DebugMotorPage::Refresh()
{
	if(hasChanged)
	{
		EnterMillisValue = millis();
		switch(ShownMenu)
		{
			default:
			case 0:
			{
				lcd.setCursor(0, 0);
				lcd.print("PID");
				lcd.setCursor(0, 1);
				double kp,ki,kd;
				Regul.getPidConfig(kp,ki,kd);
				lcd.print(kp);
				lcd.print(" ");
				lcd.print(ki);
				lcd.print(" ");
				lcd.print(kd);
			}break;
			case 1:
			{
				lcd.setCursor(0, 0);
				lcd.print("Error Status");
				int returnValue = Regul.getVariable(0);
				lcd.setCursor(0, 1);
				if (returnValue == -257)
				{
					lcd.print("unknown");
				}
				else if ((returnValue & 0x1) == 0x1)
				{
					lcd.print("Safe Start Violation");
				}
				else if	((returnValue & 0x002) == 0x002)
				{
					lcd.print("Req Chan Inv");
				}
				else if	((returnValue & 0x004) == 0x004)
				{
					lcd.print("Serial Error");
				}
				else if	((returnValue & 0x008) == 0x008)
				{
					lcd.print("Command Timeout");
				}
				else if	((returnValue & 0x010) == 0x010)
				{
					lcd.print("Limit/Kill Switch");
				}
				else if	((returnValue & 0x020) == 0x020)
				{
					lcd.print("Low VIN");
				}
				else if	((returnValue & 0x040) == 0x040)
				{
					lcd.print("High VIN");
				}
				else if	((returnValue & 0x080) == 0x080)
				{
					lcd.print("Over Temperature");
				}
				else if	((returnValue & 0x100) == 0x100)
				{
					lcd.print("Motor Driver Error");
				}
				else
				{
					lcd.print("No error");
				}
			}break;
			case 2:
			{
				lcd.setCursor(0, 0);
				lcd.print("Serial Error");
				int returnValue = Regul.getVariable(2);
				lcd.setCursor(0, 1);
				if (returnValue == -257)
				{
					lcd.print("unknown");
				}
				else if ((returnValue & 0x1) == 0x1)
				{
					lcd.print("OK");
				}
				else if	((returnValue & 0x002) == 0x002)
				{
					lcd.print("Frame");
				}
				else if	((returnValue & 0x004) == 0x004)
				{
					lcd.print("Noise");
				}
				else if	((returnValue & 0x008) == 0x008)
				{
					lcd.print("RX Overrun");
				}
				else if	((returnValue & 0x010) == 0x010)
				{
					lcd.print("Format");
				}
				else if	((returnValue & 0x020) == 0x020)
				{
					lcd.print("CRC");
				}
			}break;
			case 3:
			{
				lcd.setCursor(0, 0);
				lcd.print("Target Speed");
				int returnValue = Regul.getVariable(20);
				lcd.setCursor(9, 1);
				lcd.print(returnValue);
			}break;
			case 4:
			{
				lcd.setCursor(0, 0);
				lcd.print("Current Speed");
				int returnValue = Regul.getVariable(20);
				lcd.setCursor(9, 1);
				lcd.print(returnValue);
			}break;
			case 5:
			{
				lcd.setCursor(0, 0);
				lcd.print("Brake Amount");
				int returnValue = Regul.getVariable(22);
				lcd.setCursor(9, 1);
				lcd.print(returnValue);
			}break;
			case 6:
			{
				lcd.setCursor(0, 0);
				lcd.print("Input Voltage");
				int returnValue = Regul.getVariable(23);
				lcd.setCursor(9, 1);
				lcd.print(returnValue);
			}break;
			case 7:
			{
				lcd.setCursor(0, 0);
				lcd.print("Temperature");
				int returnValue = Regul.getVariable(24);
				lcd.setCursor(9, 1);
				lcd.print(returnValue);
			}break;
			case 8:
			{
				lcd.setCursor(0, 0);
				lcd.print("Baud Rate");
				int returnValue = Regul.getVariable(27);
				lcd.setCursor(9, 1);
				lcd.print(72000000/returnValue);
			}break;
		}
		hasChanged = false;
	}
	
	// if((millis() - EnterMillisValue) >= PageDuration)
	// {
		// Navigation.ShowPage(HmiNavigation::eMainPage);
	// }
}

void DebugMotorPage::Exit()
{
	lcd.clear();
}

void DebugMotorPage::ProcessEvent(HmiNavigation::KeyBoardEventList event)
{
	if((event == HmiNavigation::eKbShortUp || event == HmiNavigation::eKbRepeatUp))
	{
		ShownMenu--;
		if(ShownMenu < 0)
			ShownMenu = 8;
		hasChanged = true;
		lcd.clear();
	}
	else if((event == HmiNavigation::eKbShortDown || event == HmiNavigation::eKbRepeatDown))
	{
		ShownMenu++;
		if(ShownMenu > 8)
			ShownMenu = 0;
		hasChanged = true;
		lcd.clear();
	}

	if(event == HmiNavigation::eKbShortEnter)
	{
		Navigation.ShowPage(HmiNavigation::eMainPage);
	}
}
