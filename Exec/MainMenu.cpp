//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MainMenu.cpp
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
#include "MainMenu.h"
#include "io_utils.h"

using namespace std;
MainMenu::Options MainMenu::displayMenu(){
	setTextColor(LIGHTBLUE);

	cout << "********************************************************************************" ;
	cout << "'||    ||'           .   '||              ..|'''.|                              " ;
	cout << " |||  |||   ....   .||.   || ..          .|'     '   ....   .. .. ..     .... 	" ;
	cout << " |'|..'||  '' .||   ||    ||' ||         ||    .... '' .||   || || ||  .|...||	" ;
	cout << " | '|' ||  .|' ||   ||    ||  ||         '|.    ||  .|' ||   || || ||  ||     	" ;
	cout << ".|. | .||. '|..'|'  '|.' .||. ||.         ''|...'|  '|..'|' .|| || ||.  '|...'	" ;
	cout << endl << "********************************************************************************" << endl << endl << endl;
	setTextColor(LIGHTGREY);

	cout << "\t\t\t---------------------------------" << endl;
	cout << "\t\t\t| 1) instructions                |" << endl;
	cout << "\t\t\t---------------------------------" << endl;
	cout << "\t\t\t| 2) play game                   |" << endl;
	cout << "\t\t\t---------------------------------" << endl;
	cout << "\t\t\t| 3) start from a specific level |" << endl;
	cout << "\t\t\t-------------------------------" << endl;
	cout << "\t\t\t| 9) exit                        |" << endl;
	cout << "\t\t\t---------------------------------" << endl;

	char selection = 0;
	do {
		selection = _getch();
	} while (!this->isValidOption("1239", selection));
	return static_cast<Options>(selection);
}

bool MainMenu::onNextAction(){
	bool userWantsToPlay = true;
	switch (displayMenu())
	{
	case MainMenu::PRESENT_INSTRUCTIONS:
		// Show the instructions page
		currentGame->showGameInstructions();
		userWantsToPlay = this->onNextAction();
		break;
	case MainMenu::PLAY_GAME:
		currentGame->setLevel(0);
		userWantsToPlay = true;
		break;
	case MainMenu::PLAY_FROM_SELECTED_SCREEN:
		int userSelectedlevel;
		clear_screen();
		cout << "Please enter the game level you wish: ";
		cin >> userSelectedlevel;
		currentGame->setLevel(userSelectedlevel);
		userWantsToPlay = true;
		break;
	case MainMenu::EXIT_APPLICATION:
		userWantsToPlay = false;
		break;
	default: // normally we shouldn't get to here...
		userWantsToPlay = false;
	};
	return userWantsToPlay;
}
