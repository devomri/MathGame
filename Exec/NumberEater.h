//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// NumberEater.h
// ---------------
// This class represents a Number eater creature in the game.
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 19/05/15		  Ori Riner				  Creation.
// 22/05/15		  Omri Avrahami			  Added nearest number functionality
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __NUMBER_EATER_H__
#define __NUMBER_EATER_H__

#include "Creature.h"
#include "Collisions.h"

class NumberEater : public Creature
{
private:
	Position nearestNumberPosition;
	bool hasDestinationNumber;
	bool hasDied;
public:
	NumberEater(const Position& position);

	virtual void setHasDestinationNumber(bool hasDestination){ this->hasDestinationNumber = hasDestination; }
	virtual bool getHasDestinationNumber()const { return this->hasDestinationNumber; }
	virtual void setNearestNumberPosition(const Position& pos){ this->nearestNumberPosition = pos; }
	virtual void informNewNumber(const Position& newNumPos);

	virtual bool isFaster()const { return true; }
	virtual void move();
	virtual void reset();
	virtual bool isDead()const{ return hasDied; }

	virtual bool collide(ICollider* otherCell){ return otherCell->collide(*this); }
	virtual bool collide(MathPlayer& player){ return Collisions::collide(player, *this); }
	virtual bool collide(PlayerShot& shot){ return Collisions::collide(shot, *this); }
	virtual bool collide(NumberCell& number){ return Collisions::collide(*this, number); }
	virtual bool collide(NumberEater& eater){ return Collisions::collide(*this,eater); }
	virtual bool collide(ColumnFlyer& flyer){ return Collisions::collide(*this, flyer); }
	virtual bool collide(RowFlyer& flyer){ return Collisions::collide(*this, flyer); }
	
	void kill(){ hasDied = true; }
};

#endif
