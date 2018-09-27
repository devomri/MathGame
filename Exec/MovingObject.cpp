//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MovingObject.cpp
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

#include "MovingObject.h"

void MovingObject::move()
{
	switch (this->lastDirection)
	{
	case Direction::DOWN:
		this->setPosition(Position(this->getPosition().getX(),
			this->getPosition().getY() + 1));
		break;
	case Direction::LEFT:
		this->setPosition(Position(this->getPosition().getX() - 1,
			this->getPosition().getY()));
		break;
	case Direction::RIGHT:
		this->setPosition(Position(this->getPosition().getX() + 1,
			this->getPosition().getY()));
		break;
	case Direction::UP:
		this->setPosition(Position(this->getPosition().getX(),
			this->getPosition().getY() - 1));
		break;
	default:
		break;
	}
}

void MovingObject::reverseMove()
{
	switch (this->lastDirection)
	{
	case Direction::DOWN:
		this->setPosition(Position(this->getPosition().getX(),
			this->getPosition().getY() - 1));
		break;
	case Direction::LEFT:
		this->setPosition(Position(this->getPosition().getX() + 1,
			this->getPosition().getY()));
		break;
	case Direction::RIGHT:
		this->setPosition(Position(this->getPosition().getX() - 1,
			this->getPosition().getY()));
		break;
	case Direction::UP:
		this->setPosition(Position(this->getPosition().getX(),
			this->getPosition().getY() + 1));
		break;
	default:
		break;
	}
}

Position MovingObject::getPosition(Direction::value direction,int incrementBy){
	Position futurePlace;

	switch (direction)
	{
	case Direction::DOWN:
		futurePlace.setX(this->getPosition().getX());
		futurePlace.setY(this->getPosition().getY() + incrementBy);
		break;
	case Direction::LEFT:
		futurePlace.setX(this->getPosition().getX() - incrementBy);
		futurePlace.setY(this->getPosition().getY());		
		break;
	case Direction::RIGHT:
		futurePlace.setX(this->getPosition().getX() + incrementBy);
		futurePlace.setY(this->getPosition().getY());
		break;
	case Direction::UP:
		futurePlace.setX(this->getPosition().getX());
		futurePlace.setY(this->getPosition().getY() - incrementBy);
		break;
	default:
		break;
	}

	return futurePlace;
}

void MovingObject::setPosition(const Position& pos)
{
	this->position.setX(pos.getX());
	this->position.setY(pos.getY());
}

void MovingObject::setLastDirection(Direction::value dir){
	previousDirection = lastDirection;
	lastDirection = dir;
}