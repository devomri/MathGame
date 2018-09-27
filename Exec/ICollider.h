//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ICollider.h
// ---------------
// This class represents a collider interface and all the other cells it can collide with.
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 05/05/15		  Ori Riner			  Creation.
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __ICOLLIDER_H__
#define __ICOLLIDER_H__

class MathPlayer;
class PlayerShot;
class NumberCell;
class NumberEater;
class ColumnFlyer;
class RowFlyer;

class ICollider{
public:
	virtual bool collide(MathPlayer& player){ return false; }
	virtual bool collide(PlayerShot& shot){ return false; }
	virtual bool collide(NumberCell& number){ return false; }
	virtual bool collide(NumberEater& eater){ return false; }
	virtual bool collide(ColumnFlyer& flyer){ return false; }
	virtual bool collide(RowFlyer& flyer){ return false; }
};

#endif