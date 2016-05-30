#include "MainMenuPage.h"
#include "HmiNavigation.h"
#include <LiquidCrystal.h>
#include <Button.h>
#include <Regulation.h>

#define PageDuration	60000	//1minute

extern LiquidCrystal lcd;

MainMenuPage::MainMenuPage()
{
	FirstShownMenuLine = 0;
	SelectionCursorLine = 0;
	EnterMillisValue = millis();
}

void MainMenuPage::Enter()
{
}

void MainMenuPage::Refresh()
{
	int CurrPrintedLcdLine = 0;
	int CurrPrintedMenuLine = FirstShownMenuLine;
	
	for(int NbLCDLine = 0; NbLCDLine < 2; NbLCDLine++)
	{
		switch(CurrPrintedMenuLine)
		{
			case 0:
			{
				lcd.setCursor(1, CurrPrintedLcdLine);
				lcd.print("Definir Date Heure");
			}break;
			case 1:
			{
				lcd.setCursor(1, CurrPrintedLcdLine);
				lcd.print("Definir Luminosite");
			}break;
			case 2:
			{
				lcd.setCursor(2, CurrPrintedLcdLine);
				lcd.print("Definir Consigne");
			}break;
			case 3://eSetDeltatTempPage,
			{
				lcd.setCursor(3, CurrPrintedLcdLine);
				lcd.print("Diff. Temperature");
			}break;
			case 4://eSetPwmCoolFanPage,
			{
				lcd.setCursor(3, CurrPrintedLcdLine);
				lcd.print("Vit. Vent. Chaud");
			}break;
			case 5://eSetPwmHeatFanPage,
			{
				lcd.setCursor(3, CurrPrintedLcdLine);
				lcd.print("Vit. Vent. Froid");
			}break;
			case 6://eSetHeatMaxPage,
			{
				lcd.setCursor(3, CurrPrintedLcdLine);
				lcd.print("Puissance Chaud");
			}break;
			case 7://eSetCoolMaxPage,
			{
				lcd.setCursor(3, CurrPrintedLcdLine);
				lcd.print("Puissance Froid");
			}break;
			case 8:
			{
				lcd.setCursor(3, CurrPrintedLcdLine);
				lcd.print("Debug Motor");
			}break;
			case 9:
			{
				lcd.setCursor(3, CurrPrintedLcdLine);
				if(!Regul.IsTunning())
					lcd.print("Start Tunning PID");
				else
					lcd.print("Stop Tunning PID");
			}break;
			case 10:
			{
				lcd.setCursor(3, CurrPrintedLcdLine);
				lcd.print("Sortir du Menu");
			}break;
		}
		CurrPrintedLcdLine++;
		CurrPrintedMenuLine++;
		if(CurrPrintedMenuLine > 10)
			CurrPrintedMenuLine = 0;
	}
	
	lcd.setCursor(0, SelectionCursorLine);
	lcd.print(">");
	lcd.setCursor(19, SelectionCursorLine);
	lcd.print("<");
	
	if((millis() - EnterMillisValue) >= PageDuration)
		Navigation.ShowPage(HmiNavigation::eMainPage);
}

void MainMenuPage::Exit()
{
	lcd.clear();
}

void MainMenuPage::ProcessEvent(HmiNavigation::KeyBoardEventList event)
{
	if(event == HmiNavigation::eKbShortEnter)
	{
		int CurrSelectedItem = FirstShownMenuLine + SelectionCursorLine;
		
		while(CurrSelectedItem > 10)
			CurrSelectedItem-=11;
		
		switch(CurrSelectedItem)
		{
			case 0:
			{
				Navigation.ShowPage(HmiNavigation::eSetDateHeurePage);
			}break;
			case 1:
			{
				Navigation.ShowPage(HmiNavigation::eSetBlkPage);
			}break;
			case 2:
			{
				Navigation.ShowPage(HmiNavigation::eSetConsPage);
			}break;
			case 3://eSetDeltatTempPage,
			{
				Navigation.ShowPage(HmiNavigation::eSetDeltatTempPage);
			}break;
			case 4://eSetPwmCoolFanPage,
			{
				Navigation.ShowPage(HmiNavigation::eSetPwmCoolFanPage);
			}break;
			case 5://eSetPwmHeatFanPage,
			{
				Navigation.ShowPage(HmiNavigation::eSetPwmHeatFanPage);
			}break;
			case 6://eSetHeatMaxPage,
			{
				Navigation.ShowPage(HmiNavigation::eSetHeatMaxPage);
			}break;
			case 7://eSetCoolMaxPage,
			{
				Navigation.ShowPage(HmiNavigation::eSetCoolMaxPage);
			}break;
			case 8://eDebugPage,
			{
				Navigation.ShowPage(HmiNavigation::eDebugPage);
			}break;
			case 9:
			{
				Regul.tune(!Regul.IsTunning());
			}//pas de break!!
			case 10:
			{
				Navigation.ShowPage(HmiNavigation::eMainPage);
			}break;

		}
		EnterMillisValue = millis();
	}
	
	if(event == HmiNavigation::eKbShortUp || event == HmiNavigation::eKbRepeatUp)
	{
		if(SelectionCursorLine == 1)
			SelectionCursorLine--;
		else
		{
			FirstShownMenuLine--;
			if(FirstShownMenuLine < 0)
				FirstShownMenuLine = 10;
		}
		
		EnterMillisValue = millis();
		lcd.clear();
	}
	
	if(event == HmiNavigation::eKbShortDown || event == HmiNavigation::eKbRepeatDown)
	{
		if(SelectionCursorLine == 0)
			SelectionCursorLine++;
		else
		{
			FirstShownMenuLine++;
			if(FirstShownMenuLine > 10)
				FirstShownMenuLine = 0;
		}

		EnterMillisValue = millis();
		lcd.clear();
	}
}
