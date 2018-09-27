//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// PlayerShot.h
// ---------------
// This class represents a base class of moving object in the game
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 24/04/15		  Omri Avrahami			  Creation.
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __PLAYER_SHOT_H__
#define __PLAYER_SHOT_H__

#include "MovingObject.h"
#include "Collisions.h"

class PlayerShot : public MovingObject
{
public:
	PlayerShot(const Position& shotPos, Direction::value shotDir)
		:MovingObject('*', shotPos, shotDir,YELLOW){};

	virtual bool collide(ICollider* otherCell){ return otherCell->collide(*this); }
	virtual bool collide(MathPlayer& player){ return Collisions::collide(player, *this); }
	virtual bool collide(PlayerShot& shot){ return Collisions::collide(*this,shot); }
	virtual bool collide(NumberCell& number){ return Collisions::collide(*this, number); }
	virtual bool collide(NumberEater& eater){ return Collisions::collide(*this,eater); }
	virtual bool collide(ColumnFlyer& flyer){ return Collisions::collide(*this, flyer); }
	virtual bool collide(RowFlyer& flyer){ return Collisions::collide(*this, flyer); }
};

#endif
