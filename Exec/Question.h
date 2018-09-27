//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Question.h
// -------------
// This class represent a question in the math game.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 26/03/15	      Ori Riner				  Creation
// 30/03/15		  Omri Avrahami			  Added question init
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef __QUESTION_H__
#define __QUESTION_H__

#include <stdlib.h>
#include <string>
#include "BaseQuestion.h"

using namespace std;

class Question : public BaseQuestion{
	Operators operatorValue;
	char operatorLabel;
	int operand1, operand2, result;
	int *variable;
	bool isFinished;
	virtual void initQuestion(int level);
public:
	Question(int level);
	virtual bool validate(int value);
	virtual bool isDone()const;
	virtual string toString()const;
};


#endif