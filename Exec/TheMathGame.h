//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// TheMathGame.h
// -------------
// This class represent the math game.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 26/03/15	      Ori Riner				  Creation
// 28/03/15		  Ori Riner				  Drawing the control rows for a level.
// 29/03/15		  Omri Avrahami			  Added math player movement method
// 30/03/15		  Omri Avrahami			  Board iniatiation
// 30/03/15	      Omri Avrahami			  Added game instructions
// 24/04/15	      Omri Avrahami			  Added BoardCell
// 25/04/15		  Omri Avrahami			  Added players shooting
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef __MATH_GAME_H__
#define __MATH_GAME_H__

#include <list>
#include "Color.h"
#include "ISpecificGame.h"
#include "MathPlayer.h"
#include "PlayerShot.h"
#include "Creature.h"

class TheMathGame : public ISpecificGame
{
private:
	static const int NUMBER_OF_LEVELS = 40;

	MathPlayer leftPlayer, rightPlayer;
	static const char LEFT_PLAYER_SIGN = '#';
	static const Direction::value LEFT_PLAYER_FIRST_DIR = Direction::LEFT;
	static const char RIGHT_PLAYER_SIGN = '@';
	static const Direction::value RIGHT_PLAYER_FIRST_DIR = Direction::RIGHT;
	bool isCurrentGameFinished;
	list<PlayerShot*> currentShots;
	list<Creature*> creatures;
	int currentLevel;
	int currentIterationsNumber;
	BoardCell* board[24][80];
	void generateNumber();
	bool verifyEmptyNeighborhood(const Position& position) const;
	void draw(const Position& position)const;
	void drawControlRows() const;
	void drawPlayerControlRows(const MathPlayer& player, int column)const;
	void moveMathPlayer(MathPlayer& player, MathPlayer& otherPlayer);
	void initBoard();
	BoardCell* getCell(const Position& position)const;
	void setCell(const Position& position, BoardCell* newCell);
	void resetNeighboors(const Position& position);
	void getDigitsForNumber(int number, list<int>& digits) const;
	void mathGameShoot(MathPlayer& fromPlayer);
	void drawNewCell(const Position& position, BoardCell* newCell);
	void moveCreatures(bool isFaster);
	Position getNearestNumber(const Position& sourcePos, bool& isFound) const;
public:
	TheMathGame();
	virtual bool isLevelDone()const;
	virtual bool hasNextLevel()const{ return currentLevel < NUMBER_OF_LEVELS; }
	virtual void startLevel();
	virtual void continueLevel();
	virtual void doIteration(list<char>& keyHits);
	virtual void doSubIteration();
	virtual void showGameInstructions();
	virtual void setLevel(int level);
	virtual int getLevel() const;
	virtual int getLastIterationsDuration()const;
	virtual bool getLeftPlayerStatus()const;
	virtual bool getRightPlayerStatus()const;
	virtual void endCurrentLevel();
	virtual void endCurrentMatch();
	virtual void startCurrentMatch();
	virtual bool isMatchEnded()const;

	~TheMathGame();
};

#endif