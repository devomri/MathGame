//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Question.cpp
// -------------
// This class represent a question in the math game.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 26/03/15	      Ori Riner				  Creation
// 27/03/15		  Ori Riner				  The Question difficulty is relative to a given level.
// 30/03/15		  Omri Avrahami			  Added question init
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "Question.h"
#include <sstream>

Question::Question(int level) {
	initQuestion(level);
}

void Question::initQuestion(int level)
{
	this->operatorValue = static_cast<Operators>(rand() % 4);
	this->operatorLabel = operatorValue == PLUS ? '+' : operatorValue == MULTIPLY ? '*' : operatorValue == MINUS ? '-' : '/';
	int random1 = rand() % (10 + level) + 1;
	int random2 = rand() % (10 + level) + 1;
	if (operatorValue < 2){
		this->operand1 = random1;
		this->operand2 = random2;
		this->result = operatorValue == PLUS ? operand1 + operand2 : operand1 * operand2;
	}
	else
	{
		this->operand2 = random1;
		this->result = random2;
		this->operand1 = operatorValue == MINUS ? result + operand2 : result * operand2;
	}
	variable =
		operatorValue < 2 ? rand() % 2 == 0 ? &operand1 : &operand2 : rand() % 2 == 0 ? &operand2 : &result;
}

string Question::toString()const {
	stringstream firststream;
	stringstream secondstream;
	stringstream thirdstream;
	firststream << operand1;
	secondstream << operand2;
	thirdstream << result;
	string first = &operand1 == variable ? "__" : firststream.str();
	string second = &operand2 == variable ? "__" : secondstream.str();
	string third = &result == variable ? "=__" : "=" + thirdstream.str();
	return first + operatorLabel +  second + third;
}

bool Question::validate(int value)
{
	return isFinished = (value == *variable);
}

bool Question::isDone()const{
	return isFinished;
}