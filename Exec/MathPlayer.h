//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MathPlayer.h
// -------------
// This class represent a player in the math game.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 23/03/15	      Omri Avrahami			  Creation
// 26/03/15		  Ori Riner				  Constructor Signiture change (removed direction,life amount, score)
// 26/03/15		  Ori Riner				  Removed the direction property and received it as a parameter to move.
// 29/03/15		  Omri Avrahami			  Added last direction of the player
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _MATH_PLAYER_H_
#define _MATH_PLAYER_H_

#include <string>
#include "Position.h"
#include "Direction.h"
#include "BaseQuestion.h"
#include "MovingObject.h"
#include "Collisions.h"

using namespace std;

class MathPlayer : public MovingObject
{
private:
	int lifeAmount;
	int gameScore;
	bool winningStatus;
	BaseQuestion* currentQuestion;
	int shotsAmount;
	Position startingPosition;
	Direction::value startingDirection;

public:
	MathPlayer(char inPlayerSign, const Position& inPlayerPos, Direction::value dir,Color color)
		: MovingObject(inPlayerSign, inPlayerPos, dir,color),
		lifeAmount(3), gameScore(0), winningStatus(false),currentQuestion(NULL), shotsAmount(5), startingPosition(inPlayerPos), startingDirection(dir) {};
	~MathPlayer();
	void init(int level);
	string getShotsString() const;
	bool getWinningStatus()const { return this->winningStatus; }
	void setWinningStatus(bool status) { this->winningStatus = status; }
	int getLifeAmount() const { return this->lifeAmount; }
	void setLifeAmount(int life) { this->lifeAmount = life; }
	void decreaseLifeAmount();
	int getGameScore() const { return this->gameScore; }
	void increaseGameScore() { this->gameScore++; }
	BaseQuestion* getQuestion() const { return this->currentQuestion; }
	void setQuestion(BaseQuestion* newQuestion){ this->currentQuestion = newQuestion; }
	string getLifeString() const;
	int getShotsAmount() const{ return this->shotsAmount; }
	void setShotsAmount(int amount){ this->shotsAmount = amount; }
	void increaseShotsAmount() { this->shotsAmount++; }
	void decreaseShotAmount() { this->shotsAmount--; }
	
	virtual bool isBlocking(){ return true; }
	virtual void reset();
	virtual bool isPremanent();
	virtual bool collide(ICollider* otherCell){ return otherCell->collide(*this); }
	virtual bool collide(MathPlayer& player){ return Collisions::collide(*this,player); }
	virtual bool collide(PlayerShot& shot){ return Collisions::collide(*this,shot); }
	virtual bool collide(NumberCell& number){ return Collisions::collide(*this, number); }
	virtual bool collide(NumberEater& eater){ return Collisions::collide(*this,eater); }
	virtual bool collide(ColumnFlyer& flyer){ return Collisions::collide(*this, flyer); }
	virtual bool collide(RowFlyer& flyer){ return Collisions::collide(*this, flyer); }
};

#endif
