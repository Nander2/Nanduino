#include "HmiNavigation.h"
#include "MotherHmiPage.h"
#include "StartUpPage.h"
#include "MainPage.h"
#include "MainMenuPage.h"
#include "SetDateHeurePage.h"
#include "SetBlkPage.h"
#include "SetConsPage.h"
#include "SetDeltaTempPage.h"
#include "SetPwmCoolFanPage.h"
#include "SetPwmHeatFanPage.h"
#include "SetCoolMaxPage.h"
#include "SetHeatMaxPage.h"
#include "DebugMotorPage.h"

HmiNavigation Navigation;

HmiNavigation::HmiNavigation()
{
	Current_Page = NULL;
}

void HmiNavigation::ShowPage(int PageId)
{
	if(Current_Page != NULL)
	{
		Current_Page->Exit();
		delete Current_Page;
	}
	
	switch(PageId)
	{
		case eStartUpPage:
		{
			Current_Page = new StartUpPage();
		}break;
		
		case eMainPage:
		default:
		{
			Current_Page = new MainPage();
		}break;
		case eMainMenuPage:
		{
			Current_Page = new MainMenuPage();
		}break;
		
		case eSetDateHeurePage:
		{
			Current_Page = new SetDateHeurePage();
		}break;
		
		case eSetBlkPage:
		{
			Current_Page = new SetBlkPage();
		}break;
		
		case eSetConsPage:
		{
			Current_Page = new SetConsPage();
		}break;
		
		case eSetDeltatTempPage:
		{
			Current_Page = new SetDeltaTempPage();
		}break;
		
		case eSetPwmCoolFanPage:
		{
			Current_Page = new SetPwmCoolFanPage();
		}break;
		
		case eSetPwmHeatFanPage:
		{
			Current_Page = new SetPwmHeatFanPage();
		}break;
		
		case eSetHeatMaxPage:
		{
			Current_Page = new SetHeatMaxPage();
		}break;
		
		case eSetCoolMaxPage:
		{
			Current_Page = new SetCoolMaxPage();
		}break;
		
		case eDebugPage:
		{
			Current_Page = new DebugMotorPage();
		}break;
		
	}
	
	Current_Page->Enter();
}

void HmiNavigation::Run()
{
	if(Current_Page != NULL)
		Current_Page->Refresh();
}

void HmiNavigation::SendEvent(KeyBoardEventList event)
{	
	if(Current_Page != NULL)
	{
		Current_Page->ProcessEvent(event);
	}
}
