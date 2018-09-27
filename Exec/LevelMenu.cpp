//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// LevelMenu.cpp
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
#include "LevelMenu.h"
#include "io_utils.h"

using namespace std;
LevelMenu::Options LevelMenu::displayMenu(){
	char action;
	clear_screen();

	setTextColor(LIGHTBLUE);
	cout << "********************************************************************************" << endl;
	cout << "\t\t'||'''|,                                   ||`" << endl;
	cout << "\t\t ||   ||                                   || " << endl;
	cout << "\t\t ||...|'  '''|.  '||  ||` ('''' .|''|, .|''|| " << endl;
	cout << "\t\t ||      .|''||   ||  ||   `'') ||..|| ||  || " << endl;
	cout << "\t\t.||      `|..||.  `|..'|. `...' `|...  `|..||." << endl;
	cout << endl << "********************************************************************************" << endl << endl << endl;
	setTextColor(LIGHTGREY);

	cout << "\t\t\t|-------------------------|" << endl;
	cout << "\t\t\t| 1) Exit application     |" << endl;
	cout << "\t\t\t|-------------------------|" << endl;
	cout << "\t\t\t| 2) Back to main menu    |" << endl;
	cout << "\t\t\t|-------------------------|" << endl;
	cout << "\t\t\t| 3) Continue             |" << endl;
	cout << "\t\t\t|-------------------------|" << endl;
	cout << "\t\t\t| 4) Replay level         |" << endl;
	cout << "\t\t\t|-------------------------|" << endl;
	cout << "\t\t\t| 5) Next level           |" << endl;
	cout << "\t\t\t|-------------------------|" << endl;
	do {
		action = _getch();
	} while (!isValidOption("12345",action));

	return static_cast<LevelMenu::Options>(action);
}
bool LevelMenu::onNextAction(){
	bool keepRunning;
	// check action based on game ended (action==BACK_TO_MAIN_MENU) or input from user on ESC menu
	switch (displayMenu()) {
	case LevelMenu::CONTINUE:
		currentGame->continueLevel();
		keepRunning = true;
		break;
	case LevelMenu::REPLAY_LEVEL:
		currentGame->setLevel(currentGame->getLevel());
		currentGame->startLevel();
		keepRunning = true;
		break;
	case LevelMenu::BACK_TO_MAIN_MENU:
		clear_screen();
		currentGame->endCurrentMatch();
		keepRunning = false;
		break;
	case LevelMenu::EXIT_APPLICATION:
		// get out from the loop
		exit(0);
		/*clear_screen();
		keepRunning = false;*/
		break;
	case LevelMenu::NEXT_LEVEL:
		// get out from the loop so we get to the next level
		currentGame->endCurrentLevel();
		keepRunning = false;
		break;
	}

	return keepRunning;
}