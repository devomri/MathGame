//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// RowFlyer.h
// ---------------
// This class represents a basic creature in the game.
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 19/05/15		  Ori Riner				  Creation.
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "MovingObject.h"

class Creature : public MovingObject
{
	Position startingPosition;
public:
	Creature(char sign, const Position& position, Direction::value direction, Color c = Color::LIGHTMAGENTA)
		:MovingObject(sign, position, direction, c), startingPosition(position){};

	//virtual void setLastDirection(Direction::value dir){};
	virtual void reset(){ setPosition(startingPosition);}
	virtual bool isFaster()const=0;
	virtual bool isPremanent(){ return true; }
	virtual bool isDead()const { return false; }

	virtual void setHasDestinationNumber(bool hasDestination){}
	virtual bool getHasDestinationNumber()const { return true; }
	virtual void setNearestNumberPosition(const Position& pos){}
	virtual void informNewNumber(const Position& newNumPos) {}
};

#endif
