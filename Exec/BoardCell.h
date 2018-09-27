//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// BoardCell.h
// ---------------
// This class represents a base class of a cell item within the board.
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 05/05/15		  Ori Riner				 Creation.
// 25/05/15		  Omri Avrahami			 Check for empty
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __BOARD_CELL_H__
#define __BOARD_CELL_H__

#include "Color.h"
#include "ICollider.h"
class BoardCell: public ICollider
{
private:
	char cellSign;
	Color color;
	bool clearAfterCollision;
protected:
	static const char EMPTY_CELL_CHARACTER = '.';
public:
	BoardCell(char sign = EMPTY_CELL_CHARACTER, Color color = LIGHTGREY)
		:cellSign(sign), color(color), clearAfterCollision(false) {}
	char getSign() const {
		return this->cellSign;
	}
	void setSign(char sign){ this->cellSign = sign; }
	Color getColor() const { return this->color; }
	void setColor(Color color){ this->color = color; }
	bool isEmpty() const { return cellSign == EMPTY_CELL_CHARACTER; }
	virtual bool getClearAfterCollision(){ return clearAfterCollision; }
	virtual void setClearAfterCollision(bool clear){ clearAfterCollision = clear; }
	virtual bool isBlocking(){ return false; }
	virtual bool isPartialCell(){ return false; }
	virtual void reset();
	virtual bool isPremanent();
	virtual bool collide(ICollider* otherCell){ return false; }
};

#endif