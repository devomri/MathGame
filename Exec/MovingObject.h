//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MovingObject.h
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
#ifndef __MOVING_OBJECT_H__
#define __MOVING_OBJECT_H__

#include "Position.h"
#include "Direction.h"
#include "BoardCell.h"

class MovingObject : public BoardCell
{
protected:
	Position position;
	Direction::value lastDirection;
	Direction::value previousDirection;
public:
	MovingObject(char sign, const Position& objectPos, Direction::value objectDir,Color color)
		: BoardCell(sign, color), lastDirection(objectDir), previousDirection(objectDir){
		this->position.setX(objectPos.getX());
		this->position.setY(objectPos.getY());
	}
	Position getPosition() const{ return this->position; }
	void setPosition(const Position& pos);
	virtual void setLastDirection(Direction::value dir);
	Direction::value getLastDirection() { return this->lastDirection; }
	Direction::value getPreviousDirection() { return this->previousDirection; }
	virtual void move();
	void reverseMove();
	Position getPosition(Direction::value direction,int incrementBy = 2);
};

#endif