//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// BaseQuestion.h
// -------------
// This interface represent the base api for any question in the math game.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 04/05/15	      Ori Riner				  Creation
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef __BASE_QUESTION_H__
#define __BASE_QUESTION_H__

#include <stdlib.h>
#include <string>

using namespace std;

class BaseQuestion{
	
public:
	enum Operators{
		PLUS,
		MULTIPLY,
		MINUS,
		DIVIDE
	};
	virtual void initQuestion(int level) = 0;
	virtual bool validate(int value) = 0;
	virtual string toString() const = 0;
	virtual bool isDone() const = 0;
};


#endif