//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MainMenu.h
// ---------------
// Main Menu is responsible for displaying and handling the actions in the main menu.
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 03/04/15		  Ori Riner				  Creation.
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "IMenu.h"

class MainMenu : public IMenu
{
	enum Options
	{
		PRESENT_INSTRUCTIONS = '1',
		PLAY_GAME = '2',
		PLAY_FROM_SELECTED_SCREEN = '3',
		EXIT_APPLICATION = '9'
	};

	Options displayMenu();
public:
	MainMenu(ISpecificGame *currentGame) :IMenu(currentGame){}
	virtual bool onNextAction();
};

#endif