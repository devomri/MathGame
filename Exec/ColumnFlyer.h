//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ColumnFlyer.h
// ---------------
// This class represents a Column Flyer creature in the game.
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
#ifndef __COLUMN_FLYER_H__
#define __COLUMN_FLYER_H__

#include "Creature.h"
#include "Collisions.h"

class ColumnFlyer : public Creature
{
public:
	ColumnFlyer(const Position& position, Direction::value direction)
		:Creature('$', position, direction != Direction::UP && direction != Direction::DOWN ? Direction::STAY : direction){};

	virtual bool isFaster()const{ return false; }
	virtual bool collide(ICollider* otherCell){ return otherCell->collide(*this); }
	virtual bool collide(MathPlayer& player){ return Collisions::collide(player, *this); }
	virtual bool collide(PlayerShot& shot){ return Collisions::collide(shot, *this); }
	virtual bool collide(NumberCell& number){ return Collisions::collide(*this,number); }
	virtual bool collide(NumberEater& eater){ return Collisions::collide(eater, *this); }
	virtual bool collide(ColumnFlyer& flyer){ return Collisions::collide(*this,flyer); }
	virtual bool collide(RowFlyer& flyer){ return Collisions::collide(*this,flyer); }
};

#endif
