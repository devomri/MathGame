//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Collisions.h
// ---------------
// This class handles all the collisions in the game between two cells.
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
#ifndef __COLLISIONS_H__
#define __COLLISIONS_H__

class MathPlayer;
class PlayerShot;
class NumberCell;
class NumberEater;
class ColumnFlyer;
class RowFlyer;

class Collisions
{
public:
	static bool collide(  MathPlayer& player,   MathPlayer& otherPlayer);
	static bool collide(  MathPlayer& player,   NumberCell& number);
	static bool collide(  MathPlayer& player,   PlayerShot& shot);
	static bool collide(  MathPlayer& player,   NumberEater& eater);
	static bool collide(  MathPlayer& player,   ColumnFlyer& flyer);
	static bool collide(  MathPlayer& player,   RowFlyer& flyer);
		   
	static bool collide(  PlayerShot& shot,   PlayerShot& otherShot);
	static bool collide(  PlayerShot& shot,   NumberCell& number);
	static bool collide(  PlayerShot& shot,   NumberEater& eater);
	static bool collide(  PlayerShot& shot,   ColumnFlyer& flyer);
	static bool collide(  PlayerShot& shot,   RowFlyer& flyer);
		   
	static bool collide(  NumberEater& eater,   NumberCell& number);
	static bool collide(  NumberEater& eater,   NumberEater& otherEater);
	static bool collide(  NumberEater& eater,   ColumnFlyer& flyer);
	static bool collide(  NumberEater& eater,   RowFlyer& flyer);
		   
	static bool collide(  ColumnFlyer& flyer,   NumberCell& number);
	static bool collide(  ColumnFlyer& flyer,   ColumnFlyer& otherFlyer);
	static bool collide(  ColumnFlyer& flyer,   RowFlyer& otherFlyer);
		   
	static bool collide(  RowFlyer& flyer,   NumberCell& number);
	static bool collide(  RowFlyer& flyer,   RowFlyer& otherFlyer);
};

#endif
