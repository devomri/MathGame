//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// NumberCell.h
// ---------------
// This class represents a numeric cell that contains a number.
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 05/05/15		  Ori Riner					Creation.
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __NUMBER_CELL_H__
#define __NUMBER_CELL_H__

#include "BoardCell.h"
#include "Collisions.h"

class NumberCell : public BoardCell
{
private:
	int numericValue;
	static const int EMPTY_CELL_NUMERIC_VALUE = -1;
public:
	NumberCell(char sign = EMPTY_CELL_CHARACTER, int numericValue = EMPTY_CELL_NUMERIC_VALUE)
		:BoardCell(sign), numericValue(numericValue){}
	int getNumericValue() const { return numericValue; }
	void setNumericValue(int numericVal){ numericValue = numericVal; }
	bool getIsEmptyNumber(){ return (numericValue == EMPTY_CELL_NUMERIC_VALUE); }

	virtual bool isPartialCell(){ return true; }
	virtual void reset();

	virtual bool collide(ICollider* otherCell){ return otherCell->collide(*this); }
	virtual bool collide(MathPlayer& player){ return Collisions::collide(player, *this); }
	virtual bool collide(PlayerShot& shot){ return Collisions::collide(shot, *this); }
	virtual bool collide(NumberCell& number){ return false; }
	virtual bool collide(NumberEater& eater){ return Collisions::collide(eater, *this); }
	virtual bool collide(ColumnFlyer& flyer){ return Collisions::collide(flyer, *this); }
	virtual bool collide(RowFlyer& flyer){ return Collisions::collide(flyer, * this); }
};

#endif