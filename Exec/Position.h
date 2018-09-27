//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Position.h
// -------------
// This class represents a position of an element (player, target, enemy etc) on the board
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 23/03/15		  Omri Avrahami			  Creation
// 27/03/15		  Ori Riner				  Getting 'near' location to the current position.
// 29/03/15		  Omri Avrahami			  Added checking of the screen borders + cyklik change
// 30/03/15		  Omri Avrahami			  Operator == overloading
// 22/04/15		  Omri Avrahami			  Operator overloading + position distance
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _BOARD_POSITION_H
#define _BOARD_POSITION_H

#include "Direction.h"

using namespace std;

class Position
{
private:
	int xLocation;
	int yLocation;
public:
	enum{
		X_EDGE = 80,
		Y_EDGE = 24,
		CONTROL_ROWS = 5,
		CONTROL_ROW_SIZE = 17
	};
	Position(int xLoc = 0, int yLoc = 0)
		:xLocation(xLoc), yLocation(yLoc) {}
	Position(const Position& position, Direction::value dir) :
		xLocation(dir == Direction::LEFT ? position.getLeftX() : dir == Direction::RIGHT ? position.getRightX() : position.getX()),
		yLocation(dir == Direction::UP ? position.getUpY() : dir == Direction::DOWN ? position.getDownY() : position.getY()){}
	int getX() const { return this->xLocation; }
	void setX(int x)  {
		this->xLocation = x >= X_EDGE ? 0 : x < 0 ? X_EDGE -1 : x; 
	}
	int getY() const{ return this->yLocation; }
	void setY(int y) {
		this->yLocation = y >= Y_EDGE ? CONTROL_ROWS : y < CONTROL_ROWS ? Y_EDGE - 1 : y; 
	}
	int getLeftX() const{
		return xLocation > 0 ? xLocation - 1 : xLocation;
	}
	int getRightX() const{
		return xLocation < X_EDGE - 1 ? xLocation + 1 : xLocation;
	}
	int getUpY() const{
		return yLocation > CONTROL_ROWS - 1 ? yLocation - 1 : yLocation;
	}
	int getDownY() const{
		return yLocation < Y_EDGE - 1 ? yLocation + 1 : yLocation;
	}
	bool operator == (const Position &other)const{
		return other.xLocation == this->xLocation && other.yLocation == this->yLocation;
	}
	bool operator!= (const Position &other)const{
		return !(*this == other);
	}

	int getDistanceFrom(const Position& other);
	Position toRange();
};

#endif