//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ComplexQuestion.h
// -------------
// This class represent a complex question in the math game.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 22/04/15	      Ori Riner				  Creation
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef __COMPLEX_QUESTION_H__
#define __COMPLEX_QUESTION_H__

#include <stdlib.h>
#include <string>
#include "BaseQuestion.h"
using namespace std;

class ComplexQuestion : public BaseQuestion{
	enum Operands{
		first,
		second,
		third,
		answer
	};

	Operators operatorValue1, operatorValue2;
	char operatorLabel1, operatorLabel2;
	int operand1, operand2, operand3, result;
	Operands variable1, variable2;
	bool isAfterFirstAnswer, isFinished;
	int calculate(Operators action, int operand1, int operand2, bool inverse = false);
	int calculateFromAnswer(Operators action, int operand1, int operand2);
	bool isNotAllowed(Operators action, int operand1, int operand2);
	bool isNotAllowedFromAnswer(Operators action, int operand1, int operand2);
	virtual void initQuestion(int level);
public:
	ComplexQuestion();
	virtual bool validate(int value);
	virtual bool isDone()const;
	virtual string toString()const;
};


#endif