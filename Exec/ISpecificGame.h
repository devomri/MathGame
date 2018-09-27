//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ISpecificGame.h
// ---------------
// ISpecificGame is an abstract base class without any implementation.
// (We call such a class "interface" though there are no interfaces in C++).
// This class is the base class for any actual game that wants to be managed by GameManager.
// All relevant operations that GameManager needs from an actual game will be declared here, however specific operations
// which are specific for a certain game and are not generic will not be declared here.
// NOTE that this class doesn't have any cpp file as there are NO actual implemenations, only signatures.
//
// Authors: Amir Kirsh, Iris Gaber
// First version: 2014-12-09
// 
// This code is part of a solution for "the math game" excercise in C++ course, Semester B 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 30/03/15		  Omri Avrahami			  Added instructions & level setting methods
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _ISPECIFIC_GAME_H_
#define _ISPECIFIC_GAME_H_

#include <list>

using namespace std;

// this is a base class for actual games
// actual games will inherit from this class and implement the required methods
class ISpecificGame
{
public:
	// virtual fucnction with =0 is called an "abstract method"
	// abstract method must be implemented by non-abstract inherited class
	virtual bool isLevelDone()const=0;
	virtual bool hasNextLevel()const=0;
	virtual void startLevel()=0;
	virtual void continueLevel() = 0;

	// get a list with keyHits and returns a list with the keys that were used
	virtual void doIteration(list<char>& keyHits)=0;
	virtual void doSubIteration()=0;

	virtual void showGameInstructions()=0;
	virtual void setLevel(int level) = 0;
	virtual int getLevel()const = 0;
	virtual int getLastIterationsDuration()const = 0;
	virtual bool getLeftPlayerStatus()const = 0;
	virtual bool getRightPlayerStatus()const = 0;
	virtual void endCurrentLevel()=0;
	virtual void endCurrentMatch() = 0;
	virtual void startCurrentMatch() = 0;
	virtual bool isMatchEnded()const = 0;
};

#endif