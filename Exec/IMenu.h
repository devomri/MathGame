//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// IMenu.h
// ---------------
// IMenu is responsible for displaying some kind of menu.
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 03/04/15		  Ori Riner				  Created the interface.
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __IMENU_H__
#define __IMENU_H__

#include "ISpecificGame.h"
#include <string>

class IMenu
{
protected:
	ISpecificGame *currentGame;
	IMenu(ISpecificGame *currentGame) : currentGame(currentGame){}
	static bool isValidOption(string allOptions, char option) {
		return (allOptions.find(option) != string::npos);
	}
public:

	virtual bool onNextAction() = 0;
};

#endif