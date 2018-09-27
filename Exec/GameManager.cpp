//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// GameManager.cpp
// ---------------
// GameManager is the top level manager, the game starts from here.
// This class manages the game iterations, menus etc., but WITHOUT knowing anything about the actual game itself.
//
// Author: Amir Kirsh
// First version: 2014-12-09
// 
// This code is part of "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 30/03/15		  Omri Avrahami			  Added spleep time for user message + changed menu
// 06/04/15		  Ori Riner				  Handling the game when there are no more levels.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <list>
#include "GameManager.h"
#include "MainMenu.h"
#include "LevelMenu.h"
#include "ISpecificGame.h"
#include "io_utils.h"

using namespace std;


void GameManager::run()
{
	MainMenu mainMenu(&actualGame);
	// we run as long as the user wants
	while (mainMenu.onNextAction()) {
		playGame();
	}
}

void GameManager::playGame()
{
	// we assume that we have multiple levels so there is a need to loop through levels
	// till all levels were played or till user quits - if user quits we do not continue to next level
	//-------------------------------------------------------------
	// this is the game LEVELS loop
	//-------------------------------------------------------------
	// When we still have a next level and the current one is done - let's play another level!
	while(actualGame.hasNextLevel() && actualGame.isLevelDone() && !actualGame.isMatchEnded()) {
		playNextLevel();
		actualGame.endCurrentLevel();
	}
	//-------------------------------------------------------------
	// END of game LEVELS loop
	//-------------------------------------------------------------
	
	// Clearing the screen after the match has ended and making sure the game match is reset.
	if (!actualGame.hasNextLevel() || actualGame.isMatchEnded()){
		clear_screen();
		actualGame.startCurrentMatch();
	}

}

// return action to take in case of ESC
void GameManager::playNextLevel()
{
	actualGame.startLevel();

	//=============================================================================================
	// this is the actual call to play game iterations
	while (doLevelIterations()) {}
	//=============================================================================================

}

// return action to take in case of ESC
bool GameManager::doLevelIterations()
{
	//char action;
	bool escapePressed = false;
	//---------------------------------------
	// this is the game iterations loop
	//---------------------------------------
	while(!actualGame.isLevelDone() && !escapePressed) {
		escapePressed = !doIteration();
	}
	//-----------------------------------------------------
	// END of game iterations loop or exit on ESC
	//-----------------------------------------------------

	// check why we are here
	if(actualGame.isLevelDone()) {
		clear_screen();
		bool someoneWon = false;
		if (actualGame.getRightPlayerStatus())
		{
			cout << "Good job player 1!" << endl;
			someoneWon = true;
		}
		if (actualGame.getLeftPlayerStatus())
		{
			cout << "Good job player 2!" << endl;
			someoneWon = true;
		}

		if (!someoneWon)
		{
			cout << "Shame on you!" << endl;
		}

		cout << endl << "Happy Hunger Games, and may the odds be ever in your favor!" 
			<< endl << endl << "Loading next level..." << endl;
		Sleep(2000);
		return false;
	}
	else {

		LevelMenu levelMenu(&actualGame);
		return levelMenu.onNextAction();

	}
}

bool GameManager::doIteration()
{
	unsigned int sleepLength = clockCycleInMillisec/iterationsPerClockCycle;
	for(unsigned int i=0; i<iterationsPerClockCycle-1; ++i) {
		Sleep(sleepLength);
		actualGame.doSubIteration();
	}
	return doInputIteration();
}

bool GameManager::doInputIteration()
{
	list<char> keyHits(KEYBOARD_HIT_LOOP); // set vector initialize size to the max key strokes that we may collect
	bool shouldContinue = true;
	// get keyboard input in a loop, to get enough keyboard hits
	unsigned int sleepLength = clockCycleInMillisec/iterationsPerClockCycle / KEYBOARD_HIT_LOOP;
	for(unsigned int i=0; i<KEYBOARD_HIT_LOOP; ++i) {
		Sleep(sleepLength);
		if (_kbhit()) {
			char ch = _getch();
			if(ch == ESC) {
				// ESC pressed
				shouldContinue = false;
			}
			else {
				// we got keyHits byref, so we actually set input into the original list sent here
				keyHits.push_front(ch); // we want recent keys to come first, thus we use push_front
			}
		}
	}
	// send the keystrokes to the game
	// (even if ESC was hit, we may still have something in the keystrokes vector and should use it)
	actualGame.doIteration(keyHits);

	return shouldContinue;
}

