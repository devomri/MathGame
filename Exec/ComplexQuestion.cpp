//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ComplexQuestion.cpp
// -------------
// This class represent a complex question in the math game.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 28/04/15	      Ori Riner				  Creation
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "ComplexQuestion.h"
#include <algorithm>
#include <sstream>

ComplexQuestion::ComplexQuestion(){
	initQuestion(0);
}

void ComplexQuestion::initQuestion(int level){
	isAfterFirstAnswer = false;
	isFinished = false;
	operatorValue1 = static_cast<Operators>(rand() % 4);
	operatorValue2 = static_cast<Operators>(rand() % 4);
	
	operatorLabel1 = operatorValue1 == PLUS ? '+' : operatorValue1 == MULTIPLY ? '*' : operatorValue1 == MINUS ? '-' : '/';
	operatorLabel2 = operatorValue2 == PLUS ? '+' : operatorValue2 == MULTIPLY ? '*' : operatorValue2 == MINUS ? '-' : '/';
	
	int random1 = (rand() % 21) + 1;
	int random2 = (rand() % 21) + 1;
	int random3 = (rand() % 21) + 1;
	
	if (operatorValue2 % 2 == 1 && operatorValue1 % 2 == 0){
		// inverse order
		operand3 = (operatorValue2 < 2) ? random2 : random1;
		operand2 = (operatorValue2 < 2) ? random1 : random1 * random2;
		int temp = (operatorValue2 < 2) ? random1 * random2 : random2;
		operand1 = (operatorValue1 < 2) ? random3 : temp + random3;
		result = (operatorValue1 >= 2) ? random3 : temp + random3;

	}
	else{
		// regular order
		if (operatorValue2 >= 2 && operatorValue1 >=2){
			operand2 = random1;
			operand3 = random2;
			result = random3;
			int temp = operatorValue2 == MINUS ? result + operand3 : result * operand3;
			operand1 = operatorValue1 == MINUS ? temp + operand2 : temp * operand2;
		}
		else{
			int temp;
			if (operatorValue2 < 2){
				operand1 = (operatorValue1 < 2) ? random1 : (operatorValue1 == MINUS) ? random1 + random2 : random1 * random2;
				operand2 = (operatorValue1 < 2) ? random2 : random1;
				temp = (operatorValue1 >= 2) ? random2 : (operatorValue1 == PLUS) ? random1 + random2 : random1 * random2;
				operand3 = random3;
				result = calculate(operatorValue2, temp, random3);
			}
			else{
				operand3 = random3;
				temp = random2;
				operand2 = calculate(operatorValue2, operand3, temp, true);
				operand1 = random1;
				result = calculate(operatorValue1, operand1, temp);
			}
		}
	}

	int* operands = new int[4]{operand1, operand2, operand3, result};
	sort(operands, operands + 4);
	variable1 = (operands[0] == operand1) ? first : (operands[0] == operand2) ? second : (operands[0] == operand3) ? third : answer;
	variable2 = (operands[1] == result) ? answer : (operands[1] == operand3) ? third : (operands[1] == operand2) ? second : first;
	
	// if by any chance the variables are reversed.
	if (variable2 < variable1){
		Operands temp = variable1;
		variable1 = variable2;
		variable2 = temp;
	}
}

bool ComplexQuestion::validate(int value){
	Operands variable = isAfterFirstAnswer ? variable2 : variable1;
	int* actualValue = variable == first ? &operand1 : variable == second ? &operand2 : variable == third ? &operand3 : &result;
	
	// exact value for variable is good.
	if (value == *actualValue){
		if (isAfterFirstAnswer){
			isFinished = true;
		}
		else{
			isAfterFirstAnswer = true;
		}
		return true;
	}
	// if it's not the exact value and there is already a first answer so it's wrong.
	else if (isAfterFirstAnswer){
		return false;
	}
	// it's not an exact value but there are still two variables.
	else{
		int* firstVariable = variable1 == first ? &operand1 : variable1 == second ? &operand2 : &operand3;
		int* secondVariable = variable2 == second ? &operand2 : variable2 == third ? &operand3 : &result;
		int temp, optionalSecondVariableValue;
		bool isNotValid;
		if (operatorValue2 % 2 == 1 && operatorValue1 % 2 == 0){
			//Inverse order.
			if (variable1 == second && variable2 == third){
				temp = calculateFromAnswer(operatorValue1, operand1, result);
				isNotValid = isNotAllowedFromAnswer(operatorValue1, operand1, result) || isNotAllowedFromAnswer(operatorValue2, value, temp);
				optionalSecondVariableValue = calculateFromAnswer(operatorValue2, value, temp);;
			}
			else if (variable1 == first && variable2 == second){
				temp = calculateFromAnswer(operatorValue1, operand1, result);
				isNotValid = isNotAllowedFromAnswer(operatorValue1, operand1, result) || isNotAllowedFromAnswer(operatorValue2, operand3, temp);
				optionalSecondVariableValue = calculateFromAnswer(operatorValue2, operand3, temp);
			}
			else if (variable1 == first && variable2 == third){
				temp = calculateFromAnswer(operatorValue1, value, result);
				isNotValid = isNotAllowedFromAnswer(operatorValue1, value, result) || isNotAllowedFromAnswer(operatorValue2, operand2, temp);
				optionalSecondVariableValue = calculateFromAnswer(operatorValue2, operand2, temp);
			}
			else if (variable1 == first && variable2 == answer){
				temp = calculate(operatorValue2, operand2, operand3);
				isNotValid = isNotAllowed(operatorValue1, value, temp);
				optionalSecondVariableValue = calculate(operatorValue1, value, temp);
			}
			else if (variable1 == second && variable2 == answer){
				temp = calculate(operatorValue2, value, operand3);
				isNotValid = isNotAllowed(operatorValue2, value, operand3) || isNotAllowed(operatorValue1, operand1, temp);
				optionalSecondVariableValue = calculate(operatorValue1, operand1, temp);
			}
			else if (variable1 == third && variable2 == answer){
				temp = calculate(operatorValue2, operand2, value);
				isNotValid = isNotAllowed(operatorValue2, operand2, value) || isNotAllowed(operatorValue1, operand1, temp);
				optionalSecondVariableValue = calculate(operatorValue1, operand1, temp);
			}
		}
		else{
			// Regular order.
			if (variable1 == first && variable2 == second){
				temp = calculate(operatorValue2, result, operand3, true);
				isNotValid = isNotAllowedFromAnswer(operatorValue1, value, temp);
				optionalSecondVariableValue = calculateFromAnswer(operatorValue1, value, temp);
			}
			else if (variable1 == first && variable2 == third){
				temp = calculate(operatorValue1, value, operand2);
				isNotValid = isNotAllowed(operatorValue1, value, operand2) || isNotAllowedFromAnswer(operatorValue2, temp, result);
				optionalSecondVariableValue = calculateFromAnswer(operatorValue2, temp, result);
			}
			else if (variable1 == first && variable2 == answer){
				temp = calculate(operatorValue2, value, operand2);
				isNotValid = isNotAllowed(operatorValue1, value, operand2) || isNotAllowed(operatorValue2, temp, operand3);
				optionalSecondVariableValue = calculate(operatorValue2, temp, operand3);
			}
			else if (variable1 == second && variable2 == third){
				temp = calculate(operatorValue1, operand1, value);
				isNotValid = isNotAllowed(operatorValue1, operand1, value) || isNotAllowedFromAnswer(operatorValue2, temp, result);
				optionalSecondVariableValue = calculateFromAnswer(operatorValue2, temp, result);
			}
			else if (variable1 == second && variable2 == answer){
				temp = calculate(operatorValue1, operand1, value);
				isNotValid = isNotAllowed(operatorValue1, operand1, value) || isNotAllowed(operatorValue2, temp, operand3);
				optionalSecondVariableValue = calculate(operatorValue2, temp, operand3);
			}
			else if (variable1 == third && variable2 == answer){
				temp = calculate(operatorValue1, operand1, operand2);
				isNotValid = isNotAllowed(operatorValue2, temp, value);
				optionalSecondVariableValue = calculate(operatorValue2, temp, value);
			}
		}

		if (isNotValid || optionalSecondVariableValue > 21 || optionalSecondVariableValue < 1){
			return false;
		}
		else{
			*firstVariable = value;
			*secondVariable = optionalSecondVariableValue;
			isAfterFirstAnswer = true;
			return true;
		}
	}
}

bool ComplexQuestion::isDone()const{
	return isFinished;
}

int ComplexQuestion::calculate(Operators action, int operand1, int operand2, bool inverse){
	action = inverse ? (Operators)((action + 2) % 4) : action;
	return action == MULTIPLY ? operand1 * operand2 : action == DIVIDE ? operand1 / operand2 : action == PLUS ? operand1 + operand2 : operand1 - operand2;
}

int ComplexQuestion::calculateFromAnswer(Operators action, int operand1, int answer){
	return action == MULTIPLY ? answer / operand1 : action == DIVIDE ? operand1 / answer : action == PLUS ? answer - operand1 : operand1 - answer;
}

bool ComplexQuestion::isNotAllowed(Operators action, int operand1, int operand2){
	return (action == DIVIDE && operand1 % operand2 != 0) || (action == MINUS && operand1 - operand2 <= 0);
}

bool ComplexQuestion::isNotAllowedFromAnswer(Operators action, int operand1, int answer){
	return isNotAllowed(action, operand1, answer) || isNotAllowed((Operators) ((action + 2) % 4), answer, operand1);
}

string ComplexQuestion::toString()const{
	stringstream firststream;
	stringstream secondstream;
	stringstream thirdstream;
	stringstream resultstream;
	firststream << operand1;
	secondstream << operand2;
	thirdstream  << operand3;
	resultstream << result;
	string firststring = ((variable1 == first && !isAfterFirstAnswer) || variable2 == first) ? "__" : firststream.str();
	string secondstring = ((variable1 == second && !isAfterFirstAnswer) || variable2 == second) ? "__" : secondstream.str();
	string thirdstring = ((variable1 == third && !isAfterFirstAnswer) || variable2 == third) ? "__" : thirdstream.str();
	string resultstring = ((variable1 == answer && !isAfterFirstAnswer) || variable2 == answer) ? "=__" : "=" + resultstream.str();
	return firststring + operatorLabel1 + secondstring + operatorLabel2 + thirdstring + resultstring;
}