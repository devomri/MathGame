//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// BoardCell.cpp
// -------------
// This class represent the base cell within the board.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 05/05/15	      Ori Riner				  Creation
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "BoardCell.h"

void BoardCell::reset(){
	setSign(EMPTY_CELL_CHARACTER);\
}

bool BoardCell::isPremanent(){
	return false;
}