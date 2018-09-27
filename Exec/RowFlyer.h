//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// RowFlyer.h
// ---------------
// This class represents a Row Flyer creature in the game.
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
#ifndef __ROW_FLYER_H__
#define __ROW_FLYER_H__

#include "Creature.h"
#include "Collisions.h"

class RowFlyer : public Creature
{
public:
	RowFlyer(const Position& position, Direction::value direction)
		:Creature('!', position, direction != Direction::RIGHT && direction != Direction::LEFT ? Direction::STAY : direction){};
	virtual bool isFaster()const{ return true; }

	virtual bool collide(ICollider* otherCell){ return otherCell->collide(*this); }
	virtual bool collide(MathPlayer& player){ return Collisions::collide(player, *this); }
	virtual bool collide(PlayerShot& shot){ return Collisions::collide(shot, *this); }
	virtual bool collide(NumberCell& number){ return Collisions::collide(*this, number); }
	virtual bool collide(NumberEater& eater){ return Collisions::collide(eater, *this); }
	virtual bool collide(ColumnFlyer& flyer){ return Collisions::collide(flyer,*this); }
	virtual bool collide(RowFlyer& flyer){ return Collisions::collide(*this, flyer); }
};

#endif
