//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MathPlayer.cpp
// -------------
// This class represent a player in the math game.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 23/03/15	      Omri Avrahami			  Creation
// 26/03/15		  Ori Riner				  Moved the direction property from the class to a parameter to the move.
// 29/03/15		  Omri Avrahami			  Added last direction of the player
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "MathPlayer.h"
#include "Position.h"
#include "Direction.h"
#include "Question.h"
#include "ComplexQuestion.h"

string MathPlayer::getLifeString()const{
	string life = "<3 ";
	string result = "";
	for (int i = 0; i < lifeAmount; i++){
		result += life;
	}
	result.resize(8);
	return result;
}

void MathPlayer::reset(){
	decreaseLifeAmount();
	setPosition(lifeAmount != 0 ? startingPosition : Position(0,0));
	setLastDirection(lastDirection == Direction::STAY ? previousDirection : lastDirection);
}

bool MathPlayer::isPremanent(){
	return true;
}

void MathPlayer::init(int level){
	lifeAmount = 3;
	winningStatus = false;
	shotsAmount = 5;
	setPosition(startingPosition);
	setLastDirection(startingDirection);

	// Clearing the previous question.
	delete currentQuestion;
	if (level <= 20){
		currentQuestion = new Question(level);
	}
	else{
		currentQuestion= new ComplexQuestion();
	}
}

MathPlayer::~MathPlayer(){
	delete currentQuestion;
}

string MathPlayer::getShotsString() const{
	string shot = "* ";
	string result = "";
	for (int i = 0; i < shotsAmount; i++){
		result += shot;
	}
	result.resize(9);
	return result;
}

void MathPlayer::decreaseLifeAmount() { 
	this->lifeAmount--;

	if (this->lifeAmount == 0){
		this->shotsAmount = 0;
	}
}