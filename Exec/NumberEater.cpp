//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// NumberEater.cpp
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

#include "NumberEater.h"
#include <math.h>

NumberEater::NumberEater(const Position& position)
	:Creature('%', position, Direction::STAY, Color::LIGHTCYAN){
	// At the begining there is no number to search for
	hasDestinationNumber = false;
};

void NumberEater::move(){
	if (!this->hasDestinationNumber)
	{
		this->setLastDirection(Direction::STAY);
	}
	else if (this->position == this->nearestNumberPosition)
	{
		this->setLastDirection(Direction::STAY);
		this->hasDestinationNumber = false;
	}
	else
	{
		// If there is a need to move in the X axis
		if (this->nearestNumberPosition.getX() != this->position.getX())
		{
			int xDelta = this->position.getX() - this->nearestNumberPosition.getX();
			
			// Check if there is a need to move left or right
			if (abs(xDelta) < Position::X_EDGE /2)
			{
				if (xDelta > 0)
				{
					this->setLastDirection(Direction::LEFT);
				}
				else
				{
					this->setLastDirection(Direction::RIGHT);
				}
			}
			else
			{
				if (xDelta > 0)
				{
					this->setLastDirection(Direction::RIGHT);
				}
				else
				{
					this->setLastDirection(Direction::LEFT);
				}
			}
		}
		// Check if there is a need to move in the Y axis
		else if (this->nearestNumberPosition.getY() != this->position.getY())
		{
			int yDelta = this->position.getY() - this->nearestNumberPosition.getY();

			// Check if there is a need to go up or down
			if (abs(yDelta) < Position::Y_EDGE / 2)
			{
				if (yDelta > 0)
				{
					this->setLastDirection(Direction::UP);
				}
				else
				{
					this->setLastDirection(Direction::DOWN);
				}
			}
			else
			{
				if (yDelta > 0)
				{
					this->setLastDirection(Direction::DOWN);
				}
				else
				{
					this->setLastDirection(Direction::UP);
				}
			}
		}
	}

	Creature::move();
}

void NumberEater::informNewNumber(const Position& newNumPos)
{
	// Check if there is a need to update the new searching location
	if (!this->hasDestinationNumber ||
		(this->getPosition().getDistanceFrom(newNumPos) <
		 this->getPosition().getDistanceFrom(this->nearestNumberPosition)))
	{
		this->nearestNumberPosition = Position(newNumPos);

		hasDestinationNumber = true;
	}
}

void NumberEater::reset(){
	hasDestinationNumber = false;
	hasDied = false;
	Creature::reset();
}