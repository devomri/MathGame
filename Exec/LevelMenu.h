//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// LevelMenu.h
// ---------------
// Level Menu is responsible for displaying and handling the actions in the level menu.
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
#ifndef __LEVEL_MENU_H__
#define __LEVEL_MENU_H__

#include "IMenu.h"

class LevelMenu : public IMenu
{
	enum Options
	{
		EXIT_APPLICATION = '1',
		BACK_TO_MAIN_MENU = '2',
		CONTINUE = '3',
		REPLAY_LEVEL = '4',
		NEXT_LEVEL = '5'
	};

	Options displayMenu();
public:
	LevelMenu(ISpecificGame *currentGame) :IMenu(currentGame){}
	virtual bool onNextAction();
};

#endif