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
// 22/04/15		  Omri Avrahami			  Operator overloading + position distance
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "Position.h"
#include <math.h>

int Position::getDistanceFrom(const Position& other)
{
	int xDelta = fminf(abs(this->getX() - other.getX()), abs(80 - (this->getX() - other.getX())));
	int yDelta = fminf(abs(this->getY() - other.getY()), abs(24 - (this->getY() - other.getY())));

	return xDelta + yDelta;
}

Position Position::toRange()
{
	// Fix X loc
	if (this->xLocation >= 80)
	{
		this->xLocation = this->xLocation % 80;
	}
	else if (this->xLocation < 0)
	{
		while (this->xLocation < 0)
		{
			this->xLocation += 80;
		}
	}

	// Fix Y loc
	if (this->yLocation >= 24)
	{
		this->yLocation = this->yLocation % 24;
	}
	else if (this->yLocation < 0)
	{
		while (this->yLocation < 0)
		{
			this->yLocation += 24;
		}
	}

	return Position(*this);
}